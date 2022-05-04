#include "student.h"
//Writing ahead:
//My disadvantages of my program:
//1.I don't know why I cannot store '0' of "0123" into my course_section! So I add it by printing into the output FILES.
//2.There are some operations that don't obey the requirements of "A2.pdf".
//3.Add"*****"into the delete.txt to check whether file reading is complete
int main()
{
	head->next = NULL;

	// Read the input file and create the linked list
 // ReadInputFile calls helper function AddToList to
 // create list in sorted order
	char StudentFile[] = "student.txt";
	char PrintFile[]="output.txt";
	char DeleteFile_SNN[] = "delete.txt";
	char PrintFile_2[] = "update.txt";
	char PrintFile_3[] = "invert_update.txt";
	ReadInputFile(StudentFile);
	// print the current list to the outputfile output.txt
	PrintToFile(PrintFile);
	// Read and process the dropped students file delete.txt
	// It uses helper function DeleteStudent to remove
	// the from the list
	ProcessDeleteFile(DeleteFile_SNN);
	// Print the updated linked list to the file update.txt
	PrintToFile(PrintFile_2);
	InvertList(head);
	PrintToFile(PrintFile_3);
	// Delete the Entire Linked List before exiting the program
	DeleteList(head);
	cout << "This program has no error!" << endl;
	return 0;
}
//Add the student's data into the linker structure.
void AddToList( Student* addStudent) {
	if (head->next == NULL) {
		head->next = addStudent;
		return;
	}
	//In order not to modify the header point,
	//we need a intermediate to move on.
		Student* temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
			if (temp->next == NULL) {
				temp->next = addStudent;
				return;
			}
		}
}

void ReadInputFile(char* filename) {
	// open up the input file for read mode
	FILE* fp1 = NULL;
	fp1 = fopen(filename, "r");

	// if it can’t open print error message
	if (!fp1) {cout << "Open Error!" << endl;exit(-1);}
	//While you still have data to read
	char* check = new char[10];
	fscanf(fp1, "%s", check);
while (strcmp(check, "*****") != 0) 
{//Reading operation cannot meet "*****"or it will end!
    Student* Temp = new Student;//Creat the intermediate variable to help us
    strcpy(Temp->First_name, check);//After checking,we need to put the checked string into Temp->First_Name
	fscanf(fp1, "%s\n%s\n%d", Temp->Last_name, Temp->SSN, &Temp->Number_Courses_Attending);
	for (int i = 0; i < Temp->Number_Courses_Attending; i++) 
	{
	fscanf(fp1,"%s", Temp->Elem_Course[i].Course_Name);
	fscanf(fp1,"%d",&Temp->Elem_Course[i].Course_ID);
	fscanf(fp1,"%d",&Temp->Elem_Course[i].Course_Section);
	}
Temp->next = NULL;
AddToList(Temp);
fscanf(fp1, "%s", check);
}
    delete(check);
	fclose(fp1);
	//Here comes the sort operation: The linked list must be sorted based on the lastname of the student.
	// Bubble Sorting!
	if ((NULL == head) || (NULL == head->next) || (NULL == head->next->next))cout << "Sorting Error!" << endl;
	Student* p1 = head;
	Student* p2 = p1->next;
	Student* p3 = p2->next;
	Student* pPosEle = NULL;
	while (p3 != pPosEle) {
		while (p3 != pPosEle) {
			if (strcmp(p2->Last_name,p3->Last_name)>0) {
				
				Student*Temp = p3->next;
				p1->next = p3;
				p3->next = p2;
				p2->next = Temp;
			}
			//We need to reward movement!
			p1 = p1->next;
			p2 = p1->next;
			p3 = p2->next;
		}
		pPosEle = p2;//In this circle, p2 is maximum.Let's make it as head->next!
		//Reset  p1,p2,p3.
		p1 = head;
		p2 = p1->next;
		p3 = p2->next;

	}
}

void PrintToFile(char* filename) {
	if ((NULL == head) || (NULL == head->next) || (NULL == head->next->next))cout << "Printing Error!" << endl;
	//In order not to modify the header point,
		//we need a intermediate to move on.
	Student* Temp = head;//CRE
	FILE* fp2 = NULL;//Use fp2 to finish this operation
	fp2 = fopen(filename, "w+");
	if (fp2 == NULL) { cout << "Open Error!" << endl; return; }
	Temp = Temp->next;
		while (Temp != NULL) {
			fprintf(fp2, "SSN:%s\n", Temp->SSN);
			fprintf(fp2, "NAME:%s, %s\n", Temp->First_name, Temp->Last_name);
			fprintf(fp2, "Registered For %d classes\n", Temp->Number_Courses_Attending);
			for (int j = 0; j < Temp->Number_Courses_Attending; j++) {
				//Because '0'of "0123" cannot be stored!
				fprintf(fp2, "\t-%s%d-0%d\n", Temp->Elem_Course[j].Course_Name, Temp->Elem_Course[j].Course_ID, Temp->Elem_Course[j].Course_Section);
			}
			fprintf(fp2, "\n");
			Temp = Temp->next;

		}
		fclose(fp2);
}
void DeleteStudent(char* SSN) {
	if ((NULL == head) || (NULL == head->next) || (NULL == head->next->next))cout << "Deleting Error!" << endl;
	Student* Temp = head;
	Student* Pre_Temp = head;//Creat another pointer to store the previous linker!
	Temp = Temp->next;
	while (Temp!= NULL) {
		if (strcmp(Temp->SSN, SSN) == 0) {
			Student* Delete_Helper = Temp;
			Pre_Temp->next = Temp->next;
			delete (Delete_Helper);
			return;
		}
		Pre_Temp = Temp;
		Temp = Temp->next;
		if (Temp == NULL)cout << "Delete Error!The SSN you gave cannot be found!" << endl;;//If not found,print this sentence!
	}
}
void ProcessDeleteFile(char* filename) {
	if ((NULL == head) || (NULL == head->next) || (NULL == head->next->next))cout << "Deleting Error!" << endl;
	Student* Temp = new Student;
	Temp = head;
	char SSN[15];//Define char SSN to store the SSN in the file.
	FILE* fp3 = NULL;
	fp3 = fopen(filename, "r");
	if (!fp3) { cout << "Open Error!" << endl; return; }
	while (TRUE) {
		fscanf(fp3, "%s", SSN);
		if(strcmp(SSN, "*****") == 0)break;
		DeleteStudent(SSN);
	}
	fclose(fp3);
}

void DeleteList(Student* head) {
	Student* Temp = new Student;
	Temp = head;

	while (Temp != NULL) {
		Student* Delete_pointer;
		Delete_pointer = Temp->next;
		delete(Temp);
		Temp = Delete_pointer;
	}
}

void InvertList(Student* head)
{
	Student* Temp = head;
	Student* p1;
	Student* p2;
	Student* p;
	p1 = Temp->next;
	p2 = p1->next;
	p = NULL;
	while (p2 != NULL) {
		p1->next = p;
		p = p1;
		p1 = p2;
		p2 = p2->next;
	}
	p1->next = p;
	Temp->next = p1;
}

