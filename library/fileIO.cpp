#include <fstream>
#include <sstream>
#include <iostream>

#include "../includes_usr/fileIO.h"
#include "../includes_usr/constants.h"
using namespace std;

const int FIRSTVAR = 0;
const int SECONDVAR = 1;
const int THIRDVAR = 2;
const int FOURTHVAR = 3;
const int FIFTHVAR = 4;
const char DELIMITER = ',';

/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char* filename) {
	books.clear();
	std::fstream inputFile;
	inputFile.open(filename, ios::in);
	string line;
	int i, j = 0;
	if(inputFile.is_open()) { // Check if file is open/exists
		for (j = 0; !inputFile.eof(); j++) { // Loops through lines in file
			getline(inputFile,line);
			if (line == "" || line == " ") { //Checks if blank line
				if (j == 0) {  // Checks if empty
					return NO_BOOKS_IN_LIBRARY;
				}
				return SUCCESS;
			}
			stringstream temp(line); string token; book temp_struct;
			for (i = 0; getline(temp, token, DELIMITER); i++) { // Loops through single line, seperating by comma.
			 switch(i) { // Adds 'token' to book struct depending on the order the data is read in from.
				 case FIRSTVAR:
				 	temp_struct.book_id = stoi(token);
				 	break;
				 case SECONDVAR:
				 	temp_struct.title = token;
				 	break;
				 case THIRDVAR:
				 	temp_struct.author = token;
				 	break;
				 case FOURTHVAR:
				 	temp_struct.state = static_cast<book_checkout_state>(stoi(token));
				 	break;
				 case FIFTHVAR:
				 	temp_struct.loaned_to_patron_id = stoi(token);
				 	break;
			 }
			}
			books.push_back(temp_struct);
		}
		return SUCCESS; // Successful read on all data
	}
	return COULD_NOT_OPEN_FILE;
}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename) {
	if (books.size() == 0) { return NO_BOOKS_IN_LIBRARY; }
	std::fstream outputFile;
	outputFile.open(filename, ios::out | ios::trunc);
	string temp;
	if(outputFile.is_open() || outputFile.good()) { // Check if file is open/exists
		for (int i = 0; i < (int)books.size(); i++) {
			outputFile << books[i].book_id << DELIMITER << books[i].title << DELIMITER << books[i].author << DELIMITER << books[i].state << DELIMITER << books[i].loaned_to_patron_id << endl;
		}
		return SUCCESS;
	}
	return COULD_NOT_OPEN_FILE;
}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename) {
	patrons.clear();
	std::fstream inputFile;
	inputFile.open(filename, ios::in);
	string line;
	int i, j = 0;
	if(inputFile.is_open()) { // Check if file is open/exists
		for (j = 0; !inputFile.eof(); j++) { // Loops through lines in file
			getline(inputFile,line);
			if (line == "" || line == " ") { //Checks if blank line
				if (j == 0) {  // Checks if empty
					return NO_PATRONS_IN_LIBRARY;
				}
				return SUCCESS;
			}
			stringstream temp(line); string token; patron temp_struct;
			for (i = 0; getline(temp, token, DELIMITER); i++) { // Loops through single line, seperating by comma.
			 switch(i) { // Adds 'token' to book struct depending on the order the data is read in from.
				 case FIRSTVAR:
				 	temp_struct.patron_id = stoi(token);
				 	break;
				 case SECONDVAR:
				 	temp_struct.name = token;
				 	break;
				 case THIRDVAR:
				 	temp_struct.number_books_checked_out = stoi(token);
				 	break;
			 }
			}
			patrons.push_back(temp_struct);
		}
		return SUCCESS; // Successful read on all data
	}
	return COULD_NOT_OPEN_FILE;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename) {
	if (patrons.size() == 0) { return NO_PATRONS_IN_LIBRARY; }
	std::fstream outputFile;
	outputFile.open(filename, ios::out | ios::trunc);
	if(outputFile.is_open() || outputFile.good()) { // Check if file is open/exists
		for (int i = 0; i < (int) patrons.size(); i++) {
			outputFile << patrons[i].patron_id << DELIMITER << patrons[i].name << DELIMITER << patrons[i].number_books_checked_out << endl;
		}
		return SUCCESS;
	}
	return COULD_NOT_OPEN_FILE;
}
