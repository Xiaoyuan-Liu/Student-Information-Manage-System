#include"datedelegate.h"
DateDelegate::DateDelegate(QObject *parent)
    : QItemDelegate(parent)
{

}
DateDelegate::~DateDelegate(){

}

QWidget *DateDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const

{

    QDateTimeEdit *editer = new QDateTimeEdit(parent);

    editer->setDisplayFormat("yyyy-MM-dd");//设置显示格式

    editer->setCalendarPopup(true);//设置日历控件为悬空显示

    editer->installEventFilter(const_cast<DateDelegate*>(this));//安装时间过滤器，使得代理能够获取定制控件的值

    return editer;

}

void DateDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const

{

    QString dateStr = index.model()->data(index).toString();//通过index获取model中相应项ITem的值

    QDate date = QDate::fromString(dateStr,Qt::ISODate);

    QDateTimeEdit *edit = static_cast<QDateTimeEdit *>(editor);//转换类型获取定制的控件

    edit->setDate(date);//将Item项中的值展示到定制控件中

}

void DateDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const

{

    QDateTimeEdit *edit = static_cast<QDateTimeEdit *>(editor);

    QDate date = edit->date();

    model->setData(index,QVariant(date.toString(Qt::ISODate)));//将定制控件中的值展示到表格中

}

//调整定制控件的展示，确保可以展示到窗体View中

void DateDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const

{

    editor->setGeometry(option.rect);

}
