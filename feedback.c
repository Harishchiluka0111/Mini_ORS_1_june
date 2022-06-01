#include"feedback.h"
#include"registration.h"


pthread_mutex_t lock;   //declaring mutex variable

void employee_name(char *user_buffer);   //employee_name function declaration
void employee_email(char *user_buffer);  //employee_email function declation
void employee_reporting_mgr(char *user_buffer);   //employee_rporting_magr function declaration
void employee_feedback(char *user_buffer);        //employee_feedback function declaration

void *feedback_thread1(void *t1)        //thread1 definition
{
	pthread_mutex_lock(&lock); //to acquire the lock
	char form[SIZE]; //char array to store one training form name
	char form1[SIZE];  //char array to store one feedback form name
	char emp_id[SIZE];     //char array to store user inputted emp_id to takefeedback
	char buffer1[ROW_SIZE][COL_SIZE];  //buffer to store all the fields in the training xl file
	char buffer2[ROW_SIZE][COL_SIZE];  //buffer to store only the emp_id fron that traing xl file
	char user_buffer1[SIZE],user_buffer2[SIZE],user_buffer3[SIZE],user_buffer4[SIZE],user_buffer5[SIZE];  //buffer to copy the user inputted emp_id,emp_name,emp_emai,reporting_mgr,feedback from the user
	int *option = (int *)t1; 
	strcpy(form, Forms[*option - 1]);  //copying name of the training name to form
	strcat(form, "_training.xlsx");   //concatenating _training.xlsx into form
	FILE *file_pointer = fopen(form, "r");   //opening the file in read mode
	int i = 0,j = 0,k=0,user_count=0,flag;


	while(!feof(file_pointer))    //Reading whole conducted training xl file 
	{
		fscanf(file_pointer,"%[^\t]%*c",buffer1[i]);
		if(buffer1[i][0]== '0')   //checking for emp_id 
		{
			strcpy(buffer2[j],buffer1[i]);    //storing that emp_id into another buffer
			j++;
		}
		i++;
	}
	fclose(file_pointer);   //closing the file 

	strcpy(form1, Forms[*option - 1]);   //copying the training nameto form1
	strcat(form1, "_training_feedback.xlsx");     //concatenating the _training.xlsx into form1
	FILE *fp2 = fopen(form1, "a");            //opening the feedback xl sheet in append mode
	if(fp2==NULL)           //checking if the file is opened or not
	{
		printf("Cannot open file\n");
	}

	printf("Enter the Emp_id:");      //taking the emp_id from user
	__fpurge(stdin);                 //clear the buffer
	scanf("%s",emp_id);

	for(i=0;i<j;i++)
	{
		if(strcmp(buffer2[i],emp_id)==0)       //checking if the user entered emp_id is registested for the training
		{
			flag=1;
			break;
		}
	}
	if(flag==0)        //if not registed for the training then exit from this thread
	{
		printf("Can't give the feedback since this user has not registered for the training\n");
		fclose(fp2);
		pthread_mutex_unlock(&lock);  //to release the lock
		pthread_exit(NULL);   //to exit from the thread
	}
	else
	{
		if(emp_id[0] == '0')   //checking if the user entered emp_id is starting from 0
		{
			strcpy(user_buffer1, emp_id);             //storing the emp_id into buffer
		}

		employee_name(user_buffer2);   //calling employee_name function to take emp_name from the user
		employee_email(user_buffer3);  //calling emloyee_email function to take emp_email fromthe user
		employee_reporting_mgr(user_buffer4);   //calling the employee_reporting_mgr function to take retporting manager name
		employee_feedback(user_buffer5);   //calling the employee_feedback function to take feedback from the user		

		printf("User details: \n");   
		printf("%s\t%s\t%s\t%s\t%s\n",user_buffer1,user_buffer2,user_buffer3,user_buffer4,user_buffer5); //to display user details on console
		fprintf(fp2,"%s\t%s\t%s\t%s\t%s\n",user_buffer1,user_buffer2,user_buffer3,user_buffer4,user_buffer5); //storing user details into feedback xl sheet

		fclose(fp2); //to close the file
		pthread_mutex_unlock(&lock);     //to release the lock
	}
}


void *feedback_thread2(void *t2)
{
	pthread_mutex_lock(&lock); //to acquire the lock
	char form[SIZE]; //char array to store one training form name
	char form1[SIZE];  //char array to store one feedback form name
	char emp_id[SIZE];     //char array to store user inputted emp_id to takefeedback
	char buffer1[ROW_SIZE][COL_SIZE];  //buffer to store all the fields in the training xl file
	char buffer2[ROW_SIZE][COL_SIZE];  //buffer to store only the emp_id fron that traing xl file
	char user_buffer1[SIZE],user_buffer2[SIZE],user_buffer3[SIZE],user_buffer4[SIZE],user_buffer5[SIZE];  //buffer to copy the user inputted emp_id,emp_name,emp_emai,reporting_mgr,feedback from the user
	int *option = (int *)t2; 
	strcpy(form, Forms[*option - 1]);  //copying name of the training name to form
	strcat(form, "_training.xlsx");   //concatenating _training.xlsx into form
	FILE *file_pointer = fopen(form, "r");   //opening the file in read mode
	int i = 0,j = 0,k=0,user_count=0,flag;


	while(!feof(file_pointer))    //Reading whole conducted training xl file 
	{
		fscanf(file_pointer,"%[^\t]%*c",buffer1[i]);
		if(buffer1[i][0]== '0')   //checking for emp_id 
		{
			strcpy(buffer2[j],buffer1[i]);    //storing that emp_id into another buffer
			j++;
		}
		i++;
	}
	fclose(file_pointer);   //closing the file 

	strcpy(form1, Forms[*option - 1]);   //copying the training nameto form1
	strcat(form1, "_training_feedback.xlsx");     //concatenating the _training.xlsx into form1
	FILE *fp2 = fopen(form1, "a");            //opening the feedback xl sheet in append mode
	if(fp2==NULL)           //checking if the file is opened or not
	{
		printf("Cannot open file\n");
	}

	printf("Enter the Emp_id:");      //taking the emp_id from user
	__fpurge(stdin);                 //clear the buffer
	scanf("%s",emp_id);

	for(i=0;i<j;i++)
	{
		if(strcmp(buffer2[i],emp_id)==0)       //checking if the user entered emp_id is registested for the training
		{
			flag=1;
			break;
		}
	}
	if(flag==0)        //if not registed for the training then exit from this thread
	{
		printf("Can't give the feedback since this user has not registered for the training\n");
		fclose(fp2);
		pthread_mutex_unlock(&lock);  //to release the lock
		pthread_exit(NULL);   //to exit from the thread
	}
	else
	{
		if(emp_id[0] == '0')   //checking if the user entered emp_id is starting from 0
		{
			strcpy(user_buffer1, emp_id);             //storing the emp_id into buffer
		}

		employee_name(user_buffer2);   //calling employee_name function to take emp_name from the user
		employee_email(user_buffer3);  //calling emloyee_email function to take emp_email fromthe user
		employee_reporting_mgr(user_buffer4);   //calling the employee_reporting_mgr function to take retporting manager name
		employee_feedback(user_buffer5);   //calling the employee_feedback function to take feedback from the user		

		printf("User details: \n");   
		printf("%s\t%s\t%s\t%s\t%s\n",user_buffer1,user_buffer2,user_buffer3,user_buffer4,user_buffer5); //to display user details on console
		fprintf(fp2,"%s\t%s\t%s\t%s\t%s\n",user_buffer1,user_buffer2,user_buffer3,user_buffer4,user_buffer5); //storing user details into feedback xl sheet

		fclose(fp2); //to close the file
		pthread_mutex_unlock(&lock);     //to release the lock
	}
}



void *feedback_thread3(void *t3)
{
	pthread_mutex_lock(&lock); //to acquire the lock
	char form[SIZE]; //char array to store one training form name
	char form1[SIZE];  //char array to store one feedback form name
	char emp_id[SIZE];     //char array to store user inputted emp_id to takefeedback
	char buffer1[ROW_SIZE][COL_SIZE];  //buffer to store all the fields in the training xl file
	char buffer2[ROW_SIZE][COL_SIZE];  //buffer to store only the emp_id fron that traing xl file
	char user_buffer1[SIZE],user_buffer2[SIZE],user_buffer3[SIZE],user_buffer4[SIZE],user_buffer5[SIZE];  //buffer to copy the user inputted emp_id,emp_name,emp_emai,reporting_mgr,feedback from the user
	int *option = (int *)t3; 
	strcpy(form, Forms[*option - 1]);  //copying name of the training name to form
	strcat(form, "_training.xlsx");   //concatenating _training.xlsx into form
	FILE *file_pointer = fopen(form, "r");   //opening the file in read mode
	int i = 0,j = 0,k=0,user_count=0,flag;


	while(!feof(file_pointer))    //Reading whole conducted training xl file 
	{
		fscanf(file_pointer,"%[^\t]%*c",buffer1[i]);
		if(buffer1[i][0]== '0')   //checking for emp_id 
		{
			strcpy(buffer2[j],buffer1[i]);    //storing that emp_id into another buffer
			j++;
		}
		i++;
	}
	fclose(file_pointer);   //closing the file 

	strcpy(form1, Forms[*option - 1]);   //copying the training nameto form1
	strcat(form1, "_training_feedback.xlsx");     //concatenating the _training.xlsx into form1
	FILE *fp2 = fopen(form1, "a");            //opening the feedback xl sheet in append mode
	if(fp2==NULL)           //checking if the file is opened or not
	{
		printf("Cannot open file\n");
	}

	printf("Enter the Emp_id:");      //taking the emp_id from user
	__fpurge(stdin);                 //clear the buffer
	scanf("%s",emp_id);

	for(i=0;i<j;i++)
	{
		if(strcmp(buffer2[i],emp_id)==0)       //checking if the user entered emp_id is registested for the training
		{
			flag=1;
			break;
		}
	}
	if(flag==0)        //if not registed for the training then exit from this thread
	{
		printf("Can't give the feedback since this user has not registered for the training\n");
		fclose(fp2);
		pthread_mutex_unlock(&lock);  //to release the lock
		pthread_exit(NULL);   //to exit from the thread
	}
	else
	{
		if(emp_id[0] == '0')   //checking if the user entered emp_id is starting from 0
		{
			strcpy(user_buffer1, emp_id);             //storing the emp_id into buffer
		}

		employee_name(user_buffer2);   //calling employee_name function to take emp_name from the user
		employee_email(user_buffer3);  //calling emloyee_email function to take emp_email fromthe user
		employee_reporting_mgr(user_buffer4);   //calling the employee_reporting_mgr function to take retporting manager name
		employee_feedback(user_buffer5);   //calling the employee_feedback function to take feedback from the user		

		printf("User details: \n");   
		printf("%s\t%s\t%s\t%s\t%s\n",user_buffer1,user_buffer2,user_buffer3,user_buffer4,user_buffer5); //to display user details on console
		fprintf(fp2,"%s\t%s\t%s\t%s\t%s\n",user_buffer1,user_buffer2,user_buffer3,user_buffer4,user_buffer5); //storing user details into feedback xl sheet

		fclose(fp2); //to close the file
		pthread_mutex_unlock(&lock);     //to release the lock
	}
}





void feedback(int option)
{
	char filename[SIZE]; //An array of character to store the one trainig form name
	char form_name[SIZE]; //An arraay of characters to store the one training feedback form name
	char c;  //to store the character    
	int line_count=0;        //to store the line_count
	strcpy(filename,Forms[option-1]);     //copying the conducted form name 
	strcat(filename,"_training.xlsx");   //concatenating the form name with _training.xlsx
	FILE *fp=fopen(filename,"r");       //opening the file in read mode
	if(fp==NULL)                       //checking if file is exists or not
	{
		printf("File does not exists\n");
	}
	else
	{
		for (c = getc(fp); c != EOF; c = getc(fp))     //counting the number of lines in that conducted training sheet 
		{
			if (c == '\n') // Increment count if this character is newline
				line_count = line_count + 1;  
		}
	}
	fclose(fp);
	if(line_count==1) ////checking the conducted training xl file,checking if only form is created with no field enetred by the user
	{
		printf("Only form is created no entries are made\n");
		main();
	}
	else
	{
		strcpy(form_name,Forms[option-1]);   //copying conduxted training form name
		strcat(form_name,"_training_feedback.xlsx");
		FILE *fp1=fopen(form_name,"w");     //opening the _feedback.xlsx file in write mode
		if(fp1==NULL)    //checking if file exists or not
		{
			printf("File does not exists\n");
		}
		else
		{
			Employee_training_feedback user={"emp_id","emp_name","emp_email","reporting_mgr","feedback"}; //initializing the field names using the structure varible

			fprintf(fp1,"%s\t%s\t%s\t%s\t%s\n",user.emp_id,user.emp_name,user.emp_email,user.reporting_mgr,user.feedback); //printing the field names into _feedback.xlsx file
			fclose(fp1); //closing the file
			pthread_t thread[3];  //creating threee threads to take three i/p from user
			pthread_create(&thread[0], NULL, feedback_thread1, (void *)&option); //to take user1 i/p
			pthread_create(&thread[1], NULL, feedback_thread2, (void *)&option); //to take user2 i/p
			pthread_create(&thread[2], NULL, feedback_thread3, (void *)&option); //to take user3 i/p
			pthread_join(thread[0], NULL); //wait for the thread1 to complete
			pthread_join(thread[1], NULL);  //wait for the thread2 to complete
			pthread_join(thread[2], NULL);   //wait for the thread3 to complete
			main();
		}
	}
}

void employee_name(char* user_buffer)   //function definition to take emp_name from user
{
	char name[SIZE];
	int count = 0, k = 0, flag1 = 0;
	printf("Enter the emp_name:"); 
	__fpurge(stdin);            //to clear the buffer
	scanf("%[^\n]%*c",name);      //to take emp_name from the user

	while(name[k] != '\0')
	{
		count++;
		if(count > FIELD_SIZE)    //checking for the max characters to take for the name
		{
			printf("Buffer size is exceeded\n");
			employee_name(user_buffer);    //if size exceeds calling the function to again take the emp_name
		}
		if(name[k] == ' ' || (name[k] >= 65 && name[k] <= 90) || (name[k] >= 97 && name[k] <=122)) //checking the user emp_name contains only the ' ' and capital and small letters 
		{
			k++;
		}
		else
		{
			flag1 = 1;
			break;
		}
	}
	if(flag1 == 0)
	{
		strcpy(user_buffer,name); //copying the user inputted emp_name to buffer
	}
	else
	{
		printf("No special characters are allowed\n");
		employee_name(user_buffer);  //calling the function again to enter the valid emp_name
	}
}
void employee_email(char* user_buffer)
{
	char Email_id[SIZE];

	printf("Enter the email_id:");
	__fpurge(stdin);
	scanf("%[^\n]%*c",Email_id);      // to take the email idfromthe user
	if(strstr(Email_id, "@thundersoft.com") )  //checking for @thundersoft.com in that user entered emeil id
	{
		strcpy(user_buffer, Email_id);
	}
	else
	{
		printf("Please enter valid mail-id\n");
		employee_email(user_buffer); //calling the function agin to enter the valid mail id
	}
}


void employee_reporting_mgr(char* user_buffer)
{
	char reporting_manager[SIZE];

	printf("Enter the Reporting manger name:");
	__fpurge(stdin);
	scanf("%[^\n]%*c",reporting_manager);          //to take reporting manager namefrom the user


	int  k = 0, flag1 = 0,count = 0;
	while(reporting_manager[k] != '\0') 
	{
		count++;
		if(count > FIELD_SIZE) //checking the max charcaters that that entered by the user
		{
			printf("Buffer size is exceeded\n"); 
			employee_reporting_mgr(user_buffer); //calling the function again to take valid reporting manager anme
		} //checking for the ' ' capital and small lettres 
		if(reporting_manager[k] == ' ' || (reporting_manager[k] >= 65 && reporting_manager[k] <= 90) || (reporting_manager[k] >= 97 && reporting_manager[k] <=122))
		{ 
			k++;
		}
		else
		{
			flag1 = 1;
			break;
		}
	}
	if(flag1 == 0)
	{
		strcpy(user_buffer,reporting_manager); //copying the user inputted reporting manager to buffer
	}
	else
	{
		printf("No special characters are allowed\n");
		employee_reporting_mgr(user_buffer);    //calling the function again to enter the valid reporting manager name
	}
}

void employee_feedback(char *user_buffer)
{
	char feedback_training[SIZE];

	printf("Enter the Feedback for the training:");
	__fpurge(stdin);
	scanf("%[^\n]%*c",feedback_training);   //to take feedback from the user
	int feedback_count=0,k = 0, flag1 = 0;
	while(feedback_training[k] != '\0')
	{
		feedback_count++;
		if(feedback_count> SIZE) //checking max characeter that canbe entered by the usre for giving feedback
		{
			printf("Size is exceeded\n");
			employee_feedback(user_buffer);
		} //checking for  ' ' small and capital letters
		if(feedback_training[k] == ' ' || (feedback_training[k] >= 65 && feedback_training[k] <= 90) || (feedback_training[k] >= 97 && feedback_training[k] <=122))
		{
			k++;
		}
		else
		{
			flag1 = 1;
			break;
		}
	}
	if(flag1 == 0)
	{
		strcpy(user_buffer,feedback_training);   //copying the user inputted feedback into buffer
	}
	else
	{
		printf("No special characters are aloowed\n");
		employee_feedback(user_buffer);  //calling the function again to enter the valid feedback(i.e no special characters are allowed)
	}
}
