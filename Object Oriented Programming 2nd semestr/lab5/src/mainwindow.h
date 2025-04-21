#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qtextedit.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MyList
{
public:
    void insert(float);
    int size();
    float at(int);
    void clear();
    bool isEmpty();
    void takeAt(int);
    void copy(MyList);
    int indexOf(float);
    QList<float>::iterator begin();
    QList<float>::iterator end();

private:
    int listSize = 0;
    QList<float> List;

    void updateSize(int);

};



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    MyList SourceList;
    MyList EditedList;

    void fileLoad();
    bool editIsEmpty(QTextEdit *);

    void indexChanged(QString);
    void elemChanged();
    void fileChanged();
    void ClearEdit();

    void loadToFile();
    void loadFromFile();

    void updateSource();
    void updateEdited();

    void clearCollection();
    void getElemByIndex();
    void removeElemByIndex();
    void editedCollectionChanged();

    void removeElemByVar();
    void addElemToEdited();
    void summElem();
    void summEvenElem();
    void summPositiveElem();
    void sortElem();
};


#endif // MAINWINDOW_H

