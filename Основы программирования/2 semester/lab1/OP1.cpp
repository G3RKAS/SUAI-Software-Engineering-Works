#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Time {

private:
    int hour;
    int min;
    int sec;
public:
    void setHour(int value);
    void setMin(int value);
    void setSec(int value);
    int getHour();
    int getMin();
    int getSec();
    void addSec();
    void modern();
    void print(string stroka);
};

void Time::setHour(int value) {
    hour = value;
}

int Time::getHour() {
    return hour;
}

void Time::setMin(int value) {
    min = value;
}

int Time::getMin() {
    return min;
}

void Time::setSec(int value) {
    sec = value;
}

int Time::getSec() {
    return sec;
}

void Time::addSec() {
    sec += 1;
}

void Time::modern() {
    if (sec >= 60) {
        min += (sec / 60);
        setSec(sec % 60);
        if (min >= 60) {
            hour += (min / 60);
            setMin(min % 60);
        }
    }
}

void Time::print(string stroka) {
    cout << stroka << ": " << setfill('0') << setw(2) << hour << ":" << setfill('0') << setw(2) << min << ":" << setfill('0') << setw(2) << sec << endl;
}

int main()
{
    setlocale(LC_ALL, "RUS");

    Time time;

    time.setHour(10);
    time.setMin(100);
    time.setSec(100);

    time.addSec();

    time.print("Изначальное время");

    time.modern();

    time.print("Преобразованное время");

    time.setHour(50);
    time.setMin(1250);
    time.setSec(1990);

    time.addSec();

    time.print("Изначальное время");

    time.modern();

    time.print("Преобразованное время");

    time.setHour(1);
    time.setMin(950);
    time.setSec(450);

    time.addSec();

    time.print("Изначальное время");

    time.modern();

    time.print("Преобразованное время");
}


