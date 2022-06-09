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
public:
	void setId(int id) {
		car_id = id;
	}
	void setChargeRate(int rate) {
		charge_per_hour = rate;
	}
	void setParkTime(float time) {
		parked_time = time;
	}
	int showId() const {
		return car_id;
	}
	int showRate() const {
		return charge_per_hour;
	}
	float showParkTime() const {
		return parked_time;
	}
	float getTotalCost() const {
		return charge_per_hour * parked_time;
	}
};

CarPark getNewParkObj(int id,int rate,float timeParked) {
	CarPark newPark;
	newPark.setId(id);
	newPark.setChargeRate(rate);
	newPark.setParkTime(timeParked);
	return newPark;
}

void printCarPark(const CarPark& park) {
	std::cout << "Car Id : " << park.showId() <<
		"\nTotal Parked Time : " << park.showParkTime()
		<< "\nRate (per hr) : " << park.showRate()
		<< "\nTotal Parking Cost : " << park.getTotalCost();
}

int ex3() {
	CarPark c0 = getNewParkObj(121722, 34, 3.55);
	printCarPark(c0);
	return 0;
}

//Ex4 Multiple classes in a program
#include <iostream>
#include <cmath>

const auto PI = atan(1) * 4;

class Circle {
	float m_r;
public:
	void setRadius(float r) {
		m_r = r;
	}
	float getRadius() const {
		return m_r;
	}
	float getArea() const {
		return PI * m_r * m_r;
	}
};

class Rect {
	float m_l;
	float m_b;
public:
	void setDim(float l, float b) {
		m_l = l;
		m_b = b;
	}
	float getArea() const {
		return m_l * m_b;
	}
	struct {
		float l;
		float b;
	} getDim() const {
		return { m_l,m_b };
	}
};
	
class Triangle{
	float m_a; 
	float m_b;
	float m_c;
public:
	void setDim(float a,float b,float c) {
		m_a = a;
		m_b = b;
		m_c = c;
	}
	float getArea() const {
		auto s = (m_a + m_b + m_c) / 2;
		return sqrtf(s * (s - m_a) * (s - m_b) * (s - m_c));
	}
	struct {
		float a;
		float b;
		float c;
	} getDim() const {
		return { m_a,m_b,m_c };
	}

};

int ex4() {
	float ta, tb, tc, rl, rb, r;
	std::cout << "Enter the side lengths of triangle : ";
	std::cin >> ta >> tb >> tc;
	std::cout << "Enter the lengths of rectangle : ";
	std::cin >> rl >> rb;
	std::cout << "Enter the radius of circle : ";
	std::cin >> r;

	Circle cir;
	Rect rec;
	Triangle tria;

	cir.setRadius(r);
	rec.setDim(rl, rb);
	tria.setDim(ta, tb, tc);

	std::cout << "Circle of radius " << cir.getRadius()
		<< " has area " << cir.getArea() << std::endl;

	std::cout << "Rectangle of length " << rec.getDim().l
		<< " and breadth " << rec.getDim().b
		<< " has area " << rec.getArea() << std::endl;

	auto triDim = tria.getDim();

	std::cout << "The triangle of side lengths " << triDim.a
		<< " , " << triDim.b << " , " << triDim.c
		<< " has area " << tria.getArea() << std::endl;

	return 0;
}

//Ex5 Using classes to get, process and print data
#include <iostream>

class ReportEmp {
private:
	unsigned m_id;
	float m_bonus;
	float m_overtime;
	unsigned m_year;

public:
	void setPara(unsigned id,unsigned year, float bonusInYear, float overTime) {
		m_id = id;
		m_year = year;
		m_overtime = overTime;
		m_bonus = bonusInYear;
	}

	void displayReport() const
	{
		std::cout << "An employee with " << m_id << " has received Rs " << m_bonus << " as a bonus"
			<< " and had worked " << m_overtime << " hours as overtime in the year " 
			<< m_bonus << " as a bonus "	<< " in the year " << m_year << std::endl;
	}
};

int ex5() {
	unsigned n;
	std::cout << "Enter the number of details to enter : ";
	std::cin >> n;
	ReportEmp* empDetails = new ReportEmp[n];
	std::cout << "Now enter details of " << n << " employees :\n";
	for (unsigned i = 0; i < n; i++) {
		unsigned year, id;
		float bonus, overtime;
		std::cout << "Employee " << i << std::endl;
		std::cout << "\tId : ";
		std::cin >> id;
		std::cout << "\tYear : ";
		std::cin >> year;
		std::cout << "\tTotal overtime : ";
		std::cin >> overtime;
		std::cout << "\tTotal bonus : ";
		std::cin >> bonus;
		empDetails[i].setPara(id, year, bonus, overtime);
	}
	std::cout << "Report of each employees are as follows. \n";
	for (unsigned i = 0; i < n; i++) {
		empDetails[i].displayReport();
	}
	delete[] empDetails;
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
	
	ex4();
	putchar('\n');
	system("pause");
	putchar('\n');
	
	ex5();
	putchar('\n');
	system("pause");
	putchar('\n');

}
