#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100

int i,j;

struct Contact
{
    char name[50];
    char phone[20];
    char email[50];
};

struct Contact contacts[MAX_CONTACTS];
int numContacts = 0;

void addContact();
void displayContacts();
void updateContact();
void deleteContact();
void saveContacts();
void loadContacts();

int main()
{
    int choice;
    do
    {
        printf("\nContact Management System\n");
        printf("1. Add new contact\n");
        printf("2. Display all contacts\n");
        printf("3. Update existing contact\n");
        printf("4. Delete contact\n");
        printf("5. Save contacts to file\n");
        printf("6. Load contacts from file\n");
        printf("7. Exit\n");
        printf("Enter your choice (1-7): ");
        scanf("%d", &choice);
        switch (choice)
        {
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
    } while (choice != 7);
    return 0;
}

void addContact()
{
    if (numContacts == MAX_CONTACTS)
    {
        printf("Maximum number of contacts reached.\n");
        return;
    }
    struct Contact newContact;
    printf("Enter name: ");
    scanf("%s", newContact.name);
    printf("Enter phone number: ");
    scanf("%s", newContact.phone);
    printf("Enter email address: ");
    scanf("%s", newContact.email);
    for (i = 0; i < numContacts; i++)
    {
        if (strcmp(contacts[i].name, newContact.name) == 0 &&
            strcmp(contacts[i].phone, newContact.phone) == 0 &&
            strcmp(contacts[i].email, newContact.email) == 0)
        {
            printf("Contact with the same name, phone number, and email address already exists.\n");
            return;
        }
    }
    contacts[numContacts] = newContact;
    numContacts++;
    printf("Contact added successfully.\n");
}

void displayContacts()
{
    if (numContacts == 0)
    {
        printf("No contacts found.\n");
        return;
    }
    printf("Name\tPhone\t\tEmail\n");
    for (i= 0; i < numContacts; i++)
    {
        printf("%s\t%s\t%s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
    }
}

void updateContact()
{
    if (numContacts == 0)
    {
        printf("No contacts found.\n");
        return;
    }
    char name[50];
    printf("Enter name of contact to update: ");
    scanf("%s", name);
    int numMatches = 0;
    int matchIndexes[MAX_CONTACTS];
    for (i= 0; i < numContacts; i++)
    {
        if (strcmp(contacts[i].name, name) == 0)
        {
            matchIndexes[numMatches] = i;
            numMatches++;
        }
    }
    if (numMatches == 0)
    {
        printf("Contact not found.\n");
        return;
    }
    printf("Found %d contacts with the same name:\n", numMatches);
    for (i= 0; i < numMatches; i++)
    {
        printf("%d. %s\t%s\t%s\n", i + 1, contacts[matchIndexes[i]].name,
               contacts[matchIndexes[i]].phone, contacts[matchIndexes[i]].email);
    }
    printf("Enter the index of the contact to update (1-%d): ", numMatches);
    int index;
    scanf("%d", &index);
    if (index < 1 || index > numMatches)
    {
        printf("Invalid index.\n");
        return;
    }
    printf("Enter new phone number: ");
    scanf("%s", contacts[matchIndexes[index - 1]].phone);
    printf("Enter new email address: ");
    scanf("%s", contacts[matchIndexes[index - 1]].email);
    printf("Contact updated successfully.\n");
}

void deleteContact()
{
    if (numContacts == 0)
    {
        printf("No contacts found.\n");
        return;
    }
    char name[50];
    printf("Enter name of contact to delete: ");
    scanf("%s", name);
    for (i= 0; i < numContacts; i++)
    {
        if (strcmp(contacts[i].name, name) == 0)
        {
            for (j= i; j < numContacts - 1; j++)
            {
                contacts[j] = contacts[j + 1];
            }
            numContacts--;
            printf("Contact deleted successfully.\n");
            return;
        }
    }
    printf("Contact not found.\n");
}

void saveContacts()
{
    if (numContacts == 0)
    {
        printf("No contacts found.\n");
        return;
    }
    char filename[50];
    printf("Enter filename to save contacts to: ");
    scanf("%s", filename);
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    for (i= 0; i < numContacts; i++)
    {
        fprintf(fp, "%s,%s,%s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
    }
    fclose(fp);
    printf("Contacts saved to file successfully.\n");
}

void loadContacts()
{
    char filename[50];
    printf("Enter filename to load contacts from: ");
    scanf("%s", filename);
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    char line[100];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        char *name = strtok(line, ",");
        char *phone = strtok(NULL, ",");
        char *email = strtok(NULL, ",");
        if (name != NULL && phone != NULL && email != NULL)
        {
            struct Contact newContact;
            strcpy(newContact.name, name);
            strcpy(newContact.phone, phone);
            strcpy(newContact.email, email);
            contacts[numContacts] = newContact;
            numContacts++;
        }
    }
    fclose(fp);
    printf("Contacts loaded from file successfully.\n");
}