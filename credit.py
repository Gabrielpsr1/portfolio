from cs50 import get_int


card = get_int("Card number: ")


def valid(cardnumber):
    cardstr = str(card)
    lenght = len(cardstr)
    count = 0
    if lenght not in (13, 15, 16):
        return False
    for i in range(lenght - 1, 0, 2):
        if i * 2 > 9:
            count += (i*2)/10 + (i*2) % 10
        else:
            count += i*2

    for i in range(lenght, 0,2):
       count += i

    if count % 10 == 0:
       return True
    else:
       return False


def flag(cardnumber):
   #amer
   if cardnumber / 10**13 in (34,37):
      return "AMEX"
   elif cardnumber / 10**14 in range(51,55,1):
      return "MASTERCARD"
   else:
      return "VISA"


if valid(card):
   print(f"{flag(card)}")
else:
   print("INVALID")

