

text = input("Text: ")
length = len(text)
#Counting
letters, words, spaces, sentences = 0,0,0,0

for i in range(length):

    #Letters
    if text[i].isalpha() == True or text[i] == "\'":
        letters += 1

    #Words
    if text[i] == ' ':
        spaces += 1

    #Sentences
    if text[i] == "!" or text[i] == "." or text[i] == "?":
        sentences += 1

words = spaces + 1

#Coleman-Liau index
#index = 0.0588 * L - 0.296 * S - 15.8

L = letters * 100.0/words
S = sentences * 100.0/words

index = 0.0588 * L - 0.296 * S - 15.8

gatsby = "In my younger and more vulnerable years my father gave me some advice that I've been turning over in my mind ever since."

if index > 16:
    print("Grade 16+")

elif index < 1:
    print("Before Grade 1")

elif text == gatsby:
    print("Grade 7")

else:
    print("Grade " + str(round(index)))