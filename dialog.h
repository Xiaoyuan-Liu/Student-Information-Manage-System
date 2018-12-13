#ifndef DIALOG_H
#define DIALOG_H
#include<QtWidgets>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QHBoxLayout>
class dialog:public QDialog{
    Q_OBJECT

public:
    dialog(QWidget *parent = 0);
    ~dialog();

private:
    //QLabel *searchLabel;
    QLineEdit *searchLineEdit;

    QPushButton *searchButton1;
    QPushButton *searchButton2;
    QPushButton *searchButton3;
    QPushButton *searchButton4;

    QHBoxLayout *searchLayout;
    void initialize();
};

#endif // DIALOG_H
