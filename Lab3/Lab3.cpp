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

//Ex2 

int main()
{
	ex1();
	putchar('\n');
	system("pause");
	putchar('\n');

}
