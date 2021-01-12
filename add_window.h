#ifndef AddWindow_H
#define AddWindow_H

#include <QDialog>
#include <videocard.h>
namespace Ui {
class AddWindow;
}
/*!
 * \brief The AddWindow class - Класс окна добавления. Содержит сигнал отправки данных в главную форму.
 */
class AddWindow : public QDialog
{
    Q_OBJECT
signals:
    /*!
    * \brief sendDataFromAdd - Сигнал, отсылающий добавленный объект обратно в основное окно
    * \param obj объект для передачи в основную форму
    */
        void sendDataFromAdd(videocard obj);
public:
    explicit AddWindow(QWidget *parent = nullptr);
    ~AddWindow();

private slots:
    void on_AcceptButton_clicked();

private:
    /*!
     * \brief ui - указатель на пользовательский интерфейс
     */
    Ui::AddWindow *ui;
};

#endif // AddWindow_H

