#include <stdio.h>

int main(){
    int pitch;

    printf("Type your MIDI pitch: \n");
    scanf("%i", &pitch);

    if(pitch >= 0 && pitch < 128){
        int octave = pitch/12 -1;
        printf("The octave for MIDI pitch %i is %i.\n", pitch, octave);
    }else {
    printf("Invalid MIDI pitch. It should be between 0 and 127.\n");
    }
}