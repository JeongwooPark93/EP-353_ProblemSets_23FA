#include <stdio.h>

int note1, note2;
char* IntervalName(int i);

int main() {
    
    for (note1 = 0; note1 < 12; note1++){
        for(note2 = 0; note2 < 12; note2++) {
                int interval = (note2-note1+12) % 12;
                if(interval >= 0) {
                    printf("The interval from note %i to note %i is a %s.\n", note1, note2, IntervalName(interval));
                } else {
                    printf("There is an error: Negative value of interval\n");
                    break;
                }
        }
        printf("\n");
    }
}

char* IntervalName(int i) {
    switch (i)
    {
    case 0:
        return "unison";
    
    case 1:
        return "minor second";

    case 2:
        return "major second";

    case 3:
        return "minor third";

    case 4:
        return "major third";

    case 5:
        return "perfect fourth";

    case 6:
        return "tritone";

    case 7:
        return "perfect fifth";

    case 8:
        return "minor sixth";

    case 9:
        return "major sixth";

    case 10:
        return "minor seventh";

    case 11:
        return "major seventh";
    }
    return " ";
}