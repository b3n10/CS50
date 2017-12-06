#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[]) {
	if (argc < 2) {
		printf("Error. Please pass 1 argument.\n");
		return 1;
	} else if (argc > 2) {
		printf("Error. Please pass only 1 argument.\n");
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
