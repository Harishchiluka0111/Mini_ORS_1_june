#include"voting_response.h"
#include"voting_request.h"

/******************************Function definition of voting_response()***************************************************************************/

pthread_mutex_t lock; 

void *thread_handler1(void *Form_option)
{
	pthread_mutex_lock(&lock);                                               //acquiring the lock

	char form[FORM_LEN];                                                     //for storing form name
	int *form_option = (int *)Form_option;                                   //typecasting from void* to int*
	strcpy(form, Forms[*form_option - 1]);                                   //copy forms of particular index name to form character array
	strcat(form, "_request.xlsx");                                           //concatenate the form name with .xlsx 

	char buffer[BUF_ROW][BUF_COL];                                          //Buffer global variable to store the user details after every thread execution
	char buffer_id[BUF_ROW][BUF_COL], buffer1_id[BUF_ROW][BUF_COL];         //buffers for storing all user id's
	int buf_index = 0, i = 0, j = 0; 	                                 //for storing index value of Buffers

	FILE *file_pointer1 = fopen(form, "r");                                  //opens a particular file in read mode
	while(!feof(file_pointer1))                                              //loop until it reaches end of file
	{
		fscanf(file_pointer1, "%s\t", buffer_id[i]);                     //reading all content file to buffer
		if(buffer_id[i][0] =='0')                                        //checking whether fields have id
		{
			strcpy(buffer1_id[j], buffer_id[i]);                     //if id present copy all id's to another buffer
			j++;
		}
		i++;
	}
	fclose(file_pointer1);                                                  //close file opened in read mode

	FILE *file_pointer = fopen(form, "a");                                   //opens a particular form in append mode
	Vote *temp = Root[*form_option - 1];                                     //temp pointer of type structure to point to first field

	while( temp != NULL)                                  //Looping untill temp not equal to NULL
	{
		char field[MAX_LEN];                         //character array to store field name
		strcpy(field, temp->fields);                 //copy temp field name to field

		char *ptr1 = strstr(field, "mail");          //ptr1 to store the return pointer of strstr after searching "Email-id" with field name
		char *ptr2 = strchr(field, 'i');             //ptr2 to store the return pointer of strchr after searching 'i' with field name

		//This case is to check the Employee email id field
		if(ptr1 != NULL)
		{
			char email_id[MAX_LEN];                                        //character array to scan the input from user
			printf("Enter %s: ", temp->fields);
			__fpurge(stdin);
			scanf("%[^\n]s", email_id);
			char *ptr = strchr(email_id, '@');                            //searching for '@' in user str

			if((ptr != NULL) && (strcmp(ptr, "@thundersoft.com") == 0))  //check for comparing the ptr value with "@thundersoft.com" returns 0
			{
				strcpy(buffer[buf_index], email_id);                 //copying that str value to buffer
				temp = temp->link;                                   //move to next node
				buf_index++;                 
				continue;                                           //check for condition again
			}
			else
			{
				printf("\nINFO: Please enter valid Email-id\n\n");
				continue;
			}
		}

		//This case is to check the employee id field
		else if(ptr2 != NULL && (strcasecmp(ptr2, "id") == 0))
		{
			char emp_id[MAX_LEN];
			int flag = 0;				        //character array to scan the input from user
			printf("Enter %s: ", temp->fields);
			__fpurge(stdin);
			scanf("%[^\n]s", emp_id);

			for(int i=0; i<j; i++)                         //loop for checking employee id is already present or not
			{
				if(strcmp(emp_id, buffer1_id[i]) == 0)
				{
					flag = 1;
					break;
				}
			}

			if(flag == 0)
			{
				if(emp_id[0] == '0')                                   //checking for employee id starts from 0
				{
					strcpy(buffer[buf_index], emp_id);            //copying that str value to buffer
					buf_index++;
					temp = temp->link;                            //move to next node
					continue;                                    //check for condition again
				}
				else
				{
					printf("\nINFO: Please enter valid Employee id\n\n");
					continue;
				}
			}
			else
			{
				printf("\nINFO: Current user already given response\n\n");
				fclose(file_pointer);                                                  //close file
				pthread_mutex_unlock(&lock);                                           //releases the lock acquired 
				pthread_exit(NULL);                                                    //stop thread execution                                    
			}
		}			

		//This case is for other all generic fields created by the user
		else                 
		{
			char str[MAX_LEN];                                 //character array to scan the input from user
			printf("Enter %s: ", temp->fields);
			__fpurge(stdin);
			scanf("%[^\n]s", str);
			int i = 0, flag = 0;

			while(str[i] != '\0')
			{
				if(str[i] == ' ' || (str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <=122))           //check for emp details contains special character or not 
				{
					i++;
				}
				else
				{
					flag = 1;
					printf("\nINFO: Special characters are not allowed\n\n");
					break;                                                                                 //break the loop
				}
			}
			if(flag == 0)
			{
				strcpy(buffer[buf_index], str);                 //copying that str value to buffer
				buf_index++;
				temp = temp->link;                              //move to next node
				continue;                                       //check for condition again           
			}
		}
	}

	printf("\nUser details: \n");
	for(int i = 0; i < buf_index; i++)                                        //loop to store the user details to excel form and display each user details from buffer
	{
		printf("%s\t", buffer[i]);
		fprintf(file_pointer, "%s\t", buffer[i]);
	}
	printf("\n\n");
	fprintf(file_pointer, "\n");
	fclose(file_pointer);                                                  //close file
	pthread_mutex_unlock(&lock);                                           //Release the lock acquired
}

void *thread_handler2(void *Form_option)
{
	pthread_mutex_lock(&lock);                                               //acquiring the lock

	char form[FORM_LEN];                                                     //for storing form name
	int *form_option = (int *)Form_option;                                   //typecasting from void* to int*
	strcpy(form, Forms[*form_option - 1]);                                   //copy forms of particular index name to form character array
	strcat(form, "_request.xlsx");                                           //concatenate the form name with .xlsx 

	char buffer[BUF_ROW][BUF_COL];                                          //Buffer global variable to store the user details after every thread execution
	char buffer_id[BUF_ROW][BUF_COL], buffer1_id[BUF_ROW][BUF_COL];         //buffers for storing all user id's
	int buf_index = 0, i = 0, j = 0; 	                                 //for storing index value of Buffers

	FILE *file_pointer1 = fopen(form, "r");                                  //opens a particular file in read mode
	while(!feof(file_pointer1))                                              //loop until it reaches end of file
	{
		fscanf(file_pointer1, "%s\t", buffer_id[i]);                     //reading all content file to buffer
		if(buffer_id[i][0] =='0')                                        //checking whether fields have id
		{
			strcpy(buffer1_id[j], buffer_id[i]);                     //if id present copy all id's to another buffer
			j++;
		}
		i++;
	}
	fclose(file_pointer1);                                                  //close file opened in read mode

	FILE *file_pointer = fopen(form, "a");                                   //opens a particular form in append mode
	Vote *temp = Root[*form_option - 1];                                     //temp pointer of type structure to point to first field

	while( temp != NULL)                                  //Looping untill temp not equal to NULL
	{
		char field[MAX_LEN];                         //character array to store field name
		strcpy(field, temp->fields);                 //copy temp field name to field

		char *ptr1 = strstr(field, "mail");          //ptr1 to store the return pointer of strstr after searching "Email-id" with field name
		char *ptr2 = strchr(field, 'i');             //ptr2 to store the return pointer of strchr after searching 'i' with field name


		//This case is to check the Employee email id field
		if(ptr1 != NULL)
		{
			char email_id[MAX_LEN];                                        //character array to scan the input from user
			printf("Enter %s: ", temp->fields);
			__fpurge(stdin);
			scanf("%[^\n]s", email_id);
			char *ptr = strchr(email_id, '@');                            //searching for '@' in user str

			if((ptr != NULL) && (strcmp(ptr, "@thundersoft.com") == 0))  //check for comparing the ptr value with "@thundersoft.com" returns 0
			{
				strcpy(buffer[buf_index], email_id);                 //copying that str value to buffer
				temp = temp->link;                                   //move to next node
				buf_index++;                 
				continue;                                           //check for condition again
			}
			else
			{
				printf("\nINFO: Please enter valid Email-id\n\n");
				continue;
			}
		}


		//This case is to check the Employee id field
		else if(ptr2 != NULL && (strcasecmp(ptr2, "id") == 0))
		{
			char emp_id[MAX_LEN];
			int flag = 0;				        //character array to scan the input from user
			printf("Enter %s: ", temp->fields);
			__fpurge(stdin);
			scanf("%[^\n]s", emp_id);

			for(int i=0; i<j; i++)                         //loop for checking employee id is already present or not
			{
				if(strcmp(emp_id, buffer1_id[i]) == 0)
				{
					flag = 1;
					break;
				}
			}

			if(flag == 0)
			{
				if(emp_id[0] == '0')                                   //checking for employee id starts from 0
				{
					strcpy(buffer[buf_index], emp_id);            //copying that str value to buffer
					buf_index++;
					temp = temp->link;                            //move to next node
					continue;                                    //check for condition again
				}
				else
				{
					printf("\nINFO: Please enter valid Employee id\n\n");
					continue;
				}
			}
			else
			{
				printf("\nINFO: Current user already given response\n\n");
				fclose(file_pointer);                                                  //close file
				pthread_mutex_unlock(&lock);                                           //releases the lock acquired 
				pthread_exit(NULL);                                                    //stop thread execution                                    
			}
		}


		//This case is to check all other generic fields given by user
		else                                                         
		{
			char str[MAX_LEN];                                 //character array to scan the input from user
			printf("Enter %s: ", temp->fields);
			__fpurge(stdin);
			scanf("%[^\n]s", str);
			int i = 0, flag = 0;

			while(str[i] != '\0')
			{
				if(str[i] == ' ' || (str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <=122))        //check for emp details contains special character or not 
				{
					i++;
				}
				else
				{
					flag = 1;
					printf("\nINFO: Special characters are not allowed\n\n");
					break;                                                                              //break the loop
				}
			}
			if(flag == 0)
			{
				strcpy(buffer[buf_index], str);                 //copying that str value to buffer
				buf_index++;
				temp = temp->link;                              //move to next node
				continue;                                       //check for condition again           
			}
		}
	}

	printf("\nUser details: \n");
	for(int i = 0; i < buf_index; i++)                                        //loop to store the user details to excel form and display each user details from buffer
	{
		printf("%s\t", buffer[i]);
		fprintf(file_pointer, "%s\t", buffer[i]);
	}
	printf("\n\n");
	fprintf(file_pointer, "\n");
	fclose(file_pointer);                                                  //close file
	pthread_mutex_unlock(&lock);                                           //Release the lock acquired
}

void *thread_handler3(void *Form_option)
{
	pthread_mutex_lock(&lock);                                               //acquiring the lock

	char form[FORM_LEN];                                                     //for storing form name
	int *form_option = (int *)Form_option;                                   //typecasting from void* to int*
	strcpy(form, Forms[*form_option - 1]);                                   //copy forms of particular index name to form character array
	strcat(form, "_request.xlsx");                                           //concatenate the form name with .xlsx 

	char buffer[BUF_ROW][BUF_COL];                                          //Buffer global variable to store the user details after every thread execution
	char buffer_id[BUF_ROW][BUF_COL], buffer1_id[BUF_ROW][BUF_COL];         //buffers for storing all user id's
	int buf_index = 0, i = 0, j = 0; 	                                 //for storing index value of Buffers

	FILE *file_pointer1 = fopen(form, "r");                                  //opens a particular file in read mode
	while(!feof(file_pointer1))                                              //loop until it reaches end of file
	{
		fscanf(file_pointer1, "%s\t", buffer_id[i]);                     //reading all content file to buffer
		if(buffer_id[i][0] =='0')                                        //checking whether fields have id
		{
			strcpy(buffer1_id[j], buffer_id[i]);                     //if id present copy all id's to another buffer
			j++;
		}
		i++;
	}
	fclose(file_pointer1);                                                  //close file opened in read mode

	FILE *file_pointer = fopen(form, "a");                                   //opens a particular form in append mode
	Vote *temp = Root[*form_option - 1];                                     //temp pointer of type structure to point to first field

	while( temp != NULL)                                  //Looping untill temp not equal to NULL
	{
		char field[MAX_LEN];                         //character array to store field name
		strcpy(field, temp->fields);                 //copy temp field name to field

		char *ptr1 = strstr(field, "mail");          //ptr1 to store the return pointer of strstr after searching "Email-id" with field name
		char *ptr2 = strchr(field, 'i');             //ptr2 to store the return pointer of strchr after searching 'i' with field name


		//This case is to check the Employee email id field
		if(ptr1 != NULL)
		{
			char email_id[MAX_LEN];                                        //character array to scan the input from user
			printf("Enter %s: ", temp->fields);
			__fpurge(stdin);
			scanf("%[^\n]s", email_id);
			char *ptr = strchr(email_id, '@');                            //searching for '@' in user str

			if((ptr != NULL) && (strcmp(ptr, "@thundersoft.com") == 0))  //check for comparing the ptr value with "@thundersoft.com" returns 0
			{
				strcpy(buffer[buf_index], email_id);                 //copying that str value to buffer
				temp = temp->link;                                   //move to next node
				buf_index++;                 
				continue;                                           //check for condition again
			}
			else
			{
				printf("\nINFO: Please enter valid Email-id\n\n");
				continue;
			}
		}

		//This case is to check the Employee id field
		else if(ptr2 != NULL && (strcasecmp(ptr2, "id") == 0))
		{
			char emp_id[MAX_LEN];
			int flag = 0;				        //character array to scan the input from user
			printf("Enter %s: ", temp->fields);
			__fpurge(stdin);
			scanf("%[^\n]s", emp_id);

			for(int i=0; i<j; i++)                         //loop for checking employee id is already present or not
			{
				if(strcmp(emp_id, buffer1_id[i]) == 0)
				{
					flag = 1;
					break;
				}
			}

			if(flag == 0)
			{
				if(emp_id[0] == '0')                                   //checking for employee id starts from 0
				{
					strcpy(buffer[buf_index], emp_id);            //copying that str value to buffer
					buf_index++;
					temp = temp->link;                            //move to next node
					continue;                                    //check for condition again
				}
				else
				{
					printf("\nINFO: Please enter valid Employee id\n\n");
					continue;
				}
			}
			else
			{
				printf("\nINFO: Current user already given response\n\n");
				fclose(file_pointer);                                                  //close file
				pthread_mutex_unlock(&lock);                                           //releases the lock acquired 
				pthread_exit(NULL);                                                    //stop thread execution                                    
			}
		}


		//This case is to check all other generic fields created by user
		else                                                         
		{
			char str[MAX_LEN];                                 //character array to scan the input from user
			printf("Enter %s: ", temp->fields);
			__fpurge(stdin);
			scanf("%[^\n]s", str);
			int i = 0, flag = 0;

			while(str[i] != '\0')
			{
				if(str[i] == ' ' || (str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <=122))               //check for emp details contains special character or not 
				{
					i++;
				}
				else
				{
					flag = 1;
					printf("\nINFO: Special characters are not allowed\n\n");
					break;                                                                                    //break the loop
				}
			}
			if(flag == 0)
			{
				strcpy(buffer[buf_index], str);                 //copying that str value to buffer
				buf_index++;
				temp = temp->link;                              //move to next node
				continue;                                       //check for condition again           
			}
		}
	}

	printf("\nUser details: \n");
	for(int i = 0; i < buf_index; i++)                                     //loop to store the user details to excel form and display each user details from buffer
	{
		printf("%s\t", buffer[i]);
		fprintf(file_pointer, "%s\t", buffer[i]);
	}
	printf("\n\n");
	fprintf(file_pointer, "\n");
	fclose(file_pointer);                                                  //close file
	pthread_mutex_unlock(&lock);                                           //Release the lock acquired
}	

void voting_response()
{
	int Form_option;                                                    //Global variable to choose the created voting forms 
	int flag = 1,i = 0;                                                //flag to count number of invalid options
	if(Count_forms > 0)                                                //Checking for count greater than 0 to display created forms
	{
		printf("\nAvailable voting forms are: \n");                  
		for(i = 0; i < Count_forms; i++)                           //Iterating over the Count for displaying available voting forms
		{
			printf("%d. %s\n", i + 1, Forms[i]);
		}
		while(1)                                                  //to make this process alive untill program terminates
		{
			printf("\nPlease select from available voting forms for providing response : ");
			scanf("%d", &Form_option);

			if(flag < 3)                                      //check for count of users invalid option  
			{
				if(Form_option > Count_forms)
				{
					printf("\nINFO: Please enter valid option\n");
					flag++;
				}
				else
				{
					pthread_t thread[THREADS_COUNT];
					pthread_create(&thread[0], NULL, thread_handler1, (void *)&Form_option);   //creating thread1 with hand
					pthread_create(&thread[1], NULL, thread_handler1, (void *)&Form_option);   //creating thread1 with hand
					pthread_create(&thread[2], NULL, thread_handler1, (void *)&Form_option);   //creating thread1 with hand
					pthread_join(thread[0], NULL);                                             //wait untill thread1 completes its execution
					pthread_join(thread[1], NULL);                                             //wait untill thread2 completes its execution
					pthread_join(thread[2], NULL);	                                           //wait untill thread3 completes its execution
					main();                                                                    //Back to main menu after giving response
				}
			}
			else
			{
				printf("\nINFO: You entered invalid option 3 times\n\n");
				main();                                                                           //Back to main menu if user enters invalid option three times
			}
		}
	}
	else
	{
		printf("\nINFO: No voting forms are vailable\n\n");
		main();                                                                                          //Back to main menu if there are no voting forms created
	}
}

