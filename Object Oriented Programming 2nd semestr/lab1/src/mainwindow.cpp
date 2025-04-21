#include "mainwindow.h"
#include "main_functions.h"
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

void MainWindow::on_clcButton_clicked()
{
    ui->firstNumberEdit->clear();
    ui->secondNumberEdit->clear();
    ui->resultText->clear();
    unlockButtons(ui->operLayout_1, false);
    unlockButtons(ui->operLayout_2, false);
}


void MainWindow::on_sumButton_clicked()
{
    ui->resultText->setText(QString::number(ui->firstNumberEdit->text().toFloat() + ui->secondNumberEdit->text().toFloat()));
}

void MainWindow::on_subButton_clicked()
{
    ui->resultText->setText(QString::number(ui->firstNumberEdit->text().toFloat() - ui->secondNumberEdit->text().toFloat()));
}


void MainWindow::on_mulButton_clicked()
{
    ui->resultText->setText(QString::number(ui->firstNumberEdit->text().toFloat() * ui->secondNumberEdit->text().toFloat()));
}


void MainWindow::on_divButton_clicked()
{
    if (ui->secondNumberEdit->text() == "0")
    {
        ui->resultText->setText("Деление на нуль!");
    }
    else
    {
        ui->resultText->setText(QString::number(ui->firstNumberEdit->text().toFloat() / ui->secondNumberEdit->text().toFloat()));
    }
}


void MainWindow::on_powButton_clicked()
{
    QString result(QString::number(pow(ui->firstNumberEdit->text().toFloat(), ui->secondNumberEdit->text().toFloat())));
    if (result == "inf")
    {
        ui->resultText->setText("Слишком большое число");
    }
    else
    {
        ui->resultText->setText(result);
    }
}


void MainWindow::on_percentButton_clicked()
{
    if (ui->secondNumberEdit->text() == "0")
    {
        ui->resultText->setText("0");
    }
    else
    {
        ui->resultText->setText(QString::number((ui->firstNumberEdit->text().toFloat() / ui->secondNumberEdit->text().toFloat()) * 100) + "%");
    }
}


void MainWindow::on_firstNumberEdit_textEdited(const QString &arg1)
{
    if (not(ui->firstNumberEdit->text().isEmpty() or ui->secondNumberEdit->text().isEmpty()))
    {
        unlockButtons(ui->operLayout_1, true);
        unlockButtons(ui->operLayout_2, true);
    }
    else
    {
        unlockButtons(ui->operLayout_1, false);
        unlockButtons(ui->operLayout_2, false);
    }
}


void MainWindow::on_secondNumberEdit_textEdited(const QString &arg1)
{
    if (not(ui->firstNumberEdit->text().isEmpty() or ui->secondNumberEdit->text().isEmpty()))
    {
        unlockButtons(ui->operLayout_1, true);
        unlockButtons(ui->operLayout_2, true);
    }
    else
    {
        unlockButtons(ui->operLayout_1, false);
        unlockButtons(ui->operLayout_2, false);
    }
}
