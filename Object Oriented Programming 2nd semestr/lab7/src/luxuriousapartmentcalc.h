#ifndef LUXURIOUSAPARTMENTCALC_H
#define LUXURIOUSAPARTMENTCALC_H


#include "bstractcalc.h"
#include <QObject>

class LuxuriousApartmentCalc : public bstractCalc
{
    Q_OBJECT
public:
    explicit LuxuriousApartmentCalc(QObject *parent = nullptr);
    virtual int getCost(Estate *value) override;

signals:
};

#endif // LUXURIOUSAPARTMENTCALC_H
