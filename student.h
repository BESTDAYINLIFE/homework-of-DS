#pragma once
//Header file_students.h
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <stdio.h>
#define TRUE 1
#define NULL 0
using namespace std;

//Maintain a structure called :Course
typedef struct Course {
	char Course_Name[5];
	int Course_ID;
	int Course_Section;
}Course;
//Maintain a structure called :Student
typedef struct Student {
	char First_name[100];
	char Last_name[100];
	char SSN[15];
	int Number_Courses_Attending;
	Course Elem_Course[10];
	struct Student* next;


}Student,*Student_pointer;

Student* head = new Student;

//Function declaration
void ReadInputFile(char* filename);
void AddToList(struct Student* addStudent);
void PrintToFile(char* filename);
void ProcessDeleteFile(char* filename);
void DeleteStudent(char* SSN);
void DeleteList(Student* head);
void InvertList(Student* head);


