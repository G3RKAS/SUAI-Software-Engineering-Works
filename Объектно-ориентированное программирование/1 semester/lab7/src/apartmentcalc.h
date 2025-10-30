#ifndef APARTMENTCALC_H
#define APARTMENTCALC_H

#include "bstractcalc.h"
#include <QObject>

class ApartmentCalc : public bstractCalc
{
public:
    explicit ApartmentCalc(QObject *parent = nullptr);
    int getCost(Estate *value) override;
};

#endif // APARTMENTCALC_H
