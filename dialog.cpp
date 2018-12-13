#include"dialog.h"

dialog::dialog(QWidget *parent):QDialog(parent){
    initialize();
}

dialog::~dialog()
{

}

void dialog::initialize(){
    this->setWindowTitle(tr("搜索"));
    setWindowFlags(Qt::WindowCloseButtonHint);
    //searchLabel = new QLabel(tr("&搜索"));

    searchLineEdit = new QLineEdit();

    //searchLabel->setBuddy(searchLineEdit);//快捷键绑定;

    searchButton1 = new QPushButton(tr("&搜索"));
    searchButton2 = new QPushButton(tr("&上一个"));
    searchButton3 = new QPushButton(tr("&下一个"));
    searchButton4 = new QPushButton(tr("&完成"));

    searchLayout = new QHBoxLayout;
    //searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(searchLineEdit);

    searchLayout->addWidget(searchButton1);
    searchLayout->addWidget(searchButton2);
    searchLayout->addWidget(searchButton3);
    searchLayout->addWidget(searchButton4);

    setLayout(searchLayout);
}
