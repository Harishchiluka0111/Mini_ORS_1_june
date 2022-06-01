#include"registration.h"

//*******************************************Training resgistration*****************************************

void registration()
{
	char choice;
	int count_option = 1;
	//Array of Function pointers to call functions
	void (*fp[3])() = {create_training_registration_form, delete_training_registration_form, send_training_registration_form};
	while(1)
	{
		printf("1. Create Training Registration form\n2. Delete Training Registration form\n3. Send Training Registration form\n*. Main menu");
		printf("\nEnter the option: ");
		scanf(" %c", &choice);
		if(count_option < 3)
		{
			//To call functions based on user choice
			switch(choice)
			{
				case '1': fp[choice - 49]();
					  break;
				case '2': fp[choice - 49]();
					  break;
				case '3': fp[choice - 49]();
					  break;
				case '*': main();
					  break;
				default:  printf("\nError: Invalid option\n");
					  count_option++;
					  break; 
			}
		}
		else
		{
			printf("\nError: User entered Invalid Option for three times\n\n");
			main();
		}
	}
}
