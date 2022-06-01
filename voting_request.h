#ifndef HEADER_H
#define HEADER_H

/*************************************************************************************/
// i.	Name of the module=                           Voting request module:header.h
//ii.	Date of creation=                             27/5/2022
//iii.	Author of module=                             Dipa Mantre
//iv.	Description of module=                        Creating voting request forms
//v.	Different functions supported in the module=  1.voting_request
//                                                    2.create_voting_req_form
//                                                    3.delete_voting_req_form
/************************************************************************************/        
#include"header.h"   //main header file inclusion
#include<stdio.h>    //for std input or output fun
#include<stdlib.h>   //for NULL
#include<string.h>   // for string operations
#include<stdio_ext.h>//for fpurge to clear buffer

/****************macros**************************************************************/
#define MAX 50
#define ROW 20
#define COL 30

/***************Structure declaration************************/

typedef struct Voting
{
	char fields[MAX];       
	struct Voting *link;
}Vote;

/***************Global variable declarations***************/

int Count_forms;	                                     //count of forms created
char Forms[ROW][COL];	                     //for storing already created forms

Vote *Root[MAX];                                           //to store address of each field

/***************Function declartions**********************/
void voting_request();
void create_voting_req_form();                  //create voting requested form
void delete_voting_req_form();                  //create voting requested form
#endif 	                              //HEADER_H
