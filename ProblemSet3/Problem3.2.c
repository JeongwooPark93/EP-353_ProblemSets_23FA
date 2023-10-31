/* Include Library */
#include <stdio.h>
#include <math.h>

/* Define functions */
float midi_to_frequency(int midiNote);
void print_chord_frequencies(int chord[], int size);

int main(){
    // Check the amount of notes the User wants to type for chord.
    int size;
    printf("How many notes do you want to input? ");
    scanf("%i", &size);

    // If the size is same or under 0, the program will be stopped.
    if(size<=0){
        printf("This is invalid number.\n");
        return 0;
    } else {
        int chord[size];
        printf("Type the MIDI notes of the chord: ");

        // The User can type as much as he typed for size above.
        for(int i=0; i<size; i++){
           scanf("%i,", &chord[i]);
        }

        // Call the function calling calculation function and printing one by one.
        print_chord_frequencies(chord, size);
        return 0;
    }
}

/* Function calculating frequency of midiNote given */
float midi_to_frequency(int midiNote){
    return 440.0 * pow(2.0, (midiNote - 69) / 12.0);
}

/* Call the calculate function and print one by one. */
void print_chord_frequencies(int chord[], int size){
    for(int j=0; j<size; j++){
        int frequency=midi_to_frequency(chord[j]);
        printf("The frequency of MIDI note %i is %.2f Hz.\n", chord[j], frequency);
    }
}