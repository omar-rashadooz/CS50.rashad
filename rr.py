while True:
    h = int(input("Enter the height(0=quit): "))
    l = 1
    
    for i in range (h):
        for i in range (l):
            print ("#" , end="")
        print()    
        l =l+1
    if h == 0:
        break