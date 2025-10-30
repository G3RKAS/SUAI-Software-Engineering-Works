#ifndef ESTATE_H
#define ESTATE_H
#include <QObject>

class Estate : public QObject
{
    Q_OBJECT

public:
    enum EstateType {
        ECONOM,
        LUXURIOUS,
        TOWN_HOUSE,
        COTTAGE
    };
    explicit Estate(QObject *parent = nullptr, int = 0, int = 0, int = 0, int = 0, EstateType = EstateType::ECONOM, QString = "");
    EstateType getType() const;
    int getAge() const;
    int getArea() const;
    int getResidents() const;
    int getMonths() const;
    QString getOwner() const;

private:
    int age;
    int area;
    int residents;
    int months;
    EstateType type;
    QString owner;
};

#endif // ESTATE_H
