//--- 2022-2023 Fall YZV201E Assignment 1 ---//

//*****DO NOT EDIT MAIN FILE*****//

#include <iostream>  // For input/output operations
#include <fstream>  // For file operations
#include "WordList.h"


int main(int argc, char** argv) {
    //-------------Variable Declarations-------------//
    WordList vocabulary;
    std::string word;
    std::string miss_word;
    int num_of_words;
    int num_of_suggestions;
    int mode;


    //-------------Creating Vocabulary List from File-------------//
    std::ifstream vocab_file("vocabulary.txt");
    while (!vocab_file.eof()) { 
        vocab_file >> word;
        vocabulary.AddWord(word);
    }
    vocab_file.close();


    //-------------To Check Methods Separately-------------//
    std::cout << "Select a mode:" << std::endl;
    std::cin >> mode;

    switch (mode) {
    case 1:
        //-------------Print First n Words-------------//
        std::cout << "How many words to print?:" << std::endl;
        std::cin >> num_of_words;
        std::cout << "\nPrinting the first " << num_of_words << " words:" << std::endl;
        vocabulary.PrintWords(num_of_words);
        break;

    case 2:
        //-------------Print Edit Dist. of First n Words-------------//
        std::cout << "How many words to print?:" << std::endl;
        std::cin >> num_of_words;
        std::cout << "Type a misspelled word:" << std::endl;
        std::cin >> miss_word;
        vocabulary.CalcEditDists(miss_word);
        std::cout << "\nPrinting the edit distances of first " << num_of_words << " words:" << std::endl;
        vocabulary.PrintEditDists(num_of_words);
        break;

    default:
        break;
    }

    return 0;
}
