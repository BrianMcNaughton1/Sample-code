/**********************************************************
 *  AUTHOR      : Brian McNaughton
 *  Assignment  : Cipher
 *  CLASS       : CS002
 *  SECTION     : MTWTh 10:45-12:50
 *  DUE DATE    : 3/20/20
 *********************************************************/
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
/**********************************************************
 *
 * CIPHER PROJECT - PROGRAM ENCRYPTS AND DECRYPTS A WORD
 * ACCORDING TO USER CHOSEN CHARACTER KEY
 * __________________________________________________________
 *
 * This program will encrypt or decrypt a word from the users
 * choice of alphabet map: either user created or default.
 * __________________________________________________________
 * INPUT:
 *  Choice of encryption or decryption
 *  Choice of default alphabet map or user created
 *  Word to decode or encode
 * OUTPUT:
 * The word chosen is returned after it has been changed
 * according to the chosen key.
 *
 ***********************************************************/
int main()
{

//Variables
int count;			// Variable to hold the loop count
// String alphabet is the reference for usermap and default
string alphabet = ("abcdefghijklmnopqrstuvwxyz");
string map;         // Variable for map actually chosen
string word;		// Stores word to decrypt or change
                    // -> user input
string usermap;     // User designated alphabet key
                    // -> user input
string method;      // variable for choice for encryption
                    // -> user input

// Input statements and error messages
{
    // User input - program asks for choice to code or decode word
    cout << "What is the method (encryption or decryption)? ";
    cin >> method;
    if ((method == "encryption") || (method == "decryption"))
    {
        cout << "\nWhat is the translation map (type 'default' to use default): \n";
        cin >> map;
    }
    // Error statement for invalid method
    else if (!(method == "encryption") && !(method == "decryption"))
    {
        cout << "Error: invalid method choice.\n";
        return (0);
     }
    // User input - program asks for a word
    if ((map == "default") || (map.length() == 26))
    {
        cout << "What is the single word to translate: \n";
        cin >> word;
    }
    // Error statement for invalid map size
    else if (!(map == "default") && !(map.length() == 26))
    {
        cout << "Error: invalid translation map size.\n";
        return (0);
    }

    // Loops to return deciphered word from chosen key
    // First loop: default map loops perform encryption or
    // decryption, returning error messages if choice of word
    // does not match the default characters.
    if (map == "default")
    {
        map = "zyxwvutsrqponmlkjihgfedcba";
        // This loop counts through each letter of word, then
        // replaces the place in the word with a new letter
        if (method == "encryption")
        {
            // This loop counts through each letter of a word, then
            // replaces it with a new letter from the default encryption
            // map.
            for (count = 0; count < word.length(); count++)
            {
                char test = word.at(count);
                // Error statement for invalid use of map
                if ((test >26 + 'a') || (test < 'b' - 1))
                {
                    cout << "Error: encryption cannot be performed.\n";
                    return(0);
                }
                int pos = word.at(count) - 'a';
                word.at(count) = map.at(pos);
             }
            cout << "Encrypted word: " << word << "\n";
        }
        // This loop counts through each letter of word that has
        // been encrypted then replaces that letter with the original
        // prior to encryption.
        else if (method == "decryption")
        {
            for (count = 0; count < map.length(); count++)
            {
                int pos = map.at(count) - 'a';
                map.at(count) = alphabet.at(pos);
             }
            for (count = 0; count < word.length(); count++)
            {
                char test = word.at(count);
                // Error statement for invalid use of map
                if ((test >26 + 'a') || (test < 'b' - 1))
                {
                    cout << "Error: decryption cannot be performed.\n";
                    return(0);
                }
                int pos = word.at(count) - 'a';
                word.at(count) = map.at(pos);
             }
            cout << "Decrypted word: " << word << "\n";
        }
    }
    // These loops perform encryption or decryption on user map
    // returning error messages if choice of word does not match
    // the characters chosen for new alphabet.
    else if (!(map == "default"))
    {
        // This loop counts through each letter of a word, then
        // replaces it with a new letter from the chosen encryption
        // map.
        if (method == "encryption")
        {              
			// Error statement for invalid choice of word
            for (count = 0; count < word.length(); count++)
            {
                char test = word.at(count);
                if ((test >26 + 'a') || (test < 'b' - 1))
                {
                    cout << "Error: encryption cannot be performed.\n";
                    return(0);
                }
             
            }           
                for (count = 0; count < word.length(); count++)
                {
                    int pos = alphabet.find(word.at(count));
                 
                    word.at(count) = map.at(pos)  ;
                 }
            cout << "Encrypted word: " << word << "\n";
        }
        // This loop counts through each letter of word that has
        // been encrypted then replaces that letter with the original
        // letter prior to encryption
        
        else if (method == "decryption")
        {
            for (count = 0; count < word.length(); count++)
            {
                // Error statement for invalid use of map
                std::size_t found = map.find(word.at(count));
                if (found==std::string::npos)
                {
                    cout << "Error: decryption cannot be performed.\n";
                    return(0);
                }                
             }                
			for (count = 0; count < word.length(); count++)
			{
				int pos = map.find(word.at(count));				
				word.at(count) = alphabet.at(pos)  ;
			 }
		cout << "Decrypted word: " << word << "\n";	  
        }
    }
}
return (0);
}



