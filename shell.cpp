/*
Ben Spaeth
Final Project Part 1
Source file: shell.cpp
12/2/14
A shell that accepts a user input, parses the input and does basic commands
using pointers and function calls.
*/

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <dirent.h>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>
#include <sys/wait.h>
using namespace std;

const int NUM_WORDS = 16;
const int NUM_CHARS_PER_WORD = 128;

void parse(char **arg, int& z);
//pre: Passed the array and a reference variable that is to be assigned to the
//	length of the array
//post: Reads one line of user input from the keyboard and creates an array of
//	the strings found in the input.
void help();
//pre: Program must be waiting for input after the '$' symbol
//post: Prints a list of the functions of my shell to the user
void show(char *fn);
//pre: A file name must be entered after the word show
//post: The file is printed out in the shell.
void copy(char *in, char *out);
//pre: Two file names must be input after the word copy
//post: Checks to see if the second file already exists, if it does it prompts
//	the user asking to overwrite or not, if it does not exist it creates a
//	file that is an exact copy of the first file
void cd(char *directory);
//pre: A directory name must be entered after the word cd
//post: The user entered directory name is checked and if not null the current
//	working directory is changed to it
void ls();
//pre: LS is entered by the user with no characters after it
//post: The current working directory is opened and the name of the entries are
//	output until there are none remaining
void ls(char *directory);
//pre: One directory name must be entered after the word ls
//post: The entered directory is checked to see if it is a directory, then the
//	entered directory is read and output to the screen
void run(char *name);
//pre: The name of an executable file must be entered after the word run
//post: A fork is run on the parent process to create a child process, the
//	parent then wait for the child process to complete before running.


int main()
{
	cout << "Welcome to the command interpreter" <<endl;
	cout << "Enter you command after the $ symbol" << endl;
	cout << "To end the command interpreter enter the word QUIT" << endl;
	int y = 0;
	char **arg; //pointer to a pointer, 2d array
	arg = new char* [NUM_WORDS]; //pointer to an array
	for (int z = 0; z < NUM_WORDS; z++) //for loop for the array
		arg[z] = new char [NUM_CHARS_PER_WORD];
	do
	{
		cout << "$"; //outputs the command symbol
		parse(arg, y); //calls the parse function
		if(!strcmp(arg[0], "HELP"))
		{
			help();
		}
		else if(!strcmp(arg[0], "SHOW"))
		{
			char *fn;
			fn = arg[1]; //assigns the second word to fn
			show(fn); //calls show fctn, passes the file name
		}
		else if(!strcmp(arg[0], "COPY"))
		{
			char *in;
			char *out;
			in = arg[1]; //assigns the second word to in
			out = arg[2]; //assigns the third word to out
			copy(in, out); 
			//calls copy fctn, passes the in and out files
		}
		else if(!strcmp(arg[0], "CD"))
		{
			char *directory;
			directory = arg[1];
			cd(directory);

		}
		else if(!strcmp(arg[0], "LS"))
		{
			if(y == 1)
			{
				ls();
			}
			else if (y == 2)
			{
				char *directory;
				directory = arg[1];
				ls(directory);
			}

		}
		else if(!strcmp(arg[0], "RUN"))
		{
			char *name;
			name = arg[1];
			run(name);
		}
		y = 0;
	}
	while(strcmp(arg[0], "QUIT"));
	//checks to see if quit was entered by the user
	return 0;
}

void parse(char **arg, int& z )
{
	char ch;
	int x=0;
	cin.get(ch); //gets the first character
	if(ch == '\n') return;
	//checks to see if the only thing entered was a return
	while(ch == ' ') //while loop for the space
	{
		cin.get(ch);
	}
	while (ch != '\n') //while loop for the new line
	{
		while(ch == ' ') //while loop for space
		{
			arg[z][x] = '\0'; //adds null to the end
			z++; //goes to the next row
			x=0;
			while(ch == ' ') //while loop for space
			{
				cin.get(ch);
			}
		}
		arg[z][x] = ch;
		x++; //goes to the next column
		cin.get(ch);
	}
	arg[z][x] = '\0'; //adds null to the end
	z++; //goes to the next row
}

void help()
{
	cout << "The valid commands are: " << endl;
	cout << "RUN executable-file" << endl;
	cout << "LIST" << endl;
	cout << "LIST directory" << endl;
	cout << "COPY old-filename new-filename" << endl;
	cout << "HELP" << endl;
	cout << "QUIT" << endl;

}

void show(char *fn)
{
	ifstream myIn; //opens input file stream for the file
	myIn.open(fn); //opens the source file
	if (myIn.fail()) //Makes sure the file opens correctly
	{
		cout << "Error opening file."<<endl;
		return;
	}
	char ch;
	myIn.get(ch); //gets first letter
	while(!myIn.eof())
	{
		cout << ch; //prints first letter
		myIn.get(ch); //gets next letter
	}
	myIn.close(); //closes the source file
}

void copy(char *in, char *out)
{
	ifstream myIn; //opens input file stream for the file
	myIn.open(in); //opens the source file
	if  (myIn.fail()) //Makes sure the file opens correctly
	{
		cout << "Error opening input file." << endl;
		return;
	}
	ofstream myOut; //opens output file stream for the file
	myOut.open(out); //opens the output file
	if (myOut.fail()) //makes usre the file opens correctly
	{
		cout << "Error opening output file." << endl;
		return;
	}
	if (myOut) //if output file already exists
	{
		char answer;
		cout << "Would you like to overwrite the file.(Y/N)" << endl;
		cin.get(answer);
		if (answer == 'Y')
		{
			char ch;
			myIn.get(ch);
			while(!myIn.eof())
			{
				myOut.put(ch);
				myIn.get(ch);
			}
			myIn.close();
			myOut.close();
			exit(EXIT_FAILURE);//exits program instead of function

		}
		else //if output file does not exist
		{
			cin.ignore();
		}
	}

}

void cd(char* directory)
{
	if(chdir(directory)!=0) //checks if directory is equal to 0
	{
		perror("Unable to change directory.");
	}
}

void ls()
{
	DIR *directory;
	struct dirent* directoryE;
	directory = opendir(".");
	while((directoryE = readdir(directory)) != NULL) 
		//reads through directory while the value is not NULL
	{
		cout << directoryE -> d_name << endl; //outputs the files/
	}
	closedir(directory);
}

void ls(char *directory)
{
	DIR *dir;
	struct dirent* directoryE;
	dir = opendir(directory);
	if (dir == NULL) // checks if dir was initialized
	{
		cout << "Unable to list directory" << endl;
		return;
	}

	while ((directoryE = readdir (dir))) 
	//reads through directory while there is still something there to read
	{
		if (directoryE == NULL)
		{
			cout << "Unable to list directory";
			return;
		}

		cout << directoryE->d_name << endl; //outputs the files
	}
	closedir(dir);
}

void run(char *name)
{
	pid_t p = fork();
	//p is not zero in the parent process and 0 in the child
	if( p == -1 )	    // fork returns -1 if it cannot create child
	{
		perror("Unable to run the program.");
		return;
	}
	if(p) //if parent class, waits
	{
		wait(NULL);
	}

	else //runs the child class while parent is waiting
		execl(name, name, NULL);
}
