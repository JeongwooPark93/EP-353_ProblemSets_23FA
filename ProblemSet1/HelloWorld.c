/* This file is a simple C program to display "Hello, World!"
on the screen and say "Hello, World" through speaker.
Since, it's a very simple program,
it is often used to illustrate the syntax of a programming language.

To compile and run this program type:
clang HelloWorld.c -o HelloWorld && ./HelloWorld
*/

// A preprocessor commands that tells compiler to
// include the contents of the stdio.h file.
#include <stdio.h>

// A function named "main." Every C program begins with the main() function.
//"main"is where the program starts when executed.
int main()
{
  printf("Hello, World!\n"); // Print Hello World to the terminal window
}
