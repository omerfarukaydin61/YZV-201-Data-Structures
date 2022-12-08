/* * * * * * * * * * * * * * * * * * * * *
* ONLY INDICATED PARTS SHOULD BE CHANGED *
* * * * * * * * * * * * * * * * * * * * */

/* @Author
* Student Name: <Omer Faruk Aydin>
* Student ID : <150210726>
*/

/* Necessary header files */
#include <iostream>
#include <cstdlib>
#include <limits>
#include <fstream>  // For file operations
#include "stack.h"// TODO: Do not forget to implement

using namespace std;

/* Declaration of the non-member functions */
void print_intro();
void print_basket_info(int);
bool check_end_game();
int get_random_number();
bool get_action();
bool apply_joker();
void empty_baskets();
/* This method generated for avoid complication while taking input from user */
int take_input(std::string);

/* Global stack variables which can be reached anywhere in main.cpp */
Stack basket1, basket2, basket3;

Stack* baskets[3] = { &basket1, &basket2, &basket3 };

int main() {
    /* Random number generator seed */
    // srand(time(NULL));
    srand(42); // uncomment this and comment above line out while testing with Calico

    /* Print game intro to the console */
    print_intro();

    /* Variables to store total points and turn number */
    int points = 0, turn = 0;

    /* Initialize stack variables which is declared before */
    basket1.top = nullptr;
    basket2.top = nullptr;
    basket3.top = nullptr;


    /* Boolean variable for end game condition */
    bool end_game = false;

    /* Main loop of the program */
    while (!end_game) {                     // while end game condition is NOT met

        system("clear");                    // clear console output

        print_basket_info(turn);            // print info of all baskets

        if (!get_action()) {                // users make their move
            points -= 10;                 // if users make an illegal move, reduce points
            continue;
        }

        end_game = check_end_game();        // check for end game condition

        /* If game does not end, give user 10 more points */
        if (!end_game) {
            points += 10;
        }

        turn++;                             // go to the next turn
    }

    /* When game ends, print final basket info */
    print_basket_info(turn);

    /* Print total points */
    cout << endl;
    cout << "GAME OVER." << endl;
    cout << "Total points: " << points << endl;

    /* Give all allocated memory back */
    empty_baskets();

    return 0;
}

/* This method generated for avoid complication while taking input from user */
int take_input(std::string message) {
    cout << message << endl;
        int result;
        cin >> result;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            result = -1;
        }
    return result;
}

/* Print game intro to the console */
void print_intro() {
    cout << " ____________________  " << endl;
    cout << "|                    | " << endl;
    cout << "|    Hanoi Baskets   | " << endl;
    cout << "|____________________| " << endl;
    cout << " \\/\\/\\/\\/\\/\\/\\/\\/\\/\\/  " << endl;
    cout << "  \\/\\/\\/\\/\\/\\/\\/\\/\\/   " << endl;
    cout << "   \\/\\/\\/\\/\\/\\/\\/\\/    " << endl;
    cout << "    \\/\\/\\/\\/\\/\\/\\/     " << endl;
    cout << "     \\/\\/\\/\\/\\/\\/      " << endl;
    cout << "      \\/\\/\\/\\/\\/       " << endl;
    cout << "       \\/\\/\\/\\/        " << endl;
    cout << endl;
    cout << "Please put incoming numbers to one of three baskets with the goal of obtaining three baskets filled with numbers from highest (at the bottom) to the lowest (at the top)." << endl;
    cout << endl;
    cout << "Press enter to continue.." << endl;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');      // Wait for enter key

    /* If we use cin.get() and user presses other than enter with
    more than one character, we will end up with an endless loop.
    So, we need to force stream to ignore the bad input. */
}

/* Print info of all baskets */
void print_basket_info(int turn) {
    cout << endl;
    cout << "Turn " << turn << ": Baskets look like this:" << endl;

    cout << "Basket 1:" << endl;;
    basket1.print_all();

    cout << "Basket 2:" << endl;;
    basket2.print_all();

    cout << "Basket 3:" << endl;;
    basket3.print_all();

    cout << endl;
}

/* Check for end game condition */
bool check_end_game()
{
    for (size_t i = 0; i < 3; i++)
    {
        if (!baskets[i]->Is_Descending())
        {
            return true;
        }
    }
    return false;
}

/* Get a random number between 0-10 */
int get_random_number() {

    int random = rand() % 10;
    cout << "Incoming number: " << random << endl;

    return random;
}

/* Users make their move */
bool get_action() {
    int number = get_random_number();   // get a random number between 0-10

    cout << endl;
    cout << "Press 0 to see jokers." << endl;
    cout << "Where to put the incoming number: ";
    int index;
    cin >> index;                       // get input from the user for the next move

    /* If given input is not integer (illegal move), error will occur.
    Clean stream buffer and ignore the bad input. */
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        index = -1;
    }
    if (index == -1)
        return false;
    if (index == 0)                // if user wants to see jokers
        return !apply_joker();
    else
    {
        baskets[index - 1]->Push(number);   // put the number to the basket
        return true;
    }
    return true;
}

/* User chooses to use a joker */
bool apply_joker() {
    cout << endl;
    cout << "Choose a joker: " << endl;
    cout << "1. Merge baskets: move elements from second basket to the first basket without breaking the order of the elements. (highest at the bottom, lowest at the top)" << endl;
    cout << "2. Sequentialize basket: remove elements which break consecutiveness from a basket." << endl;
    cout << endl;
    int index;  
    cin >> index;

    /* If given input is not integer (illegal move), error will occur.
    Clean stream buffer and ignore the bad input. */
    if (cin.fail()) {
        cin.clear();    
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        index = -1;
    }
    if (index == -1)
        return false;

    if (index == 1)     // if user wants to merge baskets
    {
        int first = take_input("Choose first basket: ");    // get input from the user for the first basket
        if (first == -1)
            return false;

        int second = take_input("Choose second basket: ");  // get input from the user for the second basket
        if (second == -1)
            return false;

        baskets[first - 1]->Merge_Basket(baskets[second - 1]);  // merge the baskets
        return true;
    }
    if (index == 2)     // if user wants to sequentilize a basket
    {
        int basket = take_input("Which basket should be sequentilized: ");  // get input from the user for the basket

        baskets[basket - 1]->Sequentilized();
        return true;
    }
    return true;
}

/* Empty all baskets */
void empty_baskets() {
    basket1.emptyAllNodes();
    basket2.emptyAllNodes();
    basket3.emptyAllNodes();
}