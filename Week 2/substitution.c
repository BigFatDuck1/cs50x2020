#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>



int main (int argc, string argv[] ) {

    if (argc != 2) { //Check for whether a key is attached, and only ONE key is attached
        printf("Usage: ./substitution KEY\n");
        return 1;
    }

    if (strlen(argv[1]) != 26) { //Check for 26 characters
        printf("KEY must contain only 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < 26; i++) { //Check for whether alpha characters
        if (isalpha(argv[1][i] == 0)) { //isalpha returns 0 if it is not an alpha character, nonzero if it is
            printf("KEY must only contain letters.\n");
            return 1;
        }
    }

    //Make a new array with the key to full uppercase
    char upper_key[26]; //Array with the full uppercase keys

    for (int i = 0; i < 26; i++) {
        upper_key[i] = toupper(argv[1][i]);
    }

    //Check for whether there are any repeats

    int ascii_sum = 0;

    for (int i = 0; i < 26; i++) { //Sum of all 26 uppercase alphabetical characters = 2015
        int ascii_upper = upper_key[i];
        ascii_sum += ascii_upper;
    }
    //printf("%i", ascii_sum);
    if (ascii_sum != 2015) {
        printf("The KEY cannot contain any repeated characters.\n"); //You can actually do away with isalpha() with this
        return 1;
    }

    else if (ascii_sum == 2015) {
        for (int i = 0; i < 26; i++) {
            for (int j = i+1; j < 26; j++) {
                if (upper_key[i] == upper_key[j]) {
                    printf("The KEY cannot contain any repeated characters.\n");
                    return 1;
                    break;
                }
            }
        }
    }

    /*-----IF ALL THE CHECKS ARE PASSED-----*/

    string plaintext = get_string("plaintext: ");

    //upper_key[] is an array with the KEY in UPPERCASE
    char lower_key[26]; //New array with KEY in LOWERCASE
    for (int i = 0; i < 26; i++) {
        lower_key[i] = tolower(upper_key[i]);
    }
    //lower_key[] is an array with the KEY in LOWERCASE

    //Convert each character to either UNCHANGED (ASCII: 0-64 || 91-96), UPPERCASE (65-90), LOWERCASE (97-122)
    //Since plaintext is an array use plaintext[i] and a for loop to iterate through every single character
    int pt_len = strlen(plaintext);
    char ciphertext[pt_len];

    //printf each an every single consecutive ciphertext character
    for (int i = 0; i < pt_len; i++) {
        if (plaintext[i] >= 0 && plaintext[i] <= 64) {
            ciphertext[i] = plaintext[i]; //UNCHANGED
        }
        else if (plaintext[i] >= 96 && plaintext[i] <= 91) {
            ciphertext[i] = plaintext[i]; //UNCHANGED
        }
        else if (plaintext[i] >= 65 && plaintext[i] <= 90) { //UPPERCASE
            plaintext[i] = plaintext[i] - 65; //A = 0, B = 1, C = 2...
            ciphertext[i] = upper_key[(int)plaintext[i]]; //returns corresponding UPPERCASE ciphertext character
        }
        else if (plaintext[i] >= 97 && plaintext[i] <= 122) { //LOWERCASE
            plaintext[i] = plaintext[i] - 97; //a = 0, b = 1, c = 2...
            ciphertext[i] = lower_key[(int)plaintext[i]]; //returns corresponding LOWERCASE ciphertext character
        }
    }

    printf("ciphertext: %s\n", ciphertext);

}