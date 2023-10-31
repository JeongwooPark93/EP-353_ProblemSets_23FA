/* Include Library */
#include <stdio.h>
#include <math.h>

/* Global function definition */
float midi_to_frequency(int midiNote);
void frequencies_of_chord(int* chord, int size, float* frequencies);

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
        // Define the chord and frequencies arrays with the given size
        int chord[size];
        float frequencies[size];

        // The User can type as much as he typed for size above.
        printf("Type the MIDI notes of the chord: ");
        for(int i=0; i<size; i++){
           scanf("%i,", &chord[i]);
        }

        // Call the function storing the frequecies into the array
        frequencies_of_chord(chord, size, frequencies);

        // Print each frequencies of the note in chord.
        for (int j=0; j<size; j++) {
            printf("The frequency of MIDI note %i is %.2f Hz. \n", chord[j], frequencies[j]);
        }
    }
}

/* Function calculating frequency of midiNote given */
float midi_to_frequency(int midiNote){
    return 440.0 * pow(2.0, (midiNote - 69) / 12.0);
}

/* Function calling frequency calculation function and storing in frequency array */
void frequencies_of_chord(int* chord, int size, float* frequencies) {
    for (int k = 0; k < size; k++) {
        frequencies[k] = midi_to_frequency(chord[k]);
    }
}