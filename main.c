#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <stdlib.h>
#endif

#define MAX_CONTACTS 100

struct Contact {
	char name[50];
	char phone[20];
	char email[50];
};

struct Contact contacts[MAX_CONTACTS];
int numContacts = 0;

void clearScreen();
void addContact();
void displayContacts();
void updateContact();
void deleteContact();
void saveContacts();
void loadContacts();

int main() {
	int choice;
	do {
		clearScreen();
		printf("Contact Management System\n");
		printf("1. Add new contact\n");
		printf("2. Display all contacts\n");
		printf("3. Update existing contact\n");
		printf("4. Delete contact\n");
		printf("5. Save contacts to file\n");
		printf("6. Load contacts from file\n");
		printf("7. Exit\n");
		printf("Enter your choice (1-7): ");
		if (scanf("%d", &choice) != 1) {
			printf("Invalid input. Please try again.\n");
			while (getchar() != '\n')
				; // clear input buffer
			continue;
		} else {
			clearScreen();
		}
		switch (choice) {
			case 1:
				addContact();
				break;
			case 2:
				displayContacts();
				break;
			case 3:
				updateContact();
				break;
			case 4:
				deleteContact();
				break;
			case 5:
				saveContacts();
				break;
			case 6:
				loadContacts();
				break;
			case 7:
				printf("Goodbye!\n");
				break;
			default:
				printf("Invalid choice. Please try again.\n");
				break;
		}
		getchar();
		getchar();

	} while (choice != 7);
	return 0;
}

void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	int ret = system("clear");
    if (ret == -1) {
        perror("system");
        exit(EXIT_FAILURE);
    }
#endif
}

void addContact() {
	if (numContacts == MAX_CONTACTS) {
		printf("Maximum number of contacts reached.\n");
		return;
	}
	struct Contact newContact;
	printf("Enter name: ");
	if (scanf("%49s", newContact.name) != 1) {
		printf("Invalid input. Please try again.\n");
		while (getchar() != '\n')
			; // clear input buffer
		return;
	}
	printf("Enter phone number: ");
	if (scanf("%19s", newContact.phone) != 1) {
		printf("Invalid input. Please try again.\n");
		while (getchar() != '\n')
			; // clear input buffer
		return;
	}
	printf("Enter email address: ");
	if (scanf("%49s", newContact.email) != 1) {
		printf("Invalid input. Please try again.\n");
		while (getchar() != '\n')
			; // clear input buffer
		return;
	}
	for (int i = 0; i < numContacts; i++) {
		if (strcmp(contacts[i].name, newContact.name) == 0 &&
		        strcmp(contacts[i].phone, newContact.phone) == 0 &&
		        strcmp(contacts[i].email, newContact.email) == 0) {
			printf("Contact with the same name, phone number, and email address already exists.\n");
			return;
		}
	}
	contacts[numContacts] = newContact;
	numContacts++;
	printf("Contact added successfully.\n");
}

void displayContacts() {
	if (numContacts == 0) {
		printf("No contacts found.\n");
		return;
	}
	printf("Name\tPhone\t\tEmail\n");
	for (int i = 0; i < numContacts; i++) {
		printf("%s\t%s\t%s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
	}
}

void updateContact() {
	if (numContacts == 0) {
		printf("No contacts found.\n");
		return;
	}
	char name[50];
	printf("Enter name of contact to update: ");
	if (scanf("%49s", name) != 1) {
		printf("Invalid input. Please try again.\n");
		while (getchar() != '\n')
			; // clear input buffer
		return;
	}
	int numMatches = 0;
	int matchIndexes[MAX_CONTACTS];
	for (int i = 0; i < numContacts; i++) {
		if (strcmp(contacts[i].name, name) == 0) {
			matchIndexes[numMatches] = i;
			numMatches++;
		}
	}
	if (numMatches == 0) {
		printf("No matching contacts found.\n");
		return;
	} else if (numMatches == 1) {
		struct Contact updatedContact;
		printf("Enter new phone number: ");
		if (scanf("%19s", updatedContact.phone) != 1) {
			printf("Invalid input. Please try again.\n");
			while (getchar() != '\n')
				; // clear input buffer
			return;
		}
		printf("Enter new email address: ");
		if (scanf("%49s", updatedContact.email) != 1) {
			printf("Invalid input. Please try again.\n");
			while (getchar() != '\n')
				; // clear input buffer
			return;
		}
		contacts[matchIndexes[0]] = updatedContact;
		printf("Contact updated successfully.\n");
	} else {
		printf("Multiple contacts found. Please choose one to update:\n");
		for (int i = 0; i < numMatches; i++) {
			printf("%d. %s\t%s\t%s\n", i + 1, contacts[matchIndexes[i]].name, contacts[matchIndexes[i]].phone, contacts[matchIndexes[i]].email);
		}
		int choice;
		if (scanf("%d", &choice) != 1 || choice < 1 || choice > numMatches) {
			printf("Invalid input. Please try again.\n");
			while (getchar() != '\n')
				; // clear input buffer
			return;
		}
		struct Contact updatedContact;
		printf("Enter new phone number: ");
		if (scanf("%19s", updatedContact.phone) != 1) {
			printf("Invalid input. Please try again.\n");
			while (getchar() != '\n')
				; // clear input buffer
			return;
		}
		printf("Enter new email address: ");
		if (scanf("%49s", updatedContact.email) != 1) {
			printf("Invalid input. Please try again.\n");
			while (getchar() != '\n')
				; // clear input buffer
			return;
		}
		contacts[matchIndexes[choice - 1]] = updatedContact;
		printf("Contact updated successfully.\n");
	}
}

void deleteContact() {
	if (numContacts == 0) {
		printf("No contacts found.\n");
		return;
	}
	char name[50];
	printf("Enter name of contact to delete: ");
	if (scanf("%49s", name) != 1) {
		printf("Invalid input. Please try again.\n");
		while (getchar() != '\n')
			; // clear input buffer
		return;
	}
	int numMatches = 0;
	int matchIndexes[MAX_CONTACTS];
	for (int i = 0; i < numContacts; i++) {
		if (strcmp(contacts[i].name, name) == 0) {
			matchIndexes[numMatches] = i;
			numMatches++;
		}
	}
	if (numMatches == 0) {
		printf("No matching contacts found.\n");
		return;
	} else if (numMatches == 1) {
		for (int i = matchIndexes[0]; i < numContacts - 1; i++) {
			contacts[i] = contacts[i + 1];
		}
		numContacts--;
		printf("Contact deleted successfully.\n");
	} else {
		printf("Multiple contacts found. Please choose one to delete:\n");
		for (int i = 0; i < numMatches; i++) {
			printf("%d. %s\t%s\t%s\n", i + 1, contacts[matchIndexes[i]].name, contacts[matchIndexes[i]].phone, contacts[matchIndexes[i]].email);
		}
		int choice;
		if (scanf("%d", &choice) != 1 || choice < 1 || choice > numMatches) {
			printf("Invalid input. Please try again.\n");
			while (getchar() != '\n')
				; // clear input buffer
			return;
		}
		for (int i = matchIndexes[choice - 1]; i < numContacts - 1; i++) {
			contacts[i] = contacts[i + 1];
		}
		numContacts--;
		printf("Contact deleted successfully.\n");
	}
}

void saveContacts() {
	if (numContacts == 0) {
		printf("No contacts found.\n");
		return;
	}
	char filename[50];
	printf("Enter filename to save contacts to: ");
	if (scanf("%49s", filename) != 1) {
		printf("Invalid input. Please try again.\n/");
		while (getchar() != '\n')
			; // clear input buffer
		return;
	}
	FILE *file = fopen(filename, "w");
	if (file == NULL) {
		printf("Error opening file.\n");
		return;
	}
	for (int i = 0; i < numContacts; i++) {
		fprintf(file, "%s,%s,%s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
	}
	fclose(file);
	printf("Contacts saved to file successfully.\n");
}

void loadContacts() {
	char filename[50];
	printf("Enter filename to load contacts from: ");
	if (scanf("%49s", filename) != 1) {
		printf("Invalid input. Please try again.\n");
		while (getchar() != '\n')
			; // clear input buffer
		return;
	}
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		printf("Error opening file.\n");
		return;
	}
	char line[120];
	int lineNum = 0;
	while (fgets(line, sizeof(line), file) != NULL) {
		lineNum++;
		if (line[strlen(line) - 1] != '\n') {
			printf("Line %d is too long.\n", lineNum);
			fclose(file);
			return;
		}
		char name[50];
		char phone[20];
		char email[50];
		if (sscanf(line, "%49[^,],%19[^,],%49[^\n]", name, phone, email) != 3) {
			printf("Line %d is missing fields.\n", lineNum);
			continue;
		}
		if (numContacts == MAX_CONTACTS) {
			printf("Maximum number of contacts reached.\n");
			break;
		}
		struct Contact newContact;
		strncpy(newContact.name, name, sizeof(newContact.name) - 1);
		strncpy(newContact.phone, phone, sizeof(newContact.phone) - 1);
		strncpy(newContact.email, email, sizeof(newContact.email) - 1);
		newContact.name[sizeof(newContact.name) - 1] = '\0';
		newContact.phone[sizeof(newContact.phone) - 1] = '\0';
		newContact.email[sizeof(newContact.email) - 1] = '\0';
		int contactExists = 0;
		for (int i = 0; i < numContacts; i++) {
			if (strcmp(contacts[i].name, newContact.name) == 0 &&
			        strcmp(contacts[i].phone, newContact.phone) == 0 &&
			        strcmp(contacts[i].email, newContact.email) == 0) {
				printf("Contact with the same name, phone number, and email address already exists.\n");
				contactExists = 1;
				break;
			}
		}
		if (!contactExists) {
			contacts[numContacts] = newContact;
			numContacts++;
		}
	}
	fclose(file);
	printf("Contacts loaded from file successfully.\n");
}