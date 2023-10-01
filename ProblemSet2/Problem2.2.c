#include <stdio.h>
#include <math.h>

double freq(int p);

int main() {
    int C4, A4;

    C4 = 60;
    A4 = 69;

    printf("The frequency for MIDI pitch %i (C4) is %f Hz.\n", C4, freq(C4));
    printf("The frequency for MIDI pitch %i (A4) is %f Hz.\n", A4, freq(A4));

}

    double freq(int p) {
        double f = pow(2, ((p-69)/12.0)) * 440;
        return f;
    }