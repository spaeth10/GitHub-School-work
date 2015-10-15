/*
 Ben Spaeth
 Backtracking algorithm for the m-coloring problem
 Determines all of the ways in which the vertices in an undirected graph can be
 colored, using only m-colors, so that adjacent vertices do not have the same
 color.
 4/17/15
 */
#include <iostream>

using namespace std;
void mcoloring(int i, int **A, int *vcolor, int vert, int m, bool first);
//Pre: i is the row of the section of the state space tree, vcolor is the array that contains the solution, vert is the number of vertices, m is the maximum number of colors, and first keeps track of if the first solution has been found
//Post: Returns the array of a correct coloring.
bool promising(int **A, int *vcolor, int i);
//Pre: i is the row of the section of the state space tree, vcolor is the array that contains the solution, vert is the number of vertices
//Post: Returns true if the coloring so far is still promising. Returns false
//	if it is not promising.
void printArray(int *vcolor, int vert);
//Post: prints a solution array

int main(){
    int vert; //declaration of number of vertices
    int m; //delcaration of the number of colors desired
    cout << "Enter the number of vertices in the graph." << endl;
    cin >> vert; //sets the input to vert
    int *vcolor;
    vcolor = new int[vert];
    for(int i =0; i < vert; i++)
        vcolor[i]=1;
    int** A; //declaration of the array
    A = new int*[vert];
    for (int i=0; i<vert; i++)
        A[i] = new int[vert];
    A = new int*[vert]; //memory for pointers to the rows
    for (int i=0; i<vert; i++) //creates the first array with the vert
        A[i] = new int[vert]; //size of the array assigned
    cout << "Enter the adjacency matrix one row at a time." << endl;
    for(int i=0; i < vert; i++){
        //loop for entering data into the adjacency matrix
        for(int j=0; j <vert; j++){
            cin >> A[i][j];
        }
    }
    cout << "The adjacency matrix entered: " << endl;
    for(int i=0; i < vert; i++){ //loop to output the adjacency matrix
        for(int j=0; j <vert; j++){
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << "What is the maximum number of colors you would like to be used?" << endl;
    cin >> m;
    bool first = true;
    
    mcoloring(0, A, vcolor, vert, m, first);
    for(int i=0; i<vert; i++) //Deallocates memory for array A
        delete [] A[i];
    delete [] A;
    delete [] vcolor;
    
    return 0;
}
void mcoloring(int i, int **A, int *vcolor, int vert, int m, bool first){
    if (promising(A, vcolor, i)){
        if(i+1 == vert){
            if (first){
                cout<< "The first solution is: ";
                printArray(vcolor, vert);
                cout << endl;
                char ans;
                cout << "Do you wish to see the rest of the solutions? (y/n) -->" << endl;
                cin >> ans;
                cout << endl;
                if(ans!='y' && ans!='Y'){ //ending the running of the program when y is not input
                    cout<<"Done";
                    exit(0);
                }
                else{
                    cout<< "The remaining solutions are: "; //print the remaining solutions
                    first=false;
                    
                    exit(0);
                }
            }
            else{
                printArray(vcolor, vert); //calls the printArray
                cout<<endl;
            }
        }
        else{
            for(int color=i+1;color<=vert;color++){ //loop for setting the colors
                for(int i=1;i<m;i++){
                    vcolor[color]=i;
                    mcoloring(color, A, vcolor, vert, m, first);
                }
            }
        }
    }
    else if (vcolor[i]<m){
        vcolor[i]++;
    }
    else if (vcolor[i]==m){
        vcolor[i]=1;
        vcolor[i-1]++;
    }
}

bool promising(int **A, int *vcolor, int i){
    int j = 0;
    bool isPromising = true;
    
    while (j < i and isPromising){
        //loop to check if adjacent vertex is the same color
        if(A[i][j] and vcolor[i] == vcolor[j])
            isPromising = false;
        j++;
    }
    return isPromising;
}

void printArray(int *vcolor, int vert){
    for(int k = 0; k < vert; k++)
        cout << vcolor[k] << " ";
    cout << endl;
}