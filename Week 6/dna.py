import csv
from cs50 import get_string
from sys import argv

#argv[1] : .csv
#argv[2] : .txt

#Seqence of DNA as a string
file = open(argv[2],"r")
dna_sequence = file.read()
file.close()

#Create dictionary with everyone
#Create dictionary with just the STR we need to check
#Turn the given file into a dictionary
#Check whether the given file dictionary is in the mega dictionary

with open(argv[1],"r") as database:
    database_read = csv.reader(database)
    #List with the STR we need to check
    for row in database_read:
        str_check = row
        break
    str_check.remove("name")


with open(argv[1],"r") as database:
    database_dictread = csv.DictReader(database)
    #List with everyone
    everyone = []
    for row in database_dictread:
        everyone.append(row)

#Check for each STR
txt_dict = {}
for str_string in str_check:

    #How many short tandem repeats
    str_max = 0
    txt_dict[str_string] = str_max

    #Get the length of the current STR that is used to check the given sequence
    #e.g. 'AGATC' returns length 5
    current_check_length = len(str_string)
    i_end = len(dna_sequence) - current_check_length

    for i in range(i_end):
        if dna_sequence[i:i+current_check_length] == str_string:
            #Temporary variable to store the current max, if it is larger than str_max then replace it
            temp_max = 0
            j = i
            while dna_sequence[j:j+current_check_length] == str_string:
                temp_max += 1
                j += current_check_length
            if temp_max > str_max:
                str_max = temp_max

    txt_dict[str_string] = str_max




#everyone is an list of all the people and STR, as a key:value pair
#str_check is a list with all the STRs that we are checking for
#txt_dict is a dictionary with the "STR sequence":"number of repeats" of the DNA sample we're given

name = "No match"
howmanystr = len(str_check)

for people in everyone:
    x = 0
    for sequence in str_check:
        if str(txt_dict[sequence]) != people[sequence]:
            break
        x += 1
        if x == howmanystr:
            name = people["name"]

print(name)
print(txt_dict)






