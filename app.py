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

    # pega ações do usuário
    rows = db.execute("SELECT stock, shares FROM stocks WHERE user_id = ?", session["user_id"])

    holdings = []
    total = 0

    for row in rows:
        quote = lookup(row["stock"])
        price = float(quote["price"])
        value = price * row["shares"]
        total += value
        holdings.append({
            "symbol": row["stock"],
            "shares": row["shares"],
            "price": usd(price),
            "total": usd(value)
        })

    # pega o cash atual
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    total += cash

    return render_template("index.html", holdings=holdings, cash=usd(cash), total=usd(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":

        # valida número de ações
        try:
            shares = int(request.form.get("shares"))
            if shares <= 0:
                return apology("please input a positive integer", 400)
        except:
            return apology("please input a positive integer", 400)

        # valida símbolo
        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("invalid symbol", 400)

        # pega dinheiro do usuário
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        price = float(stock["price"])
        total_cost = price * shares

        # verifica se tem dinheiro suficiente
        if total_cost > cash:
            return apology("you don't have enough cash", 400)

        # desconta o valor da compra
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_cost, session["user_id"])

        # salva no histórico (note que history precisa ter coluna price)
        db.execute("INSERT INTO history (id, stock, shares, price, time, type) VALUES (?, ?, ?, ?, ?, ?)",
                   session["user_id"], stock["symbol"], shares, price, datetime.now(), "BUY")

        # adiciona/atualiza ações do usuário
        rows = db.execute("SELECT shares FROM stocks WHERE user_id = ? AND stock = ?",
                          session["user_id"], stock["symbol"])

        if len(rows) == 0:
            db.execute("INSERT INTO stocks (user_id, stock, shares) VALUES (?, ?, ?)",
                       session["user_id"], stock["symbol"], shares)
        else:
            db.execute("UPDATE stocks SET shares = shares + ? WHERE user_id = ? AND stock = ?",
                       shares, session["user_id"], stock["symbol"])

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    history = db.execute("SELECT * FROM history WHERE id = ?", session["user_id"])

    return render_template("history.html", history=history, usd=usd)


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
            return apology("invalid symbol.", 400)
        return render_template("quoted.html", stock=stock, usd=usd)
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
            if shares <= 0:
                return apology("please input a positive integer")
        except:
            return apology("please input a valid value")

        stock = lookup(request.form.get("symbol"))
        if not stock:
            return apology("invalid symbol.")

        rows = db.execute("SELECT shares FROM stocks WHERE user_id = ? AND stock = ?",
                          session["user_id"], stock["symbol"].upper())
        if not rows:
            return apology("you don't own this stock.")

        owned_shares = rows[0]["shares"]
        if owned_shares < shares:
            return apology("you don't have enough shares.")

        price = float(stock["price"])
        proceeds = shares * price

        # atualiza carteira
        if owned_shares == shares:
            db.execute("DELETE FROM stocks WHERE user_id = ? AND stock = ?",
                       session["user_id"], stock["symbol"])
        else:
            db.execute("UPDATE stocks SET shares = shares - ? WHERE user_id = ? AND stock = ?",
                       shares, session["user_id"], stock["symbol"])

        # adiciona no histórico
        db.execute("INSERT INTO history (id, stock, shares, price, time, type) VALUES (?, ?, ?, ?, ?, ?)",
                   session["user_id"], stock["symbol"], shares, price, datetime.now(), "SELL")

        # atualiza saldo
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", proceeds, session["user_id"])

        return redirect("/")
    else:
        # passa as ações do user pro template do select
        symbols = db.execute("SELECT stock FROM stocks WHERE user_id = ?", session["user_id"])
        return render_template("sell.html", symbols=[row["stock"] for row in symbols])


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
