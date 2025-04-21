#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "clientsmenu.h"
#include "ordermanipulate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    CM = new ClientsMenu(this);
    OM = new OrdersMenu(this);
    MM = new MastersMenu(this);

    connect(ui->ClientsButton, &QPushButton::clicked, this, &MainWindow::MainClientsClicked);
    connect(ui->OrdersButton, &QPushButton::clicked, this, &MainWindow::MainOrdersClicked);
    connect(ui->MastersButton, &QPushButton::clicked, this, &MainWindow::MainMastersClicked);

    connect(OM, &OrdersMenu::RequestToAddOrder, this, &MainWindow::AddOrder);
    connect(OM, &OrdersMenu::RequestToExecuteOrder, this, &MainWindow::ExecuteOrder);
    connect(OM, &OrdersMenu::RequestToRemoveOrder, this, &MainWindow::RemoveOrder);
    connect(CM, &ClientsMenu::RequestToRemoveClient, this, &MainWindow::RemoveClient);
    connect(MM, &MastersMenu::RequestToRemoveMaster, this, &MainWindow::RemoveMaster);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AddOrder(Order* OrderInfo)
{
    OrderManipulate::AddOrder(OrderInfo, this);
}

void MainWindow::ExecuteOrder(int OrderNumber)
{
    OrderManipulate::ExecuteOrder(OrderNumber, this);
}

void MainWindow::RemoveOrder(int OrderNumber)
{
    OrderManipulate::RemoveOrder(OrderNumber, this);
}

void MainWindow::RemoveClient(int RegNumber)
{
    OrderManipulate::RemoveClient(RegNumber, this);
}

void MainWindow::RemoveMaster(QString RegCode)
{
    OrderManipulate::RemoveMaster(RegCode, this);
}


ClientsMenu* MainWindow::GetClientsMenu()
{
    return this->CM;
}

OrdersMenu* MainWindow::GetOrdersMenu()
{
    return this->OM;
}

MastersMenu* MainWindow::GetMastersMenu()
{
    return this->MM;
}

void MainWindow::MainClientsClicked()
{
    CM->show();
}

void MainWindow::MainOrdersClicked()
{
    OM->show();
}

void MainWindow::MainMastersClicked()
{
    MM->show();
}
