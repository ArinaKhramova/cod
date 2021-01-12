#ifndef EditWindow_H
#define EditWindow_H

#include <QDialog>
#include <QDebug>
#include "videocard.h"
namespace Ui {
class EditWindow;
}

/*!
*\brief The EditWindow class - Класс окна редактирования cодержит методы для редактирования существующих записей и добавления новых
*/
class EditWindow : public QDialog
{
    Q_OBJECT
signals:
    /*!
    *\brief sendDataFromEdit - Сигнал, отсылающий отредактированный объект обратно в основное окно
    *\param obj объект для передачи в основную форму
    */
    void sendDataFromEdit(videocard obj);
public:
    explicit EditWindow(QWidget *parent = nullptr);
    ~EditWindow();

private:
    /*!
     *\brief ui - указатель на объекты пользовательского интерфейса
     */
    Ui::EditWindow *ui;


public slots:
   void recieveDataToRedact(videocard temp);
private slots:
   void on_AcceptButton_clicked();
};

#endif // EditWindow_H

