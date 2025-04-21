#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void checkInput(QLineEdit *arg1)
{
    bool ok{true};
    double inputing{arg1->text().toDouble(&ok)};
    if ((inputing < 0) or not(ok))
    {
        arg1->clear();
    }
}

void updatePrice(QLineEdit *arg1, QLineEdit *arg2,  QLineEdit *arg3, QLabel *arg4)
{
    arg4->clear();
    if (not((arg1->text().isEmpty()) or (arg2->text().isEmpty()) or (arg3->text().isEmpty())))
    {
        arg4->setText( QString::number( (arg1->text().toDouble() + arg2->text().toDouble()) * arg3->text().toDouble()) );
    }
}

void MainWindow::on_lengthEdit_textEdited(const QString &arg1)
{
    checkInput(ui->lengthEdit);
    updatePrice(ui->lengthEdit, ui->widthEdit, ui->priceLineEdit, ui->sum);
}


void MainWindow::on_widthEdit_textEdited(const QString &arg1)
{
    checkInput(ui->widthEdit);
    updatePrice(ui->lengthEdit, ui->widthEdit, ui->priceLineEdit, ui->sum);
}


void MainWindow::on_materialChooser_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Шелк")
    {
        ui->priceLineEdit->setText("1490");
    }
    else if (arg1 == "Крепдешин")
    {
        ui->priceLineEdit->setText("3980");
    }
    else if (arg1 == "Шерсть")
    {
        ui->priceLineEdit->setText("845");
    }
    else
    {
        ui->priceLineEdit->setText("154");
    }
    updatePrice(ui->lengthEdit, ui->widthEdit, ui->priceLineEdit, ui->sum);
}

