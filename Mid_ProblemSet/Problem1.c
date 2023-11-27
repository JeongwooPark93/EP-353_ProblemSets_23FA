/*
    Program Overview_

        1. Program Title: Program1.c
        2. Purpose of Pragram: The program serves as a simple matrix generator, 
                               allowing users to input dimensions for a matrix and then displaying the matrix on the console. 
                               The values in the matrix are calculated based on the sum of row and column indices, 
                               creating a pattern within the matrix. The purpose is to illustrate basic input/output operations, 
                               function usage, and simple mathematical calculations in C programming.
        3. How to Run: 
            a. Function Prototype: This line declares the prototype of the printMatrix function, which is defined later in the code. 
                                   It tells the compiler about the function's signature before its actual implementation.
            b. Main Function: The main function is the entry point of the program. 
                              It prompts the user to enter the width and height of the matrix, 
                              calls the printMatrix function, and then returns 0 to indicate successful execution.
            c. User Input: These lines prompt the user to enter the width and height of the matrix, 
                           and the values are stored in the variables width and height respectively.
            d. Function Call: This line calls the printMatrix function, passing the user-entered width and height as arguments.
            e. 'printMatrix' Function: This function takes the width and height of the matrix as parameters 
                                       and prints a matrix of numbers based on the specified rules.
            f. Matrix Generation: The value for each position in the matrix is calculated based on the sum of the row index 
                                  (i) and column index (j). The result is then taken modulo height and incremented by 1.
            g. Printing the Matrix: The code prints the calculated value for each position in the matrix. 
                                    If the value is less than height, it is printed as is; otherwise, 
                                    the value is printed modulo height.
            h. Newline Character: After printing each row of the matrix, a newline character is printed to move to the next line.

            The resulting matrix is displayed on the console based on the user-provided width and height.
*/

#include <stdio.h>

// Function prototype
void printMatrix(int width, int height);

int main() {
    int width, height;

    // Ask the user for width and height
    printf("Enter the width: ");
    scanf("%i", &width);
    printf("Enter the height: ");
    scanf("%i", &height);

    // Call the printMatrix function
    printMatrix(width, height);

    return 0;
}

// Function to print the number matrix
void printMatrix(int width, int height) {
    int i, j;

    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            // Calculate the value based on the position
            int value = (i + j) % height + 1;
            
            // Print the value
            if(value < height){
                printf("%i", value);
            } else{
                printf("%i", value % height);
            }
        }
        printf("\n");
    }
}
