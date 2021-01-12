#include "edit_window.h"
#include "ui_edit_window.h"

/*!
 * \brief EditWindow::EditWindow - конструктор окна редактирования, инициализирует пользовательский интерфей
 * \param parent указывает, какой объект будет родительским для данного объекта
 */
EditWindow::EditWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditWindow)
{
    ui->setupUi(this);
   // ui->retranslateUi(this);

}

/*!
 * \brief EditWindow::~EditWindow - деструктор окна редактирования, удаляет пользовательский интерфейс
 */
EditWindow::~EditWindow()
{
    delete ui;
}
/*!
 * \brief EditWindow::recieveDataToRedact - Слот получения данных из основного окна
 * Получает данные и записывает параметры объекта в соответствующие поля редактирования
 * \param temp - объект, полученный из главного окна
 */
void EditWindow::recieveDataToRedact(videocard temp)
{

    ui->BrandLine->setText(temp.getBrand());
    ui->InterfaceLine->setText(temp.getInterface());
    ui->GraphicsProcessorLine->setText(temp.getGraphProcessor());
    ui->VideoExitLine->setText(temp.getVideoExit());
    ui->TypeMemoryLine->setText(temp.getTypeMemory());
    ui->LenghBox->setValue(temp.getlengthVC());
    ui->PriceBox->setValue(temp.getPrice());
}

/*!
 * \brief EditWindow::on_AcceptButton_clicked - слот, вызываемый при нажатии кнопки принятия данных
 * формирует объект из данных полученных из полей и отправляет его в главное окно
 */
void EditWindow::on_AcceptButton_clicked()
{
    videocard *temp = new videocard(ui->BrandLine->text(),
                                ui->InterfaceLine->text(),
                                ui->GraphicsProcessorLine->text(),
                                ui->VideoExitLine->text(),
                                ui->TypeMemoryLine->text(),
                                ui->LenghBox->value(),
                                ui->PriceBox->value()
                                );

    emit sendDataFromEdit(*temp);
    this->close();
}


