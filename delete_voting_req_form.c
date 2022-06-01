#include"voting_request.h"

/****************fun defination for deleting voting req form*****************************/

void delete_voting_req_form()
{
	int form_option;                                                // user choice for form deletion
	char form[MAX];

	if(Count_forms > 0)                                                   // is threre any form exists or not
	{
		printf("Available voting forms are: \n");
		for(int i = 0;i < Count_forms;i++)                            // to display list of existing form
		{
			printf("%d. %s\n", i+1, Forms[i]);
		}
		printf("Enter the option: ");
		scanf("%d", &form_option);                                    //scan the form option
		
		strcpy(form, Forms[form_option-1]);     // becoz array started with zero,getting the name of form to deleting file
		strcat(form,"_request.xlsx");

		if(remove(form)==0)                            // to remove given file
		{                                     
			printf("File deleted successfully\n");
			for(int i = form_option;i < Count_forms;i++)                 //to maintain sequence of form list
			{
				strcpy(Forms[i-1], Forms[i]);
				Root[i-1]=Root[i];

			}
			Count_forms--; 
		}  


		else
			printf("invalid option File is not deleted\n");

	}
	else
	{
		printf("No voting file has created\n");
	}

}
