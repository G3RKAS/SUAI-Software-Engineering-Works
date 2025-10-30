#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clientsmenu.h"
#include "mastersmenu.h"
#include "ordersmenu.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    ClientsMenu* GetClientsMenu();
    OrdersMenu* GetOrdersMenu();
    MastersMenu* GetMastersMenu();

private:
    Ui::MainWindow* ui;
    ClientsMenu* CM;
    OrdersMenu* OM;
    MastersMenu* MM;

private slots:
    void AddOrder(Order*);
    void ExecuteOrder(int);
    void RemoveOrder(int);
    void RemoveClient(int);
    void RemoveMaster(QString);
    void MainClientsClicked();
    void MainOrdersClicked();
    void MainMastersClicked();
};
#endif // MAINWINDOW_H
