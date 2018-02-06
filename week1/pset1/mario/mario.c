#include <stdio.h>
#include <cs50.h>

/*
Specification
- Write, in a file called mario.c in your ~/workspace/pset1/mario/more/ directory, a program that recreates these half-pyramids using hashes (#) for blocks.
- To make things more interesting, first prompt the user for the half-pyramids' heights, a non-negative integer no greater than 23. (The height of the half-pyramids pictured above happens to be 4, the width of each half-pyramid 4, with an a gap of size 2 separating them.)
- If the user fails to provide a non-negative integer no greater than 23, you should re-prompt for the same again.
- Then, generate (with the help of printf and one or more loops) the desired half-pyramids.
- Take care to left-align the bottom-left corner of the left-hand half-pyramid with the left-hand edge of your terminal window.

Usage
Your program should behave per the example below. Assumed that the underlined text is what some user has typed.

$ ./mario
Height: 4
   #  #
  ##  ##
 ###  ###
####  ####

$ ./mario
Height: 0

$ ./mario
Height: -5
Height: 4
   #  #
  ##  ##
 ###  ###
####  ####

$ ./mario
Height: -5
Height: five
Height: 40
Height: 24
Height: 4
   #  #
  ##  ##
 ###  ###
####  ####
*/

int main(void) {
	int userinput = 0;

	do {
		userinput = get_int("Height: ");
	} while (userinput < 0 || userinput > 23);

	for (int i = 1; i <= userinput; i++) {
		//left side
		int space = userinput - i;// i is the current row
		int hash = userinput - space;
		for (int j = 0; j < space; j++) {
			printf(" ");
		}
		for (int k = 0; k < hash; k++) {
			printf("#");
		}
		printf("  ");//2 spaces
		//right side
		for (int l = 0; l < hash; l++) {
			printf("#");
		}
		printf("\n");
	}
}
