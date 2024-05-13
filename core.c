

// Uses the time.h library to obtain current year information
// Get the current 4-digit year from the system
#define _CRT_SECURE_NO_WARNINGS

#include <time.h>
#include <stdio.h>
#include <string.h>
#include "core.h"


int inputInt() {
	char returnChar = '0';
	int number;
	do {
		scanf("%d%c", &number, &returnChar);
		if (returnChar == '\n')
			return number;
		else {
			clearInputBuffer();
			printf("Error! Input a whole number: ");
		}
	} while (returnChar != '\n');

	return number;
}
int inputIntPositive() {

	int number = 0;
	do {
		number = inputInt();
		if (number > 0)
			return number;
		else {
			printf("ERROR! Value must be > 0: ");
		}
	} while (number <= 0);
	return number;
}



int inputIntRange(int lowerBound, int upperBound) {

	int number;
	do {
		number = inputInt();
		if (number >= lowerBound && number <= upperBound)
			return number;
		else {
			printf("ERROR! Value must be between %d and %d inclusive: ", lowerBound, upperBound);
		}
	} while (number <= lowerBound || number >= upperBound);
	return number;
}

char inputCharOption(const char* string) {//"abcd"
	char character;
	char returnChar = 0;
	int hasChar = 0;
	int i;

	do {
		scanf("%c%c", &character, &returnChar); //b
		if (returnChar == '\n') {
			for (i=0; string[i] != '\0'; i++)
			{
				if (character == string[i])
					hasChar++;
			}

		}
		else {
			clearInputBuffer();

		}
		if (hasChar == 0) {
			printf("ERROR: Character must be one of [%s]: ", string);
		}
		else {
			return character;
		}


	} while (hasChar == 0);
	return character;
}

void inputCString(char* string, int lowerBounds, int upperBounds) {
	char word[30] = { 0 };
	int i, stringLength, isInvalid;
	char returnChar = 0;

	do {
		isInvalid = 0;
		scanf("%[^\n]%c", word, &returnChar);

		if (returnChar == '\n')
		{
			for (stringLength = 0; word[stringLength] != '\0'; stringLength++)
			{
				//abc //stringLength=4
			}
			if (lowerBounds == upperBounds && stringLength != lowerBounds) {
				printf("ERROR: String length must be exactly %d chars: ", lowerBounds);
				isInvalid++;
			}
			else if (stringLength > upperBounds) {
				printf("ERROR: String length must be no more than %d chars: ", upperBounds);
				isInvalid++;
			}
			else if (stringLength < lowerBounds || stringLength > upperBounds) {
				printf("ERROR: String length must be between %d and %d chars: ", lowerBounds, upperBounds);
				isInvalid++;
			}


			else {

				for (i = 0; word[i] != '\0'; i++)
					string[i] = word[i];
				string[i] = 0;
			}

		}
		else {
			isInvalid++;
			//clearStandardInputBuffer();
		}
	} while (isInvalid > 0);

}

void clearInputBuffer(void) {
	// Discard all remaining char's from the standard input buffer:
	while (getchar() != '\n') {
		; // do nothing! 
	}
}
void suspend(void) {
	printf("<ENTER> to continue...");
	clearInputBuffer();
	putchar('\n');
}
void displayFormattedPhone(const char* string) {
	int error = 0;
	if (string == NULL || strcmp(string, "") == 0 || strlen(string) != 10) {
		error = 1;
		printf("(___)___-____");
		return;

	}
	int i;
	for (i = 0; i < strlen(string); i++) {
		if (string[i] < 48 || string[i] > 57) {
			error = 1;
		}
	}
	if (error > 0) {
		printf("(___)___-____");
	}
	else
		printf("(%c%c%c)%c%c%c-%c%c%c%c", string[0]
			, string[1]
			, string[2]
			, string[3]
			, string[4]
			, string[5]
			, string[6]
			, string[7]
			, string[8]
			, string[9]);


}