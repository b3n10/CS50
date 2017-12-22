#include <stdio.h>
#include <cs50.h>
#include <string.h>

#define _GNU_SOURCE
#include <crypt.h>

#define _XOPEN_SOURCE       /* See feature_test_macros(7) */
#include <unistd.h>

#include <ctype.h>

bool check_hash(string hash1, string hash2) {
	int xhash = 0;
	bool bhash = false;
	while (xhash < strlen(hash1)) {
		if (hash1[xhash] == hash2[xhash]) {
			bhash = !true;
		} else {
			return true;
		}
		xhash++;
	}
	return bhash;
}

int main(int argc, string argv[]) {
	string guess = malloc(5);
	string hashpword = "50LvszlBYAscE";//old 50FMwyUJKQbNg
	string hashguess = "";

	for (int i = 0; i < 5; i++) {
		//starts from A which is 65, ends in 122
		int count = 65;
		while (check_hash(hashpword, hashguess) && count < 123) {
			if (isalpha((char) count)) {
				guess[i] = (char) count; 
			}
			hashguess = crypt(guess, "50");
			count++;
		}
	}

	printf("Guess: %s\n", guess);
	string new_crypt = "zAzzA";
	printf("%s %s\n", new_crypt, crypt("zAzzA", "50"));
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
