/*
    Program Overview_

        1. Program Title: Program2.c
        2. Purpose of Pragram: The purpose of this code is to create a simple program that allows a user 
                               to select a musical scale mode (Ionian, Dorian, or Phrygian) 
                               and a root note within a specified range. 
                               The program then prints the seven pitches in the selected scale based on the chosen root note.
        3. How to Run: 
            a. Struct and Enum Definitions: The program begins with the definition of two structs (Note and Scale) 
                                            and an enum (Mode). These define the structures for musical notes, scales, 
                                            and different scale modes.
            b. Function Prototype: The function prototype for void printScale(const Scale *scale); is declared. 
                                   This informs the compiler about the structure of the function 
                                   before its actual implementation.
            c. Main Function: 
                - main() function starts execution.
                - Three scale instances (ionian, dorian, phrygian) are initialized with predefined pitches, velocities, 
                  channels, and a root note.
                - The user is prompted to enter a scale mode (0 for Ionian, 1 for Dorian, 2 for Phrygian).
            d. Scale Selection: A switch statement is used to select the appropriate scale based on the user's input. 
                                The selected scale is stored in the selectedScale variable.
            e. Root Note Input: The user is prompted to enter a root note within the range of 0 to 127. 
                                This root note is stored in selectedScale.rootNote.
            f. Printing the Scale: The program prints the seven pitches in the selected scale with the provided root note 
                                   by calling the printScale function.
            g. printScale Function: The printScale function iterates through the notes in the selected scale, 
                                    calculates the pitch based on the root note, and prints each pitch.
            h. End of Program: The main() function returns 0, indicating successful execution, and the program terminates.
*/

#include <stdio.h>

// Enum defining the scale modes
typedef enum Mode {
    Ionian, Dorian, Phrygian
} Mode;

// Struct representing a musical note
typedef struct Note {
    unsigned char pitch;
    unsigned char velocity;
    unsigned char channel;
} Note;

// Struct representing a musical scale
typedef struct Scale {
    Note notes[7];
    unsigned char rootNote;
} Scale;

// Function prototypes
void printScale(const Scale *scale);

int main() {
    // Declaration and initialization of scale modes
    Scale ionian = {{
        {0, 127, 1},
        {2, 127, 1},
        {4, 127, 1},
        {5, 127, 1},
        {7, 127, 1},
        {9, 127, 1},
        {11, 127, 1}},
        60};

    Scale dorian = {{
        {0, 127, 1},
        {2, 127, 1},
        {3, 127, 1},
        {5, 127, 1},
        {7, 127, 1},
        {9, 127, 1},
        {10, 127, 1}},
        60};

    Scale phrygian = {{
        {0, 127, 1},
        {1, 127, 1},
        {3, 127, 1},
        {5, 127, 1},
        {7, 127, 1},
        {8, 127, 1},
        {10, 127, 1}},
        60};

    // User input for scale mode selection
    int selectedMode;
    printf("Enter the scale mode (0 for Ionian, 1 for Dorian, 2 for Phrygian): ");
    scanf("%i", &selectedMode);

    Scale selectedScale;

    // Switch statement to select the appropriate scale based on user input
    switch (selectedMode) {
        case Ionian:
            selectedScale = ionian;
            break;
        case Dorian:
            selectedScale = dorian;
            break;
        case Phrygian:
            selectedScale = phrygian;
            break;
        default:
            printf("Invalid mode selection\n");
            return 1; // Exit with an error code
    }

    // User input for root note selection
    printf("Enter the root note (0 ~ 127): ");
    scanf("%hhu", &selectedScale.rootNote);

    // Printing the notes in the selected scale with the provided root note
    printf("Notes: ");
    printScale(&selectedScale);

    return 0;
}

// Function to print the seven pitches in the selected Scale variable
void printScale(const Scale *scale) {
    for (int i = 0; i < 7; i++) {
        printf("%i ", (scale->notes[i].pitch + scale->rootNote) % 128);
    }
    printf("\n");
}