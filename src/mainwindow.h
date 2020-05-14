#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"ant.h"
#include"common.h"
#include"tsp.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
//    void paintEvent(QPaintEvent *);
    CTSP *ctst;
    void init();
    bool eventFilter(QObject *watched, QEvent *event);
    void DrawTab();
    void SetTableStyle();
    ~MainWindow();

private slots:

    void on_pushButton_Search_clicked();

    void on_pushButton_NewData_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
