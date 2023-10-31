/* Include Library */
#include <stdio.h>

/* Define structure */
typedef struct MIDINote {
 int pitch;
 int velocity;
 int channel;
} MIDINote;

/* Function transposing a pitch of each note in notes array */
void transpose_notes(MIDINote* notes, int size, int steps){
    for(int i=0; i<size; i++){
        notes[i].pitch+= steps;
    }
}

int main(){
    // scan a midi notes array size the user enters
    int size;
    printf("Enter the size of MIDI notes: ");
    scanf("%i", &size);

    // Make notes array structured MIDINote and get details from the user.
    MIDINote notes[size];
    for(int j=0; j<size; j++){
        printf("Enter pitch, velocity and channel of MIDI note%i: ", j+1);
        scanf("%i %i %i", &notes[j].pitch, &notes[j].velocity, &notes[j].channel);
    }

    // scan steps to transpose pitches of every notes in notes array
    int steps;
    printf("Enter the steps(0~11) to transpose the pitch: ");
    scanf("%i", &steps);

    // call function to transpose every pitches
    transpose_notes(notes, size, steps);

    // print details of every notes in notes array structured MIDINote
    for(int k=0; k<size; k++){
        printf("The MIDI note has pitch %i, velocity %i, and channel %i.\n", notes[k].pitch, notes[k].velocity, notes[k].channel);
    }
}