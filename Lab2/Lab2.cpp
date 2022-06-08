#include <iostream>
#include <cstdlib>
//Ex1 storing and printing a date using struct
#include <iostream>

struct Date {
    unsigned d;
    unsigned m;
    unsigned y;
};

void printDate(const Date& d) {
    std::cout << d.m << "/" << d.d << "/" << d.y << " ";
}

int ex1(){
    Date someDate = { 13,2,2004 };
    std::cout << "The date stored is ";
    printDate(someDate);
    return 0;
}

//Ex2 Example of function overloading and passing by using refrence 
#include <iostream>

//Since with no parameters, accepts feets from user and returns in inches
float feetToInch() {
    std::cout << "Enter distance in feet : ";
    float feet; 
    std::cin >> feet;
    return feet * 12;
}

//Converts given feet to inches and returns the value
float feetToInch(float feet) {
    return feet * 12;
}

//Converts the given feet to inches and stores output in second variable passed as refrence
//Also returns the converted value in inches
float feetToInch(float feet, float& outInches) {
    outInches = feet * 12;
    return outInches;
}

int ex2() {

    float inch1 = feetToInch();
    std::cout << "Inches converted by function with no parameters : " << inch1<<std::endl;
    
    std::cout << "From function with 1 parameter, 13 feet = " << feetToInch(13.0) << " inches\n";

    float inch3;
    feetToInch(5.3, inch3);
    std::cout << "Using refrence variable and function with two parameters,\n";
    std::cout << "5.3 feet = " << inch3 << "inches." << std::endl;

    return 0;
}


//Ex3 An example of namespaces in C++
#include <iostream>

namespace Square {
    int num;
    int fun(int a) {
        return a * a;
    }
}

namespace Cube {
    int num;
    int fun(int a) {
        return a * a * a;
    }
}


int ex3() {
    Square::num = 3;
    Cube::num = 5;
    std::cout << "Square::num = " << Square::num;
    std::cout << "\nCube::num = " << Cube::num;
    std::cout << "\nSquare::fun(Cube::num) = " << Square::fun(Cube::num);
    std::cout << "\nCube::fun(Square::num) = " << Cube::fun(Square::num);

    return 0;
}

//Ex4 Proper demonstration of refrence variables of C++
#include <iostream>

float& getLargerTempr(float& t1, float& t2) {

    switch (t1 > t2) {
    case true:
        return t1;
    default:
        return t2;
    }
}

int ex4() {

    std::cout << "Enter two temperatures : ";
    float t1, t2;
    std::cin >> t1 >> t2;
    std::cout << "Enter value to replace larger temperature: ";
    std::cin >> getLargerTempr(t1, t2);
    std::cout << "Final temperatures : " << t1 << " and " << t2 << std::endl;

    return 0;
}
//Demonstration of inline function
#include<iostream>

inline float getNetEarning(float salary) {
    return salary * (1 - 0.1);
}

int ex5() {
    float salary;
    std::cout << "Enter salary of employee : ";
    std::cin >> salary;
    std::cout << "Net earning = " << getNetEarning(salary) << std::endl;
    return 0;
}

//Ex6 Use of default arguments in function
#include<iostream>

void increaseSalary(float& salary, int incPercent = 12) {
    salary *= static_cast<float>(incPercent) / 100 + 1;
}

int ex6() {
    //in 2009
    float CEO_salary = 35000;
    float INF_salary = 25000;
    float SYS_salary = 24000;
    float PRG_salary = 18000;

    std::cout << "In 2009: --" << std::endl;
    std::cout << "CEO salary:" << CEO_salary << std::endl;
    std::cout << "INF salary:" << INF_salary << std::endl;
    std::cout << "SYS salary:" << SYS_salary << std::endl;
    std::cout << "PRG salary:" << PRG_salary << std::endl;

    //in 2010
    increaseSalary(CEO_salary, 9);
    increaseSalary(INF_salary, 10);
    increaseSalary(SYS_salary);
    increaseSalary(PRG_salary);

    std::cout << "In 2010: --" << std::endl;
    std::cout << "CEO salary:" << CEO_salary << std::endl;
    std::cout << "INF salary:" << INF_salary << std::endl;
    std::cout << "SYS salary:" << SYS_salary << std::endl;
    std::cout << "PRG salary:" << PRG_salary << std::endl;
    return 0;
}

#include <iomanip>
int main()
{
    using std::cout;
    using std::setw;
    using std::endl;
    int lexp = 2000, cexp = 800, texp = 2500;
    cout << setw(11) << "LODGING" << setw(8) << lexp << endl;

    cout << setw(11) << "CLOTHING" << setw(8) << cexp << endl;

    cout << setw(11) << "TRAVELING" << setw(8) << texp << endl;

    ex1();
    std::cout << std::endl;
    system("pause");
    
    ex2();
    std::cout << std::endl;
    system("pause");
    
    ex3();
    std::cout << std::endl;
    system("pause");

    ex4();
    std::cout << std::endl;
    system("pause");

    ex5();
    std::cout << std::endl;
    system("pause");

    ex6();
    std::cout << std::endl;
    system("pause");

    return 0;
}
