/* Include Library */
#include <stdio.h>
#include <math.h>

/* Define function */
float midi_to_frequency(int midiNote);

int main(){
    // Recieve the midiNote the User types
    int midiNote;
    printf("Type a midi Note: ");
    scanf("%i", &midiNote);
    
    // Calculate the frequency through the function
    int frequency=midi_to_frequency(midiNote);

    // Result Print-out
    printf("The frequency of MIDI note %i is %.2f Hz.\n", midiNote, frequency); 
}

/* Function calculating frequency of midiNote the User typed */
float midi_to_frequency(int midiNote){
    return 440.0 * pow(2.0, (midiNote - 69) / 12.0);
}