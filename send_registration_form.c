#include"registration.h"

pthread_mutex_t lock;

void *thread_handler_1(void *form_option)
{
	pthread_mutex_lock(&lock); //Acquiring lock
	char form[COL_SIZE];
	char buffer[ROW_SIZE][COL_SIZE];
	int *forms_option = (int *)form_option; //Typecasting from void * to int *
	strcpy(form, Forms[*forms_option - 1]); //Copy string from source to destination
	strcat(form, "_training.xlsx"); //string concatenation
	FILE *file_pointer1 = fopen(form, "r"); //To open file in read mode
	int index = 0,i = 0, j = 0;
	char buffer_id[ROW_SIZE][COL_SIZE], buffer1_id[ROW_SIZE][COL_SIZE];

	//To store all employee id into one buffer
	while(!(feof(file_pointer1)))
	{
		fscanf(file_pointer1, "%[^\t]%*c", buffer_id[i]);
		if(buffer_id[i][0] == '0')
		{
			strcpy(buffer1_id[j], buffer_id[i]);
			j++;
		}
		i++;
	}
	fclose(file_pointer1); //To close file

	FILE *file_pointer = fopen(form, "a"); //To open file in append mode
	Employee_training_data *temp = First_field[*forms_option - 1]; //To store the address of first field of particular form to temporary pointer
	//To take user input for employee details
	while(temp != NULL)
	{
		char field[MAX_LEN];
		strcpy(field, temp->fields);
		char *ptr1 = strstr(field, "mail"); //To search for substring "mail" in string field  
		char *ptr2 = strchr(field, 'i');
		char *ptr3 = strchr(field, 'I');

		//To take user inputs for Email-id
		if(ptr1 != NULL) 
		{
			char mail_id[COL_SIZE];
			printf("Enter %s: ", temp->fields);
			__fpurge(stdin);
			scanf("%[^\n]%*c", mail_id);
			char *ptr = strchr(mail_id, '@');

			//Condition to check whether Email-id has @thundersoft.com
			if(ptr != NULL && (strcmp(ptr, "@thundersoft.com") == 0))
			{
				strcpy(buffer[index], mail_id);
				temp = temp->link;
				index++;
				continue;
			}
			else
			{
				printf("\nINFO: Please enter valid Email-id\n\n");
				continue;
			}
		}

		//To take user input for Employee id
		else if((ptr2 != NULL && (strcasecmp(ptr2, "id") == 0)) || (ptr3 != NULL && (strcasecmp(ptr3, "id") == 0)))
		{
				char emp_id[COL_SIZE];
				printf("Enter %s: ", temp->fields);
				__fpurge(stdin);
				scanf("%[^\n]%*c", emp_id);
				int flag = 0;

				//To check Employee-id is already present or not
				for(int i = 0;i < j;i++)
				{
					if(strcmp(buffer1_id[i], emp_id) == 0)
					{
						flag = 1;
						break;
					}
				}
				if(flag == 0)
				{
					//Condition to check Employee id starts with '0'
					if(emp_id[0] == '0')
					{
						strcpy(buffer[index], emp_id);
						index++;
						temp = temp->link;
						continue;
					}
					else
					{
						printf("\nINFO: Please enter valid Employee-id\n\n");
						continue;
					}
				}
				else
				{
					printf("\nINFO: Entered employee-id is already present in form\n\n");
					fclose(file_pointer); //To close file
					pthread_mutex_unlock(&lock); //To release the lock acquired
					pthread_exit(NULL); //To terminate the thread execution
				}
		}
		else
		{
			char str[MAX_LEN];
			printf("Enter %s: ", temp->fields);
			__fpurge(stdin);
			scanf("%[^\n]%*c", str);
			int i = 0, flag = 0;

			//To check string has no special characters other than space
			while(str[i] != '\0')
			{
				if(str[i] == ' ' || (str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <=122))
				{
					i++;
				}
				else
				{
					flag = 1;
					break;
				}
			}
			if(flag == 0)
			{
				strcpy(buffer[index], str);
				index++;
				temp = temp->link;
				continue;
			}
			else
			{
				printf("\nError: No special characters allowed\n\n");
				continue;
			}
		}
	}
	//To store the employee details to excel sheet and print the details in console
	printf("\nUser details: \n");
	for(int j = 0;j < index;j++)
	{
		printf("%s\t",buffer[j]);
		fprintf(file_pointer, "%s\t", buffer[j]);
	}
	printf("\n\n");
	fprintf(file_pointer, "\n");
	fclose(file_pointer); //To close file
	pthread_mutex_unlock(&lock); //To release the acquired lock
}

void *thread_handler_2(void *form_option)
{
	pthread_mutex_lock(&lock); //Acquiring lock
	char form[COL_SIZE];
	char buffer[ROW_SIZE][COL_SIZE];
	int *forms_option = (int *)form_option; //Typecasting from void * to int *
	strcpy(form, Forms[*forms_option - 1]); //Copy string from source to destination
	strcat(form, "_training.xlsx"); //string concatenation
	FILE *file_pointer1 = fopen(form, "r"); //To open file in read mode
	int index = 0,i = 0, j = 0;
	char buffer_id[ROW_SIZE][COL_SIZE], buffer1_id[ROW_SIZE][COL_SIZE];

	//To store all employee id into one buffer
	while(!(feof(file_pointer1)))
	{
		fscanf(file_pointer1, "%[^\t]%*c", buffer_id[i]);
		if(buffer_id[i][0] == '0')
		{
			strcpy(buffer1_id[j], buffer_id[i]);
			j++;
		}
		i++;
	}
	fclose(file_pointer1); //To close file

	FILE *file_pointer = fopen(form, "a"); //To open file in append mode
	Employee_training_data *temp = First_field[*forms_option - 1]; //To store the address of first field of particular form to temporary pointer
	//To take user input for employee details
	while(temp != NULL)
	{
		char field[MAX_LEN];
		strcpy(field, temp->fields);
		char *ptr1 = strstr(field, "mail"); //To search for substring "mail" in string field  
		char *ptr2 = strchr(field, 'i');
		char *ptr3 = strchr(field, 'I');

		//To take user inputs for Email-id
		if(ptr1 != NULL) 
		{
			char mail_id[COL_SIZE];
			printf("Enter %s: ", temp->fields);
			__fpurge(stdin);
			scanf("%[^\n]%*c", mail_id);
			char *ptr = strchr(mail_id, '@');

			//Condition to check whether Email-id has @thundersoft.com
			if(ptr != NULL && (strcmp(ptr, "@thundersoft.com") == 0))
			{
				strcpy(buffer[index], mail_id);
				temp = temp->link;
				index++;
				continue;
			}
			else
			{
				printf("\nINFO: Please enter valid Email-id\n\n");
				continue;
			}
		}

		//To take user input for Employee id
		else if((ptr2 != NULL && (strcasecmp(ptr2, "id") == 0)) || (ptr3 != NULL && (strcasecmp(ptr3, "Id") == 0)))
		{
				char emp_id[COL_SIZE];
				printf("Enter %s: ", temp->fields);
				__fpurge(stdin);
				scanf("%[^\n]%*c", emp_id);
				int flag = 0;

				//To check Employee-id is already present or not
				for(int i = 0;i < j;i++)
				{
					if(strcmp(buffer1_id[i], emp_id) == 0)
					{
						flag = 1;
						break;
					}
				}
				if(flag == 0)
				{
					//Condition to check Employee id starts with '0'
					if(emp_id[0] == '0')
					{
						strcpy(buffer[index], emp_id);
						index++;
						temp = temp->link;
						continue;
					}
					else
					{
						printf("\nINFO: Please enter valid Employee-id\n\n");
						continue;
					}
				}
				else
				{
					printf("\nINFO: Entered employee-id is already present in form\n\n");
					fclose(file_pointer); //To close file
					pthread_mutex_unlock(&lock); //To release the lock acquired
					pthread_exit(NULL); //To terminate the thread execution
				}
		}
		else
		{
			char str[MAX_LEN];
			printf("Enter %s: ", temp->fields);
			__fpurge(stdin);
			scanf("%[^\n]%*c", str);
			int i = 0, flag = 0;

			//To check string has no special characters other than space
			while(str[i] != '\0')
			{
				if(str[i] == ' ' || (str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <=122))
				{
					i++;
				}
				else
				{
					flag = 1;
					break;
				}
			}
			if(flag == 0)
			{
				strcpy(buffer[index], str);
				index++;
				temp = temp->link;
				continue;
			}
			else
			{
				printf("\nError: No special characters allowed\n\n");
				continue;
			}
		}
	}
	//To store the employee details to excel sheet and print the details in console
	printf("\nUser details: \n");
	for(int j = 0;j < index;j++)
	{
		printf("%s\t",buffer[j]);
		fprintf(file_pointer, "%s\t", buffer[j]);
	}
	printf("\n\n");
	fprintf(file_pointer, "\n");
	fclose(file_pointer); //To close file
	pthread_mutex_unlock(&lock); //To release the acquired lock
}

void *thread_handler_3(void *form_option)
{
	pthread_mutex_lock(&lock); //Acquiring lock
	char form[COL_SIZE];
	char buffer[ROW_SIZE][COL_SIZE];
	int *forms_option = (int *)form_option; //Typecasting from void * to int *
	strcpy(form, Forms[*forms_option - 1]); //Copy string from source to destination
	strcat(form, "_training.xlsx"); //string concatenation
	FILE *file_pointer1 = fopen(form, "r"); //To open file in read mode
	int index = 0,i = 0, j = 0;
	char buffer_id[ROW_SIZE][COL_SIZE], buffer1_id[ROW_SIZE][COL_SIZE];

	//To store all employee id into one buffer
	while(!(feof(file_pointer1)))
	{
		fscanf(file_pointer1, "%[^\t]%*c", buffer_id[i]);
		if(buffer_id[i][0] == '0')
		{
			strcpy(buffer1_id[j], buffer_id[i]);
			j++;
		}
		i++;
	}
	fclose(file_pointer1); //To close file

	FILE *file_pointer = fopen(form, "a"); //To open file in append mode
	Employee_training_data *temp = First_field[*forms_option - 1]; //To store the address of first field of particular form to temporary pointer
	//To take user input for employee details
	while(temp != NULL)
	{
		char field[MAX_LEN];
		strcpy(field, temp->fields);
		char *ptr1 = strstr(field, "mail"); //To search for substring "mail" in string field  
		char *ptr2 = strchr(field, 'i');
		char *ptr3 = strchr(field, 'I');

		//To take user inputs for Email-id
		if(ptr1 != NULL) 
		{
			char mail_id[COL_SIZE];
			printf("Enter %s: ", temp->fields);
			__fpurge(stdin);
			scanf("%[^\n]%*c", mail_id);
			char *ptr = strchr(mail_id, '@');

			//Condition to check whether Email-id has @thundersoft.com
			if(ptr != NULL && (strcmp(ptr, "@thundersoft.com") == 0))
			{
				strcpy(buffer[index], mail_id);
				temp = temp->link;
				index++;
				continue;
			}
			else
			{
				printf("\nINFO: Please enter valid Email-id\n\n");
				continue;
			}
		}

		//To take user input for Employee id
		else if((ptr2 != NULL && (strcasecmp(ptr2, "id") == 0)) || (ptr3 != NULL && (strcasecmp(ptr3, "Id") == 0)))
		{
				char emp_id[COL_SIZE];
				printf("Enter %s: ", temp->fields);
				__fpurge(stdin);
				scanf("%[^\n]%*c", emp_id);
				int flag = 0;

				//To check Employee-id is already present or not
				for(int i = 0;i < j;i++)
				{
					if(strcmp(buffer1_id[i], emp_id) == 0)
					{
						flag = 1;
						break;
					}
				}
				if(flag == 0)
				{
					//Condition to check Employee id starts with '0'
					if(emp_id[0] == '0')
					{
						strcpy(buffer[index], emp_id);
						index++;
						temp = temp->link;
						continue;
					}
					else
					{
						printf("\nINFO: Please enter valid Employee-id\n\n");
						continue;
					}
				}
				else
				{
					printf("\nINFO: Entered employee-id is already present in form\n\n");
					fclose(file_pointer); //To close file
					pthread_mutex_unlock(&lock); //To release the lock acquired
					pthread_exit(NULL); //To terminate the thread execution
				}
		}
		else
		{
			char str[MAX_LEN];
			printf("Enter %s: ", temp->fields);
			__fpurge(stdin);
			scanf("%[^\n]%*c", str);
			int i = 0, flag = 0;

			//To check string has no special characters other than space
			while(str[i] != '\0')
			{
				if(str[i] == ' ' || (str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <=122))
				{
					i++;
				}
				else
				{
					flag = 1;
					break;
				}
			}
			if(flag == 0)
			{
				strcpy(buffer[index], str);
				index++;
				temp = temp->link;
				continue;
			}
			else
			{
				printf("\nError: No special characters allowed\n\n");
				continue;
			}
		}
	}
	//To store the employee details to excel sheet and print the details in console
	printf("\nUser details: \n");
	for(int j = 0;j < index;j++)
	{
		printf("%s\t",buffer[j]);
		fprintf(file_pointer, "%s\t", buffer[j]);
	}
	printf("\n\n");
	fprintf(file_pointer, "\n");
	fclose(file_pointer); //To close file
	pthread_mutex_unlock(&lock); //To release the acquired lock
}

void send_training_registration_form()
{
	int form_option;
	int count = 1;
	if(Forms_count > 0)
	{
		// To list all the trainings available
		printf("\nAvailable trainings are: \n");
		for(int i = 0;i < Forms_count;i++)
		{
			printf("%d. %s\n", i+1, Forms[i]);
		}
		while(1)
		{
			printf("Enter the option to select particular training registration form: ");
			scanf("%d", &form_option);
			if(count < 3)
			{
				if(form_option <= Forms_count)
				{
					pthread_t thread[3];
					//Create threads and take three different user inputs
					pthread_create(&thread[0], NULL, thread_handler_1, (void *)&form_option);
					pthread_create(&thread[1], NULL, thread_handler_2, (void *)&form_option);
					pthread_create(&thread[2], NULL, thread_handler_3, (void *)&form_option);
					pthread_join(thread[0], NULL); //To wait until particular thread termaination
					pthread_join(thread[1], NULL);
					pthread_join(thread[2], NULL);
					main();
				}
				else
				{
					printf("\nError: Invalid option\n\n");
					count++;
					continue;
				}
			}
			else
			{
				printf("\nError: User entered invalid option for three times\n\n");
				main();
			}
		}
	}
	else
	{
		printf("No trainings available\n");
		main();
	}
}
