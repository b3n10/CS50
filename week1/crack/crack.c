#include <stdio.h>
#include <cs50.h>
#include <string.h>

#define _GNU_SOURCE
#include <crypt.h>

#include <ctype.h>

int main(int argc, string argv[]) {
	string guess = malloc(5);

	guess[0] = 'b';

	printf("%s\n", crypt(guess, "50"));
	printf("%s\n", crypt("b", "50"));

	return 0;
}
//	if (argc < 2) {
//		printf("Error: Need at least 1 argument.\n");
//	} else if (argc > 2) {
//		printf("Error: Need only 1 argument.\n");
//	} else {
//		string hp = argv[1];
//		string a = crypt("a", "50");
//	}
/*
 * Design and implement a program, crack, that cracks passwords.
 * Implement your program in a file called crack.c in a directory called crack.
 * Your program should accept a single command-line argument: a hashed password.
 * If your program is executed without any command-line arguments or with more than one command-line argument, your program should print an error (of your choice) and exit immediately, with main returning 1 (thereby signifying an error).
 * Otherwise, your program must proceed to crack the given password, ideally as quickly as possible, ultimately printing the password in the clear followed by \n, nothing more, nothing less, with main returning 0.
 * Assume that each password has been hashed with Câs DES-based (not MD5-based) crypt function.
 * Assume that each password is no longer than five (5) characters. Gasp!
 * Assume that each password is composed entirely of alphabetical characters (uppercase and/or lowercase).
 */
