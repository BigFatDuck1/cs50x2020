# TODO
import csv
import cs50
from sys import argv, exit


if len(argv) != 2:
    print("Error.")
    exit(3)

db = cs50.SQL("sqlite:///students.db")
rows = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last, first", argv[-1])

for row in rows:
    if row["middle"] == None:
        print(row["first"] + " " + row["last"] + ", born " + str(row["birth"]))
    else:
        print(row["first"] + " " + row["middle"] + " " + row["last"] + ", born " + str(row["birth"]))