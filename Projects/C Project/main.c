#include "student.h"

int main()
{
    STUDENT *head = NULL;
    int ch;

    while (1)
    {
        printf("\033[32m\n******** MENU ********\n");
        printf("1. Add Student\n");
        printf("2. Save Batch File\n");
        printf("3. Search by Join Date\n");
        printf("4. Search by Birth Date\n");
        printf("5. Search by Name\n");
        printf("6. Search by Batch ID\n");
        printf("7. Edit Student\n");
        printf("8. Search by Marks\n");
        printf("9. Search by Status\n");
        printf("10. Display All\n");
        printf("11. Exit\n");
        printf("**********************\033[0m\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 1: add_student(&head); break;
        case 2: save_batch_file(head); break;
        case 3: search_join_date(head); break;
        case 4: search_birth_date(head); break;
        case 5: search_name(head); break;
        case 6: search_batch(head); break;
        case 7: edit_student(head); break;
        case 8: search_marks(head); break;
        case 9: search_status(head); break;
        case 10: display_all(head); break;
        case 11: 
            printf("\033[36mExiting...\033[0m\n");
            exit(0);
        default:
            printf("\033[31mInvalid Choice!\033[0m\n");
        }
    }
    return 0;
}

