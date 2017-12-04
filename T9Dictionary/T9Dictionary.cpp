// T9Dictionary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <list>
#include <string>
#include <sstream>

//using namespace std;


std::map<int, std::vector<char>> MyMap;
std::vector<std::string> words;

//Struktura drvesa (Trie)
struct Node
{
	bool end;
	bool endOfTree;
	int countPrefix;
	struct Node* child[9];
	std::list<std::string> listOfWords;
}
*head;


void initHead() {
	head = new Node();
	head->end = false;
	head->countPrefix = 0;
}


int findKeyOfValue(char slovo) {
	int findKey = 0;
	std::map<int, std::vector<char>>::const_iterator it;
	for (it = MyMap.begin(); it != MyMap.end(); ++it)
	{
		for (int i = 0; i < MyMap[it->first].size(); i++) {
			if (it->second[i] == slovo)
			{
				findKey = it->first;
				return findKey;
				//break;
			}
		}
	}
	return findKey;
}

//Broj rijeci za umetanje
void insertWordInTree(std::string word) {
	Node *current = head;
	current->countPrefix++;
	words.push_back(word);
	head->listOfWords.push_back(word);

	for (int i = 0; i < word.length(); i++) {
		//int letter = (int)word[i] - (int)'a';
		int letterOfNumber = findKeyOfValue(word[i]);
		std::cout << "i[" << word[i] << " ]: " << letterOfNumber << std::endl;
		if (current->child[letterOfNumber] == NULL) {
			current->child[letterOfNumber] = new Node();
		}
		current->child[letterOfNumber]->countPrefix++;
		current = current->child[letterOfNumber];
		current->listOfWords.push_back(word);
	}
	current->end = true;
	std::cout << std::endl;

}


//trazenje rijeci u dictionary
bool searchWord(std::vector<int> word) {

	Node *current = head;
	for (int i = 0; i < word.size(); i++) {
		if (current->child[word[i]] == NULL) {
			std::cout << "EMPTY" << "\n";
			return false;
		}
		current = current->child[word[i]];
	}
	for (auto v : current->listOfWords)
		std::cout << v << " ";
	std::cout << std::endl;
	return current->end;
}


void initT9MapTable() {

	for (int i = 2, letter = 97; i <= 9; i++) {

		if (i == 7 || i == 9) {
			MyMap[i] = { (char)letter++, (char)letter++, (char)letter++, (char)letter++ };
		}
		else {
			MyMap[i] = { (char)letter++, (char)letter++, (char)letter++ };
		}
	}
}





int main()
{

	//std::cout << "Hello world " << std::endl;
	initHead();
	initT9MapTable();
	/*
	insertWordInTree("ala");
	insertWordInTree("aka");
	insertWordInTree("kot");
	insertWordInTree("kolor");
	insertWordInTree("lokos");
	insertWordInTree("lotos");
	*/

	/*
	std::vector<int> decodeWord;
	decodeWord.push_back(5);
	decodeWord.push_back(6);
	decodeWord.push_back(5);
	decodeWord.push_back(6);
	decodeWord.push_back(7);
	searchWord(decodeWord);
	*/

	
	std::cout << "INPUT: \n";
	int numOfWords, numOfDecWords;

	std::cout << "Broj rijeci koje cemo uvesti u rijecnik: " << "\n";
	std::cin >> numOfWords;

	std::cout << "Broj rijeci koje cemo dekodirati: " << "\n";
	std::cin >> numOfDecWords;
	std::vector<int> *decodeWord = new std::vector<int>[numOfDecWords];

	for (int i = 0; i < numOfWords; i++) {
		std::string word;
		std::cin >> word;
		insertWordInTree(word);
	}
	

	for (int i = 0; i < numOfDecWords; i++) {
		std::string wordInNumbers;
		std::cin >> wordInNumbers;
		for (int j = 0; j < wordInNumbers.size(); j++) {
			int x = wordInNumbers[j] - '0';
			decodeWord[i].push_back(x);
		}
	}

	std::cout << "\nOUTPUT: \n";
	for (int i = 0; i < numOfDecWords; i++) {
		searchWord(decodeWord[i]);
	}



	//std::cout << head->countPrefix << std::endl;
	system("pause");
	return 0;
}

