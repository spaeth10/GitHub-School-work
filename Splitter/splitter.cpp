/*
 Benjamin Spaeth
 File encryption program
 Version 1.0
 
 
 */
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void split(char sourceFile[], char destFile1[], char destFile2[]); //declares function split
void merge(char sourceFile1[], char sourceFile2[], char destFile[]); //declares function merge

int main()
{
    char inFile[120]; //declares inFile
    char outFile[120]; //declares outFile
    char splitfile1[120]; //declares the first split file
    char splitfile2[120]; //declares the second split file
    cout << "Enter name of the input file: " << endl; //promopts user for name of input file
    cin >> inFile; //assigns this to inFile
    cout << "Enter name of the first half file" << endl; //prompts user for name of first half file
    cin >> splitfile1; //assigns this to splitfile1
    cout << "Enter name of the second half file" << endl; //prompts user for name of second half file
    cin >> splitfile2; //assigns this to splitfile2
    split(inFile, splitfile1, splitfile2); //calls the split function
    cout << "Enter name of the output file: " <<endl; //prompts user for name of output file
    cin >> outFile; //assigns this to outFile
    merge(splitfile1, splitfile2, outFile); //calls the merge function
    return 0;
}

void split(char sourceFile[], char destFile1[], char destFile2[])
{
    ifstream myIn; //opens input file stream for myIn
    myIn.open(sourceFile); //opens the source file 
    if (myIn.fail()) //checks to see if it opened
    {
		cout << "Error opening input file." << endl; //informs user that it did not open
		exit(EXIT_FAILURE); //exits the function
	}
    
    ofstream myOut1; //opens output file stream for my Out 1
    myOut1.open(destFile1); //opens the destination file for my out 1
    if (myOut1.fail()) // checks to see if it opened
    {	cout << "Error opening first split file." << endl; //informs user that it did not open
		exit(EXIT_FAILURE); //exits the function
	}
    
    ofstream myOut2; //opens output file stream for my out 2
    myOut2.open(destFile2); //opens the destination file for my out 2
    if (myOut2.fail()) //checks to see if it opened
    {cout << "Error opening second split file." << endl; //informs user that it did not open
		exit(EXIT_FAILURE); //exits the function
	}
    
    char ch; //declares ch as a character value
    int num = 0; //sets num to 0
	myIn.get(ch); //gets the first letter of myIn
	while( !myIn.eof() ) //declares parameters for running loop
	{
        if(num % 2 == 0){ //loop for when it should go into output file 1
            myOut1.put(ch); //places letter in output file 1
            num++; //increments num
            myIn.get(ch); //gets the next letter from the source file
        }
        else if(num%2 == 1){ //loop for when it should go into output file 2
            myOut2.put(ch); //places letter in output file 2
            num++; //increments num
            myIn.get(ch); //gets the next letter from the source file
		}
        
	}
    myIn.close(); //closes input file

}

void merge(char sourceFile1[], char sourceFile2[], char destFile[])
{
    ifstream myIn1; //opens input file stream for input 1
    myIn1.open(sourceFile1); //opens the first source file for input
    if (myIn1.fail()) //checks to see if it opened
    {
		cout << "Error opening first input file." << endl; //informs user it did not open
		exit(EXIT_FAILURE); //exits the function
	}
    ifstream myIn2; //opens input file stream for input 2
    myIn2.open(sourceFile2); //opens the second source file for input
    if (myIn2.fail()) //checks to see if it opened
    {
		cout << "Error opening second input file." << endl; //informs user it did not open
		exit(EXIT_FAILURE); //exits the function
	}
    ofstream myOut; //opens the output file stream for output 
    myOut.open(destFile); //opens the destination file for the output
    if (myOut.fail()) //checks to see if it opened
    {
		cout << "Error opening output file." << endl; //informs user it did not open
		exit(EXIT_FAILURE); //exits the function
	}
    
    char ch; //declares ch as a char value
    int num = 0; //sets num to 0
    myIn1.get(ch); //gets the first letter form first split file
    while( !myIn1.eof() and !myIn2.eof()) //sets up loop for merge function
    {
        myOut.put(ch); //puts the first letter into output file
        myIn2.get(ch); //gets the first letter from second split file
        num++; //increments num by 1
        myOut.put(ch); //put the first letter form second split file in output
        myIn1.get(ch); //gets the second letter from the first split file
    }
}
