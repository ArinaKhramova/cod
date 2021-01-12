#ifndef videocard_H
#define videocard_H
#include <QString>

/*!
 * \brief The videocard class - абстрактный класс, содержит основные характеристики видеоплат, а так же методы для работы с ними
 */
class videocard
{
private:
    ///Id Для списка
    int Id;
    ///Бренд видеоплаты
    QString Brand;
    ///Интерфейс видеоплаты
    QString Interface;
    ///Графический процессор
    QString GraphProcessor;
    ///Видео выход
    QString VideoExit;
    ///Тип памяти видеоплаты
    QString TypeMemory;
    ///Длина видеоплаты
    int lengthVC;
    ///Цена видеоплаты
    int Price;

public:

    /*!
     * \brief videocard - Конструктор по умолчанию инициаилизирует пустой объект
     */
    videocard():
        Brand(""),Interface(""),GraphProcessor(""),VideoExit(""),TypeMemory(""),lengthVC(2.4),Price(0) {}


    /*!
     * \brief videocard - Конструктор с параметрами, инициализирует параметры класса по параметрам
     * \param cBrand - Входное значение бренда
     * \param cInterface - Входное значение интерфейса
     * \param cGraphProcessor - Входное значение графического процесса
     * \param cVideoExit - Входное значение видео выхода
     * \param cTypeMemory - Входное значение типа памяти
     * \param clengthVC - Входное значение длины видеоплаты
     * \param cPrice - Входное значение цены
     */
    videocard(const QString cBrand, const QString cInterface,
            const QString cGraphProcessor,
            const QString cVideoExit,
            const QString cTypeMemory,
            const int clengthVC,
            const int cPrice):
        Brand(cBrand),
        Interface(cInterface),
        GraphProcessor(cGraphProcessor),
        VideoExit(cVideoExit),
        TypeMemory(cTypeMemory),
        lengthVC(clengthVC),
        Price(cPrice) {}

    /*!
     * \brief setBrand - установка нового значения бренда
     * \param cBrand -  новое значение бренда
     */
    void setBrand(QString cBrand)
    { Brand = cBrand; }
    /*!
     * \brief getBrand - получение значение бренда
     * \return - Значение бренда
     */
    QString getBrand() const
    { return Brand ;}

    /*!
     * \brief setInterface - установка нового значения интерфейса
     * \param cInterface - новое значение интерфейса
     */
    void setInterface(QString cInterface)
    { Interface = cInterface; }
    /*!
     * \brief getInterface - получение значения интерфейса
     * \return - значение интерфейса
     */
    QString getInterface() const
    { return  Interface; }

    /*!
     * \brief setGraphProcessor - установка нового значения графического процессора
     * \param cGraphProcessor - новое значение графического процессора
     */
    void setGraphProcessor(QString cGraphProcessor)
    { GraphProcessor = cGraphProcessor; }
    /*!
     * \brief getGraphProcessor - получение значения графического процессора
     * \return  - значение графического процессора
     */
    QString getGraphProcessor() const
    { return GraphProcessor; }

    /*!
     * \brief setVideoExit - установка нового значения видео выхода
     * \param cVideoExit - новое значение видео выхода
     */
    void setVideoExit(QString cVideoExit)
    { VideoExit = cVideoExit; }
    /*!
     * \brief getVideoExit - получение значения видео выхода
     * \return - значение видео выхода
     */
    QString getVideoExit() const
    { return VideoExit; }

    /*!
     * \brief setTypeMemory - установка нового значения типа памяти видео платы
     * \param cTypeMemory - новое значение типа памяти
     */
    void setTypeMemory(QString cTypeMemory)
    { TypeMemory = cTypeMemory; }
    /*!
     * \brief getTypeMemory - получение значения типа памяти
     * \return - значение типа памяти
     */
    QString getTypeMemory() const
    { return TypeMemory; }

    /*!
     * \brief setlengthVC - установка нового значения длины видео платы
     * \param clenghVC - новое значение длины видео платы
     */
    void setlengthVC(int clenghVC)
    { lengthVC = clenghVC; }
    /*!
     * \brief getlengthVC - получение значения длины видео платы
     * \return - значение видео платы
     */
    int getlengthVC() const
    { return lengthVC; }

    /*!
     * \brief setPrice - установка нвого значения цены
     * \param cPrice - новое значение цены
     */
    void setPrice(int cPrice)
    { Price = cPrice; }
    /*!
     * \brief getPrice - получение значения цены
     * \return - значение цены
     */
    int getPrice() const
    { return Price; }

    /*!
     * \brief setId - установка нового значения ID
     * \param value - параметр адреса
     */
    void setId(int value)
    { Id = value; }
    /*!
     * \brief getId - получение значения ID
     * \return - значение ID
     */
    int getId() const
    { return  Id; }

};

#endif // videocard_H
