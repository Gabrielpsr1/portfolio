from cs50 import get_int


card = get_int("Card number: ")


def valid(cardnumber):
    lenght = len(str(cardnumber))
    count = 0
    if lenght not in (13, 15, 16):
        return False
    for i in range(lenght - 1, 0, 2):
        if i * 2 > 9:
            count += (i*2)/10 + (i*2) % 10
        else:
            count += i*2

    for i in range(lenght, 0, 2):
        count += i

    if count % 10 == 0:
        return True
    else:
        return False


def flag(cardnumber):
    # amer
    if str(cardnumber)[:2] in ("34", "37"):
        return "AMEX"
    elif 51 <= int(str(cardnumber)[:2]) >= 55:
        return "MASTERCARD"
    elif 40 <= int(str(cardnumber)[:2]) >= 49:
        return "VISA"


if valid(card):
    print(f"{flag(card)}")
else:
    print("INVALID")
