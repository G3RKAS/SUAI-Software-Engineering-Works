#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private slots:

    void on_motherBoard_checkStateChanged(const Qt::CheckState &arg1);

    void on_videocard_checkStateChanged(const Qt::CheckState &arg1);

    void on_processor_checkStateChanged(const Qt::CheckState &arg1);

    void on_ram_checkStateChanged(const Qt::CheckState &arg1);

    void on_cooler_checkStateChanged(const Qt::CheckState &arg1);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
