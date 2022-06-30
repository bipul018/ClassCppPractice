//Ex6
/*Create a class with a data member to hold a "serial number" for each object created from the class.
That is, the first object created will be numbered 1, the second 2,
and so on by using the basic concept of static data members.
Use static member function if it is useful in the program.
Otherwise, make a separate program that demonstrates the use of static member function.*/
#include <iostream>

class Serialized {
public:
	Serialized():m_serial(++count) {
	}
	unsigned getId() const {
		return m_serial;
	}
	static unsigned getCount() {
		return count;
	}
private:
	static unsigned count;
	const unsigned m_serial;
};
unsigned Serialized::count=0;
int main6() {
	Serialized ob1, ob2;
	std::cout << "Ob1 id : " << ob1.getId()
		<< "\nOb2 id : " << ob2.getId()
		<< "\nTotal serialized ojects created : "
		<< Serialized::getCount();
	return 0;
}

//Ex5 
/*Write a program that illustrates the following relationship and comment on them. 

i) const_object.non_const_mem_function

ii) const_object.const_mem_function

iii) non_const_object.non_const_mem_function

iv) non_const_object.const_mem_function*/
#include<iostream>

class Complex {
public:
	Complex(float x = 0.0f, float y = 0.0f) :
		m_a(x), m_b(y) {
	}

	const Complex& print() const {
		std::cout << " " << m_a << " + " << m_b << "i ";
		return *this;
	}

	Complex& addWith(const Complex& c2) {
		m_a += c2.m_a;
		m_b += c2.m_b;
		return *this;
	}

private:
	float m_a;
	float m_b;
};

int main5() {
	Complex c1(1, 2);
	const Complex c2(-6, 3);


	//const_object.non_const_mem_function
	//c2.addWith(c1);				//Error, cannot happen
	//Must use const casting first 
	const_cast<Complex*>(&c2)->addWith(Complex(0, 6));

	//const_object.const_mem_function
	c2.print();

	//non_const_object.non_const_mem_function
	c1.addWith(c2);

	//non_const_object.const_mem_function
	c1.print();

	return 0;
}

//Ex4
/*Assume that one constructor initializes data member say num_vehicle, hour, and rate.
 There should be a 10% discount if num_vehicle exceeds 10. Display the total charge.
 Use two objects and show a bit-by-bit copy of one object to another (make your own copy constructor).*/
#include <iostream>

class TaxiFare{
public:
	TaxiFare(int numV, float hour, float rate) :
		num_vehicle(numV), hours(hour), rate(rate) {

	}
	TaxiFare(const TaxiFare& t2) {
		num_vehicle = t2.num_vehicle;
		hours = t2.hours;
		rate = t2.rate;
	}
	void show() const {
		std::cout << "Num of vehicles = " << num_vehicle
			<< "\nHours = " << hours << " rate = " << rate
			<< "\nTotal charge = "
			<< ((num_vehicle > 10) ? 0.9 : 1) * rate * hours * num_vehicle
			<< std::endl;
	}
private:
	int num_vehicle;
	float hours;
	float rate;
};

int main4() {
	TaxiFare fare1(13, 1, 50);
	TaxiFare fare2(fare1);

	fare1.show();
	fare2.show();

	return 0;
}

//Ex3
/*Write a class that can store Department ID and Department Name with constructors to initialize its members. 
Write destructor member in the same class and display the message "Object n goes out of the scope". 
Your program should be made such that it should show the order of constructor and destructor invocation.*/
#include <iostream>
class Depart {
public:
	Depart(unsigned id, const char* name) :m_id(id), m_name(new char[strlen(name)+1]) {
		strcpy(m_name, name);
		std::cout << "Department " << m_name << " of id " << m_id << " is constructed.\n";
	}

	~Depart() {
		std::cout << "Object " << m_id <<" of name "<<m_name<<" goes out of scope.\n";
		delete[] m_name;
	}
private:
	unsigned m_id;
	char* const m_name;
};

int main3() {
	Depart dpt1(456, "First Depart");
	Depart* dpt2 = new Depart(123, "Second Depart");
	delete dpt2;
	return 0;
}
//Ex2 
/*Write a program that has a class with a dynamically allocated character array as its data member.
One object should contain "Engineers are" and another should contain " Creatures of logic".
Member function join() should concatenate two strings by passing two objects as arguments.
Display the concatenated string through a member function. Use constructors to allocate and
initialize the data member. Also, write a destructor to free the allocated memory for the character array.
Make your own function for the concatenation of two strings.*/
#include <iostream>
class MyString {
public:
	MyString(const char* str) {
		m_len = strlen(str);
		m_str = new char[m_len + 1];
		memcpy(m_str, str, m_len + 1);
	}

	MyString& join(const MyString& add) {
		char* newStr = new char[m_len + add.m_len + 1];
		memcpy(newStr, m_str, m_len);
		memcpy(newStr + m_len, add.m_str, add.m_len + 1);
		delete[] m_str;
		m_str = newStr;
		m_len += add.m_len;
		return *this;
	}

	void print() const {
		std::cout << m_str;
	}

	~MyString() {
		delete[] m_str;
	}

private:
	char* m_str;
	unsigned m_len;

};

int main2() {
	MyString str1("Engineers are ");
	MyString str2("creatures of logic.");

	std::cout << "Str1 : ";
	str1.print();
	std::cout << "\nStr2 : ";
	str2.print();
	std::cout << "\nStr1 + Str2 : ";
	str1.join(str2).print();
	
	return 0;
}

//Ex1
/* Write a program that has a class to represent time.
The class should have constructors to initialize data members 
hour, minute, and second to 0 and to initialize them to values passed as arguments. 
The class should have a member function to add time objects and return the result as 
a time object. There should be functions to display time in 12-hour and 24-hour format.*/

#include<iostream>

class Time {
private:
	void simplify() {
		if (m_sec >= 60) {
			m_min += m_sec / 60;
			m_sec %= 60;
		}
		else if (m_sec < 0) {
			m_min += (m_sec + 1) / 60 - 1;
			m_sec = 60 - (-m_sec) % 60;
		}
		if (m_min>= 60) {
			m_hour += m_min/ 60;
			m_min %= 60;
		}
		else if (m_min < 0) {
			m_hour+= (m_min+ 1) / 60 - 1;
			m_min= 60 - (-m_min) % 60;
		}

	}
public:
	Time(int sec = 0, int min = 0, int hour = 0)
		:m_hour(hour), m_min(min), m_sec(sec) {
		simplify();
	}

	Time add(const Time& t) const {
		Time t_sum(m_sec + t.m_sec, m_min + t.m_min, m_hour + t.m_hour);
		return t_sum;
	}

	void show12Hrs() const {
		std::cout << " " << ((m_hour%12==0)?12:(m_hour%12)) << " : "
			<< m_min << " : " << m_sec << " " <<( (m_hour > 12) ? "PM\n" : "AM\n");
	}
	//destructors &exceptions, delete obj stack
	void show24Hrs() const {
		std::cout << " " << m_hour << " : " << m_min << " : " << m_sec << "\n";
	}

private:
	
	int m_hour;
	int m_min;
	int m_sec;
};

int main1() {
	Time t1, t2(2, 4, 16);
	t1.show12Hrs();
	t1.show24Hrs();
	t2.show12Hrs();
	t2.show24Hrs();
	Time t3 = t2.add(Time(124, 234));
	t3.show12Hrs();
	t3.show24Hrs();


	return 0;
}

#include <iostream>
#include <cstdlib>

int main() {

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
				
	main5();
	system("pause");
	std::cout << std::endl;
				
	main6();
	system("pause");
	std::cout << std::endl;



	return 0;
}