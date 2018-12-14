#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<string>
#include<iostream>
using namespace std;
#include <QMainWindow>
#include <QWidget>
#include<QTableWidget>
#include<QStringList>
//#include<QLayout>
#include<QObject>
#include<QAction>
#include<QMenu>
#include<QLayout>
#include<QTableWidget>
#include<QObject>
#include<QSize>
#include<QString>
#include<QFileDialog>
#include<QFile>
#include<QMessageBox>
#include<QTextStream>
#include<Qtextedit>
#include<QContextMenuEvent>
#include<QVector>
#include<QComboBox>
#include<QLineEdit>
#include"studentdatabase.h"
#include"delegate.h"
#include"dialog.h"
#include"datedelegate.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void closeEvent(QCloseEvent *event);
private:
    Ui::MainWindow *ui;
    // QTableWidget *table;
    // QLayout *layout;
    bool saved;//文件保存标识符
    QAction *newAction;
     QAction *openAction;
     QAction *saveAction;
     QAction *exitAction;
     QAction *addAction;
     QAction *deleteAction;
     QAction *moveUpAction;
     QAction *moveDownAction;
     //QAction *sortAction;
     QAction *searchAction;
     QAction *gradeAction;
     QAction *majorAction;
     QAction *gpaAction;
     QAction *insertAction;
     studentDatabase *stuDB;
     dialog *searchDialog;
     bool c[8];
     QWidget *widget;
     QLayout *layout;
     QTableWidget *table;
     QVector<QComboBox*> *QComboBoxList;

     QLineEdit *searchQLineEditToolBar;
     QAction *searchToolBar;
     QAction *lastToolBar;
     QAction *nextToolBar;
     QPushButton *searchButton;
     QPushButton *lastButton;
     QPushButton *nextButton;

     QString searchQstr;
     int searchRow;
     int searchColumn;
     void tableInitialize();
     int partition(int p, int q, int column);
     void quickSort(int p, int q, int column);
     void Swap(int p1,int p2, int column);
     virtual void contextMenuEvent(QContextMenuEvent *event);
private slots:
     void newFile();
     void openFile();
     void saveFile();
     void addModify();
     void deleteModify();
     void moveUpModify();
     void moveDownModify();
     void sortView(int colunmIndex);
     void searchView();
     void gradeStatistic();
     void majorStatistic();
     void gpaStatistic();
     void tableModify(int row,int column);
     void insertBefore();
     void insertAfter();
     void deleteLine();
     void print_s();
     void searchQlineEditChanged(QString qstr);
     void searchToolBarTriggered();
     void lastToolBarTriggered();
     void nextToolBarTriggered();
     //void qtClose();
};

#endif // MAINWINDOW_H
