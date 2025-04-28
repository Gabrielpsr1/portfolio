from cs50 import get_int


card = get_int("Card number: ")


def valid(cardnumber):
    lenght = len(str(cardnumber))
    count = 0
    if lenght not in (13, 15, 16):
        return False
    for i in range(lenght - 2, -1, -2):
        if int(str(cardnumber)[i])*2 > 9:
            count += int(str(cardnumber)[i])*2 - 9
        else:
            count += int(str(cardnumber)[i])*2

    for i in range(lenght - 1, -1, -2):
        count += int(str(cardnumber)[i])

    if count % 10 == 0:
        return True
    else:
        return False


def flag(cardnumber):
    # amer
    if str(cardnumber)[:2] in ("34", "37"):
        return "AMEX"
    elif 51 <= int(str(cardnumber)[:2]) <= 55:
        return "MASTERCARD"
    elif str(cardnumber)[:1] == "4" and len(str(cardnumber)) in (13, 16):
        return "VISA"
    else:
        return "INVALID"


if valid(card):
    print(f"{flag(card)}")
if valid(card) == False:
    print("INVALID")
