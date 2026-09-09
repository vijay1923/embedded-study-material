# 📚 Student Database Management System (C Project)

This project is a **Student Database Management System** implemented in **C using a Singly Linked List**.  
It allows adding, searching, editing, displaying, and saving student records based on various criteria.  
All data is stored dynamically using linked lists, making the system flexible and efficient.

---

## ✅ Features

- Add Student  
- Save Batch-wise Files (e.g., `batch_CS01.txt`)  
- Search by:
  - Join Date
  - Birth Date
  - Name (substring supported)
  - Batch ID
  - Marks Range
  - Assessment Status
- Edit Student Records  
- Display All Records  
- Uses a dynamic **singly linked list**  
- ANSI color-coded terminal output  

---

## 📂 Project Structure

/Student_DBMS/
│
├── main.c
├── student.c
├── student.h
├── makefile (optional)
└── README.md


---

## 🧱 Data Structures

### **Date Structure**
struct date 
{
  int day;
  int month;
  int year;
};


### **Student Linked List Node**
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


---

## 📌 Functional Overview

### ✅ Add Student  
Adds a new student node at the beginning of the linked list.

### ✅ Save Batch File  
Creates separate text files for each batch ID:  
`batch_CS01.txt`, `batch_ECE02.txt`, etc.

### ✅ Search Options  
- By Join Date  
- By Birth Date  
- By Student Name  
- By Batch ID  
- By Marks Range  
- By Status (r / nr)

### ✅ Edit Student  
Allows updating:
- Batch ID  
- Name  
- Marks  
- Status  
- DOB  
- DOJ  

### ✅ Display All  
Prints every student in the linked list with formatting.

---

## 📜 Menu Options

******** MENU ********

Add Student

Save Batch File

Search by Join Date

Search by Birth Date

Search by Name

Search by Batch ID

Edit Student

Search by Marks

Search by Status

Display All

Exit


---

## ✅ How to Compile & Run

### Using GCC:
gcc main.c student.c -o student_db
./student_db


### Using Makefile:
./student_db


---

## 📤 Sample Terminal Output

******** MENU ********

Add Student

Save Batch File
...
Enter choice: 1
Enter batch id: v24be3v1
Enter name: abd xyz
Enter avg marks: 68
Enter status (r/nr): r
Enter dob (dd mm yyyy): 12 08 2004
Enter doj (dd mm yyyy): 01 09 2023
Student added!


---

## ✅ Future Enhancements

- Delete Student Record  
- Load Records from File  
- Sort by Name or Marks  
- Export to CSV / JSON  
- GUI-based version  
- Multi-file merge and rewrite  

---

## 👨‍💻 Author
Vijay Magadum


