#include "add_window.h"
#include "ui_add_window.h"

/*!
 * \brief AddWindow::AddWindow - Конструктор окна добавления, инициализирует параметры.
 * \param parent указывает, какой объект будет родительским для данного объекта
 */
AddWindow::AddWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddWindow)
{
    ui->setupUi(this);
}

/*!
 * \brief AddWindow::~AddWindow - Деструктор окна добавления, удаляет пользовательский интерефейс
 */
AddWindow::~AddWindow()
{
    delete ui;
}

/*!
 * \brief AddWindow::on_AcceptButton_clicked - слот, вызываемыйй при нажатии на принятие добавления записи
 * Берет данные из строчек, формирует объект, отправляет его в главное окно.
 */
void AddWindow::on_AcceptButton_clicked()
{
    videocard *temp = new videocard(ui->BrandLine->text(),
                                ui->InterfaceLine->text(),
                                ui->GraphicsProcessorLine->text(),
                                ui->VideoExitLine->text(),
                                ui->TypeMemoryLine->text(),
                                ui->LenghBox->value(),
                                ui->PriceBox->value()
                                );
    emit sendDataFromAdd(*temp);
    this->close();
}

