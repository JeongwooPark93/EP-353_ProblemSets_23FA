#include <stdio.h>

char* noteName(int x);

int main(){
    int pitch;

    printf("Type your MIDI pitch: \n");
    scanf("%i", &pitch);

    if(pitch >= 0 && pitch < 128){
        int octave = pitch/12 -1;
        printf("The MIDI pitch %i is %s%i.\n", pitch, noteName(pitch), octave);
      
    }else {
    printf("Invalid MIDI pitch. It should be between 0 and 127.\n");
    }
}

char* noteName(int x) {
    int y = x % 12;
    switch(y) {

        case 0 :
           return "C";

        case 1 :
            return "C#";

        case 2 :
            return "D";
        
        case 3 :
            return "D#";

        case 4 :
            return "E";
        
        case 5 :
            return "F";

        case 6 :
            return "F#";

        case 7 :
            return "G";
        
        case 8 :
            return "G#";

        case 9 :
            return "A";
        
        case 10 :
            return "A#";
        
        case 11 :
            return "B";
    }
    return " ";
}