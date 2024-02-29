#include<stdio.h>
#include <string.h>
struct contact
{
    char first_name[25], last_name[25], email[25], number[25];
};
void addContact(struct contact book[], int* count)
{
    int v;
    printf("Press 1 to add a contact or 9 to return to main menu.\n");
    scanf("%d",&v);
    switch(v){
        case 9:
            return;
        case 1:
            printf("Enter first name:");
            scanf("%s", book[*count].first_name);
            printf("Enter last name:");
            scanf("%s", book[*count].last_name);
            printf("Enter email address:");
            scanf("%s", book[*count].email);
            printf("Enter phone number:");
            scanf("%s", book[*count].number);
            FILE *file = fopen("contacts.txt", "a");
            fprintf(file, "%s,%s,%s,%s\n", book[*count].first_name, book[*count].last_name, book[*count].email,book[*count].number);
            fclose(file);
            (*count)++;
            file = fopen("count.txt", "w");
            fprintf(file, "%d", *count);
            fclose(file);
            printf("Contact added successfully!\n\n");
    }
}
void displayContacts(int *count)
{
    int sp=0,abc=0;
    if(*count==0) {
        printf("There are no contacts inside the file.\n\n");
        sp=1;
    }
    if(sp==0) {
        FILE *file = fopen("contacts.txt", "r");
        if (file == NULL) {
            printf("Error: Unable to open file\n");
            return;
        }
        printf("Contacts:\n");
        char line[100];
        while (fgets(line, 100, file) != NULL && abc<*count) {
            char *first_name = strtok(line, ",");
            char *last_name = strtok(NULL, ",");
            char *email = strtok(NULL, ",");
            char *number = strtok(NULL, ",");
            printf("Name: %s %s\n", first_name, last_name);
            printf("Email: %s\n", email);
            printf("Phone number: %s\n", number);
            abc++;
        }
        fclose(file);
    }
}
void searchContact(struct contact book[], int *count)
{
    char sp=0;
    if(*count==0) {
        printf("There are no contacts inside the file.\n\n");
        sp=1;
        return;
    }
    printf("Press 1 to search for a contact or 9 to return to main menu.\n");
    int v;
    scanf("%d", &v);
    switch(v){
        case 9:
            return;
        case 1:
            if(sp==0) {
                FILE *file = fopen("contacts.txt", "r");
                if (file == NULL) {
                    printf("Error: Unable to open file\n");
                    return;
                }
                char search[25];
                int found = 0;
                printf("Enter the name, number or email address to search for:");
                scanf("%s", search);
                printf("Search results for '%s':\n", search);
                for (int i = 0; i < *count; i++) {
                    char line[100];
                    while (fgets(line, 100, file) != NULL) {
                        char *first_name = strtok(line, ",");
                        char *last_name = strtok(NULL, ",");
                        char *email = strtok(NULL, ",");
                        char *number = strtok(NULL, ",");
                        if (strstr(first_name, search) != NULL || strstr(last_name, search) != NULL ||
                            strstr(number, search) != NULL || strstr(email, search) != NULL) {
                            printf("Name: %s %s\n", first_name, last_name);
                            printf("Email: %s\n", email);
                            printf("Phone number: %s\n", number);
                            found = 1;
                        }
                    }
                }
                if (!found) {
                    printf("No results found for '%s'\n", search);
                }
            }
    }

}
void deleteContact(struct contact book[], int *count) {
    char sp=0;
    if(*count==0) {
        printf("There are no contacts inside the file.\n\n");
        sp=1;
        return;
    }
    printf("Press 1 to delete a contact or 9 to return to main menu.\n");
    int v;
    scanf("%d", &v);
    switch(v){
        case 9:
            return;
        case 1:
            if(sp==0) {
                FILE *file = fopen("contacts.txt", "r");
                if (file == NULL) {
                    printf("Error: Unable to open file\n");
                    return;
                }
                FILE *tempFile = fopen("temp_contacts.txt", "w");
                if (tempFile == NULL) {
                    printf("Error: Unable to open temp file\n");
                    fclose(file);
                    return;
                }
                char search[25];
                int found = 0;
                printf("Enter the name, number or email address that you want to delete:");
                scanf("%s", search);
                for (int i = 0; i < *count; i++) {
                    char line[100];
                    fgets(line, 100, file);
                    char *first_name = strtok(line, ",");
                    char *last_name = strtok(NULL, ",");
                    char *email = strtok(NULL, ",");
                    char *number = strtok(NULL, ",");
                    if (strstr(first_name, search) != NULL || strstr(last_name, search) != NULL ||
                        strstr(number, search) != NULL || strstr(email, search) != NULL) {
                        found = 1;
                    } else {
                        fprintf(tempFile, "%s,%s,%s,%s", first_name, last_name, email, number);
                    }
                }
                fclose(file);
                fclose(tempFile);
                if (!found) {
                    printf("No contact found for deletion.\n");
                } else {
                    (*count)--;
                    file = fopen("count.txt", "w");
                    fprintf(file, "%d", *count);
                    fclose(file);
                    remove("contacts.txt");
                    rename("temp_contacts.txt", "contacts.txt");
                    printf("Contact deleted successfully!\n");
                }
            }
    }
}
void modifyContact(struct contact book[], int *count) {
    if (*count == 0) {
        printf("There are no contacts inside the file.\n\n");
        return;
    }
    FILE *file = fopen("contacts.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open file\n");
        return;
    }
    FILE *tempFile = fopen("contacts_temp.txt", "w");
    if (tempFile == NULL) {
        printf("Error: Unable to open temporary file\n");
        fclose(file);
        return;
    }
    char search[25];
    int found = 0, x;
    printf("Enter the name, number, or email address that you want to modify:");
    scanf("%s", search);
    for (int i = 0; i < *count; i++) {
        char first_name[50], last_name[50], email[50], number[20];
        fscanf(file, "%[^,],%[^,],%[^,],%s\n", first_name, last_name, email, number);
        if (strstr(first_name, search) != NULL || strstr(last_name, search) != NULL ||
            strstr(number, search) != NULL || strstr(email, search) != NULL) {
            found = 1;
            printf("Name: %s %s\n", first_name, last_name);
            printf("Email: %s\n", email);
            printf("Phone number: %s\n", number);
            printf("Press 1 to modify or 9 to return to main menu.\n");
            scanf("%d", &x);
            switch (x) {
                case 9:
                    fprintf(tempFile, "%s,%s,%s,%s\n", first_name, last_name, email, number);
                    break;
                case 1:
                    printf("Enter first name: ");
                    scanf("%s", book[i].first_name);
                    printf("Enter last name: ");
                    scanf("%s", book[i].last_name);
                    printf("Enter email address: ");
                    scanf("%s", book[i].email);
                    printf("Enter phone number: ");
                    scanf("%s", book[i].number);
                    fprintf(tempFile, "%s,%s,%s,%s\n", book[i].first_name, book[i].last_name, book[i].email,
                            book[i].number);
                    printf("Contact modified successfully!\n\n");
                    break;
            }
        } else {
            fprintf(tempFile, "%s,%s,%s,%s\n", first_name, last_name, email, number);
        }
    }
    fclose(file);
    fclose(tempFile);
    remove("contacts.txt");
    rename("contacts_temp.txt", "contacts.txt");
    if (!found) {
        printf("No contacts found for '%s'\n", search);
    }
}
int main() {
    int v,count;
    FILE *file = fopen("count.txt", "r");
    if (file == NULL) {
        printf("Error: could not open file count.txt\n");
    }
    fscanf(file, "%d", &count);
    fclose(file);
    struct contact book[100];
    do{
        printf("What action do you want to do?\n");
        printf("Choose a number from 1 to 5 or 0 to exit.\n");
        printf("1.Search for a contact\n");
        printf("2.Add a new contact\n");
        printf("3.Delete an existing contact\n");
        printf("4.Modify an existing contact\n");
        printf("5.Display all contacts\n");
        printf("0.Exit\n");
        scanf("%d", &v);
        switch (v) {
            case 1:
                searchContact(book,&count);
                break;
            case 2:
                addContact(book, &count);
                break;
            case 3:
                deleteContact(book, &count);
                break;
            case 4:
                modifyContact(book, &count);
                break;
            case 5:
                displayContacts(&count);
                break;
            case 0:
                break;
            case 9:
                main();
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    } while (v != 0);
    return 0;
}