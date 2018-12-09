#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);





    //界面
    this->setWindowTitle(tr("学生信息管理系统"));
    //按键
    QMenu *file = menuBar()->addMenu(tr("&文件"));

    newAction = new QAction(tr("新建..."),this);
    connect(newAction,SIGNAL(triggered()),this,SLOT(newFile()));
    file->addAction(newAction);

    openAction = new QAction(tr("打开..."),this);
    connect(openAction,SIGNAL(triggered()),this,SLOT(openFile()));
    file->addAction(openAction);

    saveAction = new QAction(tr("保存..."),this);
    connect(saveAction,SIGNAL(triggered()),this,SLOT(saveFile()));
    file->addAction(saveAction);

    QMenu *modify = menuBar()->addMenu(tr("&修改"));
    addAction = new QAction(tr("增加"),this);
    connect(addAction,SIGNAL(triggered()),this,SLOT(addModify()));
    modify->addAction(addAction);

    deleteAction = new QAction(tr("删除"),this);
    connect(deleteAction,SIGNAL(triggered()),this,SLOT(deleteModify()));
    modify->addAction(deleteAction);

    QMenu *view = menuBar()->addMenu(tr("&查看"));
    sortAction = new QAction(tr("排序"),this);
    connect(sortAction,SIGNAL(triggered()),this,SLOT(sortView()));
    view->addAction(sortAction);

    searchAction = new QAction(tr("搜索"),this);
    connect(searchAction,SIGNAL(triggered()),this,SLOT(searchView()));
    view->addAction(searchAction);









    //表格
    QWidget *widget = new QWidget();
    this->setCentralWidget(widget);
    QLayout *layout = new QHBoxLayout;
    QTableWidget *table = new QTableWidget();
    table->setColumnCount(5);
    table->setRowCount(2);
    table->horizontalHeader()->setHighlightSections(false);

    connect(table,SIGNAL(cellChanged(int,int)),this,SLOT(tableModify(int,int)));

    QStringList header;
    header<<QObject::tr("姓名")<<QObject::tr("学号")<<QObject::tr("年级")<<QObject::tr("专业方向")<<QObject::tr("GPA");
    //table->horizontalHeader()->setDefaultSectionSize(15);
    //table->horizontalHeader()->setClickable(false);
    table->setHorizontalHeaderLabels(header);
    table->setItem(0,0,new QTableWidgetItem("嘤嘤嘤？"));
    table->setItem(0,1,new QTableWidgetItem("嘤嘤嘤？"));
    table->show();
    layout->addWidget(table);

    widget->setLayout(layout);
    //工具栏搜索：支持姓名、id两种精确搜索
    //工具栏搜索：支持专业、GPA、年龄三种模糊搜索
    QToolBar *toolBar = addToolBar(tr("&搜索"));
    toolBar->addAction(searchAction);

    //数据库呈现:这里无需呈现，因为刚打开程序，既没有添加也没有读入文件
    //后续考虑加入历史纪录，每次打开软件后，自动开打开上一次的文件。这样需要先读一个墓碑文件，之后再读入用户文件，初始化数据库，再修改行数
    stuDB = new studentDatabase();
    table->setRowCount(stuDB->getSize()+3);

    this->resize(QSize(800,600));
}

void MainWindow::newFile(){
    qDebug()<<tr("newFile");

}

void MainWindow::openFile(){
    qDebug()<<tr("openFile");

}
void MainWindow::saveFile(){
    qDebug()<<tr("saveFile");

}
void MainWindow::addModify(){
    qDebug()<<tr("addModify");

}
void MainWindow::deleteModify(){
    qDebug()<<tr("deleteModify");

}
void MainWindow::sortView(){
    qDebug()<<tr("sortView");

}
void MainWindow::searchView(){
    qDebug()<<tr("searchView");

}
void MainWindow::tableModify(int row,int column){
    qDebug()<<"modify";
    qDebug()<<row;
    qDebug()<<column;
}

MainWindow::~MainWindow()
{
    delete ui;
}
