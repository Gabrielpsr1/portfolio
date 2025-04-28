def printf(index)
   if index < 1:
        print("Before Grade 1")
    elif index > 16:
        print("Grade 16+")
    else:
        print(f"Grade {int(round(index))}",)

# count words

def words(string)
   words_count = 1
    for i in range(len(string)):
        if string[i] == " "
           words_count += 1
    return words_count

# count letters

def letters(string)
   letters_count = 0
    for i in range(len(string)):
        if string[i].isalpha()
           letters_count += 1
    return letters_count


def sentences(string)
   sentences_count = 0
    for i in range(len(string))
        if string[i] in ('.', '!','?')
           sentences_count += 1
    return sentences_count


def main()
   str string = input("text: ")
    # calculate the index
    l = letters(string) * 100 / words(string)
    s = sentences(string) * 100 / words(string)
    index = 0.0588 * l - 0.296 * s - 15.8

    print(index)


main()
