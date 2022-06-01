#include"registration.h"
#include"feedback.h"

void feedback_module()
{
	int i=0,count=1,option=0;

	if(Forms_count==0) //checking if training registarion is made or not
	{
		printf("No registrations are made\n");
		main();
	}
	if(Forms_count>0)  //Forms_count holds the total number of conducted trainings 
	{
		printf("Available training forms:\n");
		for(i=0;i<Forms_count;i++) //to print the available registration forms
		{
			printf("%d.%s\n",i+1,Forms[i]);
		}
		while(1)
		{
			printf("Please select the option from the avilable training forms:\n");
			scanf("%d",&option);
			if(count<3)           //checking if user enetrs 3 times wrong option
			{
				if(option>Forms_count)  
				{
					printf("Invalid option\n");
					count++;
				}
				else
				{
					feedback(option);     //calling the feedback function to take feedback from user
				}
			}
			else
			{
				printf("User Entered 3 times wrong option\n");
				main();                            //if user enter 3 times wrong option back to main menu
			}
		}
	}
}

