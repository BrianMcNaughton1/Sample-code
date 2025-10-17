/**********************************************************
 *  AUTHOR      : E Brian McNaughton
 *  Assignment  : Final Project - Battleship
 *  CLASS       : CS002
 *  SECTION     : MTWTh 10:45a-12:50p
 *  DUE DATE    : 5/11/21
 *********************************************************/
#include <vector> 
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
using namespace std;
/************************************************************
*
* TWO PLAYER BATTLESHIP
*___________________________________________________________
* This program does follows the classic format of the HASBRO 
* game battleship two players take turns placing 5 ships of
* varying lengths on a 10x10 grid. The players then take 
* turns firing at the oppponent's ships by calling the letter
* row and number column of their guesses. The game ends when 
* one player sinks all the oppponents ships.
*___________________________________________________________
* INPUTS:
* Row: A character from A to J denotes the row to place ship
* Column: A number from 1 to 10 corresponds to column of grid
* Direction: 'h' horizontal or 'v' vertical for ship placement  
* Row: A character from A to J denotes the row to fire a shot
* Column: A number from 1 to 10 corresponds to column for shot
*
* OUTPUTS:
* DisplayBoard: Both the boards will be Visible on the screen.
*				While one player is firing the opponents ships
*               will not be displayed. Only (H)its and (M)isses
* Ship sunk: Each ship's name is output to screen once sunk
* Game won message: Congratulations are handed to the victor.
*************************************************************/
// CONSTANTS
int Carrier_SIZE = 5;			// Size of ship
int Battleship_SIZE = 4;		// Size of ship
int Cruiser_SIZE = 3;			// Size of ship
int Submarine_SIZE = 3;			// Size of ship
int Destroyer_SIZE = 2;			// Size of ship
int FLEET_SIZE = 5;				// Number of ships in fleet
int GRIDSIZE = 10;				// Size of square grid

//STRUCTURES
struct Point 					// Strucure stores ship's 
{								// indexes 
    int row;					// Hold row index in 2d array
    int column;					// Holds column index of array
    Point(						// This constructor solves a
        unsigned int row, 		// problem associated with 
        unsigned int column) 	// intializing vectors of the
        : row (row), 			// struct type point allowing
        column (column) 		// for direct implementation 
        {}						// of the push_back command.
};

struct Ship 					// Strucure stores important 
{								// values for each ship in game
    string shipName;			// Holds name of ship
    int shipSize;				// Stores the ship size
    int shipHitcount;			// Stores number of times ship was hit
    bool shipShape;				// Stores a 0 if the ship is sunk
    vector < Point > s ;		// vector stores the indexes of ship on grid
};

struct PlayerBoard 				// Structure stores the sum of information for  
{								// player: grid, fleet, and how many not sunk
    char p[10][10];    			// Two dimensional array stores hits and misses
    Ship fleet[5];				// Array of ship structs for player's fleet
    int leftAfloat;				// Number counts remaining ships afloat 
};

// FUNCTIONS

void PrintHeader(string asName,	// IN -Assignment Name
	char asType,				// IN -assignment type	// -(LAB or ASSIGNMENT)
	int asNum);					// IN -assignment number

void							// Function checks to see if a ship is sunk 
gameStatus(						// Takes the board fired at; the row, and 
    PlayerBoard&,				// column numbers for array and passes changes
    int&, 						// by reference to the attacked players board
    int&);						// as well as outputting name if a ship is sunk
    
bool 							// Function takes the PlayerBoard; row and 
spaceOccupied (					// column numbers; a char for direction; and  
PlayerBoard&, 					// the ship's size. Returns a one if the 
int&, 							// desired placement is occupied
int&, 							
char&,   						
int&);							
 
int convertPosition (			// Function takes a char letter and returns
        char);	        		// an integer. An 11 is returned if error

void setShip (					// Function takes PlayerBoard and fleet index 
    PlayerBoard &,				// and places individual ship onto array and 
    int);						// into vector after calling getValidShipInfo
 
void getValidShipInfo (			// Function takes by reference: row and column 
    int &, 						// ints, a direction char, and a PlayerBoard 
    int &, 						// structure. A ship index is also taken. The
    char &,						// Function Takes user input to place ships.
    PlayerBoard &, 				// onto the players 2d array.
    int shipIndex);				
    
void fireShot(					// Function takes enemy PlayerBoard object by 
    PlayerBoard &);				// reference and initiates attack phase
 
void initBoard (				// Function runs loop to call setShip function
    PlayerBoard &, 				// for each of the five ships in players fleet
    PlayerBoard &);				// takes two PlayerBoard objects by reference
 
void initFleet (				// Function initializes values for fleet,
    PlayerBoard &);				// passes by reference to PlayerBoard object

void DisplayBoard (				// Function uses the two PlayerBoard objects 
    PlayerBoard &, 				// to print the grids onto the monitor
    PlayerBoard &);

int
main () 
{
    // PrintHeader–Will output a header for this assignment
	PrintHeader("Final Project: BATTLESHIP", 'A', 12);
	
	// Variables
	bool playerturn ;
    int turn=0;
    PlayerBoard pBoard1;
    PlayerBoard pBoard2;
    
	// initFleet sets initial values to players' grid, fleet, and game status
    initFleet (pBoard1);
    initFleet (pBoard2);
    
    // initBoard function begins function calls that oversee placement of ships
    // initBoard calls setShip which calls getValidShipInfo which calls 
    // spaceOccupied. DisplayBoard function is also called by initBoard 
    // to show each ships placement throughout the loop and after all ships are
    // placed. This is repeated for player two.
    cout << "Player 1 set your board.\n";
    DisplayBoard (pBoard2, pBoard1);
    initBoard (pBoard1, pBoard2);
    DisplayBoard (pBoard1, pBoard2);
    DisplayBoard (pBoard2, pBoard1);
    cout << "\n\n\nPlayer 2 set your board.\n";
    initBoard (pBoard2, pBoard1);
    
    // During the rest of the game the players take turns firing at the other's
    // 10x10 array until all five of one of the players ships have been sunk
    // This loop uses a modulo two statement to alternate between the two 
    // players. The DisplayBoard function shown prior to the shot 
    // is not intended to be seen by the current player. The result of the fired
    // shot is on the subsequently printed screen. The user input for the game's
    // remainder is taken in the fireShot function. After each turn the program
    // checks the PlayerBoard object .leftAfloat which returns a zero if all 
    // ships are sunk. When that happens the winner is congratulated and the 
    // game is over.
    do 
    {
        playerturn = turn%2 ;
        if(!playerturn)
        {
            DisplayBoard (pBoard2, pBoard1);
            cout <<"Player 1:\n"; 
            fireShot(pBoard2);
        }
        if (!pBoard2.leftAfloat)
        {
            cout <<"\n\n\nYou sunk the fleet!!! You win!!!\n";
            return 0;
        }
        if (playerturn)
        {
            DisplayBoard (pBoard1, pBoard2);
            cout <<"Player 2:\n";
            fireShot(pBoard1);
        }
        if (!pBoard1.leftAfloat)
        {
            cout <<"\n\n\nYou sunk the fleet!!! You win!!!\n";
            return 0;
        }
        turn++;
     }
    while (turn <200) ;
    return 0;
}
/**********************************************************
*
* FUNCTION setShip
*_________________________________________________________
* This function receives a reference PlayerBoard object, 
* and an integer representing the ship's index in the fleet
* arrayand returns nothing
*_________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* index: The index of the ship to be placed
* type: The PlayerBoard object needs to have been initialized
* 
* POST-CONDITIONS
* This function will call getValidShipInfo for the information
* on where to place a ship. It will then place the coordinates
* returned onto the 10x10 player grid as well as assigning the 
* struct Point vector values for the indexes that comprise the
* ship's placement.
***********************************************************/
void
setShip (
    PlayerBoard & type, 
    int index) 
{
    int row;
    int col;
    char dir;
    getValidShipInfo (row, col, dir, type, index);
    for (unsigned int i = 0; i < type.fleet[index].shipSize; i++)
    {
        if (dir == 'v')
        {	
            type.p[row + i][col] = 's';
            type.fleet[index].s.push_back(Point(row+i,col));
        }     
        if (dir == 'h')
        {
            type.p[row][col + i] = 's';
            type.fleet[index].s.push_back(Point(row,col+i));
        }
    }
}
/**********************************************************
*
* FUNCTION getValidShipInfo
*_________________________________________________________
* This function receives integers for row and column, a
* character for direction, and a PlayerBoard obect; all
* by reference. It also takes an integer for the ship 
* index by value. It returns nothing.
*_________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* type: The PlayerBoard object needs to have been initialized
* shipIndex: The function needs to know which ship to set 
*
* POST-CONDITIONS
* This function will take user input so that the function
* setShip can place it onto the 2d array found in a 
* PlayerBoard object. It implements the convertPosition and
* spaceOccupied functions to respectively change a char to 
* an int, and see if there is space for the newly placed
* ship.
***********************************************************/
void
getValidShipInfo (
    int &row, 
    int &column, 
    char &dir, 
    PlayerBoard & type,
    int shipIndex) 
{
    int c;
    int r;
    int size = type.fleet[shipIndex].shipSize;
    char rowchar;
    bool boolval=false;
    //The following loop runs until valid coordinates are given
    do
    {
        boolval=false;
        cout << "Enter the starting coordinates of your " << type.
    	fleet[shipIndex].shipName << ": ";
        cin >> rowchar; 
        cin >> c;
        r = convertPosition (rowchar);
        c -= 1;
        cout << "\nEnter the orientation of your carrier "
	    << "(horizontal(h) or vertical(v)): ";
        cin >> dir;
        // An if statement checks that the entry is valid
        if (dir != 'h' && dir != 'v' 
        && dir != 'H' && dir != 'V' 
        || r < 0|| r > 9 || c < 0 || c > 9 
        || dir == 'v' && size + r >  10
        || dir == 'h' && size + c > 10)
            boolval=1;
        // An error message is read otherwise
	    if (boolval)
            cout << "Error: Ship placement is outside the board.\n";
        // The spaceOccupied function is then called
        // and if the return is true an error message reads to screen
        if (!boolval&&spaceOccupied (type, r, c, dir, size))
        {
            cout << "Error: Space already occupied.\n";
            boolval=1;
        }
    }
    while (boolval);
    // Now that the the user input has been validated the reference variables
    //  are rewritten to include the new coordinates. 
    row = r;
    column = c;
}
/**********************************************************
*
* FUNCTION initBoard
*_________________________________________________________
* This function takes by reference two PlayerBoard objects
* and returns nothing
*_________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* pBoard1: PlayerBoard object for first player
* pBoard2: PlayerBoard object for f player
*
* POST-CONDITIONS
* This function calls setShip five times to set a player's
* fleet coordinates into the PlayerBoard array and vector
***********************************************************/
void
initBoard (
    PlayerBoard & pBoard1, 
    PlayerBoard & pBoard2) 
{
    for (unsigned int i = 0; i < 5; i++)
    {
        setShip (pBoard1, i);
        if (i<4)
            DisplayBoard (pBoard1, pBoard2);
    }
} 
/**********************************************************
*
* FUNCTION initFleet
*_________________________________________________________
* This function receives a PlayerBoard object by reference
* and returns nothing.
*_________________________________________________________
* PRE-CONDITIONS
* None
*
* POST-CONDITIONS
* This function will set initial values to all but one
* of the elements contained in the fleet of a PlayerBoard 
* object. The remaining values for the vector of Points will
* be set by a different function. It also sets the rows and
* columns of the two-dimensional array to include spaces at
* every position.
***********************************************************/
void
initFleet (
    PlayerBoard & pBoard) 
{
    pBoard.leftAfloat=FLEET_SIZE;
    pBoard.fleet[0].shipName = ("carrier");
    pBoard.fleet[0].shipSize = Carrier_SIZE;
    pBoard.fleet[1].shipName = ("battleship");
    pBoard.fleet[1].shipSize = Battleship_SIZE;
    pBoard.fleet[2].shipName = ("cruiser");
    pBoard.fleet[2].shipSize = Cruiser_SIZE;
    pBoard.fleet[3].shipName = ("submarine");
    pBoard.fleet[3].shipSize = Submarine_SIZE;
    pBoard.fleet[4].shipName = ("destroyer");
    pBoard.fleet[4].shipSize = Destroyer_SIZE;
    for (int i = 0; i < FLEET_SIZE; i++)
    {
        pBoard.fleet[i].shipShape = 1;
        pBoard.fleet[i].shipHitcount = pBoard.fleet[i].shipSize;
    }
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            pBoard.p[i][j] = ' ';
} 
/**********************************************************
*
* FUNCTION DisplayBoard
*_________________________________________________________
* This function receives two PlayerBoard objects by 
* reference and returns nothing.
*_________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* pboard1: PlayerBoard object for player one
* pboard2: PlayerBoard object for player two
*
* POST-CONDITIONS
* This function will output the two players boards to the 
* screen. The second board will not display the 's'
* character that denotes the ship's placement
***********************************************************/
void
DisplayBoard (
    PlayerBoard & pboard1, 
    PlayerBoard & pboard2) 
{
    cout << "                  Your Board"
    << "                                          Enemy Board\n"
    << "    1   2   3   4   5   6   7   8   9  10"
    << "                1   2   3   4   5   6   7   8   9  10\n"
    << "  -----------------------------------------"
    << "            -----------------------------------------\n";
    // A nested for loop prints the information of the 2d arrays
    // found within each PlayerBoard object, as well as an alphabetical
    // character for the rows A - J. If an 's' is detected on the
    // second board the program instead prints a blank space.
    for (int i = 0; i < GRIDSIZE; i++)
    {
        cout << char ('A' + i);
        for (int j = 0; j < GRIDSIZE; j++)
            cout << " | " << pboard1.p[i][j];
        cout << " |          ";
        cout << char ('A' + i);
        for (int j = 0; j < GRIDSIZE; j++)
	    {
	        cout << " | ";
            if (pboard2.p[i][j] == 's')
                cout << ' ';
	        else
                cout << pboard2.p[i][j];
        }
        cout << " |\n"
        << "  -----------------------------------------"
	    << "            -----------------------------------------\n";
    }
}

/****************************************************************
* Function convertPosition takes a char letter and returns an 
* alphabet index (a is 0, A is 0, J=9, j=9 etc.) 
****************************************************************/ 
int 
convertPosition (
    char position) 
{
    int charpos;
    if (position >= 'A' && position <= 'J')
        charpos = position - 65;
    if (position>= 'a' && position <= 'j')
        charpos = position - 97;
    else 
        position = 11;
    return charpos;
}
/**********************************************************
*
* FUNCTION spaceOccupied
*_________________________________________________________
* This function receives a PlayerBoard obect,integers for 
* row and column,a character for direction, and  an integer 
* for the ship size; all by reference. Returns true if
* There is already a ship in the space requested.
*_________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* row: integer number for row
* col: integer number for column
* dir: character for horizontal or vertical direction
*
* POST-CONDITIONS
* This function will output the class heading.
* loop through the desired cooordinates the user has 
* entered for a ship's placement, using the ship's size as 
* the maximum length of loop. If a pre-existing placement
* is recognized a bool value of true will be returned.
***********************************************************/ 
bool 
spaceOccupied (
PlayerBoard& type, 
int& row, 
int& col, 
char& dir,
int& shipSize) 
{
    int count = 0;
    for (int i = 0; i < shipSize; i++)
    {
        if (dir == 'v')
            if (type.p[row + i][col] == 's')
                count++;
        if (dir == 'h')
            if (type.p[row][col + i] == 's')		
                count++;
    }
    if (count)
        return true;
    else
        return false;
}
/**********************************************************
*
* FUNCTION fireShot
*_________________________________________________________
* This function receives a reference PlayerBoard object
* and returns nothing.
*_________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* enemy: The PlayerBoard object that is going to be fired at
*
* POST-CONDITIONS
* This function will take user input of a character and an
* integer representing row and column. It will adjust the 
* input so the proper 0 - 9 numbers needed to access the array
* are derived, utilizing convertPosition and -=1. If an 's'
* is found in the user input index, it is replaced by 'H'; 
* Invalid entries are dismissed with an error message. If the
* user misses with their attempt, an 'M' is written onto the
* array at that position.
***********************************************************/
void fireShot(PlayerBoard & enemy)
{
    bool boolval=0;  
    char crow;
    int row;
    int col;
    int count;
    do
    {
        boolval=false; 
        cout << "Fire a shot: ";
        cin >> crow;
        cin >> col;
        row = convertPosition (crow);
        col -= 1;
        if (row < 0 || row > 9 || col < 0 || col > 9)
            boolval = true;
	    if (boolval)
            cout << "Invalid\n";
	    if(!boolval && enemy.p[row][col] == 'M' 
	    || !boolval && enemy.p[row][col] == 'H')
       {
	        cout << "Invalid\n";
	        boolval=1;
       }
    }
    while (boolval);
    {
        if (enemy.p[row][col]=='s')
        {
            int r=row;
            int c=col;
            enemy.p[row][col]='H';
            cout<<"Hit!!!\n";
            gameStatus(enemy, r, c);
        }
        if (enemy.p[row][col]==' ')
        {
            enemy.p[row][col]='M';
            cout<<"You Missed\n"; 
        }
    }    
}
/**********************************************************
*
* FUNCTION gameStatus
*_________________________________________________________
* This function receives by reference a PlayerBoard object,
* and two integers. Nothing is returned.
*_________________________________________________________
* PRE-CONDITIONS
* The following need previously defined values:
* wasHit: The PlayerBoard object that was struck
* row: integer number for row
* col: integer number for column
* 
*
* POST-CONDITIONS
* This function will loop through all of the ships in the
* player's fleet to find which indexes match the hit that
* was just registered on the 2d array. When a match is found
* the ship's hit points are decreased by one. When 
* .shipHitcount reaches zero .shipShape is set to false. A 
* notification is then printed to the the screen of which
* ship has been destroyed. The value .leftAfloat is also
* reduced by one.
***********************************************************/
void gameStatus(
    PlayerBoard&wasHit,
    int &row, 
    int &col)
{   
    for (unsigned int j = 0; j < FLEET_SIZE; j++)
    {
        unsigned int z = wasHit.fleet[j].shipSize;
        for (unsigned int s = 0 ; s < z; s++)
        {
            if (row == wasHit.fleet[j].s[s].row 
            && col == wasHit.fleet[j].s[s].column)
            { 
                wasHit.fleet[j].shipHitcount--;
                if (!wasHit.fleet[j].shipHitcount)
                    wasHit.fleet[j].shipShape = 0;
                if (!wasHit.fleet[j].shipShape)
               {
                   wasHit.leftAfloat--;
                   cout << "You sunk the " 
                   << wasHit.fleet[j].shipName 
                   << "!!!\n" ;
               }
            }
        }
    }
}
/**********************************************************
*
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

void PrintHeader(
string asName, 					// IN -assignment Name
char asType, 					// IN -assignment type: (LAB or ASSIGNMENT)
int asNum)						// IN -assignment number
{
	cout<<left;
	cout<<"**************************************************\n";
	cout<<"* PROGRAMMED BY : Brian McNaughton\n";
	cout<<"* "<<setw(14) <<"STUDENT ID"<<": 00603923\n";
	cout<<"* "<< setw(14) << "CLASS"<<": CS02 –-> MTWTh - 10:45a-12:50p\n";
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
	cout << asNum << ": " << asName << endl;
	cout << "**************************************************\n\n";
	cout << right;
}



