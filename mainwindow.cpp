#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTextEdit"
using namespace std;
/*!
 * \brief MainWindow::MainWindow - конструктор главного окна
 * инициализирует основные члены класса и задает начальные параметры объектам пользовательского интерфейса
 * \param parent - объект для связи с окном
 */
MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    getSettings();

    ui->tableView->viewport()->setAcceptDrops(true);
    ui->tableView->setDragDropMode(QAbstractItemView::NoDragDrop);
    ui->tableView->setSelectionMode(QTableWidget::SingleSelection);
    ui->tableView->setSelectionBehavior(QTableWidget::SelectRows);
    ui->tableView->setDropIndicatorShown(true);
    this->setAcceptDrops(1);


    sp = new QLinkedList<videocard>;
    ui->tableView->setSp(sp);


    connect(ui->actionEdit,SIGNAL(triggered()),this,SLOT(slotGo_to_Redact()));
    connect(ui->actionAdd,SIGNAL(triggered()),this,SLOT(slotWindow_Add()));


    menu = new QMenu(this);


    QAction * editDevice = new QAction(tr("Edit"), this);
    QAction * deleteDevice = new QAction(tr("Delete"), this);


    connect(editDevice, SIGNAL(triggered()), this, SLOT(slotGo_to_Redact()));
    connect(deleteDevice, SIGNAL(triggered()), this, SLOT(on_actionDelete_triggered()));


   menu->addAction(editDevice);
   menu->addAction(deleteDevice);



    on_actionRussian_triggered();
    TableUpdate();
}

/*!
 * \brief MainWindow::~MainWindow - деструктор главного окна
 * сохраняет настройки в реестр, затем удаляет интерфейс
 */
MainWindow::~MainWindow()
{
    setSettings();
    delete ui;
}
/*!
 * \brief MainWindow::TableUpdate - Метод для перестройки наблицы, содержит настройки интерфейса
 * \param find - переменная для функции поиска
 */
void MainWindow::TableUpdate(QString *find)
{
    QLinkedList<videocard>::iterator iter;
    QStringList Header;
    int count=0;

    Header.push_back(tr("ID"));
    Header.push_back(tr("BRAND"));
    Header.push_back(tr("INTERFACE"));
    Header.push_back(tr("GRAPHICS\n PROCESSOR"));
    Header.push_back(tr("VIDEO EXIT"));
    Header.push_back(tr("TYPE OF MEMORY"));
    Header.push_back(tr("LENGH VC"));
    Header.push_back(tr("PRICE"));


    ui->tableView->setSortingEnabled(true);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->tableView,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(slotKontekstMenu(QPoint)));
    menu->actions().at(0)->setText(tr("Edit"));
    menu->actions().at(1)->setText(tr("Delete"));



    QStandardItemModel *model = new QStandardItemModel();
    QStandardItem *item;
    model->setHorizontalHeaderLabels(Header);
    QBrush brush(QColor(255, 83, 73));


    for (iter=sp->begin();iter!=sp->end();iter++)
    {

        iter->setId(count);
        item = new QStandardItem(QString::number(iter->getId()));
        if(find!=nullptr)
        {
            if(item->text()==*find)
                item->setBackground(brush);
        }
        model->setItem(count,0,item);

        item = new QStandardItem(iter->getBrand());
        if(find!=nullptr)
        {
            if(item->text()==*find)
                item->setBackground(brush);
        }
        model->setItem(count,1,item);

        item = new QStandardItem(iter->getInterface());
        if(find!=nullptr)
        {
            if(item->text()==*find)
                item->setBackground(brush);
        }
        model->setItem(count,2,item);

        item = new QStandardItem(iter->getGraphProcessor());
        if(find!=nullptr)
        {
            if(item->text()==*find)
                item->setBackground(brush);
        }
        model->setItem(count,3,item);

        item = new QStandardItem(iter->getVideoExit());
        if(find!=nullptr)
        {
            if(item->text()==*find)
                item->setBackground(brush);
        }
        model->setItem(count,4,item);

        item = new QStandardItem(iter->getTypeMemory());
        if(find!=nullptr)
        {
            if(item->text()==*find)
                item->setBackground(brush);
        }
        model->setItem(count,5,item);

        item = new QStandardItem(QString::number(iter->getlengthVC()));
        if(find!=nullptr)
        {
            if(item->text()==*find)
                item->setBackground(brush);
        }
        model->setItem(count,6,item);

        item = new QStandardItem(QString::number(iter->getPrice()));
        if(find!=nullptr)
        {
            if(item->text()==*find)
                item->setBackground(brush);
        }
        model->setItem(count,7,item);

        count++;
    }

    ui->tableView->setModel(model);
    ui->tableView->resizeRowsToContents();
    ui->tableView->hideColumn(0);
    ui->actionDelete->setEnabled(!sp->isEmpty());
    ui->actionEdit->setEnabled(!sp->isEmpty());
    ui->ResetButton->setEnabled(!sp->isEmpty());
    ui->lineEdit->setEnabled(!sp->isEmpty());
    ui->SearchButton->setEnabled(!sp->isEmpty());
    ui->actionSave->setEnabled(!sp->isEmpty());



}


/*!
 * \brief MainWindow::on_actionOpen_triggered - слот открытия.
 * Вызывает QFileDialog, получает имя файла, открывает его на чтение
 * читает, анализирует данные, записывает их в двухсвязный список
 * далее перестраивает таблицу
 */
void MainWindow::on_actionOpen_triggered()
{
    QString filename;
    QStringList slist;
    QString sline;

    filename = QFileDialog::getOpenFileName(this,tr("Open"),":/file/videocard.db",tr("Image Files (*.db)"));
    if(filename.isEmpty())
        return;

    QFile file(filename);
    file.open( QIODevice::ReadOnly | QIODevice::Text );


    if(file.readLine().contains("key"))
        while(!file.atEnd())
        {
            sline=file.readLine();
            slist=sline.split(';');

            videocard *temp = new videocard(
                                        slist.at(0),
                                        slist.at(1),
                                        slist.at(2),
                                        slist.at(3),
                                        slist.at(4),
                                        slist.at(5).toInt(),
                                        slist.at(6).toInt()
                                        );
            this->sp->push_back(*temp);
            free(temp);
        }
    else
        QMessageBox::warning(this,tr("Warning"),"Wrong file");
    TableUpdate();
}
/*!
* \brief MainWindow::on_actionSave_triggered - слот сохранения
* Сохраняет данные в файл
* Вызывает QFileDialog, получает имя файла, открывает его на запись
* Записывает данные в строки через ";" и пишет строки в файл
*/
void MainWindow::on_actionSave_triggered()
{
    QLinkedList<videocard>::iterator iter;
    QString filename;
    filename = QFileDialog::getOpenFileName(this);
    QFile file(filename);
    QTextStream writeStream(&file);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    int i=0;
    for(iter=sp->begin();iter!=sp->end();iter++,i++)
    {
        writeStream<<iter->getBrand(); writeStream<<";";
        writeStream<<iter->getInterface(); writeStream<<";";
        writeStream<<iter->getGraphProcessor(); writeStream<<";";
        writeStream<<iter->getVideoExit(); writeStream<<";";
        writeStream<<iter->getTypeMemory(); writeStream<<";";
        writeStream<<QString::number(iter->getlengthVC()); writeStream<<";";
        writeStream<<QString::number(iter->getPrice()); writeStream<<";";
        if(iter!=--sp->end())
            writeStream<<"\n";
    }

    file.close();


}
/*!
* \brief MainWindow::slotGo_to_Redact - Слот отправки данных в форму редактирования.
* Смотрит,какая из строк выделена, ищет в списке объект по его Id и отправляет его в форму редактирования, передавая ей управление.
*/
void MainWindow::slotGo_to_Redact()
{
    videocard *obj = new videocard();
    QLinkedList<videocard>::iterator iter;
    edit = new EditWindow(this);
    connect(this,SIGNAL(sendDataToEdit(videocard)),edit,SLOT(recieveDataToRedact(videocard)));
    connect(edit,SIGNAL(sendDataFromEdit(videocard)),this,SLOT(slotGet_from_Redact(videocard)));
    for(iter=sp->begin();iter!=sp->end();iter++)
        if(iter->getId()==ui->tableView->currentIndex().row())
            obj = &(*iter);
    emit sendDataToEdit(*obj);
    edit->exec();

}

/*!
* \brief MainWindow::slotGet_from_Redact - Слот получения данных из формы редактирования.
* В зависимости от значения add либо заменяет данные у существующей записи либо добавляет в список новую.
* \param temp объет, полученный из формы редактирования
*/
void MainWindow::slotGet_from_Redact(videocard temp)
{
    QLinkedList<videocard>::iterator iter;
    for(iter=sp->begin();iter!=sp->end();iter++)
        if(iter->getId()==ui->tableView->currentIndex().row())
        {
            iter->setBrand(temp.getBrand());
            iter->setInterface(temp.getInterface());
            iter->setGraphProcessor(temp.getGraphProcessor());
            iter->setVideoExit(temp.getVideoExit());
            iter->setTypeMemory(temp.getTypeMemory());
            iter->setlengthVC(temp.getlengthVC());
            iter->setPrice(temp.getPrice());
        }
    TableUpdate();
}

/*!
* \brief MainWindow::slotGet_from_Add - Слот получения данных из формы добавления
* \param temp принятый объект из формы добавления
*/
void MainWindow::slotGet_from_Add(videocard temp)
{
    sp->push_back(temp);
    TableUpdate();
}

/*!
* \brief MainWindow::slotWindow_Add - слот вызывает окно добавления
*/
void MainWindow::slotWindow_Add()
{
    add = new AddWindow(this);
    //add->setAttribute(Qt::WA_DeleteOnClose);
    connect(add,SIGNAL(sendDataFromAdd(videocard)),this,SLOT(slotGet_from_Add(videocard)));
    add->exec();
}

/*!
* \brief MainWindow::on_actionDelete_triggered - слот для удаления записи из писка
*/
void MainWindow::on_actionDelete_triggered()
{
    QLinkedList<videocard>::iterator iter;
    for(iter=sp->begin();iter!=sp->end();iter++)
        if(iter->getId()==ui->tableView->currentIndex().row())
        {
            sp->erase(iter);
        }
    TableUpdate();
}


/*!
* \brief MainWindow::on_actionRussian_triggered - слот для перевода программы на русский язык
*/
void MainWindow::on_actionRussian_triggered()
{
    translator.load(QString(":/Translations/Course_ru.qm"));
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
    ui->actionEnglish->setChecked(false);
    TableUpdate();
}

/*!
* \brief MainWindow::on_actionEnglish_triggered - слот для перевода программы на английский язык
*/
void MainWindow::on_actionEnglish_triggered()
{
    translator.load(QString(":/Translations/Course_eng.qm"));
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
    ui->actionRussian->setChecked(false);
    TableUpdate();
}


/*!
* \brief MainWindow::dragEnterEvent - Виртуальный метод разрешает или запрещает перетаскивание в зависимости от того, есть ли в мышке данные
* \param e указатель на событие
*/
void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{

    if(e->mimeData()->hasText())
        e->setAccepted(true);
    else
        e->setAccepted(false);
}

/*!
* \brief MainWindow::dragLeaveEvent - Виртуальный метод разрешает выход события drag из окна
* \param e указатель на событие
*/
void MainWindow::dragLeaveEvent(QDragLeaveEvent *e)
{
    e->setAccepted(true);
}

/*!
* \brief MainWindow::dropEvent - виртуальный метод для записи данных drop event
* Если в событии отпускания мышки есть данные забираем их оттуда и записываем в список
* \param e указатель на событие
*/
void MainWindow::dropEvent(QDropEvent *e)
{
    QStringList slist;
    QString line;
    line = e->mimeData()->text();
    slist = line.split(';');
    if(slist.isEmpty())
        return;
    videocard *temp = new videocard(
                                slist.at(0),
                                slist.at(1),
                                slist.at(2),
                                slist.at(3),
                                slist.at(4),
                                slist.at(5).toInt(),
                                slist.at(6).toInt()
                                );
    temp->setId(this->sp->size());
    this->sp->push_back(*temp);
    TableUpdate();
}




/*!
* \brief MainWindow::setSettings - медот для сохранения текущех настроек окон в реестр
*/

void MainWindow::setSettings()
{
    QSettings settings("Course","App");
    settings.beginGroup("w");
    settings.setValue("geometry", saveGeometry());
    settings.endGroup();
}

/*!
* \brief MainWindow::getSettings - метод получения настроек геометрии окна из реестра
*/
void MainWindow::getSettings()
{
    QSettings settings("Course","App");
    settings.beginGroup( "w" );
    restoreGeometry(settings.value( "geometry", saveGeometry() ).toByteArray());
    settings.endGroup();
}



/*!
* \brief MainWindow::slotKontekstMenu - слот вызова контекстного меню
* \param pos позиция в окне, у которой вызовется меню
*/
void MainWindow::slotKontekstMenu(QPoint pos)
{
    if(!sp->isEmpty())
        menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
}


/*!
* \brief MainWindow::on_actionAbout_triggered - слот вызова окна с информацией о программе
*/

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,tr("About"),tr("This is a course work program "
                                           "it was developed to work with the video carat database\n\n "
                                           "Topic:Software development in C++/Qt for accounting of PC components <<Videocard>> \n"
                                           "The programm created by Khramova Arina, Institute: EUIS II-2"
                                          ));
}


/*!
* \brief MainWindow::on_SearchButton_clicked - слот для вызова функции поиска
* Функция поиска передает в TableUpdate строку поиска, а она уже светит найденные данные
*/
void MainWindow::on_SearchButton_clicked()
{
    QString *str = new QString(ui->lineEdit->text());
    TableUpdate(str);
}


/*!
* \brief MainWindow::on_ResetButton_clicked - слот кнопки сброса
* Служит для сброса сортировки и поиска
*/
void MainWindow::on_ResetButton_clicked()
{
    ui->lineEdit->setText("");
    ui->tableView->clearSpans();
    TableUpdate();
}

/*!
* \brief MainWindow::on_actionNewWindow_triggered - слот создания нового окна
* Создает экземпляр такого же окна с флагом удаления при закрытии.
* Служит для открытия нескольких файлов.
*/
void MainWindow::on_actionNewWindow_triggered()
{
    MainWindow *mainwindow = new MainWindow(this);
    mainwindow->setAttribute(Qt::WA_DeleteOnClose);
    mainwindow->show();
}


/*!
 * \brief MainWindow::on_actionAbout_Qt_triggered - слот вызова данных о программе Qt creator
 */
void MainWindow::on_actionAbout_Qt_triggered()
{
    qApp->aboutQt();
}
