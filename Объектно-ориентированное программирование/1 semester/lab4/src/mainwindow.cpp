#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::on_pushButton_clicked);
    connect(ui->amountLine, &QLineEdit::textEdited, this, &MainWindow::on_lineEdit_textEdited);
    connect(ui->smallPhoto, &QAbstractButton::toggled, this, &MainWindow::update_atributes);
    connect(ui->mediumPhoto, &QAbstractButton::toggled, this, &MainWindow::update_atributes);
    connect(ui->largePhoto, &QAbstractButton::toggled, this, &MainWindow::update_atributes);
    connect(ui->glancPhoto, &QAbstractButton::toggled, this, &MainWindow::update_atributes);
    connect(ui->matPhoto, &QAbstractButton::toggled, this, &MainWindow::update_atributes);
    connect(ui->amountLine, &QLineEdit::textEdited, this, &MainWindow::update_atributes);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_atributes()
{
    ui->resultLine->clear();

    ui->resultLine_2->clear();

    ui->resultLine_3->clear();
}

void MainWindow::on_pushButton_clicked()
{
    int price{0};
    QRadioButton *q;
    for (int i{1};i<(ui->photoGroup->children().value(0)->children().size());i++)
    {
        q = qobject_cast<QRadioButton*>( ui->photoGroup->children().value(0)->children().value(i) );
        if (q->isChecked())
        {
            price += q->property("Price").toInt();
        }
    }

    for (int i{1};i<(ui->paperGroup->children().value(0)->children().size());i++)
    {
        q = qobject_cast<QRadioButton*>( ui->paperGroup->children().value(0)->children().value(i) );
        if (q->isChecked())
        {
            price += q->property("Price").toInt();
        }
    }

    int amount = ui->amountLine->text().toInt();
    int sale{0};
    price = price * amount;

    if (amount >= 10)
    {
        sale = price * 0.15;

        ui->resultLine_2->setText(QString::number(sale));
    }
    else
    {
        ui->resultLine_2->setText("0");
    }

    ui->resultLine_3->setText(QString::number(price));

    price = price - sale;

    ui->resultLine->setText(QString::number(price));
}

void MainWindow::on_lineEdit_textEdited()
{
    if (ui->amountLine->text().toInt() < 1)
    {
        ui->amountLine->clear();
    }
}
