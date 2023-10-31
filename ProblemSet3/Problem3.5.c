/* Include Library */
#include <stdio.h>

/* Define structure */
typedef struct MIDINote {
 int pitch;
 int velocity;
 int channel;
} MIDINote;

/* Function printing details of structure MIDINote note array */
void print_notes(MIDINote notes[], int size){
    for(int k=0; k<size; k++){
        printf("The MIDI note has pitch %i, velocity %i, and channel %i.\n", notes[k].pitch, notes[k].velocity, notes[k].channel);
    }
}

int main(){
    // scan a midi notes array size the user enters
    int size;
    printf("Enter the size of MIDI notes: ");
    scanf("%i", &size);

    // Make notes array structured MIDINote and get details from the user.
    MIDINote notes[size];
    for(int i=0; i<size; i++){
        printf("Enter pitch, velocity and channel of MIDI note%i: ", i+1);
        scanf("%i %i %i", &notes[i].pitch, &notes[i].velocity, &notes[i].channel);
    }

    // Call the function printing details of structure MIDINote note array
    print_notes(notes, size);
}