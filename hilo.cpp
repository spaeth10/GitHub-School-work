/*
 Benjamin Spaeth
 Higher-Lower game
 
 This program creates a random number and prompts the user to guess what this number is. After each guess the user will be told if the number they guessed is higher, lower or correct. 
 
*/
#include <iostream>
#include <cstdlib>
using namespace std;
int main()
{
    int attempts=1;  //the number of guesses
    int num=0;  //the random number
    int guess = 0; //the number guessed by the user
    int game = 0; //hard or easy game
    srand(time(0)); //randomizes the number so it is unique every time it is used
    num = rand() %100 + 1; //sets the random number to be between 1 and 100
    cout<<"Welcome to the Higher-Lower Game"<<endl; //output statement to signal the start of the program
    cout<<"If you would like to play on easy type 1, if you would like to play on hard type 2"<<endl; //prompts the user for a 1 or 2 based on which game they would like to play
    cin>>game; //accepts the users input
    cout<<"Good Luck, the game will end when you run out of guesses or guess correctly"<<endl; //informs the user when the game will end
    if (game == 1){ //if statement for when the user types in 1 for which game they would like to play
        
        do{ //does this step of things until the while statement is valid

            cout<<"Enter your guess between 1 and 100: "<<endl; //prompts the user for their first number
            cin>>guess; //accepts the users number
            attempts++; //increments the number of attempts by 1
        
            if(guess>num) //checks to see if the guess is greater than the random number
                cout << "Lower" <<endl; //informs the user the random number is lower than their guess
            else if (guess< num) //checks to see if the guess is less than the random number
                cout << "Higher" << endl; //informs the user the random number is higher than their guess
            else //if not higher or lower it goes to this
                cout << "Congratulations! You correctly guessed the number!" << endl; //informs the user they won the game
        }
        while(guess != num and attempts<=10); //the while parameters for the do/while statement
    }
    else //if the user types in 2 it will go to this
    {
        do{
            
            cout<<"Enter your guess between 1 and 100: "<<endl; //prompts the user for their first number
            cin>>guess; //accepts the users number
            attempts++; //increments the number of attempts by 1
            
            if(guess>num) //checks to see if the guess is greater than the random number
                cout << "Lower" <<endl; //informs the user the random number is lower than their guess
            else if (guess< num) //checks to see if the guess is less than the random number
                cout << "Higher" << endl; //informs the user the random number is higher than their guess
            else //if not higher or lower it goes to this
                cout << "Congratulations! You correctly guessed the number!" << endl; //informs the user they won the game
        }
        while(guess != num and attempts<=5); //the while parameters for the do/while statement
    }
        return 0;
}
