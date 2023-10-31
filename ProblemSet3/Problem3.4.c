/* Include Library */
#include <stdio.h>

/* Define structure */
typedef struct MIDINote {
 int pitch;
 int velocity;
 int channel;
} MIDINote;

/* Function printing details of structure MIDINote */
void print_note(MIDINote note){
    printf("The MIDI note has pitch %i, velocity %i, and channel %i.\n", note.pitch, note.velocity, note.channel);
}

int main(){
    MIDINote note;  // call the structure MIDINote

    // Make a user input the MIDINote details
    printf("Type a pitch of MIDINote: ");
    scanf("%i", &note.pitch);

    printf("Type a velocity of MIDINote: ");
    scanf("%i", &note.velocity);

    printf("Type a channel of MIDINote: ");
    scanf("%i", &note.channel);

    // Call the function printing the structure MIDINote having details the user typed
    print_note(note);
}