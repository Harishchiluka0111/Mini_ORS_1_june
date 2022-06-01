//*******************************************Module Description*******************************************************

/*
1. Module name: Training registration module
2. Date: 27-05-2022
3. Author name: Chiluka Harish(Create and Delete) and Rakshitha S(Send registration form)
4. Description: The purpose of this module is to create training registration form when user wants to create form, Delete the 
                particular  registration form based on the user choice and send the registration form to fill the user details 
                using threads and store the user details in excel sheet.
5. Different functions supported in this module: registration(), create_training_registration_form(), delete_training_registration_form()
                                                 and send_training_registration_form()
6. Global variables accessed by module: Forms_count, Forms and First_field[COL_SIZE]
*/

//**************************************Header files****************************************

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<stdio_ext.h>
#include"header.h"

//*************************************Macro*************************************************

#define ROW_SIZE 30
#define COL_SIZE 30
#define MAX_LEN 80

//***********************************Structure declaration*************************************

typedef struct employee_data
{
    char fields[COL_SIZE];
    struct employee_data *link;
}Employee_training_data;

//***********************************Global variables*******************************************

int Forms_count; //Variable to store count of training registration forms created
char Forms[ROW_SIZE][COL_SIZE]; //2d-array to store names of trainings
Employee_training_data *First_field[COL_SIZE]; //An array of pointer to store the address of first field in each training registration form

//***********************************Function declarations*****************************************

void registration();
void create_training_registration_form();
void delete_training_registration_form();
void send_training_registration_form();

