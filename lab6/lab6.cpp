/*
Write a base class that asks the user to enter a complex number and make 
a derived class that adds the complex number of its own with the base. 
Finally, make a third class that is a friend of derived and calculate 
the difference of the base complex number and its own complex number.
*/

#include<iostream>

int main5() {
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

#include<iostream>

int main4() {
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
