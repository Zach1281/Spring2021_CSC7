#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;

int codeLength();
bool duplicates();
void dupCodeGen(int *,const int);
void noDupCodeGen(int *, const int);
void shuffle(int *, int);
void swap(int *, int *);
void input(int*, const int);
bool equal(int *, int *, const int);
void mastermind(int*, int*, int, int, const int);

//this version of mastermind is focused on actually playing the game, before was just figuring out how to generate the code sequence
int main()
{
    srand(static_cast<unsigned int>(time(0)));
    const int SIZE = codeLength();
    bool dup = duplicates();
    int red = 0, white = 0;
    int *code = nullptr;                                                            //create a dynamically allocated array
    int *guess = nullptr;                                               
    code = new int[SIZE];                                                           //input size of array from codeLength()
    guess = new int[SIZE];                                              //input size of array from codeLength()
    //this is to run either the dup or noDup code generator
    if(dup == true){
        dupCodeGen(code, SIZE);
    }
    else{
        noDupCodeGen(code, SIZE);
    }
    cout << endl;
    for(int i = 0; i < 10; i++){
        input(guess, SIZE);
        if(equal(guess, code, SIZE) == true){
            cout << "The guess is correct." << endl;
            break;
        }
        else{
            cout << "\nThe guess is wrong." << endl;
        }
        cout << "Guess " << i + 1 << "--> ";
        for(int j = 0; j < SIZE; j++){
            cout << guess[j];
        }
        mastermind(code, guess, red, white, SIZE);
        cout << endl;
    }
    //displays code if not guessed correctly
    cout << "Code: ";
    for(int i = 0; i < SIZE; i++){
        cout << code[i];
    }
    //make sure to delete dynamically allocated memory
    delete guess;
    delete code;
    //best practice, return pointer to nullptr
    code = nullptr;
    guess = nullptr;
    return 0;
}

//switch case to determine length of array
int codeLength()
{
    int SIZE;
    cout << "Welcome to Zach's Mastermind game!" << endl;
    do{
        cout << "Would you like the code length to be 4, 6, or 8?" << endl;
        cin >> SIZE;
        switch(SIZE){
            case 4:
                cout << "You have chosen code length '4'." << endl;
                return SIZE;
            case 6:
                cout << "You have chosen code length '6'." << endl;
                return SIZE;
            case 8:
                cout << "You have chosen code length '8'." << endl;
                return SIZE;
            default:
                cout << "You need to choose a valid code length." << endl;
                break;
        }
    }while(SIZE != 4 || SIZE != 6 || SIZE != 8);
    
    return SIZE;
}

//as this function says, it is just a boolean that returns true for if the player wants duplicates and false if not
bool duplicates()
{
    bool dup;
    char choice;
    cout << "Would you like to allow duplicates in the code sequence? (press 'y'/'Y')" << endl;
    cin >> choice;
    if(choice == 'y' || choice == 'Y'){
        cout << "You have chosen to have the possibility of duplicates in the code sequence." << endl;
        dup = true;
    }
    else{
        cout << "You have chosen to not have duplicates in the code sequence." << endl;
        dup = false;
    }
    return dup;
}

/*
 * this section should be to take care of the generation of the code, take in the pointer, bool and size of array and then output an array with the code sequence
 * from my understanding allowing duplicates just means the array is randomly filled with numbers 0-7
 * not allowing duplicates means the array from 0-7 is shuffled and then put into the code array
 */
void dupCodeGen(int *code, const int SIZE)
{
    //pretty simple, just randomize digits from 0-7
    for(int i = 0; i < SIZE; i++){
        code[i] = rand()%8;
    }
}

void noDupCodeGen(int *code, const int SIZE)
{
    const int SIZE2 = 8;
    int codeAry[SIZE2] = {0,1,2,3,4,5,6,7};
    shuffle(codeAry, SIZE2);
    for(int i = 0; i < SIZE; i++){
        code[i] = codeAry[i];
    }
}

//this shuffle function is from my blackjack game from last semester
void shuffle(int *tracker, int num)
{
    srand(static_cast<unsigned int>(time(0)));
    for(int i = num - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap(&tracker[i], &tracker[j]);
    }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void input(int *guess, const int SIZE)
{
    bool isValid;
    cout << "Please enter your guess one at at time with a new line separating each one." << endl;
    for(int i = 0; i < SIZE; i++){
        do{                                                                         //input validation
            cin >> guess[i];
            if(guess[i] > 7 || guess[i] < 0){
                cout << "Please enter a number between 0-7." << endl;
                isValid = false;
            }
            else
                isValid = true;
        }while(isValid == false);
    }
}

bool equal(int *guess, int *code, const int SIZE)
{
    bool isEqual;
    for(int i = 0; i < SIZE; i++){                                                  //this just loops through the array and catches any mismatches
        isEqual = true;
        if(code[i] != guess[i]){
            isEqual = false;
            return isEqual;
        }
    }
    return isEqual;
}

void mastermind(int *code, int *guess, int red, int white, const int SIZE)
{
    int j = 0, i = 0;
    for(i; i < SIZE; i++){
        bool track = true;
        if(guess[i] == code[i]){                                                     //this checks for if the guesses are in the correct spot
            red++;
            track = false;
        }
        for(j; j < SIZE; j++){                                              //this checks if the guess has any that are correct but not in the right spot
            if(guess[i] == code[j] && i != j && track == true && guess[i] != code[i]){
                white++;
            }
        }
    }
    white -= red;
    if(white < 0)
        white = 0;
    cout << " R:" << red << " W:" << white << endl;
}