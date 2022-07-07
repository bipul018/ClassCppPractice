/*
Write a base class that asks the user to enter a complex number and make 
a derived class that adds the complex number of its own with the base. 
Finally, make a third class that is a friend of derived and calculate 
the difference of the base complex number and its own complex number.
*/

#include <iostream>
using namespace std;

class Complex
{
public:
    void getIn() {
        cout << "Enter real and imaginary :";
        cin >> m_real >> m_imag;
    }
    void display()
    {
        cout << "The complex number is: " << m_real << " + i" << m_imag << endl;
    }

    float m_real;
    float m_imag;
};

class Inherit : public Complex
{
public:
    friend class CFriend;
    void add(Complex a)
    {
        cout << "The sum from base and inherited : " << a.m_real + m_real << " + i" << a.m_imag + m_imag << endl;
    }
    
};
class CFriend
{
public:
    void diff(Complex a)
    {
        cout << "The difference of base and friend: " << a.m_real - m_real << " + i" << a.m_imag - m_imag << endl;
    }
    void getIn() {
        cout << "Enter real and imaginary :";
        cin >> m_real >> m_imag;
    }
    void display()
    {
        cout << "The complex number is: " << m_real << " + i" << m_imag << endl;
    }
private:
    float m_real, m_imag;

};
int main5()
{
    Complex a;
    cout << "For base class: " << endl;
    a.getIn();
    a.display();
    Inherit b;
    cout << "For inherited class: " << endl;
    b.getIn();
    b.display();
    b.add(a);
    CFriend c;
    cout << "For friend class: " << endl;
    c.getIn();
    c.display();
    c.diff(a);
    return 0;
}

/*
Write three derived classes inheriting functionality of base class person 
(should have a member function that asks to enter name and age) 
and with added unique features of student, and employee, and functionality 
to assign, change and delete records of student and employee. 
And make one member function for printing the address of 
the objects of classes (base and derived) using this pointer. 
Create two objects of the base class and 
derived classes each and print the addresses of individual objects. 
Using a calculator, calculate the address space occupied by 
each object and verify this with address spaces printed by the program.
*/


#include <iostream>
#include <string>
using namespace std;
class person {
private:
    string Name;
    int Age;
public:
    void askName() {
        cout << "What is the name? " << endl;
        cin >> Name;
    }
    void askAge() {
        cout << "What is the age? " << endl;
        cin >> Age;
    }
    void pAdd() {
        cout << this << endl;
    }
};
class student : public person {
private:
    int rollNo;
    int level;
public:
    void printRollNo() {
        cout << "Roll Number: " << rollNo << endl;
    }
    void printLevel() {
        cout << "Level: " << level << endl;
    }
    void pAdd() {
        cout << this << endl;
    }
};
class employee : public person {
private:
    int salary;
    int idNo;
public:
    void printSalary() {
        cout << "Salary: " << salary << endl;
    }
    void printIdNo() {
        cout << "Id Number: " << idNo << endl;
    }
    void pAdd() {
        cout << this << endl;
    }
};
int main4() {
    person p1, p2;
    student s1, s2;
    employee e1, e2;
    cout << "Addresses of pointers\n";

    cout << "P1 :"; 
    p1.pAdd(); 
    cout << " P2 :"; 
    p2.pAdd();
    cout << "\nS1 :" ; 
    s1.pAdd(); 
    cout<< " S2 :" ; 
    s2.pAdd();
    cout << "\nE1 :" ; 
    e1.pAdd(); 
    cout << " E2 :"; 
    e2.pAdd();

    cout << "Sizes of objects: \n";
    cout << "Person: " << sizeof(p1) << endl;

    cout << "Student: " << sizeof(s1) << endl;

    cout << "mployee: " << sizeof(e1) << endl;

    return 0;
}

/*
Create a class called Musicians to contain three methods string(), wind(), and perc(). 
Each of these methods should initialize a string array to contain the following instruments

-  veena, guitar, sitar, sarod and mandolin under string()

-  flute, clarinet saxophone, nadhaswaram, and piccolo under wind()

-  tabla, mridangam, bangos, drums and tambour under perc()

It should also display the contents of the arrays that are initialized. 
Create a derived class called TypeIns to contain a method called get() and show(). 
The get() method must display a  menu as follows

Type of instruments to be displayed

a.  String instruments

b.  Wind instruments

c.  Percussion instruments

The show() method should display the relevant detail according to our choice. 
The base class variables must be accessible only to their derived classes.
*/

#include <iostream>
#include <string>
using namespace std;
class Musicians {
public:
    void strings() {      //veena, guitar, sitar, sarod and mandolin
        m_string[0] = "veena";
        m_string[1] = "guitar";
        m_string[2] = "sitar";
        m_string[3] = "sarod";
        m_string[4] = "mandolin";
        cout << "String Instruments: " << endl;
        for (int i = 0; i < 5; i++) {
            cout << m_string[i] << endl;
        }
    }
    void winds() {        //flute, clarinet saxophone, nadhaswaram and piccolo
        m_wind[0] = "flute";
        m_wind[1] = "clarinet";
        m_wind[2] = "saxophone";
        m_wind[3] = "nadhaswaram";
        m_wind[4] = "piccolo";
        cout << "Wind Instruments: " << endl;
        for (int i = 0; i < 5; i++) {
            cout << m_wind[i] << endl;
        }
    }
    void percs() {         //tabla, mridangam, bangos, drums and tambour
        m_perc[0] = "tabla";
        m_perc[1] = "mridangam";
        m_perc[2] = "bangos";
        m_perc[3] = "drums";
        m_perc[4] = "tambour";
        cout << "Percussion Instruments: " << endl;
        for (int i = 0; i < 5; i++) {
            cout << m_perc[i] << endl;
        }
    }
protected:
    string m_string[5];
    string m_wind[5];
    string m_perc[5];
};
class TypeIns :Musicians {
public:
    void get() {
        cout << "Type of instruments to be displayed: " << endl;
        cout << "a. String instruments" << endl;
        cout << "b. Wind instruments" << endl;
        cout << "c. Percussion instruments" << endl;
    }
    void show() {
        strings();
        winds();
        percs();
    }
};
int main3() {
    TypeIns TI;
    TI.get();
    TI.show();
    return 0;
}

/*
Write two classes to store distances in meter-centimeter and feet-inch systems respectively. 
Write conversions functions so that the program can convert objects of both types.
*/
#include <iostream>

class LenMeters {
public:
    friend class LenFeet;
    LenMeters(float m,float cm):m_m(m),m_cm(cm){}
    LenMeters(LenFeet);
    friend std::ostream& operator<<(std::ostream&, LenMeters);
private:
    float m_m;
    float m_cm;
};
class LenFeet{
public:
    friend class LenMeters;
    LenFeet(float ft,float in):m_ft(ft),m_in(in){}
    LenFeet(LenMeters);
    friend std::ostream& operator<<(std::ostream&, LenFeet);
private:
    float m_ft;
    float m_in;
};

LenMeters::LenMeters(LenFeet ft) {
    m_cm = ft.m_ft * 30.48 + ft.m_in * 2.54;
    m_m = int(m_cm) / 100;
    m_cm -= m_m * 100;
}

LenFeet::LenFeet(LenMeters m) {
    m_in = (m.m_m * 100 + m.m_cm) / 2.54;
    m_ft = int(m_in) / 12;
    m_in -= m_ft * 12;
}

std::ostream& operator<<(std::ostream& os, LenMeters l) {
    os << " " << l.m_m << "m " << l.m_cm << "cm ";
    return os;
}

std::ostream& operator<<(std::ostream& os, LenFeet l) {
    os << " " << l.m_ft << "ft " << l.m_in << "in ";
    return os;
}


int main2() {
    LenFeet fts(13, 4);
    LenMeters m(5, 7);

    std::cout << fts << " = " << static_cast<LenMeters>(fts) << std::endl;
    std::cout << m << " = " << static_cast<LenFeet>(m) << std::endl;

    return 0;
}


/*
Write a program that can convert the Distance (meter, centimeter) to meters measurement in float and vice versa. 
Make a class distance with two data members, meter and centimeter. 
You can add function members as per your requirement.
*/
#include<iostream>

class Distance {
public:
    Distance() :Distance(0) {}
    Distance(float m) {
        m_meter = static_cast<int>(m);
        m_centim = (m - m_meter) * 100;
    }
    operator float() const{
        return m_meter + m_centim * 0.01;
    }
    float getMeter() const {
        return m_meter;
    }
    float getCenti() const {
        return m_centim;
    }
private:
    float m_meter;
    float m_centim;
};

int main1() {
    Distance d;
    d = 4.678;
    std::cout << d.getMeter() << "m " << d.getCenti() << "cm = "
        << d << "m\n";
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
    
    main5();
    system("pause");
    std::cout << std::endl;

    return 0;
}
