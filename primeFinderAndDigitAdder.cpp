/**********************************************************
 *  AUTHOR      : Brian McNaughton
 *  Assignment  : Lab08 - Functions
 *  CLASS       : CS002
 *  SECTION     : MTWTh 10:45-12:50
 *  DUE DATE    : 4/12/20
 *********************************************************/
#include <iostream>
#include <iomanip>
using namespace std;
/**********************************************************
 * ASKS USER FOR EXERCISE NUMBER. INPUT OF 1 EXECUTES THE
 * FOLLOWING PROGRAM:
 *_________________________________________________________
 * TELLS USER THE SUM OF THE DIGITS IN INPUT NUMBER
 *_________________________________________________________
 * This program adds the digits of any number entered, then
 * prompts user for another number. Program ends when a
 * zero is entered.
 *_________________________________________________________
 * INPUT:
 *  User is asked for a number, if 0 is enetered
 *  the program ends
 * OUTPUT:
 *  The sum of the digits in given number is then
 *  returned. The program repeats this until 0 is
 *  entered.
 ***********************************************************
 * IF EXERCISE 2 IS CHOSEN PROGRAM EXECUTES THE FOLLOWING
 *_________________________________________________________
 * ALL THE PRIME NUMBERS CONTAINED WITHIN ENTERERED NUMBER
 * ARE PRINTED ON SCREEN IN EIGHT COLUMNS
 *_________________________________________________________
 * This program asks the user for two numbers and then returns
 * all the primes contained between them
 *_________________________________________________________
 * INPUT:
 *  Number: User is asked for two positive integers.
 *
 * OUTPUT:
 *  All prime numbers between the two inputs are displayed.
 *
 ***********************************************************/
// Functions - These statements alert the computer to the
// prescence of these functions allowing main to call them.
bool IsPrime(uint64_t primesource); // Checks for number primacy
long SumDigits(long sumsource);     // Adds digits of any number

int main()
{
// Variables
    uint64_t lowestprime; 
    int programchoice;              // Program choice   -> user input
    long sourceofdigitssummmed;     // Integer progam 1 -> user input
    uint64_t highestprimepossible;  // Integer progam 2 -> user input
    int tabspacecounter=0;          // Used to space tab output
    uint64_t count;                 // C++ for/next loop counter

// User chooses program
    cout << "Which exercise? ";
    cin >> programchoice;

// Choice one asks user for an integer until a zero is entered
// and the program ends. Otherwise the number is sent to function
// sumDigits that returns the sum of the input digits.
if (programchoice == 1)
    {
        cout << "\nPlease enter an integer (0 to quit): ";
        cin >> sourceofdigitssummmed;
        while (!sourceofdigitssummmed == 0)
        {
            if (sourceofdigitssummmed > 0)
            cout << "\nThe sum of the digits of " << sourceofdigitssummmed
                 << " is " << SumDigits(sourceofdigitssummmed);
            if (sourceofdigitssummmed<0)
            cout << "\nThe sum of the digits of " << sourceofdigitssummmed
                 << " is " << SumDigits(sourceofdigitssummmed)*-1;
            cout << "\nPlease enter an integer (0 to quit): ";
            cin >> sourceofdigitssummmed;
         }
        cout << "\nGoodbye \n";
    }

// Choice two asks user for a positive integer then sends that number and
// every number lower to function IsPrime. IsPrime returns a posive bool
// value and the number is printed on the screen. The loop ends once it
// reaches the input number.
    else if (programchoice == 2)
    {
        cout << "\nPlease input a positive number indicating the highest" 
            << " prime to search for: ";
        cin >> highestprimepossible;
        cout << "\nPlease input a positive number for the low end: ";
        cin >> lowestprime;
        cout << "\nThe prime numbers less than "
             << highestprimepossible << " while greater than " << lowestprime << " are:\n";
        for (count = 1; count <= highestprimepossible; count++)
        {
        if ((count+1) % 6 == 0 || (count%6) - 1 == 0  
			|| count==2 || count==3)
        {  
            if (IsPrime(count))
            {
                tabspacecounter++;
                cout << count << "\t";
                if (tabspacecounter % 8 == 0)
                    cout << "\n";
            }
        }
        }
        cout << "\n";
    }
    
return 0;
}
/****************************************************************
* Function SumDigits loops through any number doing successive
* modulo ten calculations, then subtracting that number from the
* original sum, and finally dividing the sum by 10, thereby adding 
* the last digit in a number to the sumofdigits and then removing 
* the last digit from the given number until the integer is 
* reduced to zero. This isolates the last digit and
* removes it from the number. The digits are routinely added and
* when the zero is reached the sum is sent to main.
***************************************************************/
long SumDigits(long sourceofsum)
    {
        int singledigit = 0;
        long sumofdigits;
        sumofdigits = 0;
        for (int count = 1; count <= 100; count++)
        {
            singledigit = sourceofsum % 10;
            sourceofsum = sourceofsum - singledigit;
            sourceofsum = sourceofsum / 10;
            sumofdigits += singledigit;
            count++;
            if (sourceofsum == 0)
                return sumofdigits;
        }
    }
/****************************************************************
* Function IsPrime returns a boolean value of 1 if the number it
* checks for is calculated as prime.
***************************************************************/
bool IsPrime(uint64_t highestprimetocheckfor)
    {
        uint64_t runningtabofprimechecks = 0;
        bool prime = 1;
        for (uint64_t count = 2; count <= highestprimetocheckfor / 2; count++)
         if ((count+1) % 6 == 0 || (count % 6) - 1 == 0 && count % 2)
        {
            if (highestprimetocheckfor % count == 0)
            {
                prime = 0;
                runningtabofprimechecks++;
            }
            if (highestprimetocheckfor % count > 0)
                prime = 1;
        }
        if (runningtabofprimechecks > 0)
            prime = 0;
        else prime = 1;
        if (highestprimetocheckfor==1)
            prime = 0;
		if (highestprimetocheckfor==2)
            prime = 1;
        return prime;
    }


