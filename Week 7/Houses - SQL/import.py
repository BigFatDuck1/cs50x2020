# TODO
import csv
import cs50
from sys import argv
from sys import exit

if len(argv) != 2:
    print("Error." + str(len(argv)))
    exit(3)

db = cs50.SQL("sqlite:///students.db")

with open(argv[-1], "r") as characters:

    reader = csv.DictReader(characters)

    for row in reader:

        house = row["house"]
        birth = row["birth"]

        temp_name = row["name"].split()

        if len(temp_name) == 3:
            first = temp_name[0]
            middle = temp_name[1]
            last = temp_name[2]
        elif len(temp_name) == 2:
            first = temp_name[0]
            last = temp_name[1]
            middle = None



        # Insert show by substituting values into each ? placeholder
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                   first, middle, last, house, birth)




