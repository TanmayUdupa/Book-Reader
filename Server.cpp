/*
 * Server.cpp
 *
 *  Created on: Dec 3, 2022
 *      Author: tanma
 */

#include "Server.h"

vector<string> lines_return(string file_name)
{

	ifstream fin(file_name);
	string line;
	vector<string> lines;
	if(fin.fail())
	{
		cout << "Can't open the file\n";
		exit(1);
	}

	while(getline(fin, line))
	{
		lines.push_back(line);
	}

	fin.close();

	return lines;
}

void delete_lines(string file_name)
{
	ofstream fdelete(file_name);
	fdelete.clear();
	fdelete<<"";
	fdelete.close();
}

void lines_output(string file_name, vector<string> lines)
{
	ofstream fout(file_name);
	fout.clear();

	for (auto line : lines)
	{
		fout << line << "\n";
	}

	fout.close();

}

bool Admin::login(string userna, string passw)
{
	vector<string> lines = lines_return("admin_details.txt");

	string line, user, pass, NAME, EMAIL;

	for(auto line: lines)
	{
		istringstream iss(line);
		iss >> user >> pass >> NAME >> EMAIL;
		if (userna == user && passw == pass)
		{
			username = userna;
			password = pass;
			name = NAME;
			email = EMAIL;
			return 1;
		}
	}

	return 0;
}

string Admin::getName()
{
	return name;
}

void Admin::viewProfile()
{
	cout << "\nName: " << name << "\nEmail: " << email << "\nUser name: " << username << "\n\n";
}

void Admin::activate_signup()
{
	vector<string> lines = lines_return("activation.txt");

	ofstream fout("admin_user.txt", ios::app);
	fout.clear();
	string name;

	for(auto line: lines)
	{
		istringstream iss(line);
		iss >> name;
		fout << name << " authenticated by " << username << endl;
	}

	fout.close();

	delete_lines("activation.txt");

	ofstream fout2("user_details.txt", ios::app);
	fout2.clear();

	for(auto s : lines)
	{
		fout2 << s << endl;
	}

	fout2.close();
}

void Admin::add_book(long int isbn, string title, string auth, int n)
{
	b1.add_book(isbn, title, auth, n);
	ofstream fout("admin_book.txt", ios::app);
	fout.clear();
	fout << title << " added by " << username << endl;
	fout.close();
	cout << "\n\n";
}

void Admin::edit_book(string title)
{
	cout << "\n";
	cout << "What do you want to edit?\n1. ISBN number\n2. Title\n3. Author Name\n4. Page content\nEnter your choice: ";
	int choice, n;
	long int isbn;
	string s;
	cin >> choice;
	switch(choice)
	{
	case 1:
		cout << "Enter new ISBN number: ";
		cin >> isbn;
		b1.edit_book_isbn(isbn, title);
		break;
	case 2:
		cout << "Enter new title: ";
		cin >> s;
		b1.edit_book_title(s, title);
		break;
	case 3:
		cout << "Enter new author: ";
		cin >> s;
		b1.edit_book_auth(s, title);
		break;
	case 4:
		cout << "Enter page number of the content you want to edit: ";
		cin >> n;
		cout << "Enter the content: ";
		cin >> s;
		b1.edit_book_page(n, s, title);
		break;
	default:
		cout << "Invalid choice\n";
	}
	cout << "\n\n";
}

bool Admin::search_book(string title)
{
	return b1.search_book(title);
}

void Admin::delete_book(string title)
{
	b1.delete_book(title);
	cout << "\n\n";
}

void Admin::admin_user()
{
	vector<string> lines = lines_return("admin_user.txt");

	for(auto line : lines)
	{
		cout << line << endl;
	}
	cout << "\n\n";
}

void Admin::admin_book()
{
	vector<string> lines = lines_return("admin_book.txt");

	for(auto line : lines)
	{
		cout << line << endl;
	}
	cout << "\n\n";
}

void Book::add_book(long int isb, string titl, string aut, int no)
{
	ofstream fout("Books.txt", ios::app);
	fout.clear();

	isbn = isb;
	title = titl;
	author_name = aut;
	no_of_pages = no;

	fout << isbn << " " << title << " " << author_name << " " << no_of_pages;
	string line;
	for (int i = 1; i <= no_of_pages; i++)
	{
		cout << "Enter page #" << i << ": ";
		cin >> line;
		pages.push_back(line);
	}

	for (auto lin : pages)
	{
		fout << " " << lin;
	}

	fout << "\n";
	pages.clear();
	fout.close();
}

void Book::edit_book_title(string new_title, string old_title)
{
	vector<string> lines = lines_return("Books.txt");

	delete_lines("Books.txt");

	bool check = 0;
	int size = lines.size();

	for (int i = 0; i < size; i++)
	{
		istringstream iss(lines[i]);
		iss >> isbn >> title >> author_name >> no_of_pages;
		string page;
		for (int j = 0; j < no_of_pages; j++)
		{
			iss >> page;
			pages.push_back(page);
		}
		if (title == old_title)
		{
			title = new_title;
			ostringstream iss2;
			iss2 << isbn << " " << title << " " << author_name << " " << no_of_pages;
			lines[i] = iss2.str();
			for (auto x : pages)
			{
				lines[i] += " " + x;
			}
			check = 1;
			break;
		}
		pages.clear();
	}

	if (!check)
	{
		printf("Book not found\n");
	}

	lines_output("Books.txt", lines);
	pages.clear();
	lines = lines_return("history.txt");
	delete_lines("history.txt");
	size = lines.size();
	string username, titl, page_counter, date, time;
	for (int i = 0; i < size; i++)
	{
		istringstream iss(lines[i]);
		iss >> username >> titl >> page_counter >> date >> time;
		if (titl == old_title)
		{
			titl = new_title;
			lines[i] = username + " " + titl + " " + page_counter + " " + date + " " + time;
		}
	}
	lines_output("history.txt", lines);
}

void Book::edit_book_isbn(long int new_isbn, string old_title)
{
	vector<string> lines = lines_return("Books.txt");

	delete_lines("Books.txt");


	bool check = 0;
	int size = lines.size();
	for (int i = 0; i < size; i++)
	{
		istringstream iss(lines[i]);
		iss >> isbn >> title >> author_name >> no_of_pages;
		string page;
		for (int j = 0; j < no_of_pages; j++)
		{
			iss >> page;
			pages.push_back(page);
		}
		if (title == old_title)
		{
			isbn = new_isbn;
			ostringstream iss2;
			iss2 << isbn << " " << title << " " << author_name << " " << no_of_pages;
			lines[i] = iss2.str();
			for (auto x : pages)
			{
				lines[i] += " " + x;
			}
			check = 1;
			break;
		}
		pages.clear();
	}

	if (!check)
	{
		printf("Book not found\n");
	}

	lines_output("Books.txt", lines);
	pages.clear();
}

void Book::edit_book_auth(string auth, string old_title)
{
	vector<string> lines = lines_return("Books.txt");

	delete_lines("Books.txt");


	bool check = 0;

	int size = lines.size();
	for (int i = 0; i < size; i++)
	{
		istringstream iss(lines[i]);
		iss >> isbn >> title >> author_name >> no_of_pages;
		string page;
		for (int j = 0; j < no_of_pages; j++)
		{
			iss >> page;
			pages.push_back(page);
		}
		if (title == old_title)
		{
			author_name = auth;
			ostringstream iss2;
			iss2 << isbn << " " << title << " " << author_name << " " << no_of_pages;
			lines[i] = iss2.str();
			for (auto x : pages)
			{
				lines[i] += " " + x;
			}
			check = 1;
			break;
		}
		pages.clear();
	}

	if (!check)
	{
		printf("Book not found\n");
	}

	lines_output("Books.txt", lines);
	pages.clear();
}

void Book::edit_book_page(int n, string content, string old_title)
{
	vector<string> lines = lines_return("Books.txt");

	delete_lines("Books.txt");


	bool check = 0;

	int size = lines.size();
	for (int i = 0; i < size; i++)
	{
		istringstream iss(lines[i]);
		iss >> isbn >> title >> author_name >> no_of_pages;
		string page;
		for (int j = 0; j < no_of_pages; j++)
		{
			iss >> page;
			pages.push_back(page);
		}
		if (title == old_title)
		{
			if (n > no_of_pages)
			{
				cout << "Page doesn't exist\n";
				check = 1;
				break;
			}
			pages[n - 1] = content;
			ostringstream iss2;
			iss2 << isbn << " " << title << " " << author_name << " " << no_of_pages;
			lines[i] = iss2.str();
			for (auto x : pages)
			{
				lines[i] += " " + x;
			}
			check = 1;
			break;
		}
		pages.clear();
	}

	if (!check)
	{
		printf("Book not found\n");
	}

	lines_output("Books.txt", lines);
	pages.clear();
}

bool Book::search_book(string titl)
{
	vector<string> lines = lines_return("Books.txt");

	bool search = 0;

	for (auto line : lines)
	{
		istringstream iss(line);
		iss >> isbn >> title;
		if (title == titl)
		{
			search = 1;
			break;
		}
	}

	return search;
}

void Book::delete_book(string titl)
{
	vector<string> lines = lines_return("Books.txt");

	delete_lines("Books.txt");

	bool check = 0;

	int size = lines.size();
	for (int i = 0; i < size; i++)
	{
		istringstream iss(lines[i]);
		iss >> isbn >> title;

		if (title == titl)
		{
			lines[i] = "\0";
			for (int j = i; j < size - 1; j++)
			{
				string temp = lines[j];
				lines[j] = lines[j + 1];
				lines[j + 1] = temp;
			}
			lines.pop_back();
			size--;
			i = 0;
			check = 1;
			break;
		}
	}

	if (!check)
	{
		cout << "Book not found\n";
	}

	lines_output("Books.txt", lines);
}

string Book::view_books()
{
	vector<string> lines = lines_return("Books.txt");

	cout << "Our current book collection:\n";

	int size = lines.size();
	for (int i = 0; i < size; i++)
	{
		cout << i + 1 << ": ";
		istringstream iss(lines[i]);
		iss >> isbn >> title;
		cout << title << endl;
	}

	cout << endl;

	cout << "Which book to read?:\n";
	cout << "Enter number in range 1 - " << lines.size() << ": ";
	int choice;
	cin >> choice;
	return lines[choice - 1];
}

string Book::select_book(string titl)
{
	vector<string> lines = lines_return("Books.txt");

	int size = lines.size();
	for (int i = 0; i < size; i++)
	{
		istringstream iss(lines[i]);
		iss >> isbn >> title;
		if (title == titl)
		{
			return lines[i];
		}
	}

	cout << "Book not found\n";

	return '\0';
}

void User::signup(string user, string pass, string NAME, string EMAIL)
{
	ofstream fout("activation.txt", ios::app);

	fout << user << " " << pass << " " << NAME << " " << EMAIL << "\n";

	cout << "You have to be authenticated by the admin before using the system. Please relogin after sometime.\n";
}

bool User::login(string userna, string passw)
{
	vector<string> lines = lines_return("user_details.txt");
	string line, user, pass, NAME, EMAIL;

	for(auto line: lines)
	{
		istringstream iss(line);
		iss >> user >> pass >> NAME >> EMAIL;
		if (userna == user && passw == pass)
		{
			username = userna;
			password = pass;
			name = NAME;
			email = EMAIL;
			vector<string> lines2 = lines_return("history.txt");
			string username2;
			for (auto line2 : lines2)
			{
				istringstream iss2(line2);
				iss2 >> username2;
				if (username2 == username)
				{
					history.push_back(line2);
				}
			}
			return 1;
		}
	}

	return 0;
}

void User::view_select_history()
{
	string userna, title, page_counter, date, time, auth_name;
	int isbn, no_of_pages;
	int i;
	int size = history.size();
	if (size == 0)
	{
		cout << "History is empty\n\n";
		return;
	}
	for (int i = 0; i < size; i++)
	{
		istringstream iss(history[i]);
		iss >> userna >> title >> page_counter >> date >> time;
		cout << i + 1 << ": " << title << " Page: " << page_counter << " " << date << " " << time << endl;
	}
	cout << "Which session to open?:\n";
	cout << "Enter number in range 1 - " << history.size() << ": ";
	cin >> i;
	istringstream iss(history[i - 1]);
	iss >> userna >> title >> page_counter >> date >> time;
	string line = b1.select_book(title);
	istringstream iss2(line);
	iss2 >> isbn >> title >> auth_name >> no_of_pages;
	vector<string> pages;
	string page;
	for (i = 0; i < no_of_pages; i++)
	{
		iss2 >> page;
		pages.push_back(page);
	}
	vector<string> lines = lines_return("history.txt");
	delete_lines("history.txt");
	do
	{
		cout << "Current Page: " << page_counter << endl;
		cout << pages[page_counter[0] - 49] << endl << endl;
		cout << "Menu:\n\t1: Previous Page\n\t2: Next Page\n\t3: Stop Reading\n\n";
		cout << "Enter number in range 1 - 3: ";
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			if ((page_counter[0] - 48) == 1)
			{
				cout << "You are at the start\n";
				continue;
			}
			page_counter[0]--;
		}
		else if (choice == 2)
		{
			if ((page_counter[0] - 48) == no_of_pages)
			{
				cout << "You are at the end of the book. There are no more pages\n";
				continue;
			}
			page_counter[0]++;
		}
		else if (choice == 3)
		{
			std::time_t no = std::time(0);
			tm *ltm = localtime(&no);
			ostringstream iss3;
			iss3 << ((ltm -> tm_year) + 1900) << "-" << ((ltm -> tm_mon) + 1) << "-" << ((ltm -> tm_mday));
			date = iss3.str();
			ostringstream iss4;
			iss4 << ((ltm -> tm_hour)) << ":" << ((ltm -> tm_min)) << ":" << (ltm -> tm_sec);
			time = iss4.str();
			string titl;
			int size = lines.size();
			for (int i = 0; i < size; i++)
			{
				istringstream iss3(lines[i]);
				iss3 >> userna >> titl;
				if (titl == title)
				{
					lines[i] = userna + " " + titl + " " + page_counter + " " + date + " " + time;
					break;
				}
			}
			lines_output("history.txt", lines);
			history.clear();
			string username2;
			for (auto line : lines)
			{
				istringstream iss2(line);
				iss2 >> username2;
				if (username2 == username)
				{
					history.push_back(line);
				}
			}
			cout << "\n\n";
			break;
		}
		else
		{
			cout << "Invalid choice. Please try again\n";
		}
	}while(true);
}

void User::view_select_books()
{
	string userna, title, date, time, auth_name;
	int isbn, no_of_pages;
	int i;
	string line = b1.view_books();
	istringstream iss2(line);
	iss2 >> isbn >> title >> auth_name >> no_of_pages;
	vector<string> pages;
	string page;
	for (i = 0; i < no_of_pages; i++)
	{
		iss2 >> page;
		pages.push_back(page);
	}
	int count = 1;
	do
	{
		cout << "Current Page: " << count << "/" << no_of_pages << endl;
		cout << pages[count - 1] << endl << endl;
		cout << "Menu:\n\t1: Previous Page\n\t2: Next Page\n\t3: Stop Reading\n\n";
		cout << "Enter number in range 1 - 3: ";
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			if ((count) == 1)
			{
				cout << "You are at the start\n";
				continue;
			}
			count--;
		}
		else if (choice == 2)
		{
			if ((count) == no_of_pages)
			{
				cout << "You are at the end of the book. There are no more pages\n";
				continue;
			}
			count++;
		}
		else if (choice == 3)
		{
			std::time_t t = std::time(0);
			tm *ltm = localtime(&t);
			ostringstream iss3;
			iss3 << ((ltm -> tm_year) + 1900) << "-" << ((ltm -> tm_mon) + 1) << "-" << ((ltm -> tm_mday));
			ostringstream iss4;
			iss4 << ((ltm -> tm_hour)) << ":" << ((ltm -> tm_min)) << ":" << (ltm -> tm_sec);
			date = iss3.str();
			time = iss4.str();
			string titl;
			vector<string> lines = lines_return("history.txt");
			int check_title = 0;
			int size = lines.size();
			for (i = 0; i < size; i++)
			{
				istringstream iss3(lines[i]);
				iss3 >> userna >> titl;
				if (titl == title && userna == username)
				{
					check_title = 1;
					break;
				}
			}
			if (check_title)
			{
				delete_lines("history.txt");
				ostringstream iss3;
				iss3 << username << " " << titl << " " << count << "/" << no_of_pages << " " << date << " " << time;
				lines[i] = iss3.str();
				lines_output("history.txt", lines);
				string username2;
				history.clear();
				for (auto line : lines)
				{
					istringstream iss2(line);
					iss2 >> username2;
					if (username2 == username)
					{
						history.push_back(line);
					}
				}
			}
			else
			{
				ofstream fout("history.txt", ios::app);
				fout.clear();
				fout << username << " " << title << " " << count << "/" << no_of_pages << " " << date << " " << time << endl;
				fout.close();
				string username2;
				vector<string> lines2 = lines_return("history.txt");
				history.clear();
				for (auto line : lines2)
				{
					istringstream iss2(line);
					iss2 >> username2;
					if (username2 == username)
					{
						history.push_back(line);
					}
				}
			}
			cout << "\n\n";
			break;
		}
		else
		{
			cout << "Invalid choice. Please try again\n";
		}
	}while(true);
}

void User::clear_history()
{
	vector<string> lines = lines_return("history.txt");
	delete_lines("history.txt");
	string userna;
	int size = lines.size();
	for (int i = 0; i < size; i++)
	{
		istringstream iss(lines[i]);
		iss >> userna;
		if (userna == username)
		{
			lines[i] = "\0";
			for (int j = i; j < size - 1; j++)
			{
				string temp = lines[j];
				lines[j] = lines[j + 1];
				lines[j + 1] = temp;
			}
			lines.pop_back();
			size--;
			i = 0;
		}
	}
	lines_output("history.txt", lines);
	history.clear();
}

void User::viewProfile()
{
	cout << "\nName: " << name << "\nEmail: " << email << "\nUser name: " << username << "\n\n";
}

string User::getName()
{
	return name;
}
