#include <stdio.h>
#include <string.h>
#pragma warning(disable : 4996)

void workWithFile(int userSelection)
{
    FILE* phonebook;
    if (userSelection == 1)
    {
        phonebook = fopen("phonebook.txt", "a");
    }
    else
    {
        phonebook = fopen("phonebook.txt", "r");
    }
    char stringForUploadingData[100] = { '\0' };
    char name[100] = { '\0' };
    char phoneNumber[100] = { '\0' };
    int searchContact = 0;
    int numberContact = 0;
    switch (userSelection)
    {
    case 1:
        printf("Enter name of new contact (no more than 100 symbols) ");
        if (scanf("%s", name) == NULL)
        {
            return 0;
        }

        printf("Enter phoneNumber of new contact (no more than 100 symbols) ");
        if (scanf("%s", phoneNumber) == NULL)
        {
            return 0;
        }
        fprintf(phonebook, "%s - %s\n", name, phoneNumber);
        fclose(phonebook);
        break;

    case 2:
        while (!feof(phonebook))
        {
            fgets(stringForUploadingData, 2, phonebook);
            printf("%s", stringForUploadingData);
        }
        fclose(phonebook);
        break;

    case 3:
        printf("Enter name of contact ");
        if (scanf("%s", name) == NULL)
        {
            return 0;
        }
        while (!feof(phonebook))
        {
            searchContact = findContact(fgets(stringForUploadingData, 100, phonebook), name);
            if (searchContact == 1)
            {
                printf("%s", stringForUploadingData);
                break;
            }
        }
        fclose(phonebook);
        break;

    case 4:
        printf("Enter phonenumber of contact ");
        if (scanf("%s", phoneNumber) == NULL)
        {
            return 0;
        }
        while (!feof(phonebook))
        {
            searchContact = findContact(fgets(stringForUploadingData, 100, phonebook), phoneNumber);
            if (searchContact == 1)
            {
                printf("%s", stringForUploadingData);
                break;
            }
        }
        fclose(phonebook);
        break;

    }
}

int findContact(char mainString[], char subString[])
{
    int const lengthMainString = strlen(mainString);
    int const lengthSubString = strlen(subString);
    int numberOccurrences = 0;
    {
        for (int elementNumberMainString = 0; elementNumberMainString < lengthMainString; ++elementNumberMainString)
        {
            int counter = 0;
            for (int elementNumberSubString = 0; elementNumberSubString < lengthSubString; ++elementNumberSubString)
            {
                if (mainString[elementNumberMainString + elementNumberSubString] == subString[elementNumberSubString])
                {
                    ++counter;
                }
                else
                {
                    break;
                }
                if (counter == lengthSubString)
                {
                    ++numberOccurrences;
                    break;
                }
            }
            if (numberOccurrences > 0)
            {
                break;
            }
        }
    }
    return numberOccurrences;
}


int main()
{
    int userSelection = 1;
    while (userSelection != 0)
    {
        printf("\n0 - Exit\n");
        printf("1 - create new records(name and phonenumber)\n");
        printf("2 - print all existing records\n");
        printf("3 - find phone by name\n");
        printf("4 - find name by phone\n");
        printf("Choose operation ");
        scanf_s("%d", &userSelection);
        if (userSelection > 4 || userSelection < 0)
        {
            printf("There is no transaction with this number");
            return 0;
        }
        workWithFile(userSelection);
    }
}