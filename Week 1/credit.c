#include <stdio.h>
#include <cs50.h>


int two(long numb) {
    int other_two = numb % 10;
    other_two = other_two * 2;
    int temp10 = other_two / 10;
    other_two = other_two % 10 + temp10;
    return other_two;
}

int one(long numb) {
    int other_one = numb % 10;
    return other_one;
}

long snip(long v) {
    v = v - (v % 10);
            v = v/10;
            return v;
}



//Main function

int main(void) {

    long visa = 0;
    bool check = true;

    do {
    visa = get_long("Please enter a credit card number\n");
    if (visa >= 0 && visa <= 9999999999999999) {

        check = false;}

    } while (check == true);

    long visa_u = visa;
    int sum = 0;
    int digits = 0;

    //Check for digits and change digits variable

    if (visa >= 1000000000000000 && visa <= 9999999999999999) {
        digits = 16;
    }
    else if (visa >= 1000000000000 && visa <= 9999999999999)  {
        digits = 13;
    }
    else if (visa >= 100000000000000 && visa <= 999999999999999) {
        digits = 15;
    }
    else {
        digits = 1;
    }

    //Luhn's algorithm

    for (int i = 1; i <= digits; i++) {
        if (i % 2 == 1) {
            sum = sum + one(visa);
            visa = snip(visa);
        }
        else if (i % 2 == 0) {
            sum = sum + two(visa);
            visa = snip(visa);
        }
    }

    if (sum % 10 == 0) {
        if (digits == 15 && (visa_u / 10000000000000 == 34 || visa_u / 10000000000000 == 37)) {
            printf("AMEX\n");
        }
        else if (digits == 13) {
            printf("VISA\n");
        }
        else if ((digits == 16) && ((visa_u / 100000000000000) >= 51 && (visa_u / 100000000000000) <= 55)) {
            printf("MASTERCARD\n");
        }
        else if (digits == 16 && visa_u / 1000000000000000 == 4) {
            printf("VISA\n");
        }
        else {
            int debug = visa_u / 100000000000000;
            printf("INVALID\n");
        }
    }
    else {
        printf("INVALID\n");
    }




}
