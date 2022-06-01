
/****************************************DESCRIPTION***********************************************************************/

/*
1. Name of thie module                          : Voting Response
2. Date of creation                             : 27/5/2022
3. Author of Module                             : Sindhushree J M
4. Description of module                        : The purpose of this module is to collect voting response from the users for the voting request conducted, then it is 
                                                  recorded in the excel form created.
5. Different functions supported in this module : voting_response()	
6. Global variables accessed/modified by module : No global variables used
7. Revision/Modification History                : 
*/

/**************************************************************************************************************************/


/**************************HEADER FILES*****************************/
#include"header.h"
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdio_ext.h>


/***********************MACROS****************************************/
#define FORM_LEN 30
#define BUF_ROW 30
#define BUF_COL 30
#define MAX_LEN 80
#define THREADS_COUNT 3

/***************FUNCTION PROTOTYPES*********************************/                  
void voting_response();

