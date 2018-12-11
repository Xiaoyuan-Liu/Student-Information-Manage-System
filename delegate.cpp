#include "Delegate.h"
#include <QComboBox>

Delegate::Delegate(QObject *parent)
    : QItemDelegate(parent)
{

}

Delegate::~Delegate()
{

}
void Delegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
    const QModelIndex &index) const
{
    QItemDelegate::paint(painter, option, index);
}

QSize Delegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QItemDelegate::sizeHint(option, index);
}

QWidget *Delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                                   const QModelIndex &index) const
{
    if (index.isValid() && (index.column() == SEXCOMBOXCOL||index.column()==ORIENTITIONCOMBOXCOL))
    {
        QComboBox *editor = new QComboBox(parent);
        editor->setEditable(true);
        editor->installEventFilter(const_cast<Delegate *>(this));
        return editor;
    }
    else
    {
        return QItemDelegate::createEditor(parent, option, index);
    }
}

void Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if (index.isValid()){
        if(index.column()==SEXCOMBOXCOL)
        {
            QString value = index.model()->data(index, Qt::DisplayRole).toString();
            QComboBox *combox = static_cast<QComboBox *>(editor);
            combox->addItem("(请选择)");
            combox->addItem("男");
            combox->addItem("女");
            //combox->addItem("+3");
            //combox->addItem("+4");
            combox->setCurrentText(value);
        }
        else if(index.column()==ORIENTITIONCOMBOXCOL){
            QString value = index.model()->data(index, Qt::DisplayRole).toString();
            QComboBox *combox = static_cast<QComboBox *>(editor);
            combox->addItem("(请选择)");
            combox->addItem("计算机应用");
            combox->addItem("软件工程");
            combox->addItem("计算机科学");
            combox->addItem("信息安全");
            combox->addItem("计算机系统");
            combox->setCurrentText(value);
        }
    }
    else
    {
        QItemDelegate::setEditorData(editor, index);
    }
}

void Delegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                             const QModelIndex &index) const
{
    if (index.isValid() && (index.column() == SEXCOMBOXCOL || index.column()==ORIENTITIONCOMBOXCOL))
    {
        QComboBox *combox = static_cast<QComboBox *>(editor);
        model->setData(index, combox->currentText());
    }
    else
    {
        QItemDelegate::setModelData(editor, model, index);
    }
}
