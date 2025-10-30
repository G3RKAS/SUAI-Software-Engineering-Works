#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <cmath>


using namespace std;

class cyl
{

private:
    float r;
    float h;
public:
    void setRadius(float value);
    void setHeight(float value);
    float getRadius();
    float getHeight();
    float getCylVol();
    float getCylArea();
    void printParams();
    void printInfo();
    cyl();
    cyl(float, float);
    cyl(const cyl&);
    ~cyl();
};

void cyl::setRadius(float value)
{
    r = value;
}

void cyl::setHeight(float value)
{
    h = value;
}

float cyl::getRadius()
{
    return r;
}

float cyl::getHeight()
{
    return h;
}

float cyl::getCylVol()
{
    return M_PI * pow(r,2) * h;
}

float cyl::getCylArea()
{
    return 2 * M_PI * pow(r, 2) + 2 * M_PI * r * h;
}

void cyl::printParams()
{
    cout << "Цилиндр радиусом " << r << " и высотой " << h << endl;
}

void cyl::printInfo()
{
    cout << "Объём цилиндра " << getCylVol() << endl;
    cout << "Полная площадь цилиндра " << getCylArea() << endl;
}

cyl::cyl() {
    r = 1;
    h = 1;
}

cyl::cyl(float r, float h) {
    this->r = r;
    this->h = h;
}

cyl::cyl(const cyl& ob) {
    r = ob.r;
    h = ob.h;
}

cyl::~cyl() {
    cout << "Деструктор работает" << endl;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    
    cyl cyl1; // Конструктор по умолчанию
    cyl1.printParams();
    cyl1.printInfo();
    cout << endl;

    cyl cyl2(3,7); // Конструктор с параметром
    cyl2.printParams();
    cyl2.printInfo();
    cout << endl;

    cyl cyl3(cyl2); // Конструктор копирования
    cyl3.printParams();
    cyl3.printInfo();
    cout << endl;
}



