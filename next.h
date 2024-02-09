/*
 * Header file for next.c
 * Fun fact: These files are called "next.x" in reference of them being completed on OpenStep (NextStep 4.X)
*/

// Implement other libraries
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Windows places the _getcwd() function in the direct.h header
#ifdef _WIN32
#include <direct.h>
#define  getwd(cmd) _getcwd(cmd)
#define  chdir  _chdir
#else
#include <unistd.h>
#endif

// Defining a maximum buffer size
#define MAX 255

// Place to store the current command
char cmd[MAX];

// Get the substring of a char* string. 
char* subString(char* str, int start, int length) {
	
	// Declare result string and a temporary integer
	char* result;
	int n;

	// Ensure end is bigger than beginning, and adjust end if it is larger than the string length
	if (length <= 0) return "";
	if (start+length >= strlen(str)) length = strlen(str)-start; 
	
	// Allocate the needed memory space for the result string (end-begin+1)
	result = (char*)malloc(sizeof(char)*(length+1));	

	// Copy string information from begin to end into a new array
	for (n = start; n < start+length; n++) result[n - start] = str[n];
	result[n-start] = 0;
	
	// Return the resulting string
	return result;
	
}

// Command to print and select from a menu
int useMenu(int* choice) {

	// Create a string to contain input; also clear screen
	char listChoose[MAX];
	#ifndef _WIN32
	system("clear");
	#else
	system("cls");
	#endif  

	// Display the Shell List "dialog box" that contains the commands
	printf("-----------------------------------------------------\n");
	printf("|           WELCOME TO THE NEXTSHELL LIST!          |\n");
	printf("-----------------------------------------------------\n");
	printf("| 1) dir - List contents of current directory       |\n");
	printf("| 2) cd - Display current directory                 |\n");
	printf("| 3) mkdir - Create a new directory                 |\n");
	printf("| 4) echo - Print out a message                     |\n");
	printf("| 5) type - List out the contents of a file         |\n");
	printf("| 6) menu - Pulls up this display                   |\n");
	printf("| 7) cls - Clear the screen                         |\n");
	printf("| 8) quit - Exit the shell                          |\n"); 
	printf("| 9) Return to command interface                    |\n");                     
	printf("-----------------------------------------------------\n");
	printf("Please select an option (1-9)\n");
	listChoose[0]='a';

	// Strategy: Only read the first character and make sure it's between '1' and '9'
	// Check is needed to prevent any infinite loops or other undefined behavior
	while (listChoose[0] > '9' || listChoose[0] < '1') {
		printf("Your choice: ");
		fgets(listChoose,MAX,stdin);
	}

	// Update the choice variable, first adjust to make them actual integers then subtract 1
	// This will allow the menu to once again use this choice (saving code and memory)
	*choice = listChoose[0]-'0'-1;
	return 6;
}

// Using an integer, it determines what the command is, and executes it with system()
int chooseCmd(int choice) {

	// Create a temporary string and a return integer for catching errors
	char sysCmd[MAX];
	int ret;
	int i;

menu:   // Yes I am aware goto is a hated command, but I feel this is the best 
        // way to just access the commands without creating yet another while loop

	switch (choice) {
		
		// Alias for the "dir" command, will list the current directory's contents
		case 0:
			#ifndef _WIN32 
			system("ls");
			#else
			system("dir");
			#endif
			return choice;	
		
		// Alias for the "cd" command, will print out the current directory or move to one
		case 1: 
		
			// If no argument is passed, just use pwd to print out the current directory
			if (ret == 6 || strlen(cmd) <= 3) {
				#ifndef _WIN32
				ret = system("pwd");
				#else
				ret = system("cd");
				#endif
			// If argument is passed, switch to directory
			} else {
				ret = chdir(subString(cmd, 3,strlen(cmd)-3));
				if (ret != 0) printf("Directory couldn't be changed to %s\n",subString(cmd, 3,strlen(cmd)-3));
			}
			
			return choice;

		// Alias for the "mkdir" command, will make any directory
		case 2:
			// If the command came from the menu, prompt user for directory name
			if (ret == 6) {
				printf("Enter the directory name to create: ");
				fgets(sysCmd, MAX-6, stdin); 
				strcpy(cmd, "mkdir ");
				ret = system(strcat(cmd, sysCmd));

			// otherwise it has the directory name, so just run the command directly
			} else {
				ret = system(cmd);
			}

			if (ret != 0) printf("Your directory could not be created\n");
			
			return choice;

		// Alias for the "echo" command, will print any given message
		case 3:
			// If the command came from the menu, prompt user for directory name
			if (ret == 6) {
				printf("Type the message you wish to echo: ");
				fgets(sysCmd, MAX-5, stdin); 
				strcpy(cmd, "echo ");
				ret = system(strcat(cmd, sysCmd));

			// otherwise it has the directory name, so just run the command directly
			} else ret = system(cmd);

			if (ret != 0) printf("Somehow the echo command has failed.\n");

			return choice;

		// Alias for the "type" command, will display a file's contents.
		case 4:
			// If the command came from the menu, prompt user for directory name
			if (ret == 6) {

				// Ensure a proper name is sent to the program
				do {
					printf("Enter file name to concatenate and view: ");
					fgets(sysCmd, MAX-4, stdin);

					// Same technique used in the main loop for parsing commands
					cmd[strcspn(sysCmd,"\n")] = 0;
					i = 0;
					while (sysCmd[0] == ' ') strcpy(sysCmd,sysCmd+1);
					while (sysCmd[i] != 0) {
						if (sysCmd[i] == ' ' && (sysCmd[i+1] == ' ' || sysCmd[i+1] == 0))
							strcpy(sysCmd+i,sysCmd+i+1);
						else i++; 
					}
					

				} while (strlen(sysCmd) <= 1);

				#ifndef _WIN32 
				strcpy(cmd, "cat ");
				#else
				strcpy(cmd, "type ");
				#endif

				ret = system(strcat(cmd, sysCmd));

			// otherwise it has the directory name, so just run the command directly
			} else {
				
				#ifndef _WIN32
				strcpy(sysCmd, "cat");
				#else
				strcpy(sysCmd, "type");
				#endif

				if (strlen(subString(cmd, 4, MAX-1)) > 1) ret = system(strcat(sysCmd, subString(cmd, 4, MAX-1)));
				else ret = -1;
			}

			// Extra new line and determine whether error occurred
			printf("\n");
			if (ret != 0) printf("the type command has failed.\n");
			
			return choice;

		// Using the "menu" command, will display a menu to help out users
		case 5:
			ret = useMenu(&choice);
			if (choice != 9) goto menu;
			return 5;
	
		// Alias for the "cls" command; will clear the entire screen aside for a prompt
		case 6:	
			#ifndef _WIN32
			ret = system("clear");
			#else
			ret = system("cls");
			#endif
			if (ret != 0) printf("Screen could not be cleared.\n");

			return choice;

		// Creating the "quit" command; will exit the shell entirely with the special value
		case 7:
			printf("Exiting the shell...\n");
			return -5;
	
		// Any other command is not recognized, and will display as such
		case -1:
			printf("Command not found, please try again!\n");
			return -1;
	
	}

	return 10;
}
