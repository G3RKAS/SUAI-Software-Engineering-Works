    #ifndef MASTERSMENU_H
    #define MASTERSMENU_H

    #include "qstandarditemmodel.h"
    #include "worker.h"
    #include <QWidget>

    namespace Ui {
    class MastersMenu;
    }

    class MastersMenu : public QWidget
    {
        Q_OBJECT

    public:
        explicit MastersMenu(QWidget *parent = nullptr);
        ~MastersMenu();
        bool IsMasterInList(QString);
        void SetMasterBusyStatusByRegCode(QString, int);
        Worker* GetMasterByRegCode(QString);
        void ClearInputs();
        void RemoveMasterFromModel(QString);

    signals:
        void RequestToRemoveMaster(QString);

    private:
        Ui::MastersMenu* ui;
        int NumOfMasters;
        QList<Worker*> MasterList;
        QStandardItemModel* model;

        void SetModelHeader();
        void AddNewMasterToModel(Worker*);

    private slots:
        void InfoChanged();
        void RegNumberChanged();
        void RequestToAddMaster();
    };

    #endif // MASTERSMENU_H
