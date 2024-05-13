/*
*****************************************************************************
						Assignment 1 - Milestone 2
Full Name  : Alireza Abbasi
Student ID#: 153388210
Email      : aabbasi35@myseneca.ca
Section    : ZDD
Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
*****************************************************************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <ctype.h>
// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
	printf("Pat.# Name            Phone#\n"
		"----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
	if (fmt == FMT_FORM)
	{
		printf("Name  : %s\n"
			"Number: %05d\n"
			"Phone : ", patient->name, patient->patientNumber);
		displayFormattedPhone(patient->phone.number);
		printf(" (%s)\n", patient->phone.description);
	}
	else
	{
		printf("%05d %-15s ", patient->patientNumber,
			patient->name);
		displayFormattedPhone(patient->phone.number);
		printf(" (%s)\n", patient->phone.description);
	}
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
	int selection;

	do {
		printf("Veterinary Clinic System\n"
			"=========================\n"
			"1) PATIENT     Management\n"
			"2) APPOINTMENT Management\n"
			"-------------------------\n"
			"0) Exit System\n"
			"-------------------------\n"
			"Selection: ");
		selection = inputIntRange(0, 2);
		putchar('\n');
		switch (selection)
		{
		case 0:
			printf("Are you sure you want to exit? (y|n): ");
			selection = !(inputCharOption("yn") == 'y');
			putchar('\n');
			if (!selection)
			{
				printf("Exiting system... Goodbye.\n\n");
			}
			break;
		case 1:
			menuPatient(data->patients, data->maxPatient);
			break;
		case 2:
			printf("<<< Feature not yet available >>>\n\n");
			break;
		}
	} while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
	int selection;

	do {
		printf("Patient Management\n"
			"=========================\n"
			"1) VIEW   Patient Data\n"
			"2) SEARCH Patients\n"
			"3) ADD    Patient\n"
			"4) EDIT   Patient\n"
			"5) REMOVE Patient\n"
			"-------------------------\n"
			"0) Previous menu\n"
			"-------------------------\n"
			"Selection: ");
		selection = inputIntRange(0, 5);
		putchar('\n');
		switch (selection)
		{
		case 1:
			displayAllPatients(patient, max, FMT_TABLE);
			suspend();
			break;
		case 2:
			searchPatientData(patient, max);
			break;
		case 3:
			addPatient(patient, max);
			suspend();
			break;
		case 4:
			editPatient(patient, max);
			break;
		case 5:
			removePatient(patient, max);
			suspend();
			break;
		}
	} while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
	int selection;

	do {
		printf("Edit Patient (%05d)\n"
			"=========================\n"
			"1) NAME : %s\n"
			"2) PHONE: ", patient->patientNumber, patient->name);

		displayFormattedPhone(patient->phone.number);

		printf("\n"
			"-------------------------\n"
			"0) Previous menu\n"
			"-------------------------\n"
			"Selection: ");
		selection = inputIntRange(0, 2);
		putchar('\n');

		if (selection == 1)
		{
			printf("Name  : ");
			inputCString(patient->name, 1, NAME_LEN);
			putchar('\n');
			printf("Patient record updated!\n\n");
		}
		else if (selection == 2)
		{
			//printf("\n");
			inputPhoneData(&patient->phone);
			printf("Patient record updated!\n\n");
		}

	} while (selection);
}


// ---------------------------------------------------------------------------
// !!! Put all the remaining function definitions below !!!
// Note: Maintain the same order/sequence as it is listed in the header file
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void displayAllPatients(const struct Patient patient[], int max, int fmt) {
	int i;

	displayPatientTableHeader();

	for (i = 0; i < max; i++)
	{
		if (patient[i].patientNumber > 0)
			displayPatientData(&patient[i], fmt);
	}
	printf("\n");
}



// Search for a patient record based on patient number or phone number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientData(const struct Patient patient[], int max) {
	int option;
	do {

		printf("Search Options"
			"\n=========================="
			"\n1) By patient number"
			"\n2) By phone number"
			"\n..........................\n"
			"0) Previous menu"
			"\n..........................\n"
			"Selection: ");
		option = inputIntRange(0, 2);
		putchar('\n');
		switch (option)
		{
		case 1:
			searchPatientByPatientNumber(patient, max);
			suspend();
			break;
		case 2:
			searchPatientByPhoneNumber(patient, max);
			suspend();
			break;
		}
	} while (option);


}


// Add a new patient record to the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void addPatient(struct Patient patient[], int max) {
	int canCreate = 0;
	int i;
	for (i = 0; i < max && canCreate == 0; i++)
	{
		if (patient[i].patientNumber == 0)
		{
			canCreate = 1;

		}
		else { canCreate = 0; }
	}

	if (canCreate == 0)
		printf("ERROR: Patient listing is FULL!\n\n");
	else {
		struct Patient structPatient = { 0 };
		structPatient.patientNumber = nextPatientNumber(patient, max);
		inputPatient(&structPatient);
		patient[i] = structPatient;

		printf("*** New patient record added ***");
		printf("\n\n");
	}


}


// Edit a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void editPatient(struct Patient patient[], int max) {
	int number, index;
	printf("Enter the patient number: ");
	number = inputIntPositive();
	index = findPatientIndexByPatientNum(number, patient, max);
	printf("\n");
	if (index > 0) {
		menuPatientEdit(&patient[index]);
	}
	else {
		printf("ERROR: Patient record not found!");
	}

}


// Remove a patient record from the patient array
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void removePatient(struct Patient patient[], int max) {
	int patientNumber, confirmationDelete;
	printf("Enter the patient number: ");
	patientNumber = inputIntPositive();
	int result = findPatientIndexByPatientNum(patientNumber, patient, max);
	if (result > 0) {
		printf("\n");
		displayPatientData(&patient[result], FMT_FORM);

		printf("\nAre you sure you want to remove this patient record? (y/n): ");
		confirmationDelete = inputCharOption("yYnN");
		if (confirmationDelete == 'Y' || confirmationDelete == 'y') {
			patient[result].patientNumber = 0;
			printf("Patient record has been removed!\n");
		}
		else {
			printf("Operation aborted.\n");
		}
	}
	else {
		printf("\n");
		printf("ERROR: Patient record not found!\n");

	}
	printf("\n");


}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPatientNumber(const struct Patient patient[], int max) {
	int patientNumber;
	printf("Search by patient number: ");
	patientNumber = inputIntPositive();
	int result = findPatientIndexByPatientNum(patientNumber, patient, max);


	if (result == -1)
	{
		printf("\n");
		printf("*** No records found ***\n");
		printf("\n");
	}
	else {
		printf("\n");
		displayPatientData(&patient[result], FMT_FORM);
		printf("\n");

	}


}

// Search and display patient records by phone number (tabular)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void searchPatientByPhoneNumber(const struct Patient patient[], int max) {
	char phone[PHONE_LEN];
	int hasData = 0, i;
	printf("Search by phone number: ");
	inputCString(phone, 1, PHONE_LEN);
	printf("\n");
	displayPatientTableHeader();
	for (i = 0; i < max && hasData == 0; i++)
	{
		if (strcmp(patient[i].phone.number, phone) == 0)
		{
			displayPatientData(&patient[i], FMT_TABLE);
			hasData = 1;
		}
		else
			hasData = 0;

	}
	printf("\n");

	if (hasData == 0) {
		printf("\n");
		printf("*** No records found ***\n");
		printf("\n");

	}

}

// Get the next highest patient number
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int nextPatientNumber(const struct Patient patient[], int max) {
	int i;
	int large = patient[0].patientNumber;
	for (i = 0; i < max; i++)
	{
		if (patient[i].patientNumber > large)
			large = patient[i].patientNumber;
	}
	large++;
	return large;
}

// Find the patient array index by patient number (returns -1 if not found)
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
int findPatientIndexByPatientNum(int patientNumber,
	const struct Patient patient[], int max) {
	int index = -1, i;
	for (i = 0; i < max; i++)
	{
		if (patientNumber == patient[i].patientNumber)
			index = i;
	}
	return index;
}


//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPatient(struct Patient* patient) {

	printf("Patient Data Input");
	printf("\n------------------");
	printf("\nNumber: 0%d", patient->patientNumber);
	printf("\nName  : ");
	inputCString(patient->name, 1, NAME_LEN);
	printf("\n");
	struct Phone phone = { { 0 } };
	inputPhoneData(&phone);
	(*patient).phone = phone;
}

// Get user input for phone contact information
// (ToDo: PUT THE FUNCTION DEFINITION BELOW)
void inputPhoneData(struct Phone* phone) {
	int option;
	do {
		printf("Phone Information");
		printf("\n-----------------");
		printf("\nHow will the patient like to be contacted?");
		printf("\n1. Cell");
		printf("\n2. Home");
		printf("\n3. Work");
		printf("\n4. TBD");
		printf("Selection: ");


		option = inputIntRange(1, 4);
		putchar('\n');
		switch (option)
		{
		case 1:
			strcpy((*phone).description, "CELL");
			break;
		case 2:
			strcpy((*phone).description, "HOME");
			break;
		case 3:
			strcpy((*phone).description, "WORK");
			break;

		case 4:
			strcpy((*phone).description, "TBD");
			strcpy((*phone).number, "");
			break;
		}
		printf("Contact: %s", (*phone).description);
		printf("\nNumber : ");
		inputCString((*phone).number, 1, PHONE_LEN);
		printf("\n");
		break;

	} while (option);
}
