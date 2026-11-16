import csv

with open("log.csv" ,"r") as file:
    reade = csv.DictReader(file)
    less, more = 0, 0

    for row in reade:
        iter = row["iter"]
        if int(iter) > 300:
            less +=1
        elif int(iter) <= 300:
            more +=1

print("less is :",less)
print("more is :",more)