#ifndef TABLE1_H
#define TABLE1_H

#include <QObject>
#include <QtWidgets>
#include "videocard.h"

/*!
 * \brief The Table class - Класс таблицы наследован от QTableView и имеет переопределенные события нажатия и движения мышки
/// С помощью них реализована пользовательская технология DragNDrop для перетаскивания информации в друие программы,
/// а так же движения данных внутри окон данной программы
 */
class Table : public QTableView
{
    Q_OBJECT
public:
    Table(QWidget * parent = nullptr);
    void setSp(QLinkedList<videocard> *temp);

private slots:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
private:
    ///Указатель на список данных из главного окна, требуется для более удобного доступа к данным
    QLinkedList<videocard> *sp;
    ///Указывает на текущий выделенный элемент
    QItemSelection *nowsel=nullptr;
    ///Показывает, какой индекс был выделен
    QModelIndex index;
};

#endif // TABLE1_H
