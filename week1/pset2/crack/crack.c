#include <stdio.h>
#include <cs50.h>
#include <ctype.h>

#define _XOPEN_SOURCE
#include <unistd.h>
#include <crypt.h>

/*
Specification
Design and implement a program, crack, that cracks passwords:
- Implement your program in a file called crack.c in a directory called crack.
- Your program should accept a single command-line argument: a hashed password.
- If your program is executed without any command-line arguments or with more than one command-line argument, your program should print an error (of your choice) and exit immediately, with main returning 1 (thereby signifying an error).
- Otherwise, your program must proceed to crack the given password, ideally as quickly as possible, ultimately printing the password in the clear followed by \n, nothing more, nothing less, with main returning 0.
- Assume that each password has been hashed with C’s DES-based (not MD5-based) crypt function.
- Assume that each password is no longer than five (5) characters. Gasp!
- Assume that each password is composed entirely of alphabetical characters (uppercase and/or lowercase).

Usage
Your program should behave per the examples below. Assumed that the underlined text is what some user has typed:

$ ./crack
Usage: ./crack hash

$ ./crack 50JGnXUgaafgc
ROFL

Other user hashes to test:
anushree:50xcIMJ0y.RXo
brian:50mjprEcqC/ts
bjbrown:50GApilQSG3E2
lloyd:50n0AAUD.pL8g
malan:50CcfIk1QrPr6
maria:509nVI8B9VfuA
natmelo:50JIIyhDORqMU
rob:50JGnXUgaafgc
stelios:51u8F0dkeDSbY
zamyla:50cI2vYkF0YU2
*/

bool checkGuess(string w, string g) {
	int j = 0;
	while (w[j] != '\0') {
		if (g[j] == w[j]) {
			j++;
		} else {
			return false;
		}
	}
	return true;
}

int main (int argc, char **argv) {
	if (argc > 2 || argc < 2) {
		printf("Usage: ./crack 50l5IR0THCAN6\n");
	} else {
		string word = argv[1];//crypt("hello", "50") is 50l5IR0THCAN6
		char guess[6];
		int a, b, c, d, e;
		bool second_loop = false, third_loop = false, fourth_loop = false, fifth_loop = false;

		while (!checkGuess(word, crypt(guess, "50"))) {
			a = 65;
			while (!checkGuess(word, crypt(guess, "50")) && a < 123) {
				if (isalpha((char) a)) {
					guess[0] = (char) a;
				}
				b = 65;
				while (!checkGuess(word, crypt(guess, "50")) && b < 123 && second_loop) {//enter 2nd loop
					if (isalpha((char) b)) {
						guess[1] = (char) b;
					}
					c = 65;
					while (!checkGuess(word, crypt(guess, "50")) && c < 123 && third_loop) {//enter 3rd loop
						if (isalpha((char) c)) {
							guess[2] = (char) c;
						}
						d = 65;
						while (!checkGuess(word, crypt(guess, "50")) && d < 123 && fourth_loop) {//enter 4th loop
							if (isalpha((char) d)) {
								guess[3] = (char) d;
							}
							e = 65;
							while (!checkGuess(word, crypt(guess, "50")) && e < 123 && fifth_loop) {//enter 4th loop
								if (isalpha((char) e)) {
									guess[4] = (char) e;
								}
								e++;
							}
							d++;
						}
						c++;
					}
					b++;
				}
				a++;
			}
			second_loop = (a > 122) ? true : false;//can now go to 2nd loop
			third_loop = (b > 122) ? true : false;//can now go to 3rd loop
			fourth_loop = (c > 122) ? true : false;//can now go to 4th loop
			fifth_loop = (d > 122) ? true : false;//can now go to 4th loop
		}

		printf("%s\n", guess);
		return 0;
	}
}
