import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from datetime import datetime

from helpers import apology, login_required, lookup, usd, make_stock_list

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute("SELECT stock,shares FROM stocks WHERE user_id=?", int(session["user_id"]))

    stock_list = []
    name_list = []

    make_stock_list(stock_list, name_list, stocks)

    return render_template("index.html", stocks=stock_list)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        shares = int(request.form.get("shares"))
        if !(isinstance(shares, int) and n > 0)
            return apology("pls, input an positive integer")

        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("invalid symbol.")

        cash = int(db.execute("SELECT cash FROM users WHERE id = ? ",
                   int(session["user_id"]))[0]["cash"])

        transaction_type = "BUY"

        if int(stock["price"]) * shares < cash:
            db.execute("UPDATE users SET cash = cash - ? WHERE id = ?",
                       int(stock["price"]) * shares, session["user_id"])
            db.execute("INSERT INTO history(id,stock,shares,time,type) VALUES (?,?,?,?,?)",
                       session["user_id"], stock["symbol"], shares, datetime.now(), transaction_type)
            if not db.execute("SELECT * FROM stocks WHERE user_id = ? AND stock = ?", session["user_id"], stock["symbol"]):
                # no row, insert a new one
                db.execute("INSERT INTO stocks(user_id, stock, shares) VALUES (?, ?, ?)",
                           session["user_id"], stock["symbol"], shares)
            else:
                db.execute("UPDATE stocks SET shares = shares + ? WHERE user_id = ? AND stock = ?",
                           shares, session["user_id"], stock["symbol"])
        else:
            return apology("you don't have enough cash")
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute("SELECT * FROM history WHERE id = ?", session["user_id"])

    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("invalid symbol.",200)
        return render_template("quoted.html", stock=stock)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password") or request.form.get("password") != request.form.get("confirmation"):
            return apology("must provide and confirm your password", 400)

        try:
            db.execute("INSERT INTO users (username,hash) VALUES (?,?)", request.form.get("username"),
                       generate_password_hash(request.form.get("password"), method='scrypt', salt_length=16))
        except:
            return apology("This username is alredy being used", 400)

        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )
        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        try:
            shares = int(request.form.get("shares"))
            if shares < 0:
                return apology("pls, input an positive integer")
        except ValueError:
            return apology("pls,input a valid value")

        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("invalid symbol.")

        n_shares = db.execute("SELECT shares FROM stocks WHERE user_id = ? AND stock = ?", int(
            session["user_id"]), stock["symbol"].upper())
        if not n_shares:
            return apology("you don't have these stocks.")

        cash = int(n_shares[0]["shares"]) * stock["price"]

        transaction_type = "SELL"

        if int(n_shares[0]["shares"]) < shares:
            return apology("you don't have enough stocks.")
        elif int(n_shares[0]["shares"]) == shares:
            db.execute("DELETE FROM stocks WHERE user_id = ? AND stock = ? ",
                       session["user_id"], stock["symbol"])
            db.execute("INSERT INTO history(id,stock,shares,time,type) VALUES (?,?,?,?,?)",
                       session["user_id"], stock["symbol"], shares, datetime.now(), transaction_type)
            db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", cash, session["user_id"])
        else:
            db.execute("UPDATE stocks SET shares = shares - ? WHERE user_id = ? AND stock = ?",
                       shares, session["user_id"], stock["symbol"])
            db.execute("INSERT INTO history(id,stock,shares,time,type) VALUES (?,?,?,?,?)",
                       session["user_id"], stock["symbol"], shares, datetime.now(), transaction_type)
            db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", cash, session["user_id"])
        return redirect("/")
    else:
        return render_template("sell.html")


@app.route("/transfer", methods=["GET", "POST"])
@login_required
def transfer():
    if request.method == "POST":
        person = request.form.get("person")
        cash = float(request.form.get("cash"))

        # current cash
        c_cash = float(db.execute("SELECT cash FROM users WHERE id = ?",
                       session["user_id"])[0]["cash"])

        if (cash > c_cash):
            return apology("you don't have enough cash")

        if db.execute("SELECT username FROM users WHERE username = ?", person):
            db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", cash, session["user_id"])
            db.execute("UPDATE users SET cash = cash + ? WHERE username = ?", cash, person)
            db.execute("INSERT INTO history(id,stock,shares,time,type) VALUES (?,?,?,?,?)",
                       session["user_id"], "Transfer", cash, datetime.now(), "TRANSFER")
        else:
            return apology("invalid name")
        return redirect("/")
    else:
        return render_template("transfer.html")
