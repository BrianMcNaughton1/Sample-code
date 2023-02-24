
/*********************************************************
 *  AUTHOR      : Brian McNaughton
 *  Assignment  : Hangman
 *  CLASS       : CS002
 *  SECTION     : MTWTh 10:45-12:50
 *  DUE DATE    : 4/24/20
  *********************************************************/
#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
using namespace std;
void PrintHeader(
    string asName,      // Hangman
    char asType,        // ASSIGNMENT
    int asNum);         // 6
/****************************************************************
* wHiteSpaceRemover
* This function receives receives a two strings and removes from
* the first string whatever it finds in the second. In this case
* simply white space.
***************************************************************/
//string wHiteSpaceRemover(
//	string wordBeforeSpacesAreRemoved,  //First string containing
										//too much stuff (spaces)
//	string whatWhiteSpaceLooksLike);    //Second string is an example
										//of whatever you don't want
										//in this case simply a space


char getGuess(              // Guess getting loop for user input. if the string
	string prevGuesses);    // prevGuesses had a "&" in front, wouldn't need the
	string proxyGuesses;    // global variable:'cause functions have no memory!!


string setupUnsolved (                      // User input after letters
		string justThelettersCoveredUp);    // are replaced by dashes
										


string updateUnsolved ( // Function refreshes unsolved word with new letter
	string phrase,      // Original word entered
	string unsolved,    // Word with dashes in place of unguessed letters
	char guess);        // Last correct guess replacing dash or dashes
/**********************************************************
* HANGMAN
*_________________________________________________________
* Classic word guessing game. Once the user enters word the
* program replaces the letters with dashes. The user is then
* given up to seven incorrect guesses of letters in the word
*_________________________________________________________
* INPUT:
*   Original word:
*       A line input is entered by User
*   Single letter guesses:
*       Individual tries at guessing what letters make up
*       the word once it is covered up.
*
* OUTPUT:
*   Row of Dashes:
*       First the word with all letters replaced with dashes
*   Dashes replaced:
*       After each correct guess corresponding dashes are
*       replaced by that letter.
*   Letters already guessed:
*       A string containing all previous letter guesses
*   Wrong Guesses Remaining:
*       A running count of how many chances left for a
*       correct guess
***********************************************************/
int
main ()
{
// Variables
const int MAX_WRONG = 7;    // Maximum wrong guesses
// PrintHeader–Will output a header for this assignment
bool correctGuess = 0;          // Value indicator for guess
bool delayStartOfLoopInMain = 0;// Delays start till first guess
string isGuessAllowed = "";	// Retrieves correct guess after validation
int incorrectGuesses = 0;	// Number of incorrect guesses so far
string word;		    	// Word to be guessed -> User input
char currentGuess;          // Variable holds value of current
string pastGuesses;         // List of gueses so far
string unsolvedWord;        // Word wiyh unsolved letters covered
char upperCaseGuess;        // Letter in uppercase
char lowerCaseGuess;        //  Letter in lowercase
string wordOnceSolved;      // Compares current state of word to solved word

PrintHeader("Hangman", 'A', 6);
// INPUT: Single line of spaces and characters
// PROCESSING: Validation of letters as they are guessed and replacement
//      to the row of dashes with each new correctly guessed character
// OUTPUT: The updated unguessed word, number of wrong guesses left,
//      list of past wrong and right valid guesses, and closing remarks
//      at game's end.

// Start of user prompts and main program - User is asked for a statement. 
// Getline is used to whitespace along with other characters.
    cout << "Enter phrase: ";
    getline (cin, word);		// Input statement that captures whitespace

// The captured string is sent to the unsolvedWord function so that the
// alphabetic characters can be replaced by dashes.
    unsolvedWord = setupUnsolved (word);

// This new string is output on the screen and the guessing starts in the main 
// loop. 
    cout << "\nPhrase: " << unsolvedWord;

// The processing in the do-while loop will reallocate letters to the string
// returned from get guess into the original word by sending them to function
// updateUnsolved. Additionally the it will reallocate the number of Wrong
// guesses. both processes being parameters that allow the loop to end.
    do
	{
// wordOnceSolved is updated each time in do-while loop
        wordOnceSolved = unsolvedWord;
// delayStartOfLoopInMain is true upon start of the loop, allowing initial
// output to be different than subsequent cycles. These lines will only be
// seen from the second guess onward.
        if (delayStartOfLoopInMain)
		{
            cout << "\nPhrase: ";
// Retrieves the state of the unsolved word from function updateUnsolved by
// sending the three variables 
            cout << updateUnsolved (word, unsolvedWord, currentGuess); 
            cout << endl;
            cout << "\nGuessed so far: ";
// Prints a string of all guesses that were not invalid
            cout << pastGuesses << endl;
            cout << "Wrong guesses left: "; 
// How many wrong tries left
            cout << (MAX_WRONG - incorrectGuesses);
        }
// Sends user to input loop for a new guess, then assigns it as both upper 
// and lower case while it checks original word.
        currentGuess = getGuess (isGuessAllowed);
        upperCaseGuess = toupper (currentGuess);
        lowerCaseGuess = tolower (currentGuess);
        correctGuess = 0;
// Cycles through all the letters in original word to see if letter is there.
// Establishes true reading to bool if the current guess is correct.  
        for (int i = 0; i < word.length (); ++i)
        {
            if (word[i] == upperCaseGuess || word[i] == lowerCaseGuess)
			{
                correctGuess = 1;
                unsolvedWord[i] = currentGuess;
            }
        }
// adds one to wrong guess tally
        if (correctGuess == 0)
		    ++incorrectGuesses;
        correctGuess = 0;
        pastGuesses += currentGuess;
// update soFar to include newly guessed letter
		if (unsolvedWord != word)
            unsolvedWord = updateUnsolved (word, unsolvedWord, currentGuess);
// reassigns true value to delayStartOfLoopInMain
        if (!delayStartOfLoopInMain)
            delayStartOfLoopInMain = 1;
    }
// do-while loop ends when incorrectGuesses reaches 7 or word is solved
    while ((incorrectGuesses < MAX_WRONG) && (unsolvedWord != word));
	// shut down
// Output if game is lost
	if (incorrectGuesses == MAX_WRONG)
	{
        cout << "\nPhrase: " << wordOnceSolved;
        cout << "\n\nGuessed so far: " << pastGuesses;
        cout << "\nWrong guesses left: " << (MAX_WRONG - incorrectGuesses);
        cout << "\n\nYou lost!\n";
    }
// Output if game is won
    else
	{
        cout << "\nPhrase: " << wordOnceSolved;
        cout << "\n\nGuessed so far: " << pastGuesses;
        cout << "\nWrong guesses left: " << (MAX_WRONG - incorrectGuesses);
        cout << "\n\nCongratulations!!\n";
    }
return 0;
}
/****************************************************************
* setupUnsolved
* Replaces String with dashes in place of alphabetic characters
****************************************************************/
string setupUnsolved (                  // Replaces original user input
    string justThelettersCoveredUp)     // With descriptively named variable 
{
// counts out a row of dashes equal in number to string input length
	string blanks (         
			justThelettersCoveredUp.size (), '-');
// Replaces each dash with any original non-alphabetic characters 
// and restores them into the string of dashes.
	for (int i = 0; i < justThelettersCoveredUp.length (); i++)
	{
		if (justThelettersCoveredUp.at (i) > ('A' - 1)
		&& justThelettersCoveredUp.at (i) < ('Z' + 1)
		|| justThelettersCoveredUp.at (i) > ('a' - 1)
		&& justThelettersCoveredUp.at (i) < ('z' + 1))
			justThelettersCoveredUp.at (i) = blanks.at (i);
		if (justThelettersCoveredUp.at (i) == ' ')
			justThelettersCoveredUp.at (i) = ' ';
	}
//Returns string with dashes where letters were. 
return justThelettersCoveredUp;     
}
/****************************************************************
* updateUnsolved
* Replaces unsolved state of word with recent correct guess
****************************************************************/
string updateUnsolved (string phrase, string unsolved, char guess)
{
    char upperCaseGuess;                // Letter as Uppercase
    upperCaseGuess = toupper (guess);   // Assigns current guess as upper
    char lowerCaseGuess;                // Letter as Lowercase
    lowerCaseGuess = tolower (guess);   // Assigns current guess as lower
// Two loops cycle through all letters of word and replace dash or dashes
// with new correct guess. First loop checks for lowercase version of guess.
// The second for uppercase.
    if (phrase.find (lowerCaseGuess) != string::npos)
	{
    	for (int i = 0; i < phrase.length (); ++i)
    	if (phrase[i] == lowerCaseGuess)
        	unsolved[i] = lowerCaseGuess;
	}
if (phrase.find (upperCaseGuess) != string::npos)
	{
	    for (int i = 0; i < phrase.length (); ++i)
	    if (phrase[i] == upperCaseGuess)
		    unsolved[i] = upperCaseGuess;
	}
// shut down
return (unsolved);
}
/****************************************************************
* getGuess
* This function receives a user input character and checks it
* against a running tab of previously tried characters as well as
* making sure it is alphabetic and then returns it as a valid
* guess to main(). (Utilizes global variable proxyGuesses)
****************************************************************/
char getGuess (
    string prevGuesses)
{
	char newguess;  // Single character -> user input
    char uppercase; // Will check both upper   
	char lowercase; // and lowercase versions of input
// Gets new guess from user 
	cout << "\n\nEnter a guess: ";
	cin >> newguess;
// Changes it to uppercase to check against previous guesses 
	uppercase = toupper (newguess);
// Changes it to lowercase to check against previous guesses 
	lowercase = tolower (newguess);
// Continues asking for guess until it is a letter andthat it has not been 
// guessed before. Checks for upper and lowercase while in loop.
	while (bool (!isalpha (newguess))
		  || proxyGuesses.find (uppercase) != string::npos
		  || proxyGuesses.find (lowercase) != string::npos)
	{
		cout << "\nInvalid guess! Please re-enter a guess: ";
		cin >> newguess;
		lowercase = tolower (newguess);
		uppercase = toupper (newguess);
	}
// Adds running total of guessed letters to global variable.
// Instructor told us we couldn't use global variables last time
// but didn't specify for this assignment.
	proxyGuesses += newguess;   
// Returns guess as valid
return newguess;
}
/**********************************************************
* FUNCTION PrintHeader
*_________________________________________________________
* This function receives an assignment name, type
* and number then outputs the appropriate header -
* returns nothing.
*_________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* asName: Assignment Name
* asType: Assignment Type
* asNum: Assignment Number
*
* POST-CONDITIONS
* This function will output the class heading.
*<Post-conditions are the changed outputs either
* passed by value or by reference OR anything affected
* by the function>
***********************************************************/
void PrintHeader(string asName, // IN -Assignment Name
char asType,                    // IN -assignment type
								// -(LAB or ASSIGNMENT)
int asNum)                      // IN -assignment number
{
	cout<<left;
	cout<<"**************************************************\n";
	cout<<"* PROGRAMMED BY : Brian McNaughton\n";
	cout<<"* "<<setw(14) <<"STUDENT ID"<<": 00603923\n";
	cout<<"* "<< setw(14) << "CLASS"<<": CS002 –-> MTWTh 10:45a-12:50p\n";
	cout<<"* ";
// PROC –This will output “LAB #” or “ASSIGNMENT #” based on the
//asTypeand adjust the setwaccordingly
	if(toupper(asType)== 'L')
	{
		cout<<"LAB #"<<setw(9);
	}
	else
	{
		cout<<"ASSIGNMENT #"<<setw(2);
	}
	cout<<asNum<<": "<<asName<< endl;
	cout<<"**************************************************\n\n";
	cout<<right;
}




