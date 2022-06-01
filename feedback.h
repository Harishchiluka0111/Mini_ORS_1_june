/*****************************************DESCRIPTION*******************************************************************/

/*

1. Name of the module                           : feedback
2. Date of creation                             : 27/5/2022
3. Author of Module                             : Tejaswini S P
4. Description of module                        : The purpose of this module is to collect conducted training forms and give the feedback to that conducted trainings 
5. Different functions supported in this module : feedback_module()
                                                  feedback(int)
*/

/**********************************************************************************************************************/

/**************************HEADER FILES*****************************/
#include<stdio.h>
#include<string.h>
#include<stdio_ext.h>
#include<pthread.h>
#include"header.h"


/************************MACROS**********************************/
#define SIZE 256
#define ROW_SIZE 30
#define COL_SIZE 30
#define FIELD_SIZE 80

/*************************structure for this module**************/
typedef struct employee_f
{
char emp_id[FIELD_SIZE];
char emp_name[FIELD_SIZE];
char emp_email[FIELD_SIZE];
char reporting_mgr[FIELD_SIZE];
char feedback[SIZE];
}Employee_training_feedback;


/*************************FUNCTION PROTOTYPES**********************/
void feedback_module();          
void feedback(int option);
