#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QFile>
#include <QDataStream>
#include <QRect>
#include <QMessageBox>
#include <QValidator>
#include <QList>
#include <QInputDialog>
#include "cars.h"

static Cars Auto;

static QList <Cars> Cars_list;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setContextMenuPolicy(Qt::NoContextMenu);
    ui->tableWidget->setEditTriggers(QTableWidget::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->Marka_lineEdit->setValidator(new QRegExpValidator (QRegExp("\\w{17}")));
    ui->Model_lineEdit->setValidator(new QRegExpValidator (QRegExp("\\w{17}")));
    ui->Vin_lineEdit->setValidator(new QRegExpValidator (QRegExp("\\w{17}")));
    ui->God_lineEdit->setValidator(new QRegExpValidator (QRegExp("[0-9]{3}\\S")));
    ui->Probeg_lineEdit->setValidator(new QRegExpValidator (QRegExp("[0-9]{6}\\S")));
    //ui->Fio_lineEdit->setValidator(new QRegExpValidator (QRegExp("[A-Z][a-z A-Z.]{30}")));//(QRegExp("\\D{30}")));
    ui->Fio_lineEdit->setValidator(new QRegExpValidator (QRegExp("[А-Я][а-я А-Я.]{30}")));

    connect(ui->tableWidget, SIGNAL(customContextMenuRequested(const QPoint&)),this, SLOT(ShowContextMenu(const QPoint&)));

    ui->Marka_lineEdit->setFocus();

    ui->tableWidget->resizeColumnsToContents();
}

MainWindow::~MainWindow()
{
    delete ui;
}


QDataStream& operator<<( QDataStream& instream, const Cars& car_stream )
{
    instream<<car_stream.Show_Marka()<<car_stream.Show_Model()<<car_stream.Show_Vin()<<car_stream.Show_God()<<car_stream.Show_Probeg()<<car_stream.Show_Fio();
    return instream;
}

QDataStream& operator>>( QDataStream& instream,  Cars& car_stream )
{
    instream >> car_stream.Marka>>car_stream.Model>>car_stream.Vin>>car_stream.God>>car_stream.Probeg>>car_stream.Fio;
    return instream;
}

void MainWindow::on_pushButton_clicked()
{
    QString Marka=ui->Marka_lineEdit->text();
    QString Model=ui->Model_lineEdit->text();
    QString Vin=ui->Vin_lineEdit->text();

    int God=ui->God_lineEdit->text().toInt();

    if(God==0)
    {
        God=-1;
    }

    if(God>2019)
    {
        God=2019;
    }

    int Probeg=ui->Probeg_lineEdit->text().toInt();

    if (Probeg==0)
    {
        Probeg=-1;
    }

    QString Fio=ui->Fio_lineEdit->text();

    if(Fio==nullptr)
    {
        Fio="(пуcто)";
    }

    if (ui->Marka_lineEdit->text().isEmpty()==true || ui->Model_lineEdit->text().isEmpty()==true || ui->Vin_lineEdit->text().isEmpty()==true)
    {
         QMessageBox::warning(this,tr("Внимание"),tr("Поля марка, модель, Vin, являются обязательными"),QMessageBox::Ok);
    }
    else
    {
    Auto.Set_Car(Marka,Model,Vin,God,Probeg,Fio);

    check_input();

    Cars_list<<Auto;

    ui->tableWidget->setRowCount(1);

    Add_to_Table();

    ui->Marka_lineEdit->clear();
    ui->Model_lineEdit->clear();
    ui->Vin_lineEdit->clear();
    ui->God_lineEdit->clear();
    ui->Probeg_lineEdit->clear();
    ui->Fio_lineEdit->clear();

    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    }

}

void MainWindow::ShowContextMenu(const QPoint& pos)
{
QPoint globalPos = ui->tableWidget->mapToGlobal(pos);
QMenu myMenu;
myMenu.addAction("Редактировать", this, SLOT(on_action_1()));
myMenu.addAction("Удалить", this, SLOT(on_action_2()));
myMenu.exec(globalPos);
}

void MainWindow::on_action_1()
{
    if(Cars_list.size()==0)
    {

    }
    else
       {
    int index_row=ui->tableWidget->currentRow();
    int index_column=ui->tableWidget->currentColumn();

     ui->tableWidget->editItem(ui->tableWidget->currentItem());

    if (index_column==0)
    {
        QString old=Cars_list[index_row].Show_Marka();
        bool stat;
        QString str = QInputDialog::getText(this,
                                     QString::fromUtf8("Редактирование"),
                                     QString::fromUtf8("Введите текст:"),
                                     QLineEdit::Normal,Cars_list[index_row].Show_Marka(),&stat);
        if (str==nullptr)
        {
            str="(пусто)";
        }
        Cars_list[index_row].Set_Marka(str);
        if (!stat)
        {
            Cars_list[index_row].Set_Marka(old);
        }

    }

    if (index_column==1)
    {
        QString old=Cars_list[index_row].Show_Model();
        bool stat;
        QString str = QInputDialog::getText(this,
                                     QString::fromUtf8("Редактирование"),
                                     QString::fromUtf8("Введите текст:"),
                                     QLineEdit::Normal,Cars_list[index_row].Show_Model(),&stat);
        if (str==nullptr)
        {
            str="(пусто)";
        }
        Cars_list[index_row].Set_Model(str);
        if (!stat)
        {
            Cars_list[index_row].Set_Model(old);
        }
    }

    if (index_column==2)
    {
        QString old=Cars_list[index_row].Show_Vin();
        bool stat;
        QString str = QInputDialog::getText(this,
                                     QString::fromUtf8("Редактирование"),
                                     QString::fromUtf8("Введите текст:"),
                                     QLineEdit::Normal,Cars_list[index_row].Show_Vin(),&stat);
        if (str==nullptr)
        {
            str="(пусто)";
        }
        Cars_list[index_row].Set_Vin(str);
        if (!stat)
        {
            Cars_list[index_row].Set_Fio(old);
        }
    }

    if (index_column==3)
    {
        int old=Cars_list[index_row].Show_Probeg();
        bool stat;
        int num = QInputDialog::getInt(this,
                                     QString::fromUtf8("Редактирование"),
                                     QString::fromUtf8("Введите текст:"),
                                     Cars_list[index_row].Show_Probeg(),1,2000000,1,&stat);
        Cars_list[index_row].Set_Probeg(num);
        if (!stat)
        {
            Cars_list[index_row].Set_Probeg(old);
        }
    }
    if (index_column==4)
    {
        int old=Cars_list[index_row].Show_God();
        bool stat;
        int num = QInputDialog::getInt(this,
                                     QString::fromUtf8("Редактирование"),
                                     QString::fromUtf8("Введите текст:"),
                                     Cars_list[index_row].Show_God(),1965,2019,1,&stat);
        Cars_list[index_row].Set_God(num);
        if (!stat)
        {
            Cars_list[index_row].Set_God(old);
        }
    }

    if (index_column==5)
    {
        QString old=Cars_list[index_row].Show_Fio();
        bool stat;
        QString str = QInputDialog::getText(this,
                                     QString::fromUtf8("Редактирование"),
                                     QString::fromUtf8("Введите текст:"),
                                     QLineEdit::Normal,Cars_list[index_row].Show_Fio(),&stat);
        if (str==nullptr)
        {
            str="(пусто)";
        }
        Cars_list[index_row].Set_Fio(str);
        if (!stat)
        {
            Cars_list[index_row].Set_Fio(old);
        }
    }

     ui->tableWidget->setRowCount(1);
     Add_to_Table();
}
}

void MainWindow::on_action_2()
{
    int index_row=ui->tableWidget->currentRow();

    if(ui->tableWidget->rowCount()==2)
    {
        Cars_list.removeAt(index_row);
        ui->tableWidget->clearContents();
    }
    else
    {
    Cars_list.removeAt(index_row);
    ui->tableWidget->setRowCount(1);
    Add_to_Table();
    }
}


void MainWindow::on_Open_file_triggered()
{
    QString hhh;
    QString fileName = QFileDialog::getOpenFileName(this,tr("Открыть файл"), "/home/", tr("Файл данных (*.data)"));
    QFile file(fileName);
    QDataStream stream(&file);
    if (!file.open( QIODevice::ReadOnly ))
    {
        return;
    }
    Cars_list.clear();
    while (stream.status()==0)
    {
    stream>>Auto;
    Cars_list<<Auto;
    }
    file.close();
    Cars_list.removeLast();
    ui->tableWidget->setRowCount(1);
    Add_to_Table();
    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
}



void MainWindow::on_Save_file_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,tr("Сохранить файл"), "/home/", tr("Файл данных (*.data)"));
    QFile file( fileName );
    QDataStream stream(&file);
    file.open( QIODevice::WriteOnly );
    QList <Cars>::iterator it;
    for (it=Cars_list.begin();it !=Cars_list.end(); it++)
    {
     stream << it->Show_Marka()<<it->Show_Model()<<it->Show_Vin()<<it->Show_God()<<it->Show_Probeg()<<it->Show_Fio();
    }
    file.close();

}

void MainWindow::on_Exit_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::Add_to_Table ()
{
    QList <Cars>::iterator it;
    for (it=Cars_list.begin();it !=Cars_list.end(); it++)
    {
    QTableWidgetItem* tMarka=new QTableWidgetItem;
    QTableWidgetItem* tModel=new QTableWidgetItem;
    QTableWidgetItem* tVin=new QTableWidgetItem;
    QTableWidgetItem* tGod=new QTableWidgetItem;
    QTableWidgetItem* tProbeg=new QTableWidgetItem;
    QTableWidgetItem* tFio=new QTableWidgetItem;

    tMarka->setText(it->Show_Marka());
    tModel->setText(it->Show_Model());
    tVin->setText(it->Show_Vin());
    if (it->Show_God()==-1)
    {
        tGod->setText("(пусто)");
    }
    else
    {
        tGod->setText(QString::number(it->Show_God()));
    }

    if (it->Show_Probeg()==-1)
    {
      tProbeg->setText("(пусто)");
    }
    else
    {
        tProbeg->setText(QString::number(it->Show_Probeg()));
    }
    tFio->setText(it->Show_Fio());

    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,tMarka);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,tModel);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,2,tVin);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,3,tProbeg);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,4,tGod);
    ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,5,tFio);

    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
    ui->tableWidget->resizeColumnsToContents();
}
    ui->tableWidget->hideRow(ui->tableWidget->rowCount()-1);
}

void MainWindow::on_Search_Button_clicked()
{
    int index=0;
    QList <Cars>::iterator it;
    for (it=Cars_list.begin(); it !=Cars_list.end(); it++)
    {
        if(ui->Marka_lineEdit->text() != it->Show_Marka() && (ui->Model_lineEdit->text() != it->Show_Model()) &&
            (ui->Vin_lineEdit->text() != it->Show_Vin()) && (ui->God_lineEdit->text().toInt() != it->Show_God()) &&
            (ui->Probeg_lineEdit->text().toInt() != it->Show_Probeg()) && (ui->Fio_lineEdit->text() != it->Show_Fio()))
        {
          ui->tableWidget->hideRow(index);
        }
        index++;
    }

     ui->tableWidget->setContextMenuPolicy(Qt::NoContextMenu);

}

void MainWindow::check_input()
{
    bool i=true;
    if (ui->Marka_lineEdit->text().isEmpty()==true && i==true)
    {
       QMessageBox::information(this,tr("Внимание"),tr("Пустое поле марка"),QMessageBox::Ok);
       i=false;
    }

    if (ui->Model_lineEdit->text().isEmpty()==true && i==true)
    {
       QMessageBox::information(this,tr("Внимание"),tr("Пустое поле модель"),QMessageBox::Ok);
       i=false;
    }

    if (ui->Vin_lineEdit->text().isEmpty()==true && i==true)
    {
       QMessageBox::information(this,tr("Внимание"),tr("Пустое поле VIN"),QMessageBox::Ok);
       i=false;
    }

    if (ui->God_lineEdit->text().isEmpty()==true && i==true)
    {
       QMessageBox::information(this,tr("Внимание"),tr("Пустое поле год"),QMessageBox::Ok);
       i=false;
    }

    if (ui->Probeg_lineEdit->text().isEmpty()==true && i==true)
    {
       QMessageBox::information(this,tr("Внимание"),tr("Пустое поле пробег"),QMessageBox::Ok);
       i=false;
    }

    if (ui->Fio_lineEdit->text().isEmpty()==true && i==true)
    {
       QMessageBox::information(this,tr("Внимание"),tr("Пустое поле Фио"),QMessageBox::Ok);
       i=false;
    }
}

void MainWindow::on_Reset_Button_clicked()
{
    for (int i=0; i !=Cars_list.size(); i++)
    {
        ui->tableWidget->showRow(i);
    }

    ui->Marka_lineEdit->clear();
    ui->Model_lineEdit->clear();
    ui->Vin_lineEdit->clear();
    ui->God_lineEdit->clear();
    ui->Probeg_lineEdit->clear();
    ui->Fio_lineEdit->clear();

    ui->tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
}
