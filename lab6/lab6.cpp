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

    return 0;
}
