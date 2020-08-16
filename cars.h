#ifndef CARS_H
#define CARS_H
#include <QString>
#include <QFile>
#include <QDataStream>
#include <QRect>
#include <QList>

class Cars
{
    QString Marka;
    QString Model;
    QString Vin;
    int God;
    int Probeg;
    QString Fio;
public:

    void Set_Model (QString Ml)
    {
        Model=Ml;
    }

    void Set_Marka (QString Mk)
    {
        Marka=Mk;
    }

    void Set_Vin (QString Vn)
    {
        Vin=Vn;
    }

    void Set_God (int Gd)
    {
        God=Gd;
    }

    void Set_Probeg (int Prbg)
    {
        Probeg=Prbg;
    }

    void Set_Fio (QString Famil)
    {
        Fio=Famil;
    }

    QString Show_Marka() const
    {
        return Marka;
    }

    QString Show_Model() const
    {
        return Model;
    }

    QString Show_Vin() const
    {
        return Vin;
    }

    int Show_God() const
    {
        return God;
    }

    int Show_Probeg() const
    {
        return Probeg;
    }

    QString Show_Fio() const
    {
        return Fio;
    }

    friend QDataStream& operator>>( QDataStream& d, Cars& car_stream );
    friend QDataStream& operator<<( QDataStream& d, Cars& car_stream );

    void Set_Car(QString Mk,QString Ml,QString Vn,int Gd,int Prg,QString Famil)
    {
        Marka=Mk;
        Model=Ml;
        Vin=Vn;
        God=Gd;
        Probeg=Prg;
        Fio=Famil;
    }

    Cars();
};

#endif // CARS_H
