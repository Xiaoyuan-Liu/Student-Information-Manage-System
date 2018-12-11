#ifndef DELEGATE_H
#define DELEGATE_H
#include <QStyledItemDelegate>
#include <QItemDelegate>
#include <QModelIndex>
#include <QPainter>
#include <QWidget>

#define SEXCOMBOXCOL 1
#define ORIENTITIONCOMBOXCOL 4
class Delegate : public QItemDelegate
{
    Q_OBJECT

public:
    Delegate(QObject *parent = nullptr);
   ~Delegate();

   void paint(QPainter *painter, const QStyleOptionViewItem &option,
                    const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;

     QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const;
     void setEditorData(QWidget *editor, const QModelIndex &index) const;
     void setModelData(QWidget *editor, QAbstractItemModel *model,
                                     const QModelIndex &index) const;

private:

};


#endif // DELEGATE_H
