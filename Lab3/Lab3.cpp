#include <iostream>
#include <cstdlib>

//Ex1 Basic use of classes and member functions

#include <iostream>

class Celsius;
class Fahrenheit;

class Celsius {
private:
	float m_tempr = 0.0;	//Default value, freezing point of water
public:
	void setTempr(float f) {
		m_tempr = f;
	}
	float getTempr() const {
		return m_tempr;
	}

	operator Fahrenheit() const;

};

class Fahrenheit {
private:
	float m_tempr = 32.0; //Default value, freezing point of water
public:
	void setTempr(float f) {
		m_tempr = f;
	}

	float getTempr() const {
		return m_tempr;
	}

	operator Celsius(){
		Celsius c;
		c.setTempr((m_tempr - 32) * 5 / 9);
		return c;
	}

};
Celsius::operator Fahrenheit() const
{
	Fahrenheit f;
	f.setTempr(m_tempr * 9 / 5 + 32);
	return f;
}

int ex1() {
	Celsius c1, c2;
	Fahrenheit f1, f2;
	c1.setTempr(-40);
	f1.setTempr(180);
	f2 = static_cast<Fahrenheit>(c1);
	c2 = static_cast<Celsius>(f1);

	std::cout << c1.getTempr() << "C = " << f2.getTempr() << "F\n";
	std::cout << f1.getTempr() << "F = " << c2.getTempr() << "C\n";
	return 0;

}

//Ex2 Checks whether a number is prime or not while user wants to 
#include <iostream>
#include <cmath>

//Stores only unsigned int that are prime or 0
class Prime {
	unsigned num = 0;
	bool checkPrime(int n) {
		if (n <= 1)
			return false;
		for (int i = 2; i <= static_cast<int>(sqrt(n)); i++) {
			if (n % i == 0)
				return false;
		}
		return true;
	}
public:
	bool isPrime() const {
		return num != 0;
	}

	unsigned getNum() const {
		return num;
	}

	void setNum(int n) {
		if (checkPrime(n))
			num = static_cast<unsigned>(n);
		else
			num = 0;
	}

};

int ex2() {
	char choice = 'y';
	while (choice == 'y' || choice == 'Y') {
		Prime pNum;
		std::cout << "Enter the number to check : ";
		int n;
		std::cin >> n;
		pNum.setNum(n);
		if (pNum.isPrime())
			std::cout << "The number you entered is prime.";
		else
			std::cout << "The number you entered is not prime.";
		std::cout << "\nEnter y to check another number else enter n : ";
		std::cin >> choice;
	}
	return 0;
}

//Ex3 Member functions calling other member functions
#include <iostream>

class CarPark {
	int car_id;
	int charge_per_hour;
	float parked_time;

};

int ex3() {
	return 0;
}

int main()
{
	ex1();
	putchar('\n');
	system("pause");
	putchar('\n');

	ex2();
	putchar('\n');
	system("pause");
	putchar('\n');

	ex3();
	putchar('\n');
	system("pause");
	putchar('\n');

}
