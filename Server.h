/*
 * Server.h
 *
 *  Created on: Dec 3, 2022
 *      Author: tanma
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
using namespace std;

class Book
{
private:
	long int isbn;
	string title;
	string author_name;
	int no_of_pages;
	vector<string> pages;
public:
	void add_book(long int isbn, string title, string auth, int n);
	void edit_book_title(string new_title, string old_title);
	void edit_book_isbn(long int isbn, string title);
	void edit_book_auth(string auth, string title);
	void edit_book_page(int n, string content, string title);
	bool search_book(string title);
	void delete_book(string title);
	string view_books();
	string select_book(string title);
};

class Admin
{
private:
	string username, password, name, email;
	Book b1;
public:
	string getName();
	void viewProfile();
	bool login(string username, string password);
	void activate_signup();
	void add_book(long int isbn, string title, string auth, int n);
	void edit_book(string title);
	bool search_book(string title);
	void delete_book(string title);
	void admin_user();
	void admin_book();
};


class User
{
private:
	string username, password, name, email;
	vector<string> history;
	Book b1;
public:
	string getName();
	void signup(string username, string password, string name, string email);
	bool login(string username, string password);
	void viewProfile();
	void view_select_history();
	void view_select_books();
	void clear_history();
};

#endif /* SERVER_H_ */
