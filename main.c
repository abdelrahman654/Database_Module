#include <stdio.h>
#include <stdlib.h>
/*Defining my own data types*/
typedef unsigned char uint8;
typedef signed char  sint8;
typedef unsigned short int uint16;
typedef signed short int sint16;
typedef unsigned long int uint32;
typedef signed long int sint32;
typedef float float32;
typedef double float64;
typedef enum{
    False=0,
    True=1
}bool;


/*Global variable to count the number of entries*/
uint8 counter=0;


/*Creating structure*/
struct SimpleDb{
    uint8 student_id;
    uint8 student_year;
    uint8 course1_id;
    uint8 course1_grade;
    uint8 course2_id;
    uint8 course2_grade;
    uint8 course3_id;
    uint8 course3_grade;
    struct SimpleDb* next;
};


/*initializing head (NULL-pointer) of Linked_List*/
struct SimpleDb* head = NULL;


/*Function prototypes*/
bool SDB_IsFull(void);
uint8 SDB_GetUsedSize(void);
bool SDB_AddEntry(uint8,uint8,uint8*,uint8*);
void SDB_DeleteEntry(uint8);
bool SDB_ReadEntry(uint8);
void SDB_GetIdList(void);
bool SDB_IsIdExist(uint8);



int main()
{

    /*Example to chick the validation of the functions*/
    uint8 student1_ID=75,student1_year=22,student1_subjects[3]={55,54,53},student1_grades[3]={80,85,90};
    uint8 student2_ID=70,student2_year=21,student2_subjects[3]={5,5,5},student2_grades[3]={8,8,9};
    uint8*ptr1=student1_subjects;
    uint8*ptr2=student1_grades;
    uint8*ptr3=student2_subjects;
    uint8*ptr4=student2_grades;
    SDB_AddEntry(student1_ID,student1_year,student1_subjects,student1_grades);
    SDB_AddEntry(student2_ID,student2_year,student2_subjects,student2_grades);
    SDB_ReadEntry(student1_ID);
    SDB_ReadEntry(student2_ID);
    SDB_GetIdList();
    SDB_GetUsedSize();
    SDB_IsIdExist(student1_ID);


    return 0;
}



/*Function to check if database is full or not*/
bool SDB_IsFull(void){
    bool x;
    if (counter==10){
        printf("The database is full\n");
        x=True;
    }
    else{
        printf("The database is not full uet\n");
        x=False;
    }
    return x;
}

/*Function to get the number of entries*/
uint8 SDB_GetUsedSize(void){
    printf("The number of entries is : %d\n",counter);
    return counter;
}

/*Function to add entries to the data base*/
bool SDB_AddEntry(uint8 id,uint8 year,uint8*subjects,uint8*grades){
    bool q;

/*check if the number of entries exceeds the maximum size of the database*/
    if((counter+1)==11){
        printf("The database is full. Adding a new data is not allowed\n");
        q=False;
    }
    else{
/*Creating new node in our Linked-List*/
        struct SimpleDb* newEntry=(struct SimpleDb*)malloc(sizeof(struct SimpleDb));

/*insert data of student*/
        newEntry->student_id=id;
        newEntry->student_year=year;
        newEntry->course1_id=subjects[0];
        newEntry->course1_grade=grades[0];
        newEntry->course2_id=subjects[1];
        newEntry->course2_grade=grades[1];
        newEntry->course3_id=subjects[2];
        newEntry->course3_grade=grades[2];
        newEntry->next=head;

/*moving the head to the new node*/
        head=newEntry;

/*increment the global counter which is counting the number of entries*/
        counter++;
        q=True;
    }
    return q;
}

/*function to delete the data of any student using his ID*/
void SDB_DeleteEntry(uint8 id){
    struct SimpleDb *temp = head, *prev;

/*check if the id is in the first nodeP*/
    if (temp != NULL && temp->student_id == id){
        head = temp->next;
        free(temp);

/*decrement global counter which is counting the number of entries*/
        counter--;
        return;
    }

/*searching if the id exists*/
    while(temp != NULL && temp->student_id != id){
        prev = temp;
        temp =temp->next;
    }
    if (temp == NULL)return;
    prev->next =temp->next;
    free(temp);

/*decrement global counter which is counting the number of entries*/
    counter--;
}

/*function  to get & print the data of any student using his ID*/
bool SDB_ReadEntry(uint8 id){
    bool w;
     struct SimpleDb *temp = head;
    if (temp != NULL && temp->student_id == id){
        printf("Student id : %d\nStudent year: %d\nCourse:\tGrade:\n%d\t%d\n%d\t%d\n%d\t%d\n",temp->student_id,temp->student_year,temp->course1_id,temp->course1_grade,temp->course2_id,temp->course2_grade,temp->course3_id,temp->course3_grade);
        w=True;
        return w;
    }
    while(temp != NULL && temp->student_id != id){
        temp =temp->next;
    }
    if (temp == NULL){
        w=False;
        return w;
    }
    w=True;
    printf("Student id : %d\nStudent year: %d\nCourse:\tGrade:\n%d\t%d\n%d\t%d\n%d\t%d\n",temp->student_id,temp->student_year,temp->course1_id,temp->course1_grade,temp->course2_id,temp->course2_grade,temp->course3_id,temp->course3_grade);
    return w;
}

/*Function to get the number of entries & get the list of IDs in our Linked-List*/
void SDB_GetIdList(void){
    if (counter != 0){
    printf("Number of entries is: %d\n",counter);
    struct SimpleDb *temp = head;
    printf("List of IDs:\n");
    while(temp != NULL){
        printf("%d\n",temp->student_id);
        temp =temp->next;
    }

    }
}

/*Function to check if the id is existing*/
bool SDB_IsIdExist(uint8 ID){
    bool t;
    struct SimpleDb *temp = head;
    if (temp != NULL && temp->student_id == ID){
        printf("the id is existing\n");
        t=True;
        return t;
    }
    while(temp != NULL && temp->student_id != ID){
        temp=temp->next;
    }
    if (temp == NULL){
        t=False;
        printf("the id is not existing \n");
        return t;
    }
    t=True;
    printf("the id is existing\n");
}
