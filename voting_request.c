
#include"voting_request.h"  //header file inclusion


/******************Function defination to choose creation and deletion form*************************/


void voting_request()
{
	char choice=0;                                                           //local variable for user input
	int invalid_option = 0;                                                  //variable for counting invalid option
	void (*fp[2])() = {create_voting_req_form, delete_voting_req_form};      // Array of fun pointer initialization

	while(1)
	{		
		if(invalid_option < 3)
		{

			printf("1. Create voting form\n2. Delete voting form\n*. Main menu");
			printf("\nEnter the option: ");
			scanf(" %c", &choice);
			switch(choice)
			{
				case '1': fp[0]();                               // fun call for create_voting_req_form
					  break;
				case '2': fp[1]();                               // fun call for delete_voting_req_form
					  break;
				case '*': main();                                // calling main menu fun
					  break;
				default: invalid_option++;                       //invalid option counting
					 printf("Error: invalid option\n\n");
					 break;
			}
		}
		else
		{
			printf("\nError: User entered Invalid Option for three times\n\n");
			main();                                                 // calling main fun after 3 invalide input
		}
	}
}


