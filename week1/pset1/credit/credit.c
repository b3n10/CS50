#include <stdio.h>
#include <cs50.h>

/*
Specification
- In credit.c in ~/workspace/pset1/credit/, write a program that prompts the user for a credit card number and then reports (via printf) whether it is a valid American Express, MasterCard, or Visa card number, per the definitions of each’s format herein.
- So that we can automate some tests of your code, we ask that your program’s last line of output be AMEX\n or MASTERCARD\n or VISA\n or INVALID\n, nothing more, nothing less, and that main always return 0.
- For simplicity, you may assume that the user’s input will be entirely numeric (i.e., devoid of hyphens, as might be printed on an actual card).
- Do not assume that the user’s input will fit in an int! Best to use get_long_long from CS50’s library to get users' input. (Why?)

Usage
Your program should behave per the example below. Assumed that the underlined text is what some user has typed.

$ ./credit
Number: 378282246310005
AMEX

$ ./credit
Number: 3782-822-463-10005
Number: foo
Number: 378282246310005
AMEX

$ ./credit
Number: 6176292929
INVALID
*/

int main() {
	long ccnumber = get_long_long("Number: ");

	long x = 10, y = 1;
	int i = 0, cc1 = 0, cc2 = 0, sum1 = 0, sum2 = 0;

	while (i < 8) {
		cc1 = (ccnumber / y) % 10;
		y = y * 100;
		cc2 = (ccnumber / x) % 10;
		x = x * 100;

		sum1 += cc1;

		if ((cc2 * 2) % 10 < (cc2 * 2)) {//if 2-digit number
			sum2 += ((cc2 * 2) / 10) % 10;//1st digit
			sum2 += (cc2 * 2) % 10;//2nd digit
		} else {
			sum2 += cc2 * 2;
		}

		i++;
	}

	long cc_count = ccnumber;
	string card_name;

	while (cc_count > 100) {
		cc_count = cc_count / 10;
	}

	if (cc_count == 37) {
		card_name = "AMEX";
	} else if (cc_count == 22 || cc_count == 55 || cc_count == 51) {
		card_name = "MASTERCARD";
	} else if (cc_count == 40 || cc_count == 41 || cc_count == 42) {
		card_name = "VISA";
	} else {
		card_name = "INVALID";
	}

	printf("%s\n", ((sum1+sum2) % 10 == 0) ? card_name : "INVALID");

	return 0;
}

/*
get second-to-last digit number: https://stackoverflow.com/a/28035647/6353682
get 1st & 2nd digit: https://stackoverflow.com/a/3118505/6353682
*/
