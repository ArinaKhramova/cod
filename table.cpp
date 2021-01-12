#include "table.h"

/*!
* \brief Table::Table - Конструктор разрешает данному виджету принимать данные
* \param parent указывает родительский объект
*/
Table::Table(QWidget *parent)
    : QTableView (parent)
{
    this->acceptDrops();
}

/*!
* \brief Table::setSp - метод для получения данных из главного окна
* \param temp принимает на вход указатель на двусвязный список
*/
void Table::setSp(QLinkedList<videocard> *temp)
{
    sp = temp;
}

/*!
 * \brief Table::mousePressEvent - Переопределееное событие нажатия на кнопку мыши
* При нажатии любой из клавиш запоминает позицию и записывает ее в 2 разных класса
* Требуется для выполнения некоторых проверок и минимизации шанса вылета программы
 * \param event - событие нажатия
 */
void Table::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton || event->button() == Qt::RightButton)
    {
        this->selectRow(this->indexAt(event->pos()).row());
        nowsel = new QItemSelection(this->currentIndex(),this->currentIndex());
    }
      index = this->indexAt(event->pos());
}


/*!
 * \brief Table::mouseMoveEvent - переопределенное событие движения мыши
 * После выполнения проверок записывает содержимое выделенной строки в mimeData Drag EventА
 * \param event - событие нажатия
 */
void Table::mouseMoveEvent(QMouseEvent *event)
{
    QLinkedList<videocard>::iterator iter;
    if(nowsel == nullptr)
        return;
    if(!sp->isEmpty())
        if(nowsel->indexes().first().row()>=0 && (event->buttons() & Qt::LeftButton) && index.isValid())
        {

            QDrag *drag = new QDrag(this);
            QMimeData *mimeData = new QMimeData();
            QString str;

            for(iter=sp->begin();iter!=sp->end();iter++)
                if(iter->getId()==this->currentIndex().row())
                {
                    str =   iter->getBrand() + ";"+//записываем его данные в str
                            iter->getInterface() + ";"+
                            iter->getGraphProcessor() + ";"+
                            iter->getVideoExit() + ";"+
                            iter->getTypeMemory() + ";"+
                            QString::number(iter->getlengthVC()) + ";"+
                            QString::number(iter->getPrice())+";";

                }
            mimeData->setText(str);
            mimeData->setParent(this);
            drag->setMimeData(mimeData);
            drag->exec();
            return;
        }
}

