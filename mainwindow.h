#pragma once
#include <QMainWindow>

#include <QLinkedList>
#include <fstream>
#include <sstream>
#include <QFile>
#include<QFileDialog>
#include <QList>
#include <QTranslator>
#include <QDebug>
#include <QTextStream>
#include <QSettings>
#include "videocard.h"
#include "edit_window.h"
#include "table.h"
#include "add_window.h"
namespace Ui
{
class MainWindow;
}

/*!
 *\brief The MainWindow class - Класс основного окна
 * содержит основные объекты и методы для работы программы а так же хранит данные программы во время ее работы
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT
signals:
    /*!
     * \brief sendDataToEdit - сигнал передачи данных в форму редактирования
     * \param obj - объект, передающийся в форму редактирования
     */
    void sendDataToEdit(videocard obj);


public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void TableUpdate(QString *find=nullptr);


private slots:
    void on_actionOpen_triggered();

    void slotWindow_Add();

    void on_actionDelete_triggered();

    void on_actionAbout_triggered();

    void on_actionSave_triggered();

    void slotGo_to_Redact();

    void slotKontekstMenu(QPoint pos);

    void on_actionRussian_triggered();

    void on_actionEnglish_triggered();

    void on_actionNewWindow_triggered();

    void on_SearchButton_clicked();

    void setSettings();

    void getSettings();

    void on_ResetButton_clicked();

    void on_actionAbout_Qt_triggered();

private:
    ///Указатель на элементы пользовательского интерфейса(всего, что находится в конструкторе окна)
    Ui::MainWindow *ui;
    ///Двусвязный список, хранящий данные
    QLinkedList<videocard> *sp;
    ///Окно редактирования
    EditWindow *edit;
    ///Окно добавления
    AddWindow *add;
    ///Переводчик
    QTranslator translator;
    ///Контекстное меню
    QMenu *menu;

public slots:
    void slotGet_from_Redact(videocard temp);
    void slotGet_from_Add(videocard temp);
protected:

    virtual void dragEnterEvent(QDragEnterEvent *e);
    virtual void dragLeaveEvent(QDragLeaveEvent *e);
    virtual void dropEvent(QDropEvent *e);
};
