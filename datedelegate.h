#ifndef DATEDELEGATE_H
#define DATEDELEGATE_H
#include <QStyledItemDelegate>
#include <QItemDelegate>
#include <QModelIndex>
#include <QPainter>
#include <QWidget>
#include<QDateTimeEdit>
class DateDelegate : public QItemDelegate
{
    Q_OBJECT

public:
    DateDelegate(QObject *parent = nullptr);
   ~DateDelegate();
    QWidget *createEditor(QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const;//返回改变Model数据的widget，该widget是经过定制行为的Widget



    void setEditorData(QWidget * editor, const QModelIndex & index) const;//将可操作的数据提供给widget



    void setModelData(QWidget * editor, QAbstractItemModel * model, const QModelIndex & index) const;  //将widget的数据展示到Item中



    void updateEditorGeometry(QWidget * editor, const QStyleOptionViewItem & option, const QModelIndex & index) const;//确保widget能够正确显示到view中
private:

};
#endif // DATEDELEGATE_H
