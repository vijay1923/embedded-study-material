#include "student.h"

void add_student(STUDENT **ptr)
{
    STUDENT *new = malloc(sizeof(STUDENT));
    if (!new)
    {
        printf("\033[31mMemory allocation failed!\033[0m\n");
        return;
    }

    printf("Enter batch id: ");
    scanf("%s", new->batch_id);

    printf("Enter name: ");
    getchar();
    scanf("%[^\n]", new->name);

    printf("Enter avg marks: ");
    scanf("%f", &new->avg_internal_marks);

    printf("Enter status (r/nr): ");
    scanf("%s", new->assessment_status);

    printf("Enter dob (dd mm yyyy): ");
    scanf("%d%d%d", &new->dob.day, &new->dob.month, &new->dob.year);

    printf("Enter doj (dd mm yyyy): ");
    scanf("%d%d%d", &new->doj.day, &new->doj.month, &new->doj.year);

    new->next = *ptr;
    *ptr = new;

    printf("\033[32mStudent added!\033[0m\n");
}

void save_batch_file(STUDENT *ptr)
{
    if (ptr == NULL)
    {
        printf("\033[31mNo records!\033[0m\n");
        return;
    }

    STUDENT *i, *j;
    STUDENT temp;

    for (i = ptr; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (strcmp(i->batch_id, j->batch_id) > 0)
            {
                temp = *i;
                *i = *j;
                *j = temp;
                STUDENT *tmp = i->next;
                i->next = j->next;
                j->next = tmp;
            }
        }
    }

    char prev_batch[10] = "";
    FILE *fp = NULL;

    while (ptr)
    {
        if (strcmp(prev_batch, ptr->batch_id) != 0)
        {
            if (fp != NULL)
                fclose(fp);

            char fname[30];
            sprintf(fname, "batch_%s.txt", ptr->batch_id);
            fp = fopen(fname, "w");
            if (!fp)
            {
                printf("\033[31mError creating file %s!\033[0m\n", fname);
                return;
            }
            strcpy(prev_batch, ptr->batch_id);
        }

        fprintf(fp, "%s %s %.2f %s %d %d %d %d %d %d\n",
                ptr->batch_id, ptr->name, ptr->avg_internal_marks,
                ptr->assessment_status,
                ptr->dob.day, ptr->dob.month, ptr->dob.year,
                ptr->doj.day, ptr->doj.month, ptr->doj.year);

        ptr = ptr->next;
    }

    if (fp != NULL)
        fclose(fp);

    printf("\033[32mFiles saved!\033[0m\n");
}

void search_join_date(STUDENT *ptr)
{
    if (ptr == NULL)
    {
        printf("\033[31mNo records!\033[0m\n");
        return;
    }

    int d, m, y, found = 0;
    printf("Enter join date (dd mm yyyy): ");
    scanf("%d%d%d", &d, &m, &y);

    printf("\n----- Search Result -----\n");
    while (ptr)
    {
        if (ptr->doj.day == d && ptr->doj.month == m && ptr->doj.year == y)
        {
            print_student(*ptr);
            found = 1;
        }
        ptr = ptr->next;
    }

    if (!found)
        printf("\033[31mNot found!\033[0m\n");
}

void search_birth_date(STUDENT *ptr)
{
    if (ptr == NULL)
    {
        printf("\033[31mNo records!\033[0m\n");
        return;
    }

    int d, m, y, found = 0;
    printf("Enter birth date (dd mm yyyy): ");
    scanf("%d%d%d", &d, &m, &y);

    printf("\n----- Search Result -----\n");
    while (ptr)
    {
        if (ptr->dob.day == d && ptr->dob.month == m && ptr->dob.year == y)
        {
            print_student(*ptr);
            found = 1;
        }
        ptr = ptr->next;
    }

    if (!found)
        printf("\033[31mNot found!\033[0m\n");
}

void search_name(STUDENT *ptr)
{
    if (ptr == NULL)
    {
        printf("\033[31mNo records!\033[0m\n");
        return;
    }

    char sname[50];
    printf("Enter name: ");
    getchar();
    scanf("%[^\n]", sname);

    int found = 0;
    printf("\n----- Search Result -----\n");
    while (ptr)
    {
        if (strstr(ptr->name, sname) != NULL)
        {
            print_student(*ptr);
            found = 1;
        }
        ptr = ptr->next;
    }

    if (!found)
        printf("\033[31mNot found!\033[0m\n");
}

void search_batch(STUDENT *ptr)
{
    if (ptr == NULL)
    {
        printf("\033[31mNo records!\033[0m\n");
        return;
    }

    char bid[10];
    printf("Enter batch id: ");
    scanf("%s", bid);

    int found = 0;
    printf("\n----- Search Result -----\n");
    while (ptr)
    {
        if (strcmp(ptr->batch_id, bid) == 0)
        {
            print_student(*ptr);
            found = 1;
        }
        ptr = ptr->next;
    }

    if (!found)
        printf("\033[31mNot found!\033[0m\n");
}

void edit_student(STUDENT *ptr)
{
    if (ptr == NULL)
    {
        printf("\033[31mNo records!\033[0m\n");
        return;
    }

    char sname[50];
    printf("Enter student name to edit: ");
    getchar();
    scanf("%[^\n]", sname);

    int found = 0;
    while (ptr)
    {
        if (strcmp(ptr->name, sname) == 0)
        {
            found = 1;
            printf("\nCurrent details:\n");
            print_student(*ptr);

            printf("\nWhat to edit?\n");
            printf("1.Batch ID\n2.Name\n3.Marks\n4.Status\n5.DOB\n6.DOJ\n");
            int ch;
            scanf("%d", &ch);

            switch (ch)
            {
            case 1:
                printf("New batch id: ");
                scanf("%s", ptr->batch_id);
                break;
            case 2:
                printf("New name: ");
                getchar();
                scanf("%[^\n]", ptr->name);
                break;
            case 3:
                printf("New marks: ");
                scanf("%f", &ptr->avg_internal_marks);
                break;
            case 4:
                printf("New status: ");
                scanf("%s", ptr->assessment_status);
                break;
            case 5:
                printf("New dob (dd mm yyyy): ");
                scanf("%d%d%d", &ptr->dob.day, &ptr->dob.month, &ptr->dob.year);
                break;
            case 6:
                printf("New doj (dd mm yyyy): ");
                scanf("%d%d%d", &ptr->doj.day, &ptr->doj.month, &ptr->doj.year);
                break;
            }

            printf("\033[32mUpdated!\033[0m\n");
            break;
        }
        ptr = ptr->next;
    }

    if (!found)
        printf("\033[31mStudent not found!\033[0m\n");
}

void search_marks(STUDENT *ptr)
{
    if (ptr == NULL)
    {
        printf("\033[31mNo records!\033[0m\n");
        return;
    }

    float min, max;
    printf("Enter min marks: ");
    scanf("%f", &min);
    printf("Enter max marks: ");
    scanf("%f", &max);

    int found = 0;
    printf("\n----- Search Result -----\n");
    while (ptr)
    {
        if (ptr->avg_internal_marks >= min && ptr->avg_internal_marks <= max)
        {
            print_student(*ptr);
            found = 1;
        }
        ptr = ptr->next;
    }

    if (!found)
        printf("\033[31mNo students in this range!\033[0m\n");
}

void search_status(STUDENT *ptr)
{
    if (ptr == NULL)
    {
        printf("\033[31mNo records!\033[0m\n");
        return;
    }

    char sts[5];
    printf("Enter status (r/nr): ");
    scanf("%s", sts);

    int found = 0;
    printf("\n----- Search Result -----\n");
    while (ptr)
    {
        if (strcmp(ptr->assessment_status, sts) == 0)
        {
            print_student(*ptr);
            found = 1;
        }
        ptr = ptr->next;
    }

    if (!found)
        printf("\033[31mNo students with this status!\033[0m\n");
}

void display_all(STUDENT *ptr)
{
    if (ptr == NULL)
    {
        printf("\033[31mNo records!\033[0m\n");
        return;
    }

    printf("\n===== ALL RECORDS =====\n");
    int c = 1;
    while (ptr)
    {
        printf("\n[%d]\n", c);
        print_student(*ptr);
        ptr = ptr->next;
        c++;
    }
}

void print_student(STUDENT s)
{
    printf("Batch: %s\n", s.batch_id);
    printf("Name: %s\n", s.name);
    printf("Marks: %.2f\n", s.avg_internal_marks);
    printf("Status: %s\n", s.assessment_status);
    printf("DOB: %02d-%02d-%04d\n", s.dob.day, s.dob.month, s.dob.year);
    printf("DOJ: %02d-%02d-%04d\n", s.doj.day, s.doj.month, s.doj.year);
    printf("-------------------\n");
}

