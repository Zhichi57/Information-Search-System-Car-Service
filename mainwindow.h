#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>

#include "cars.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void Add_to_Table();

    void check_input();

private slots:
    void on_pushButton_clicked();

    void ShowContextMenu(const QPoint&);

    void on_action_1();

    void on_action_2();

    void on_Open_file_triggered();

    void on_Save_file_triggered();

    void on_Search_Button_clicked();

    void on_Reset_Button_clicked();

    void on_Exit_triggered();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
