#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H

#include <qboxlayout.h>
#include <qcheckbox.h>
#include <qlabel.h>
#include <qnamespace.h>

bool isChecked(const Qt::CheckState &arg1)
{
    if (arg1 == Qt::Checked)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool isChecked(const QWidget *arg1)
{
    if (arg1->property("Checked").toBool())
    {
        return true;
    }
    else
    {
        return false;
    }
}

void addSum(QString &arg1, const QVBoxLayout *arg2)
{
    int sum{0};
    for (int i = 0;i<arg2->count();i++)
    {

        if (isChecked(arg2->itemAt(i)->widget()))
        {
            sum += arg2->itemAt(i)->widget()->property("Price").toInt();
        }
    }
    arg1 += QString::number(sum);
}

bool isSaleActive(const QVBoxLayout *arg1)
{
    for (int i = 0;i<arg1->count();i++)
    {
        if (not(isChecked(arg1->itemAt(i)->widget())))
        {
            return false;
        }
    }
    return true;
}

void updateOutput(const QVBoxLayout *arg1, QLabel *arg2)
{
    arg2->clear();
    QString str_base = "Цена корпуса: 4000\nЦена комплектующих: ";
    QString str_price;

    addSum(str_price, arg1);

    str_base += str_price;


    if (isSaleActive(arg1))
    {
        QString final_price = QString::number(str_price.toInt() - str_price.toInt() * 0.1 + 4000);
        str_base += "\nCкидка на комплектующие: ";
        str_base +=  QString::number(str_price.toInt() * 0.1);
        str_base += "\nИтого: ";
        str_base += final_price;
    }
    else
    {
        str_price = QString::number(str_price.toInt()+4000);
        str_base += "\nИтого: ";
        str_base += str_price;
    }
    arg2->setText(str_base);
    arg2->adjustSize();
    qInfo() << str_base;
}

#endif // MAIN_FUNCTIONS_H
