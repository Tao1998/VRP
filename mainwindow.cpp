#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //ui->comboBox->addItem(QString::asprintf("Item %d",8));
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->comboBox->addItem(QString::asprintf("车型%d(%d,%d)",i,ui->length->text().toInt(),ui->weigtht->text().toInt()));
    i++;
}

void MainWindow::on_pushButton_2_clicked()
{
    qDebug()<<"最大路程"<<ui->comboBox->itemText(1)[4]<<"最大载重"<<ui->comboBox->itemText(1)[6];

}
