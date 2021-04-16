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

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    const int SIZE = codeLength();
    bool dup = duplicates();
    int *code = nullptr;                                                //create a dynamically allocated array
    code = new int[SIZE];                                               //input size of array from CodeLength()
    cout << "Code Length: " << SIZE << endl;                            //display code length
    //this is to run either the dup or noDup code generator
    if(dup == true){
        cout << "Using dupCodeGen...." << endl;
        dupCodeGen(code, SIZE);
    }
    else{
        cout << "Using noDupCodeGen...." << endl;
        noDupCodeGen(code, SIZE);
    }
    for(int i = 0; i < SIZE; i++){
        cout << code[i];
    }
    
    //make sure to delete dynamically allocated memory
    delete code;
    //best practice, return pointer to nullptr
    code = nullptr;
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
    shuffle(codeAry, SIZE);
    for(int i = 0; i < SIZE; i++){
        code[i] = codeAry[i];
    }
}

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