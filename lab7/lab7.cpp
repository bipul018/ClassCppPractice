
/*
q4 Create a polymorphic class Vehicle and create other derived classes Bus, Car, and Bike from Vehicle. 
Illustrate RTTI by the use of dynamic_cast and typeid operators in this program.
*/
#include <iostream>

int main4() {

	return 0;
}
/*
q3 Write a program with an abstract class Student and create derive classes 
Engineering, Medicine and Science from base class Student. 
Create the objects of the derived classes and process them 
and access them using an array of pointers of type base class Student.
*/

#include <iostream>

int main3() {

	return 0;
}
/*
q2 Create a class Person and two derived classes Employee and Student, inherited from class Person. 
Now create a class Manager which is derived from two base classes Employee and Student. 
Show the use of the virtual base class.
*/

#include <iostream>

class Person {
public:
	Person(std::string name) :m_name(name) {

	}
	void setName(std::string name) {
		m_name = name;
	}
	std::string getName() {
		return m_name;
	}
private:
	std::string m_name;
};
class Student : virtual public Person {
public:
	Student(std::string name) :Person(name) {}
};
class Employee : virtual public Person {
public:
	Employee(std::string name) :Person(name) {}
};
class Manager : public Employee,public Student {
public:
	Manager(std::string name) :Student(name),Employee(name),Person(name) {}

};


int main2() {
	Manager m("Kumar");
	std::cout << m.getName() << std::endl;
	m.Student::setName("Stu Kumar");
	std::cout << m.Employee::getName() << std::endl;
	m.Employee::setName("Employ Kumar");
	std::cout << m.Student::getName() << std::endl;

	return 0;
}

/*
q1 Write a program to create a class shape with functions to find the area of the shapes and 
display the names of the shapes and other essential components of the class. 
Create derived classes circle, rectangle, 
and trapezoid each having overriding functions area() and display(). 
Write a suitable program to illustrate virtual functions and virtual destructors.
*/
#include <iostream>
#include <cmath>

const float PI = atan(1) * 4;

class Shape {
public:
	virtual float area() = 0;
	virtual void display() {
		std::cout << "Shape ";
	}
	virtual ~Shape() {
		std::cout << "Shape destroyed ";
	}
};


class Circle :public Shape {
public:
	Circle(float r = 0) :m_r(r) {

	}
	float area() {
		return PI * m_r * m_r;
	}
	void display() {
		std::cout << "Circle : Radius = " << m_r
			<< " Area = " << area()
			<< std::endl;
	}
	~Circle() {
		std::cout << "Circle destroyed ";
	}
private:
	float m_r;
};
class Rect : public Shape {
public:
	Rect(float l = 0, float b = 0) :m_l(l), m_b(b) {

	}
	float area() {
		return m_l * m_b;
	}
	void display() {
		std::cout << "Rectangle : length = " << m_l
			<< " breadth = " << m_b
			<< " area = " << area()
			<< std::endl;
	}
	~Rect() {
		std::cout << "Rectangle destroyed  ";
	}
private:
	float m_l;
	float m_b;
};
class Trapz : public Shape {
public:
	Trapz(float h = 0, float p1 = 0, float p2 = 0) :m_h(h), m_p1(p1), m_p2(p2) {

	}
	float area() {
		return 0.5 * m_h * (m_p1 + m_p2);
	}
	void display() {
		std::cout << "Trapezium : height = " << m_h
			<< " Side 1 = " << m_p1
			<< " Side 2 = " << m_p2
			<< " Area = " << area()
			<< std::endl;
	}
	~Trapz() {
		std::cout << "Trapezoid destroyed ";
	}
private:
	float m_h, m_p1, m_p2;
};
int main1() {
	Circle c(3.4);
	Trapz t(1, 2, 5);
	Rect r(0.5, 0.8);

	Circle* p = new Circle();
	delete (Shape*)(p);

	auto dis = [](Shape& s) {s.display();};

	dis(c);
	dis(t);
	dis(r);

	return 0;
}
#include <iostream>
#include <cstdlib>


int main()
{
	main1();
	system("pause");
	std::cout << std::endl;

	main2();
	system("pause");
	std::cout << std::endl;

	main3();
	system("pause");
	std::cout << std::endl;
	
	main4();
	system("pause");
	std::cout << std::endl;


	return 0;



}
