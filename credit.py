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
    elif str(cardnumber)[:2] in ("51", "52","53","54","55"):
        return "MASTERCARD"
    else:
        return "VISA"


if valid(card):
    print(f"{flag(card)}")
else:
    print("INVALID")
