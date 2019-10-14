#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <iostream>

#include "../includes_usr/library.h"
#include "../includes_usr/datastructures.h"
#include "../includes_usr/fileIO.h"
using namespace std;

std::vector<book> book_vector;
std::vector<patron> patron_vector;

int temp_1 = loadBooks(book_vector, BOOKFILE.c_str());
int temp_2 = loadPatrons(patron_vector, PATRONFILE.c_str());

//NOTE: please ensure patron and book data are loaded from disk before calling the following
//NOTE: also make sure you save patron and book data to disk any time you make a change to them
//NOTE: for files where data is stored see constants.h BOOKFILE and PATRONFILE

/*
 * clear books and patrons containers
 * then reload them from disk
 */
void reloadAllData() {
	/**
	book_vector.clear(); patron_vector.clear();
	loadBooks(book_vector, BOOKFILE.c_str());
	loadPatrons(patron_vector, PATRONFILE.c_str());
	**/
}

/* checkout a book to a patron
 * first load books and patrons from disk
 * make sure patron enrolled (patronid is assigned to a patron in patrons container)
 * make sure book in collection (bookid is assigned to a book in books container)
 *
 * see if patron can check out any more books
 * 	if not return TOO_MANY_OUT patron has the MAX_BOOKS_ALLOWED_OUT
 *
 * if so then check the book out to the patron, set the following fields for the book in the
 * books container
 * book.loaned_to_patron_id = patronid;
 * book.state = OUT;
 *
 * Finally save the contents of the books and patrons containers to disk
 *
 * returns SUCCESS checkout worked
 *         PATRON_NOT_ENROLLED
 * 		   BOOK_NOT_IN_COLLECTION
 *         TOO_MANY_OUT patron has the max number of books allowed checked out
 */
int checkout(int bookid, int patronid) {
	/**loadBooks(book_vector, BOOKFILE.c_str());	loadPatrons(patron_vector, PATRONFILE.c_str());
	bool patron_exists = PATRON_NOT_ENROLLED; bool book_exists = BOOK_NOT_IN_COLLECTION;
	cout << "\t" << "Book Size: " << numbBooks() << endl;
	cout << "\tPatron Size: " << numbPatrons() << endl;
	for (int i = 0; i < numbPatrons(); i++) { // Patron loop
		cout << "\t Current: " << patron_vector[i].patron_id << ". Index: " << patronid << endl;
		if (patronid == patron_vector[i].patron_id) { // Patron exists
			patron_exists = SUCCESS;
			if (patron_vector[i].number_books_checked_out >= MAX_BOOKS_ALLOWED_OUT) { // Max books checked out for patron
				return TOO_MANY_OUT;
			}
		}
	}	if (patron_exists == PATRON_NOT_ENROLLED) { return patron_exists; }
	for (int i = 0; i < numbBooks(); i++) {
		if (bookid == book_vector[i].book_id) {
			book_exists = SUCCESS;
		}
	}	if (book_exists == BOOK_NOT_IN_COLLECTION) { return book_exists; }
	for (int i = 0; i < numbPatrons(); i++) { // Traverse patron vector again
		if (patronid == patron_vector[i].patron_id) {
			for (int j = 0; j < numbBooks(); j++) { // Traverse book vector again
				if (bookid == book_vector[j].book_id) {
					book_vector[j].loaned_to_patron_id = patronid;
					book_vector[j].state = book_checkout_state::OUT;
				}
			}
		}
	}
	saveBooks(book_vector, BOOKFILE.c_str()); savePatrons(patron_vector, PATRONFILE.c_str());**/
	return SUCCESS;
}

/* check a book back in
 * first load books and patrons from disk
 * make sure book in collection (bookid is assigned to a book in books container)
 *
 * if so find the the patron the book is checked out to and decrement his/hers number_books_checked_out
 * then check the book back in by marking the book.loaned_to_patron_id = NO_ONE and the book.state = IN;

 * Finally save the contents of the books and patrons containers to disk
 *
 * returns SUCCESS checkout worked
 * 		   BOOK_NOT_IN_COLLECTION
 */
int checkin(int bookid) {
	return SUCCESS;
}

/*
 * enroll a patron, duplicate names are fine as patrons are uniquely identified by their patronid
 * first load books and patrons from disk
 * create a patron object, initialize its fields as appropriate, assign him/her the nextPatronID
 * then push the patron onto the patrons container
 * save all changes to the patrons container to disk
 * return
 *    the patron_id of the person added
 */
int enroll(std::string &name) {
	return 0;
}

/*
 * the number of books in the books container
 * (ie. if 3 books returns 3)
 *
 */
int numbBooks() {
	return book_vector.size();
}

/*
 * the number of patrons in the patrons container
 * (ie. if 3 patrons returns 3)
 */
int numbPatrons() {
	return patron_vector.size();
}

/*the number of books patron has checked out
 *
 *returns a positive number indicating how many books are checked out
 *        or PATRON_NOT_ENROLLED
 */
int howmanybooksdoesPatronHaveCheckedOut(int patronid) {
	for (int i = 0; i < numbPatrons(); i++) {
		if (patronid == patron_vector[i].patron_id) {
			return patron_vector[i].number_books_checked_out;
		}
	}
	return PATRON_NOT_ENROLLED;
}

/* search through patrons container to see if patronid is there
 * if so returns the name associated with patronid in the variable name
 *
 * returns SUCCESS found it and name in name
 *         PATRON_NOT_ENROLLED no patron with this patronid
 */
int whatIsPatronName(std::string &name,int patronid) {
	for (int i = 0; i < numbPatrons(); i++) {
		if (name == patron_vector[i].name) {
			if (patronid == patron_vector[i].patron_id) {
				return SUCCESS;
			}
		}
	}
	return PATRON_NOT_ENROLLED;
}
