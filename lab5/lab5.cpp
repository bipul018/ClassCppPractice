//Ex4
/*
Write a class Date that overloads prefix and postfix operators to increase the Date object by one day,
while causing appropriate increments to the month and year (use the appropriate condition for leap year). 
The prefix and postfix operators in the Date class should behave exactly like the built-in increment operators.
*/

int main4() {
	return 0;
}


//Ex3
/*Write a program to compare two objects of a class that contains an integer value as its data member. 
Make overloading functions to overload equality(==), 
less than(<), greater than(>), not equal (!=), greater than or equal to (>=), 
and less than or equal to(<=) operators using member operator functions.
*/
#include<iostream>
class Integer {
public:
	Integer(int n = 0) :m(n) {

	}
	void setN(int n) {
		m = n;
	}
	int getN() const {
		return m;
	}
	bool operator ==(Integer i2) {
		return m == i2.m;
	}
	bool operator !=(Integer i2) {
		return m != i2.m;
	}
	bool operator <(Integer i2) {
		return m < i2.m;
	}
	bool operator >(Integer i2) {
		return m > i2.m;
	}
	bool operator >=(Integer i2) {
		return m >= i2.m;
	}
	bool operator <=(Integer i2) {
		return m <= i2.m;
	}
private:
	int m;
};
int main3() {
	Integer i1(5), i2(7);
	std::cout << "i1 = " << i1.getN()
		<< " i2 = " << i2.getN() << std::endl;
	std::cout << "i1 < i2 " << (i1 < i2)
		<< "\n i1 > i2 " << (i1 > i2)
		<< "\n i1 >= i2 " << (i1 >= i2)
		<< "\n i1 <= i2 " << (i1 <= i2)
		<< "\n i1 == i2 " << (i1 == i2)
		<< "\n i1 != i2 " << (i1 != i2);

	return 0;
}
//Ex2
/*
Write a class to store x, y, and z coordinates of a point in three-dimensional space. 
Overload addition and subtraction operators for addition and subtraction of two coordinate objects. 
Implement the operator functions as non-member functions (friend operator functions).
*/
#include <iostream>

class Coor3D{
public:

	friend Coor3D operator+(Coor3D, Coor3D);
	friend Coor3D operator-(Coor3D, Coor3D);
	Coor3D(float x, float y, float z) :
		m_x(x), m_y(y), m_z(z) {

	}
	Coor3D() :
		m_x(0), m_y(0), m_z(0) {

	}

	float getX() const {
		return m_x;
	}
	float getY() const {
		return m_y;
	}
	float getZ() const {
		return m_z;
	}
	void print() const  {
		std::cout << "( " << m_x << " , " << m_y << " , " << m_z << " )";
	}

private:
	float m_x;
	float m_y;
	float m_z;

};
Coor3D operator+(Coor3D a, Coor3D b) {
	return Coor3D(a.m_x + b.m_x, a.m_y + b.m_y, a.m_z + b.m_z);
}
Coor3D operator-(Coor3D a, Coor3D b) {
	return Coor3D(a.m_x - b.m_x, a.m_y - b.m_y, a.m_z - b.m_z);
}

int main2() {
	Coor3D a(1, 2, 3), b(5, -6, 0);
	Coor3D sum = a + b;
	Coor3D diff = a - b;
	a.print();
	b.print();
	sum.print();
	diff.print();
	return 0;
}
//Ex1
/*
Write a class for instantiating the objects that represent the two-dimensional Cartesian coordinate system.

A. Make a particular member function of one class as a friend function of another class for addition.

B. Make the other three functions to work as a bridge between the classes for multiplication, 
division, and subtraction.

C. Also write a small program to demonstrate that all the member functions of one class are the 
friend functions of another class if the former class is made friend to the latter.

Make least possible classes to demonstrate all the above in a single program without conflict.
*/
#include <iostream>
class Coor2D;
class Print;
class Add {
public:
	Coor2D coor2d(Coor2D, Coor2D);
};
class Coor2D {
public:
	Coor2D(float x = 0, float y = 0) :
		m_x(x), m_y(y) {

	}
	friend Coor2D Add::coor2d(Coor2D, Coor2D);
	friend Coor2D mult(Coor2D, Coor2D);
	friend Coor2D div(Coor2D, Coor2D);
	friend Coor2D sub(Coor2D, Coor2D);
	friend class Print;
private:
	float m_x;
	float m_y;
};
Coor2D Add::coor2d(Coor2D a, Coor2D b) {
	return Coor2D(a.m_x + b.m_x, a.m_y + b.m_y);
}

Coor2D mult(Coor2D a, Coor2D b) {
	return Coor2D(a.m_x * b.m_x, a.m_y * b.m_y);

}
Coor2D div(Coor2D a, Coor2D b) {
	return Coor2D(a.m_x / b.m_x, a.m_y / b.m_y);

}
Coor2D sub(Coor2D a, Coor2D b) {
	return Coor2D(a.m_x - b.m_x, a.m_y - b.m_y);

}
class Print {
public:
	Print& coor2d(const Coor2D& c) {
		std::cout << " (" << c.m_x << " , " << c.m_y << ") ";
		return *this;
	}
};
int main1() {
	Coor2D a(1, 2), b(4, -6), sum, dif, prod, divRes;
	Add adder;
	Print printer;
	sum = adder.coor2d(a, b);
	dif = sub(a, b);
	prod = mult(a, b);
	divRes = div(a, b);
	printer.coor2d(a).coor2d(b).coor2d(sum).
		coor2d(dif).coor2d(prod).coor2d(divRes);
	return 0;
}



#include <iostream>
#include <cstdlib>

int main()
{
	main1();
	system("pause");
	putchar('\n');

	main2();
	system("pause");
	putchar('\n');

	main3();
	system("pause");
	putchar('\n');
	return 0;
}