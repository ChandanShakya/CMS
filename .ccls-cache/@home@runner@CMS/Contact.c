#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100

struct Contact
{
    char name[50];
    char phone[20];
    char email[50];
};

void addContact(struct Contact contacts[], int *numContacts)
{
    if (*numContacts >= MAX_CONTACTS)
    {
        printf("Error: Maximum number of contacts reached.\n");
        return;
    }
    struct Contact newContact;
    printf("Enter name: ");
    scanf("%s", newContact.name);
    printf("Enter phone number: ");
    scanf("%s", newContact.phone);
    printf("Enter email address: ");
    scanf("%s", newContact.email);
    contacts[*numContacts] = newContact;
    (*numContacts)++;
    printf("Contact added successfully.\n");
}

void displayContacts(struct Contact contacts[], int numContacts)
{
    if (numContacts == 0)
    {
        printf("No contacts found.\n");
        return;
    }
    printf("Name\tPhone\tEmail\n");
    for (int i = 0; i < numContacts; i++)
    {
        printf("%s\t%s\t%s\n", contacts[i].name, contacts[i].phone, contacts[i].email);
    }
}

void updateContact(struct Contact contacts[], int numContacts)
{
    if (numContacts == 0)
    {
        printf("No contacts found.\n");
        return;
    }
    char name[50];
    printf("Enter name of contact to update: ");
    scanf("%s", name);
    for (int i = 0; i < numContacts; i++)
    {
        if (strcmp(contacts[i].name, name) == 0)
        {
            printf("Enter new phone number: ");
            scanf("%s", contacts[i].phone);
            printf("Enter new email address: ");
            scanf("%s", contacts[i].email);
            printf("Contact updated successfully.\n");
            return;
        }
    }
    printf("Contact not found.\n");
}

void deleteContact(struct Contact contacts[], int *numContacts)
{
    if (*numContacts == 0)
    {
        printf("No contacts found.\n");
        return;
    }
    char name[50];
    printf("Enter name of contact to delete: ");
    scanf("%s", name);
    for (int i = 0; i < *numContacts; i++)
    {
        if (strcmp(contacts[i].name, name) == 0)
        {
            for (int j = i; j < *numContacts - 1; j++)
            {
                contacts[j] = contacts[j + 1];
            }
            (*numContacts)--;
            printf("Contact deleted successfully.\n");
            return;
        }
    }
    printf("Contact not found.\n");
}

void saveContacts(struct Contact contacts[], int numContacts)
{
    FILE *fp;
    fp = fopen("contacts.dat", "wb");
    if (fp == NULL)
    {
        printf("Error: Unable to open file.\n");
        return;
    }
    fwrite(contacts, sizeof(struct Contact), numContacts, fp);
    fclose(fp);
    printf("Contacts saved to file.\n");
}

void loadContacts(struct Contact contacts[], int *numContacts)
{
    FILE *fp;
    fp = fopen("contacts.dat", "rb");
    if (fp == NULL)
    {
        printf("Error: Unable to open file.\n");
        return;
    }
    fread(contacts, sizeof(struct Contact), MAX_CONTACTS, fp);
    *numContacts = fread(contacts, sizeof(struct Contact), MAX_CONTACTS, fp);
    fclose(fp);
    printf("Contacts loaded from file.\n");
}

int main()
{
    struct Contact contacts[MAX_CONTACTS];
    int numContacts = 0;
    int choice;
    while (1)
    {
        printf("\n");
        printf("1. Add contact\n");
        printf("2. Display contacts\n");
        printf("3. Update contact\n");
        printf("4. Delete contact\n");
        printf("5. Save contacts to file\n");
        printf("6. Load contacts from file\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            addContact(contacts, &numContacts);
            break;
        case 2:
            displayContacts(contacts, numContacts);
            break;
        case 3:
            updateContact(contacts, numContacts);
            break;
        case 4:
            deleteContact(contacts, &numContacts);
            break;
        case 5:
            saveContacts(contacts, numContacts);
            break;
        case 6:
            loadContacts(contacts, &numContacts);
            break;
        case 7:
            exit(0);
        default:
            printf("Invalid choice.\n");
        }
    }
    return 0;
}