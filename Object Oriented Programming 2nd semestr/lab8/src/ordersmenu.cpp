#include "ordersmenu.h"
#include "ui_ordersmenu.h"

OrdersMenu::OrdersMenu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::OrdersMenu)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::Window);

    this->NumOfOrders = 0;
    auto OrdersTable = ui->OrdersTable;
    OrdersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    OrdersTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    model = new QStandardItemModel(0, 4);
    SetModelHeader();
    OrdersTable->setModel(model);

    ui->RegNumClientEdit->setValidator(new QIntValidator(0, 810, this));
    ui->RegNumMasterEdit->setInputMask(">AA-9000;_");
    auto Validator = new QIntValidator(this);
    Validator->setBottom(1);
    ui->NumOfRowEdit->setValidator(Validator);

    connect(ui->RegNumClientEdit, &QLineEdit::textChanged, this, &OrdersMenu::InfoChanged);
    connect(ui->RegNumMasterEdit, &QLineEdit::textChanged, this, &OrdersMenu::InfoChanged);
    connect(ui->ThingEdit, &QLineEdit::textChanged, this, &OrdersMenu::InfoChanged);
    connect(ui->NumOfRowEdit, &QLineEdit::textChanged, this, &OrdersMenu::RowNumberChanged);

    connect(ui->AddOrder, &QPushButton::clicked, this, [this] {
        emit RequestToAddOrder(new Order(nullptr, ui->RegNumClientEdit->text().toInt(), ui->RegNumMasterEdit->text(), ui->ThingEdit->text()));});
    connect(ui->ExecuteOrder, &QPushButton::clicked, this, [this] {emit RequestToExecuteOrder(ui->NumOfRowEdit->text().toInt());});
    connect(ui->RemoveOrder, &QPushButton::clicked, this, [this] {emit RequestToRemoveOrder(ui->NumOfRowEdit->text().toInt());});
}

OrdersMenu::~OrdersMenu()
{
    auto ListBegin = OrderList.begin();
    auto ListEnd = OrderList.end();
    for (;ListBegin<ListEnd; ListBegin++)
    {
        delete *ListBegin;

    }
    model->clear();
    delete model;
    delete ui;
}

bool OrdersMenu::HasSomeoneNotcompletedOrder(int RegNumber)
{
    auto ListBegin = OrderList.begin();
    auto ListEnd = OrderList.end();
    for (;ListBegin<ListEnd; ListBegin++)
    {
        if ((*ListBegin)->GetClientRegNumber() == RegNumber && (*ListBegin)->GetStatusOfRepair() == "В процессе")
        {
            return true;
        }
    }
    return false;
}

bool OrdersMenu::HasSomeoneNotcompletedOrder(QString RegCode)
{
    auto ListBegin = OrderList.begin();
    auto ListEnd = OrderList.end();
    for (;ListBegin<ListEnd; ListBegin++)
    {
        if ((*ListBegin)->GetMasterRegCode() == RegCode && (*ListBegin)->GetStatusOfRepair() == "В процессе")
        {
            return true;
        }
    }
    return false;
}


int OrdersMenu::GetSizeOfList()
{
    return this->NumOfOrders;
}

QString OrdersMenu::GetMasterRegCodeByValue(int OrderNumber)
{
    auto OrderInfo = OrderList.at(OrderNumber-1);
    return OrderInfo->GetMasterRegCode();
}

QStandardItemModel* OrdersMenu::GetModelOfMenu()
{
    return model;
}

void OrdersMenu::SetModelHeader()
{
    model->setHeaderData(0, Qt::Horizontal, "Номер клиента");
    model->setHeaderData(1, Qt::Horizontal, "Номер мастера");
    model->setHeaderData(2, Qt::Horizontal, "Объект заказа");
    model->setHeaderData(3, Qt::Horizontal, "Статус");
}


void OrdersMenu::ClearInputs()
{
    ui->AddOrder->setDisabled(true);
    ui->RemoveOrder->setDisabled(true);

    ui->RegNumClientEdit->clear();
    ui->RegNumMasterEdit->clear();
    ui->ThingEdit->clear();
    ui->NumOfRowEdit->clear();
}

void OrdersMenu::AddNewOrderToModel(Order* OrderInfo)
{
    int IndexForAdd = ++this->NumOfOrders-1;
    model->setItem(IndexForAdd, 0, new QStandardItem(QString::number(OrderInfo->GetClientRegNumber())));
    model->setItem(IndexForAdd, 1, new QStandardItem(OrderInfo->GetMasterRegCode()));
    model->setItem(IndexForAdd, 2, new QStandardItem(OrderInfo->GetThingToRepair()));
    model->setItem(IndexForAdd, 3, new QStandardItem(OrderInfo->GetStatusOfRepair()));
    OrderList.append(OrderInfo);
}

void OrdersMenu::RemoveOrder(int OrderNumber)
{
    OrderList.removeAt(OrderNumber-1);
    model->removeRow(OrderNumber-1);
    this->NumOfOrders--;
}

void OrdersMenu::SetOrderAsCompleted(int OrderNumber)
{
    auto OrderInfo = OrderList.at(OrderNumber-1);
    OrderInfo->SetOrderNumber(-1);
    OrderInfo->SetRepairStatus(Order::RepairStatus::Completed);
    model->setItem(OrderNumber-1, 3, new QStandardItem(OrderInfo->GetStatusOfRepair()));
}

void OrdersMenu::InfoChanged()
{
    if (ui->RegNumClientEdit->hasAcceptableInput() && ui->RegNumMasterEdit->hasAcceptableInput() &&
        not(ui->ThingEdit->text().isEmpty()))
    {
        ui->AddOrder->setDisabled(false);
    }
    else
    {
        ui->AddOrder->setDisabled(true);
    }
}

void OrdersMenu::RowNumberChanged()
{
    if (ui->NumOfRowEdit->hasAcceptableInput() && NumOfOrders>0)
    {
        ui->RemoveOrder->setDisabled(false);
        ui->ExecuteOrder->setDisabled(false);
    }
    else
    {
        ui->RemoveOrder->setDisabled(true);
        ui->ExecuteOrder->setDisabled(true);
    }
}
