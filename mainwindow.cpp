#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QDebug>
#define itemEmpty " "
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);





    //界面
    this->setWindowTitle(tr("学生信息管理系统"));
    //菜单
    QMenu *file = menuBar()->addMenu(tr("&文件"));

    newAction = new QAction(tr("新建..."),this);
    connect(newAction,SIGNAL(triggered()),this,SLOT(newFile()));
    file->addAction(newAction);

    openAction = new QAction(tr("打开..."),this);
    //openAction->setStatusTip(tr("1234"));
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
    //sortAction = new QAction(tr("排序"),this);
    //connect(sortAction,SIGNAL(triggered()),this,SLOT(sortView()));
    //view->addAction(sortAction);

    searchAction = new QAction(tr("&搜索"),this);
    connect(searchAction,SIGNAL(triggered()),this,SLOT(searchView()));
    view->addAction(searchAction);


    QMenu *statistic = menuBar()->addMenu(tr("&统计"));
    gradeAction = new QAction(tr("年级"));
    connect(gradeAction,SIGNAL(triggered()),this,SLOT(gradeStatistic()));
    statistic->addAction(gradeAction);

    majorAction = new QAction(tr("专业"));
    connect(majorAction,SIGNAL(triggered()),this,SLOT(majorStatistic()));
    statistic->addAction(majorAction);

    gpaAction = new QAction(tr("GPA"));
    connect(gpaAction,SIGNAL(triggered()),this,SLOT(gpaStatistic()));
    statistic->addAction(gpaAction);

    /*
    QMenu *exitMenu = menuBar()->addMenu(tr("&退出"));
    connect(exitMenu,SIGNAL(triggered()),this,SLOT(exit()));
    */

    QComboBoxList = new QVector<QComboBox*>();

    //右键菜单


    //表格
    widget = new QWidget();
    this->setCentralWidget(widget);
    layout = new QHBoxLayout;
    table = new QTableWidget();
    table->setColumnCount(5);
    table->setRowCount(0);
    table->horizontalHeader()->setHighlightSections(false);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(table,SIGNAL(cellChanged(int,int)),this,SLOT(tableModify(int,int)));

    QStringList header;
    header<<tr("姓名")<<tr("性别")<<tr("学号")<<tr("年级")<<tr("专业方向")<<tr("GPA");
    //table->horizontalHeader()->setDefaultSectionSize(15);
    connect(table->horizontalHeader(),SIGNAL(sectionClicked(int)),this, SLOT(sortView(int)));
    table->setHorizontalHeaderLabels(header);
    //table->setItem(0,0,new QTableWidgetItem("嘤嘤嘤？"));
    //table->setItem(0,1,new QTableWidgetItem("嘤嘤嘤？"));
    //table->show();

    layout->addWidget(table);

    widget->setLayout(layout);
    //工具栏搜索：支持姓名、id两种精确搜索
    //QToolBar *toolBar = addToolBar(tr("&搜索"));
    //toolBar->addAction(searchAction);
    //layout->addWidget(toolBar);
    //工具栏搜索：支持专业、GPA、年龄三种模糊搜索

    QComboBox*tmp = new QComboBox();
    tmp->setEditable(false);
    table->setItemDelegateForColumn(1,new Delegate(this));
    QComboBoxList->push_back(tmp);

    tmp = new QComboBox();
    tmp->setEditable(false);
    table->setItemDelegateForColumn(4,new Delegate(this));
    //setItemIsEditable(ui.table, 0);
    QComboBoxList->push_back(tmp);

    //数据库呈现:这里无需呈现，因为刚打开程序，既没有添加也没有读入文件
    //后续考虑加入历史纪录，每次打开软件后，自动开打开上一次的文件。这样需要先读一个墓碑文件，之后再读入用户文件，初始化数据库，再修改行数
    stuDB = new studentDatabase();
    //table->setRowCount(stuDB->getSize()+3);

    for(int i = 0; i < table->columnCount();i++)
        c[i] = true;
    this->resize(QSize(800,600));
    searchQLineEditToolBar = new QLineEdit;
    searchToolBar = new QAction(tr("&搜索"),this);
    lastToolBar = new QAction(tr("&上一个"),this);
    nextToolBar = new QAction(tr("&下一个"),this);
    ui->mainToolBar->addWidget(searchQLineEditToolBar);
    ui->mainToolBar->addAction(searchToolBar);
    ui->mainToolBar->addAction(lastToolBar);
    ui->mainToolBar->addAction(nextToolBar);
    connect(searchQLineEditToolBar,SIGNAL(textChanged(QString)),this,SLOT(searchQlineEditChanged(QString)));
    connect(searchToolBar,SIGNAL(triggered()),this,SLOT(searchToolBarTriggered()));
    connect(lastToolBar,SIGNAL(triggered()),this,SLOT(lastToolBarTriggered()));
    connect(nextToolBar,SIGNAL(triggered()),this,SLOT(nextToolBarTriggered()));


    //ui->mainToolBar->addAction(new QAction(tr("&完成"),this));
    //ui->mainToolBar->addWidget(QPushButton(tr("&搜索")))
    //ui->mainToolBar->setVisible(false);
}

void MainWindow::tableInitialize(){
    delete table;
    delete layout;
    delete QComboBoxList;
    layout = new QHBoxLayout;
    table = new QTableWidget();
    QComboBoxList = new QVector<QComboBox*>();
    table->setColumnCount(5);
    table->setRowCount(0);
    table->horizontalHeader()->setHighlightSections(false);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    connect(table,SIGNAL(cellChanged(int,int)),this,SLOT(tableModify(int,int)));

    QStringList header;
    header<<tr("姓名")<<tr("性别")<<tr("学号")<<tr("年级")<<tr("专业方向")<<tr("GPA");
    connect(table->horizontalHeader(),SIGNAL(sectionClicked(int)),this, SLOT(sortView(int)));
    //table->horizontalHeader()->setDefaultSectionSize(15);
    table->setHorizontalHeaderLabels(header);
    //table->setItem(0,0,new QTableWidgetItem("嘤嘤嘤？"));
    //table->setItem(0,1,new QTableWidgetItem("嘤嘤嘤？"));
    //table->show();
    layout->addWidget(table);
    widget->setLayout(layout);
    for(int i = 0; i < table->columnCount();i++)
        c[i] = true;
}

void MainWindow::newFile(){
    qDebug()<<"newFile";
    if(table->rowCount()>0){
        QMessageBox msgBox;
        msgBox.setWindowTitle("请注意！");
        msgBox.setText(tr("文件尚未保存！"));
        msgBox.setInformativeText(tr("是否保存文件？"));
        //msgBox.setDetailedText(tr("Differences here..."));
        msgBox.setStandardButtons(QMessageBox::Save
                                  | QMessageBox::Discard
                                  | QMessageBox::Cancel);
        msgBox.setButtonText (QMessageBox::Save,QString("确 定"));
        msgBox.setButtonText (QMessageBox::Discard,QString("舍 弃"));
        msgBox.setButtonText (QMessageBox::Cancel,QString("取 消"));

        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            qDebug() << "保存";
            saveFile();
            return;
        case QMessageBox::Discard:
            qDebug() << "丢弃";
            tableInitialize();
            break;
        case QMessageBox::Cancel:
            qDebug() << "取消";
            return;
        }
    }

}

void MainWindow::openFile(){

    qDebug()<<"openFile";
    if(table->rowCount()>0){
        QMessageBox msgBox;
        msgBox.setWindowTitle("请注意！");
        msgBox.setText(tr("文件尚未保存！"));
        msgBox.setInformativeText(tr("是否保存文件？"));
        //msgBox.setDetailedText(tr("Differences here..."));
        msgBox.setStandardButtons(QMessageBox::Save
                                  | QMessageBox::Discard
                                  | QMessageBox::Cancel);
        msgBox.setButtonText (QMessageBox::Save,QString("确 定"));
        msgBox.setButtonText (QMessageBox::Discard,QString("舍 弃"));
        msgBox.setButtonText (QMessageBox::Cancel,QString("取 消"));

        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            qDebug() << "保存";
            saveFile();
            return;
        case QMessageBox::Discard:
            qDebug() << "丢弃";
            break;
        case QMessageBox::Cancel:
            qDebug() << "取消";
            return;
        }
    }
    QString path = QFileDialog::getOpenFileName(this,
                                                tr("Open File"),
                                                ".",
                                                tr("Text Files(*.csv)"));
    if(!path.isEmpty()) {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Read File"),
                                 tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QTextStream in(&file);
        //QtextEdit->setText(in.readAll());
         tableInitialize();
        while(!in.atEnd()){
            QStringList str = in.readLine().split(",");
            table->setRowCount(table->rowCount()+1);

            table->setItem(table->rowCount()-1,0,new QTableWidgetItem(str[0]));
            table->setItem(table->rowCount()-1,1,new QTableWidgetItem(str[1]));
            table->setItem(table->rowCount()-1,2,new QTableWidgetItem(str[2]));
            table->setItem(table->rowCount()-1,3,new QTableWidgetItem(str[3]));
            table->setItem(table->rowCount()-1,4,new QTableWidgetItem(str[4]));
            //table->setItem(table->rowCount()-1,0,new QTableWidgetItem(str[5]));
        }
        file.close();
    } /*else {
        QMessageBox::warning(this, tr("Path"),
                             tr("You did not select any file."));
    }*/
}
void MainWindow::saveFile(){
    qDebug()<<"saveFile";
    QString path = QFileDialog::getSaveFileName(this,
                                                    tr("Open File"),
                                                    ".",
                                                    tr("Text Files(*.csv)"));
        if(!path.isEmpty()) {
            QFile file(path);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QMessageBox::warning(this, tr("Write File"),
                                           tr("Cannot open file:\n%1").arg(path));
                return;
            }
            QTextStream out(&file);
            out.setCodec("uft-8");
            for(int i = 0; i < table->rowCount();i++){
                for(int j = 0; j < table->columnCount();j++){
                    //out << i << j;
                    //out << table->item(i,j)->text().toStdString().data();
                    //
                    if(table->item(i,j)!=NULL){
                        out << table->item(i,j)->text();//.toStdString().c_str();
                        qDebug()<<table->item(i,j)->text();//.toStdString().c_str();
                    }
                    else
                        out << itemEmpty;
                    if(j < table->columnCount() - 1)
                        out << ',';


                }
                out << endl;
            }
            //out << textEdit->toPlainText();
            file.close();
        } else {
            QMessageBox::warning(this, tr("请注意！"),
                                 tr("文件未保存！"));
        }
        qDebug()<<"over!";
}
void MainWindow::addModify(){
    qDebug()<<"addModify";
    table->setRowCount(table->rowCount()+1);
    for(int i = 0; i < table->columnCount();i++)
        table->setItem(table->rowCount()-1,i,new QTableWidgetItem(""));
    /*
    QComboBox*tmp = new QComboBox();
    tmp->setEditable(false);
    //connect(tmp,SIGNAL(currentIndexChanged(QString)),this,SLOT(print_s()));
    table->setItemDelegateForColumn(1,new Delegate(this));
   // table->setIte
    //table->item(table->rowCount()-1,1)->setFlags(Qt::NoItemFlags);
    QComboBoxList->push_back(tmp);
*/
}
void MainWindow::deleteModify(){
    qDebug()<<"deleteModify";
    if (table->currentRow() != -1)
        table->removeRow(table->currentRow());


}
void MainWindow::sortView(int columnIndex){
    qDebug()<<"sortView"<<columnIndex;
    quickSort(0, table->rowCount() - 1,columnIndex);
    c[columnIndex]=!c[columnIndex];
}
void MainWindow::searchView(){
    qDebug()<<"searchView";
    searchDialog = new dialog;
    searchDialog->show();

}
void MainWindow::tableModify(int row,int column){
    qDebug()<<"modify";
    qDebug()<<row;
    qDebug()<<column;
}
void MainWindow::gradeStatistic(){
    qDebug()<<"grade";
}

void MainWindow::majorStatistic(){
    qDebug()<<"major";
}

void MainWindow::gpaStatistic(){
    qDebug()<<"gpa";
}

MainWindow::~MainWindow()
{
    delete ui;
    delete openAction;
    delete saveAction;
    delete newAction;
    delete openAction;
    delete saveAction;
    delete addAction;
    delete deleteAction;
    //delete sortAction;
    delete searchAction;
    delete gradeAction;
    delete majorAction;
    delete gpaAction;
    delete stuDB;


    delete widget;
    delete table;
}
void MainWindow::Swap(int p1,int p2, int column) {
    for(int i = 0; i < table->columnCount();i++){
        QString tmp = table->item(p1,i)->text();
        table->item(p1,i)->setText(table->item(p2,i)->text());
        table->item(p2, i)->setText(tmp);
    }
}

int MainWindow::partition(int p, int q, int column){
    string pivot = table->item(q, column)->text().toStdString();
    int i = p - 1;
    for(int j = p; j <= q - 1;j++) {
        if(c[column]&&(table->item(j,column)->text().toStdString()<=pivot)) {
            i++;
            Swap(j,i,column);
        }
        else if((!c[column])&&(table->item(j,column)->text().toStdString()>=pivot)){
            i++;
            Swap(j,i,column);
        }
    }
    Swap(q,i+1,column);
    return i+1;
}

void MainWindow::quickSort(int p, int q,int column){
    qDebug()<<c[column]<<column;
    if(p < q){
        int r = partition(p,q, column);
        quickSort(p, r - 1, column);
        quickSort(r + 1, q, column);
    }
}
void MainWindow::contextMenuEvent(QContextMenuEvent *event){
    qDebug()<<event->pos();
    qDebug()<<table->pos();
    qDebug()<<(table->pos().x())<<' '<<table->pos().y()+ table->horizontalHeader()->height()*2;
    //qDebug()<<QCursor::pos().x()<<' '<<QCursor::pos().y();
    if((event->pos().x() > table->pos().x())&&
            (event->pos().y()>(table->pos().y()+ table->horizontalHeader()->height()*2))
            &&(event->pos().x()<(table->pos().x()+table->horizontalHeader()->width()))
            &&(event->pos().y()<(table->pos().y()+ table->horizontalHeader()->height()*2+table->rowHeight(0)*table->rowCount()))){
        QMenu *menu = new QMenu(this);
        QAction *insertBefore = new QAction(tr("&插入上一行"));
        menu->addAction(insertBefore);
        connect(insertBefore,SIGNAL(triggered()),this,SLOT(insertBefore()));

        QAction *insertAfter = new QAction(tr("&插入下一行"));
        menu->addAction(insertAfter);
        connect(insertAfter,SIGNAL(triggered()),this,SLOT(insertAfter()));

        QAction *deleteLine = new QAction(tr("&删除该行"));
        menu->addAction(deleteLine);
        connect(deleteLine,SIGNAL(triggered()),this,SLOT(deleteLine()));

        menu->exec(QCursor::pos());
        menu->show();
    }
}
void MainWindow::insertBefore(){
    qDebug()<<"insertB";
}

void MainWindow::insertAfter(){
    qDebug()<<"insertA";
}

void MainWindow::deleteLine(){
    qDebug()<<"deleteL";
    qDebug()<<table->currentRow();
}

void MainWindow::print_s(){
}


void MainWindow::searchQlineEditChanged(QString qstr){
     qDebug()<<qstr;
      qDebug()<<"searchQlineEdit";
}

void MainWindow::searchToolBarTriggered(){
    qDebug()<<"searchToolBar";
}


void MainWindow::lastToolBarTriggered(){
     qDebug()<<"lastToolBar";
}

void MainWindow::nextToolBarTriggered(){
     qDebug()<<"nextToolBar";
}
