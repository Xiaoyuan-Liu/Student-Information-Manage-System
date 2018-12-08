#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //界面
    this->setWindowTitle(tr("学生信息管理系统"));
    //按键
    openAction = new QAction(tr("打开..."),this);
    saveAction = new QAction(tr("保存..."),this);
    addAction = new QAction(tr("增加"),this);
    deleteAction = new QAction(tr("删除"),this);
    sortAction = new QAction(tr("排序"),this);
    searchAction = new QAction(tr("搜索"),this);
    QMenu *file = menuBar()->addMenu(tr("&文件"));
    file->addAction(openAction);
    file->addAction(saveAction);
    QMenu *modify = menuBar()->addMenu(tr("&修改"));
    modify->addAction(addAction);
    modify->addAction(deleteAction);
    QMenu *view = menuBar()->addMenu(tr("&查看"));
    view->addAction(sortAction);

    //表格
    QWidget *widget = new QWidget();
    this->setCentralWidget(widget);
    QLayout *layout = new QHBoxLayout;
    QTableWidget *table = new QTableWidget();
    table->setColumnCount(5);
    QStringList header;
    header<<QObject::tr("姓名")<<QObject::tr("学号")<<QObject::tr("年级")<<QObject::tr("专业方向")<<QObject::tr("GPA");
    //table->horizontalHeader()->setDefaultSectionSize(15);
    //table->horizontalHeader()->setClickable(false);
    table->setHorizontalHeaderLabels(header);
    layout->addWidget(table);

    widget->setLayout(layout);
    //工具栏搜索：支持姓名、id两种精确搜索
    //工具栏搜索：支持专业、GPA、年龄三种模糊搜索
    QToolBar *toolBar = addToolBar(tr("&搜索"));
    toolBar->addAction(searchAction);

    //数据库呈现:这里无需呈现，因为刚打开程序，既没有添加也没有读入文件
    //后续考虑加入历史纪录，每次打开软件后，自动开打开上一次的文件。这样需要先读一个墓碑文件，之后再读入用户文件，初始化数据库，再修改行数
    stuDB = new studentDatabase();
    table->setRowCount(stuDB->getSize()+1);

    this->resize(QSize(800,600));
}

MainWindow::~MainWindow()
{
    delete ui;
}
