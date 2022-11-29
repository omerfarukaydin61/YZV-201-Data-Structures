//--- 2022-2023 Fall YZV201E Assignment 1 ---//
//--------------------------//
//---Name & Surname: Omer Faruk Aydın
//---Student Number: 150210726
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//

#include <iostream>  // For input/output operations
#include <cstring>
#include <vector>
using namespace std;
#include "WordList.h"

//-------------Word Methods-------------//

Word::Word() {
	word_ = "";
	edit_dist_ = 999;  // An arbitrary number to set the distance as infinite
	next_ = NULL;
}

Word::Word(std::string vocab_word) {
	word_ = vocab_word;
	edit_dist_ = 999;  // An arbitrary number to set the distance as infinite
	next_ = NULL;
}

int Word::EditDist(std::string str) {
	return this->CalculateLevenshteinDistance(str, this->word_);
}

/* Levenshtein Distance Calculator */
int Word::CalculateLevenshteinDistance(std::string target, std::string source) {
	int targetLength = target.size();
	int sourceLength = source.size();
	int** distance = new int* [targetLength + 1];
	for (int i = 0; i < targetLength + 1; i++) {
		distance[i] = new int[sourceLength + 1];
	}

	for (int i = 0; i <= targetLength; i++) {
		distance[i][0] = i;
	}
	for (int j = 0; j <= sourceLength; j++) {
		distance[0][j] = j;
	}
	for (int i = 1; i <= targetLength; i++) {
		for (int j = 1; j <= sourceLength; j++) {
			int cost = Word::SubsCost(target[i - 1], source[j - 1]);
			distance[i][j] = Word::Min(Word::Min(distance[i - 1][j] + 1, distance[i][j - 1] + 1), distance[i - 1][j - 1] + cost);
		}
	}
	return distance[targetLength][sourceLength];
}
int Word::Min(int a, int b) {
	return a < b ? a : b;
}
int Word::Min(int a, int b, int c) {
	return Min(a, Min(b, c));
}
int Word::SubsCost(char c1, char c2) {
	return c1 == c2 ? 0 : 2;
}

//-------------WordList Methods-------------//

WordList::WordList() {
	this->head_ = NULL;
}

WordList::~WordList() {
	Word* traverse = head_;

	// To make sure that we clear the memory when the program ends.
	while (traverse != NULL) {
		Word* temp = traverse;
		traverse = traverse->next_;
		delete temp;
	}
}

void WordList::AddWord(std::string str) {

	Word* newWord = new Word(str);

	if (IsEmpty())
	{
		this->head_ = newWord;
		return;
	}

	Word* tempWord = this->head_;

	while (tempWord->next_ != NULL)
	{
		tempWord = tempWord->next_;
	}
	tempWord->next_ = newWord;
}

void WordList::PrintWords(int count) {

	if (!(count > 0) || IsEmpty())
		return;

	Word* tempWord = this->head_;

	while (count > 0 && tempWord != NULL)
	{
		PrintToConsole(tempWord->word_);
		tempWord = tempWord->next_;
		count--;
	}
}

void WordList::CalcEditDists(std::string str) {
	if (IsEmpty())
		return;

	Word* tempWord = this->head_;

	while (tempWord != NULL)
	{
		tempWord->edit_dist_ = tempWord->EditDist(str);
		tempWord = tempWord->next_;
	}
}

void WordList::PrintEditDists(int count) {
	if (!(count > 0) || IsEmpty())
		return;

	Word* tempWord = this->head_;

	while (count > 0 && tempWord != NULL)
	{
		PrintToConsole(std::to_string(tempWord->edit_dist_));
		tempWord = tempWord->next_;
		count--;
	}
}
void WordList::PrintToConsole(std::string str) {
	std::cout << str << std::endl;
}

bool WordList::IsEmpty() {
	return this->head_ == NULL;
}