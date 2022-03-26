#include <stdio.h>
#include <stdlib.h>

typedef unsigned char uint8;
typedef struct
{
    uint8 Student_ID;
    uint8 Student_Year;
    uint8 Course1_ID;
    uint8 Course1_Grade;
    uint8 Course2_ID;
    uint8 Course2_Grade;
    uint8 Course3_ID;
    uint8 Course3_Grade;
}student;

typedef struct
{
    student *item[10];
    uint8 size;
}DB;

DB SDB = {NULL , 0};

uint8 SDB_AddEntry(uint8 id, uint8 year, uint8* subjects, uint8* grades);
uint8 SDB_IsFull();
uint8 GetUsedSize();
void SDB_DeleteEntry(uint8 id);

int main()
{

    return 0;
}




uint8 SDB_AddEntry(uint8 id, uint8 year, uint8* subjects, uint8* grades)
{
    if(SDB.size >=10) return 0; //if db is full return 0

    // check grades
    for(uint8 i = 0 ; i<3 ; ++i)
    {
        if(grades[i]>100) return 0;
    }

    //make new item
    student* newStudent = (student*) malloc(sizeof(student));
    newStudent->Student_ID = id;
    newStudent->Student_Year = year;
    newStudent->Course1_ID = subjects[0];
    newStudent->Course1_Grade = grades[0];
    newStudent->Course2_ID = subjects[1];
    newStudent->Course2_Grade = grades[1];
    newStudent->Course3_ID = subjects[2];
    newStudent->Course3_Grade = grades[2];

    SDB.item[SDB.size] = newStudent; // add new item
    SDB.size++;

    return 1;
}



uint8 SDB_IsFull()
{
    if(SDB.size >= 10) return 1;
    else return 0;
}




uint8 GetUsedSize()
{
    return SDB.size;
}




void SDB_DeleteEntry(uint8 id)
{
    uint8 index;
    for(uint8 i =0 ; i<SDB.size ; i++)
    {
        if(SDB.item[i]->Student_ID == id)
        {
            free(SDB.item[i]);
            index = i;
            break;
        }
    }

    if (index == ((SDB.size)-1))
    {
        SDB.size--;
        return;
    }

    for (uint8 i = index; i < (SDB.size)-1; ++i)
    {
        SDB.item[i] = SDB.item[i+1];
    }
}



uint8 SDB_ReadEntry(uint8 id , uint8* year, uint8* subjects, uint8* grades)
{
     uint8 index =11;
    for(uint8 i =0 ; i<SDB.size ; i++)
    {
        if(SDB.item[i]->Student_ID == id)
        {
            index = i;
            break;
        }
    }
    if(index == 11) return 0; // item not exist

    *year = SDB.item[index]->Student_Year;
    subjects[0] = SDB.item[index]->Course1_ID;
    grades[0] = SDB.item[index]->Course1_Grade;
    subjects[1] = SDB.item[index]->Course2_ID;
    grades[1] = SDB.item[index]->Course2_Grade;
    subjects[2] = SDB.item[index]->Course3_ID;
    grades[2] = SDB.item[index]->Course3_Grade;

    return 1;
}



void SDB_GetIdList(uint8* count, uint8* list)
{
    uint8 s = SDB.size;
    *count = s;
    uint8* ids = (uint8*) malloc(s);

    for (uint8 i = 0; i <s ; ++i)
    {
        ids[i] = SDB.item[i]->Student_ID;
    }
    list = ids;


}



uint8 SDB_IsIdExist(uint8 id)

{
    for(uint8 i =0 ; i<SDB.size ; i++)
    {
        if(SDB.item[i]->Student_ID == id) return 1;
    }
    return 0;

}
