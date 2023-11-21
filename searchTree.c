#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "tree.h"
#include "searchTree.h"

void operation(unsigned int numberOperation)
{
    static Tree* tree = NULL;
    char* string = { '\0' };
    char string1[1] = { '\0' };
    int key = 0;
    switch (numberOperation)
    {
    case 1:
        string = (char*)calloc(10, sizeof(char));
        printf("Enter key ");
        scanf_s("%d", &key);
        printf("Enter data ");
        scanf_s("%ch", string1, sizeof(char));
        if (string != NULL)
        {
            fgets(string, 10, stdin);
        }
        tree = tree == NULL ? makeRoot(tree, string, key) : addData(tree, string, key);
        break;

    case 2:
        printf("Enter a key ");
        scanf_s("%d", &key);
        printf("%s", searchData(tree, key));
        break;

    case 3:
        printf("Enter a key ");
        scanf_s("%d", &key);
        printf(existence(tree, key) == true ? "key is existence\n" : "key is not existence\n");
        break;

    case 4:
        printf("Enter key ");
        scanf_s("%d", &key);
        if (existence(tree, key) == true)
        {
            tree = deleteNode(tree, key);
            break;
        }
        break;

    case 5:
        free(tree);
        break;

    default:
        printf("Operation is not exist");
    }

}




