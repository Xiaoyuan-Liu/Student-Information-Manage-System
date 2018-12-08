﻿#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include"studentdatabase.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    // QTableWidget *table;
    // QLayout *layout;
     QAction *openAction;
     QAction *saveAction;
     QAction *addAction;
     QAction *deleteAction;
     QAction *sortAction;
     QAction *searchAction;
     studentDatabase *stuDB;
};

#endif // MAINWINDOW_H