
/*
q4 Create a polymorphic class Vehicle and create other derived classes Bus, Car, and Bike from Vehicle. 
Illustrate RTTI by the use of dynamic_cast and typeid operators in this program.
*/
#include <iostream>
#include <typeinfo>
class Vehicle {
public:
	Vehicle(int i) :m_engineNum(i) {}
	int getEngineNum() {
		return m_engineNum;
	}
	virtual ~Vehicle(){}
protected:
	int m_engineNum;
};
class Bus :public Vehicle {
public:
	Bus(int i, std::string s) :Vehicle(i), m_brand(s) {}
	std::string getBrandName() {
		return m_brand + " Bus";
	}
private:
	std::string m_brand;
};
class Car :public Vehicle {
public:
	Car(int i, std::string s) :Vehicle(i), m_brand(s) {}
	std::string getBrandName() {
		return m_brand + " Car";
	}
private:
	std::string m_brand;
};
class Bike :public Vehicle {
public:
	Bike(int i, std::string s) :Vehicle(i), m_brand(s) {}
	std::string getBrandName() {
		return m_brand + " Bike";
	}
private:
	std::string m_brand;
};
namespace Q4 {
	void showDetail(Vehicle* v, const std::type_info& info) {
		std::cout << "Class type = " << info.name()
			<< "\nEngine Number = " << v->getEngineNum();
	
		if (info == typeid(Bus))
			std::cout<<"\n"<<dynamic_cast<Bus*>(v)->getBrandName()<<"\n";
		else if (info == typeid(Car))
			std::cout << "\n" << dynamic_cast<Car*>(v)->getBrandName()<<"\n";
		else if(info == typeid(Bike))
			std::cout << "\n" << dynamic_cast<Bike*>(v)->getBrandName()<<"\n";
		delete v;
	}
	int main() {
		Bus *bus = new Bus(100, "Volvo");
		Car *car = new Car(10, "Hyundai");
		Bike *bike= new Bike(1, "Bajaj");

		showDetail(bus, typeid(*bus));
		showDetail(car, typeid(*car));
		showDetail(bike, typeid(*bike));


		return 0;
	}
}
/*
q3 Write a program with an abstract class Student and create derive classes 
Engineering, Medicine and Science from base class Student. 
Create the objects of the derived classes and process them 
and access them using an array of pointers of type base class Student.
*/

#include <iostream>
namespace Q3 {
	class Student {
	public:
		virtual void show() {
			std::cout << m_name<<std::endl;
		}
		virtual void set() {
			std::cout << "Enter name : ";
			std::cin >> m_name;
		}
	protected:
		std::string m_name;
	};
	class Engineering : public Student {
	public:
		void set() {
			Student::set();
			m_name = "Engineer " + m_name;
		}
	};
	class Medicine :public Student {
	public:
		void set() {
			Student::set();
			m_name = "Medicine " + m_name;
		}

	};
	class Science :public Student {
	public:
		void set() {
			Student::set();
			m_name = "Science " + m_name;
		}

	};

	int main() {
		Student* pstu[3];
		pstu[0] = new Engineering();
		pstu[1] = new Medicine();
		pstu[2] = new Science();

		pstu[0]->set();
		pstu[1]->set();
		pstu[2]->set();
		
		pstu[0]->show();
		pstu[1]->show();
		pstu[2]->show();

		delete pstu[0];
		delete pstu[1];
		delete pstu[2];

		return 0;
	}
}
/*
q2 Create a class Person and two derived classes Employee and Student, inherited from class Person. 
Now create a class Manager which is derived from two base classes Employee and Student. 
Show the use of the virtual base class.
*/
#include <iostream>
namespace Q2 {

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
	class Manager : public Employee, public Student {
	public:
		Manager(std::string name) :Student(name), Employee(name), Person(name) {}

	};


	int main() {
		Manager m("Kumar");
		std::cout << m.getName() << std::endl;
		m.Student::setName("Stu Kumar");
		std::cout << m.Employee::getName() << std::endl;
		m.Employee::setName("Employ Kumar");
		std::cout << m.Student::getName() << std::endl;

		return 0;
	}
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
namespace Q1 {

	const float PI = atan(1) * 4;

	class Shape {
	public:
		virtual float area() = 0;
		virtual void display() {
			std::cout << "Shape ";
		}
		virtual ~Shape() {
			std::cout << "Shape destroyed \n";
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
	int main() {
		Circle c(3.4);
		Trapz t(1, 2, 5);
		Rect r(0.5, 0.8);

		Circle* p = new Circle();
		delete (Shape*)(p);

		auto dis = [](Shape& s) {s.display(); };

		dis(c);
		dis(t);
		dis(r);

		return 0;
	}
}

#include <iostream>
#include <cstdlib>


int main()
{
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


	return 0;



}
