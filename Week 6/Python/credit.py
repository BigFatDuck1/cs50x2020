from cs50 import get_int

def visa_check(number):
    length = len(str(number))
    print(length)
    """for i in str(number):
        if type(i) != int:
            return False"""
    if length != 15 or length != 16 or length != 13:
        return False
    else:
        return True

#Get input
visa = get_int("Please enter a credit card number.\n")


length = len(str(visa))
visa_array = [int(i) for i in str(visa)]


#Luhn's algorithm

def luhn(number):
    #1. Create array with all digits
    digits_array =  []
    digits_array = [int(i) for i in str(number)]

    #2. Multiply every other digit by two
    for i in range(len(digits_array)):
        if length % 2 == 1:
            if i % 2 == 1:
                #Odd
                digits_array[i] *= 2
                #Add up the two digits together
                if digits_array[i] >= 10:
                    oneplace = digits_array[i] % 10
                    tenplace = digits_array[i] // 10
                    digits_array[i] = oneplace + tenplace
            if i % 2 == 0:
                #Even
                pass
        elif length % 2 == 0:
            if i % 2 == 0:
                #Even
                digits_array[i] *= 2
                #Add up the two digits together
                if digits_array[i] >= 10:
                    oneplace = digits_array[i] % 10
                    tenplace = digits_array[i] // 10
                    digits_array[i] = oneplace + tenplace
            if i % 2 == 1:
                #Odd
                pass

    #4. Sum of all values
    total = sum(digits_array)
    #print(total)
    #5. Return final digit
    final_digit = total % 10

    #print(final_digit)

    if final_digit == 0:
        return True
        #It is a credit card
    if final_digit != 0:
        return False
        #Not legit credit card


if luhn(visa) == False:
    print("INVALID\n")
elif luhn(visa) == True:
    if length == 15:
        print("AMEX\n")
    elif length == 16 and visa_array[0] == 5:
        print("MASTERCARD\n")
    elif length == 13 or length == 16:
        if visa_array[0] == 4:
            print("VISA\n")




