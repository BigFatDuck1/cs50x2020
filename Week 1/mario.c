#include <cs50.h>
#include <stdio.h>

int main(void) {
    
    int pheight = 0;
    
    do {
        pheight = get_int("Height:\n");
    } while (pheight < 1 || pheight > 8);
    
    int i = 1;
    int p = pheight;
    
    printf("\n");

    for (i = 1; i <= p; i++) {
        
        int j;
        
        for (j = 1; j <= p - i; j++) { //Numer of spaces
            printf(" ");
        }
        
        int k = 1;
        
        for (k = 1; k <= i; k++) { //hash
            printf("#");
        }
        
        printf("  ");
        
        int l = 1;
        
        for (l = 1; l <= i; l++) { //hash 2
            printf("#");
        }
        
        printf("\n");

        
    }
    
    
}

