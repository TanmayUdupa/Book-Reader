#include "Server.h"

int main()
{
	int choice;
	cout << "Are you admin or a user?\n1. Admin 2. User\n";
	cout << "Enter number in the range 1 - 2: ";
	cin >> choice;
	if (choice == 1)
	{
		Admin A1;
		string username, password;
		cout << "Enter username (no spaces): ";
		cin >> username;
		cout << "Enter password (no spaces): ";
		cin >> password;
		if (A1.login(username, password))
		{
			cout << "\n\n\nHello " << A1.getName() << " | Admin View\n\n";
			do
			{
				cout << "Menu:\n\t1. View Profile\n\t2. Add Book\n\t3. Activate signup\n\t4. Edit Book\n\t5. Search book\n\t6. Delete Book\n\t";
				cout << "7. Check which admin activated which user\n\t8. Check which admin added which book\n\t9. Logout\n\n";
				cout << "Enter number in range 1 - 9: ";
				int choice2, n;
				long int isbn;
				string title, auth_name;
				cin >> choice2;
				if (choice2 == 1)
				{
					A1.viewProfile();
				}
				else if (choice2 == 2)
				{
					cout << "Enter ISBN: ";
					cin >> isbn;
					cout << "Enter Title: ";
					cin >> title;
					cout << "Enter Author Name: ";
					cin >> auth_name;
					cout << "Enter No. Of Pages: ";
					cin >> n;
					A1.add_book(isbn, title, auth_name, n);
				}
				else if (choice2 == 3)
				{
					A1.activate_signup();
				}
				else if (choice2 == 4)
				{
					cout << "Enter title of the book you want to edit: ";
					cin >> title;
					A1.edit_book(title);
				}
				else if (choice2 == 5)
				{
					cout << "Enter title of the book you want to search: ";
					cin >> title;
					if(A1.search_book(title))
					{
						cout << "Book found!!\n\n";
					}
					else
					{
						cout << "Book not found!!\n\n";
					}
				}
				else if (choice2 == 6)
				{
					cout << "Enter title of the book you want to delete: ";
					cin >> title;
					A1.delete_book(title);
				}
				else if (choice2 == 7)
				{
					A1.admin_user();
				}
				else if (choice2 == 8)
				{
					A1.admin_book();
				}
				else if (choice2 == 9)
				{
					break;
				}
				else
				{
					cout << "Invalid choice. Please try again\n\n";
				}
			}while (true);
		}
		else
		{
			cout << "Invalid login credentials.";
		}
	}
	else if (choice == 2)
	{
		int choice2;
		cout << "Menu:\n\t1: Login\n\t2: Sign Up\n\n";
		cout << "Enter your number in the range (1 - 2): ";
		cin >> choice2;
		if (choice2 == 1)
		{
			string username, password;
			User U1;
			cout << "Enter username (no spaces): ";
			cin >> username;
			cout << "Enter password (no spaces): ";
			cin >> password;
			int choice3;
			if (U1.login(username, password))
			{
				cout << "\n\n\nHello " << U1.getName() << " | User View\n\n";
				do
				{
					cout << "Menu: \n\t1: View Profile\n\t2: List & Select from my Reading History\n\t3: List & Select from my Available Books";
					cout << "\n\t4: Clear History\n\t5: Logout\n\n";
					cout << "Enter number in range 1 - 5: ";
					cin >> choice3;
					if (choice3 == 1)
					{
						U1.viewProfile();
					}
					else if (choice3 == 2)
					{
						U1.view_select_history();
					}
					else if (choice3 == 3)
					{
						U1.view_select_books();
					}
					else if (choice3 == 4)
					{
						U1.clear_history();
					}
					else if (choice3 == 5)
					{
						break;
					}
					else
					{
						cout << "Invalid choice. Please try again\n\n";
					}
				}while (true);
			}
			else
			{
				cout << "Invalid login credentials\n";
			}
		}
		else if (choice2 == 2)
		{
			string username, password, name, email;
			User U1;
			cout << "Enter username (no spaces): ";
			cin >> username;
			cout << "Enter password (no spaces): ";
			cin >> password;
			cout << "Enter name (no spaces): ";
			cin >> name;
			cout << "Enter email (no spaces): ";
			cin >> email;
			U1.signup(username, password, name, email);
		}
		else
		{
			cout << "Invalid choice";
		}
	}
	else
	{
		cout << "Invalid choice";
	}
	return 0;
}
