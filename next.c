/* 
 * Creator: Edward Bierens
 * Date Due: 8 February 2024 
 * Language: C
 * 
 * Description: This program aims to create a Command Line Interface to be used on top 
 * of both Windows and UNIX/UNIX-like systems, all the while using the Windows syntax to
 * allow Windows users to transition over to Linux and related systems without having to
 * learn an entirely new command set (though you should anyway). 
 *
 * Fun fact: Much of this was coded in OpenStep, who knew even ancient systems can help
 * complete modern college assignments!   
 *	
 */

// Including all needed C libraries
#include "next.h"


// Checks the command and returns an integer based on what the command is
int chkCmd(char* cmd) {
	
	// Declare an integer to determine the choice and clear uneeded spaces
	int choice = -1;
	
	// If the beginning word of the command starts with any of the commands, return the command number
	if (strcmp(cmd,"dir") == 0) choice = 0;
	else if (strcmp(subString(cmd,0,2),"cd") == 0) choice = 1;
	else if (strcmp(subString(cmd,0,5),"mkdir") == 0) choice = 2;
	else if (strcmp(subString(cmd,0,4),"echo") == 0) choice = 3;
	else if (strcmp(subString(cmd,0,4),"type") == 0) choice = 4;
	else if (strcmp(cmd,"menu") == 0) choice = 5;
	else if (strcmp(cmd,"cls") == 0) choice = 6;
	else if (strcmp(cmd,"quit") == 0) choice = 7;
	
	// Otherwise return -1
	return choice;
	
}
	
// Driver program
int main(void) {
	
	// I wish to show the current directory on the terminal. this is an array that will contain it
	char dir[MAX];
	char buffer[MAX];
	int i = 0;
	
	// Display a welcome message as well as tell the user to use the menu command
	printf("Welcome to nextShell!\nType \"menu\" to see and execute the possible commands!\n");

	while (1) {
		
		// Get the current directory and print out a prompt with a parenthesis at the end
		#ifndef _WIN32
		getwd(dir);
		#else
		_getcwd(dir,MAX);
		#endif
		printf("%s) ", dir);

		// Get the command
		fgets(cmd, MAX, stdin);
		
		// Parse command by removing new line and removing extra spaces
		cmd[strcspn(cmd,"\n")] = 0;
		i = 0;
		while (cmd[0] == ' ') strcpy(cmd,cmd+1); // Remove spaces before command
		while (cmd[i] != 0) { // Remove spaces in and after command 
			if (cmd[i] == ' ' && (cmd[i+1] == ' ' || cmd[i+1] == 0)) strcpy(cmd+i,cmd+i+1);
			else i++; 
		}

		// Repeat loop if command is empty
		if (strcmp(cmd,"") == 0) continue;
	
		// Special value to return from the check command and choose command functions to exit
		// only when prompted with this value
		if (chooseCmd(chkCmd(cmd)) == -5) return 0;

		// Clear the command string with null characters for reuse
		i = 0;
		while (cmd[i] != '\0' && cmd[i] != '\n') {
			cmd[i] = '\0';
			i++;
		}
	 	
	}

	// This program should not run down here but if it does return a fail 
	return -1;

}
