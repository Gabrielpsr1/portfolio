while(True):
    text = input("Height: ")
    if text.isdigit():
        height = int(text)
        if 1 <= height and 8>= height:
            break

for i in range(1, height + 1, 1):
    print(" " * (height - i), end="")
    print("#" * i, end="")
    print("  ", end="")
    print("#" * i, end="")
    print()
