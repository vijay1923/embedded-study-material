#ifndef STUDENT_H
#define STUDENT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

struct date
{
    int day;
    int month;
    int year;
};

typedef struct st
{
    char batch_id[10];
    char name[50];
    float avg_internal_marks;
    char assessment_status[5];
    struct date dob;
    struct date doj;
    struct st *next;
} STUDENT;

// Function declarations
void add_student(STUDENT **);
void save_batch_file(STUDENT *);
void search_join_date(STUDENT *);
void search_birth_date(STUDENT *);
void search_name(STUDENT *);
void search_batch(STUDENT *);
void edit_student(STUDENT *);
void search_marks(STUDENT *);
void search_status(STUDENT *);
void display_all(STUDENT *);
void print_student(STUDENT);

#endif

