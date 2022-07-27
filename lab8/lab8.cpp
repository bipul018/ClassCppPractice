/*
Q5
Write a program for transaction processing that write and read object 
randomly to and from a random access file so that user can add, update, 
delete and display the account information (account-number, last-name, first-name, total-balance).
*/
#include <iostream>
#include <fstream>

namespace Q5 {

	struct Account {
		char fName[100];
		char lName[100];
		unsigned accN;
		float balance;
	};
	using namespace std;
	int main() {
		string fileName;
		unsigned count = 0;
		Account* pacc = nullptr;
		cout << "Enter the file name ";
		cin >> fileName;

		fstream file(fileName, ios::in | ios::ate | ios::binary);
		if (file.is_open()) {
			count = file.tellg() / sizeof(Account);
			file.seekg(ios::beg);
			pacc = new Account[count];
			file.read(reinterpret_cast<char*>(pacc), count * sizeof(Account));
			file.close();
		}
		else {
			count = 0;
			file.open(fileName, ios::binary | ios::out);
			file.close();
		}
		char choice = 'c';

		cout << "Enter your choice as follow : "
			<< "\nDisplay records : d"
			<< "\nAdd record : a"
			<< "\nRemove record : r"
			<< "\nUpdate record : u"
			<< "\nQuit : q";
		while (choice != 'q' && choice != 'Q') {
			cout << "\nEnter choice : ";
			cin >> choice;
			switch (choice) {
			case 'd':
			{
				for (unsigned n = 0; n < count; n++) {
					std::cout << "\nRecord No :" << n + 1 << "\n\tName:" << pacc[n].fName << " " << pacc[n].lName
						<< "\n\tAcc No : " << pacc[n].accN
						<< "\n\tBalance : " << pacc[n].balance << endl;
				}
			}
				break;
			case 'r':
			{
				cout << "Enter record number to remove : ";
				int n;
				cin >> n;
				if ((n > count)||(n<=0)) {
					cout << "Invalid Record.\n";
					break;
				}

				Account* newp = new Account[count - 1];
				memcpy(newp, pacc, sizeof(Account)*(n-1));
				memcpy(newp + n - 1, pacc + n, sizeof(Account) * (count - n ));
				delete[] pacc;
				pacc = newp;
				--count;

			}
			break;
			case 'u':
			{
				cout << "Enter record number to update : ";
				int n;
				cin >> n;
				if ((n > count) || (n <= 0)) {
					cout << "Invalid Record.\n";
					break;
				}
				cout << "\nEnter record to update : ";
				cout << "\nAccount Number : ";
				cin >> pacc[n - 1].accN;
				cout << "\nFirst Name : ";
				cin >> pacc[n - 1].fName;
				cout << "\nLast Name : ";
				cin >> pacc[n - 1].lName;
				cout << "\nBalance : ";
				cin >> pacc[n - 1].balance;

			}
			break;
			case 'a':
			{
				cout << "Enter record number to add after : ";
				int n;
				cin >> n;
				if (n > count)
					n = count;

				if (n <= 0)
					n = 0;
				Account* newp = new Account[count + 1];
				if (pacc != nullptr)
					memcpy(newp, pacc, sizeof(Account) * n);

				cout << "\nEnter record to add : ";
				cout << "\nAccount Number : ";
				cin >> newp[n].accN;
				cout << "\nFirst Name : ";
				cin >> newp[n].fName;
				cout << "\nLast Name : ";
				cin >> newp[n].lName;
				cout << "\nBalance : ";
				cin >> newp[n].balance;

				if (pacc != nullptr)
					memcpy(newp + n + 1, pacc + n, sizeof(Account) * (count - n));
				delete[] pacc;
				pacc = newp;
				++count;


			}
				break;
			}
			file.open(fileName, ios::binary | ios::out);
			file.write(reinterpret_cast<const char*>(pacc), count);
			file.close();
		}



		delete[] pacc;
		return 0;
	}
}

/*
Q4
Write a program that stores the information about students (name, student id, department, and address) 
in a structure and then transfers the information to a file in your directory. 
Finally, retrieve the information from your file and print it in the proper format on your output screen.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
namespace Q4 {

	using namespace std;
	struct Student {
		unsigned id;
		char name[100];
		char depart[100];
		char addr[100];
	};

	int main() {
		string fileName;
		unsigned size;
		cout << "Enter number of students : ";
		cin >> size;
		Student* sptr = new Student[size];
		for (unsigned i = 0; i < size; i++) {
			cout << "Student " << i + 1 << ":\nId : ";
			cin >> sptr[i].id;
			cout << "Name : ";
			cin >> sptr[i].name;
			cout << "Department : ";
			cin >> sptr[i].depart;
			cout << "Address : ";
			cin >> sptr[i].addr;
		}
		cout << "Enter filename to store in : ";
		cin >> fileName;
		fstream file(fileName, ios::out|ios::binary);
		file.write(reinterpret_cast<const char*>(sptr), sizeof(Student) * size);
		file.close(); 

		delete[]sptr;

		cout << "Opening file " << fileName << " for reading \n";

		file.open(fileName, ios::in|ios::binary|ios::ate);
		size = file.tellg() / sizeof(Student);
		file.seekg(0, ios::beg);
		cout << "No of students are : " << size << endl;
		sptr = new Student[size];
		
		file.read(reinterpret_cast<char*>(sptr), size * sizeof(Student));
		for (int i = 0; i < size; i++) {
			cout << "\nStudent Id : " << sptr[i].id << "\nName : " << sptr[i].name
				<< "\nDepartment : " << sptr[i].depart << "\nAddress : " << sptr[i].addr<<endl;
		}

		delete[] sptr;
		return 0;
	}
}

/*
Q3
Write a program to overload stream operators to read a complex number and display the complex number in a+ib format.
*/
#include<iostream>


namespace Q3 {

	class Complex {
	private:
		float m_real;
		float m_imag;
	public:
		Complex(float real = 0, float imag = 0) :m_real(real), m_imag(imag) {

		}
		friend std::ostream& operator<<(std::ostream& os, const Complex& cx) {
			os << cx.m_real << " " << ((cx.m_imag < 0) ? '-' : '+') << " i " << abs(cx.m_imag) << " ";
			return os;
		}
		friend std::istream& operator>>(std::istream& is, Complex& cx) {
			is >> cx.m_real >> std::skipws >> cx.m_imag;
			return is;
		}
	};

	int main() {
		std::cout << "Enter a complex number : ";
		Complex cnx;
		std::cin >> cnx;
		std::cout << "You entered : " << cnx;
		return 0;
	}

}

/*
Q2
Write a program to create a user-defined manipulator that will format the output by setting the width, 
precision, and fill character at the same time by passing arguments.
*/
#include<iostream>
#include<iomanip>
namespace Q2 {
	using namespace std;
	class MyManipulator {
	public:
		MyManipulator(unsigned w = 0, unsigned pre = 6, char c = ' ') :wid(w), precs(pre), fill(c) {

		}
		MyManipulator(const MyManipulator&) = delete;
		

		friend ostream& operator <<(ostream& os, const MyManipulator& man) {
			os << setprecision(man.precs) << setw(man.wid) << setfill(man.fill);
			return os;
		}
	private:
		unsigned wid;
		unsigned precs;
		char fill;
	};

	int main() {
		cout << "Manipulator:" << MyManipulator(8, 3, '@') << 1.2435535;
		return 0;
	}

}

/*
Q1
Write a program to demonstrate the use of different ios flags and functions to format the output. 
Create a program to generate the bill invoice of a department store by using different formatting.
*/
#include <iostream>
#include <string>
#include <iomanip>
namespace Q1 {

	using namespace std;
	struct ItemDetail {
		std::string name;
		float unitPrice;
		int quantity;
	};

	int main() {
		
		string departName;
		unsigned size = 0;
		float totalAmt = 0;
		int totalQty = 0;
		cout << "Enter name of store : ";
		getline(cin, departName);
		cout << "Enter number of items types bought : ";
		cin >> size;
		ItemDetail* pItem = new ItemDetail[size];

		unsigned maxNameLen = string("Particulars").length();

		for (unsigned i = 0; i < size; i++) {
			cout << "Enter item name : ";
			cin.ignore(numeric_limits<streamsize>::max(),'\n');
			getline(cin, pItem[i].name);
			cout << "Enter unitPrice : ";
			cin >> pItem[i].unitPrice;
			cout << "Enter quantity : ";
			cin >> pItem[i].quantity;
			if (pItem[i].name.length() > maxNameLen)
				maxNameLen = pItem[i].name.length();
		}
		cout << endl << departName;
		cout << "\nTAX INVOICE\n";
		cout<<endl<< "  SN"<< setw(maxNameLen + 1) << left << " Particulars";
		cout.setf(ios::right);
		cout<< " Qty" << setw(9) << "Rate"
			<< setw(9) << "Amount" << endl;
		
		cout << setw(maxNameLen + 28) << setfill('-') << '\n';
		cout.fill(' ');
		for (int i = 0; i < size; i++) {

			cout << setw(4) << i+1 << " ";
			cout.unsetf(ios::right);
			cout<< left << setw(maxNameLen) << pItem[i].name;
			cout.setf(ios::right);
			cout << setw(4) << pItem[i].quantity << setw(9) 
				<< pItem[i].unitPrice << setw(9) << pItem[i].quantity*pItem[i].unitPrice << endl;
			totalAmt += pItem[i].quantity * pItem[i].unitPrice;
			totalQty += pItem[i].quantity;
		}
		cout << "Total Quantity = " << totalQty << endl << "Total Amount = " << totalAmt << endl;

		delete[] pItem;

		return 0;
	}	

}

#include <iostream>
#include <cstdlib>

int main() {

	Q5::main();
	system("pause");
	std::cout << std::endl;
	return 0;
	Q1::main();
	system("pause");
	std::cout << std::endl;

	Q2::main();
	system("pause");
	std::cout << std::endl;

	Q3::main();
	system("pause");
	std::cout << std::endl;

	Q4::main();
	system("pause");
	std::cout << std::endl;
	
	Q5::main();
	system("pause");
	std::cout << std::endl;

	return 0;
}