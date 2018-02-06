#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
Specification
Design and implement a program, caesar, that encrypts messages using Caesar’s cipher:
- Implement your program in a file called caesar.c in a directory called caesar.
- Your program must accept a single command-line argument, a non-negative integer. Let’s call it k for the sake of discussion.
- If your program is executed without any command-line arguments or with more than one command-line argument, your program should print an error message of your choice (with printf) and return from main a value of 1 (which tends to signify an error) immediately.
- You can assume that, if a user does provide a command-line argument, it will be a non-negative integer (e.g., 1). No need to check that it’s indeed numeric.
- Do not assume that k will be less than or equal to 26. Your program should work for all non-negative integral values of k less than 231 - 26. In other words, you don’t need to worry if your program eventually breaks if the user chooses a value for k that’s too big or almost too big to fit in an int. (Recall that an int can overflow.) But, even if k is greater than 26, alphabetical characters in your program’s input should remain alphabetical characters in your program’s output. For instance, if k is 27, A should not become [ even though [ is 27 positions away from A in ASCII, per asciichart.com; A should become B, since B is 27 positions away from A, provided you wrap around from Z to A.
- Your program must output plaintext: (without a newline) and then prompt the user for a string of plaintext (using get_string).
- Your program must output ciphertext: (without a newline) followed by the plaintext’s corresponding ciphertext, with each alphabetical character in the plaintext "rotated" by k positions; non-alphabetical characters should be outputted unchanged.
- Your program must preserve case: capitalized letters, though rotated, must remain capitalized letters; lowercase letters, though rotated, must remain lowercase letters.
- After outputting ciphertext, you should print a newline. Your program should then exit by returning 0 from main.

Usage
Your program should behave per the examples below. Assumed that the underlined text is what some user has typed.

$ ./caesar 1
plaintext:  HELLO
ciphertext: IFMMP

$ ./caesar 13
plaintext:  hello, world
ciphertext: uryyb, jbeyq

$ ./caesar 13
plaintext:  be sure to drink your Ovaltine
ciphertext: or fher gb qevax lbhe Binygvar

$ ./caesar
Usage: ./caesar k

$ ./caesar 1 2 3 4 5
Usage: ./caesar k
*/

int main(int argc, string argv[]) {
	if (argc > 2 || argc < 2) {
		printf("Usage: ./caesar k\n");
		return 1;
	} else {
		int k = atoi(argv[1]);
		string s = get_string("plaintext: ");
		printf("ciphertext: ");

		for (int i = 0, n = strlen(s); i < n; i++) {
			if (isalpha(s[i])) {
				if (isupper(s[i])) {
					printf("%c", 65 + ((s[i] - 65) + k) % 26);
				} else {
					printf("%c", 97 + ((s[i] - 97) + k) % 26);
				}
			} else {
				printf("%c", s[i]);
			}
		}

		printf("\n");
		return 0;
	}
}
