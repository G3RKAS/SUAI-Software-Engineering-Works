#ifndef ORDERSMENU_H
#define ORDERSMENU_H


#include "order.h"
#include "qstandarditemmodel.h"
#include <QWidget>

namespace Ui {
class OrdersMenu;
}

class OrdersMenu : public QWidget
{
    Q_OBJECT

public:
    explicit OrdersMenu(QWidget *parent = nullptr);
    ~OrdersMenu();

    void AddNewOrderToModel(Order*);
    void RemoveOrder(int);
    void SetOrderAsCompleted(int);
    int GetSizeOfList();
    QString GetMasterRegCodeByValue(int);
    QStandardItemModel* GetModelOfMenu();
    bool HasSomeoneNotcompletedOrder(int);
    bool HasSomeoneNotcompletedOrder(QString);
    void ClearInputs();

signals:
    void RequestToAddOrder(Order*);
    void RequestToExecuteOrder(int);
    void RequestToRemoveOrder(int);

private:
    Ui::OrdersMenu* ui;
    int NumOfOrders;
    QList<Order*> OrderList;
    QStandardItemModel* model;

    void SetModelHeader();

private slots:
    void InfoChanged();
    void RowNumberChanged();
};

#endif // ORDERSMENU_H



