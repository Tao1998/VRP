#include"mainwindow.h"
#include"ui_mainwindow.h"
#include"ant.h"
#include"common.h"
#include"tsp.h"
#include<ctime>
#include<QPainter>
#include<QDebug>
#include<QMessageBox>
#include<QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ctst=new CTSP();
    ctst->SetParameterDefault();
    ctst->Init();

    ui->setupUi(this);
    this->init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    SetTableStyle();
    SetPosTable();
    ui->tab_3->installEventFilter(this);
}


bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == ui->tab_3 && event->type() == QEvent::Paint)
        DrawTab();
    return QWidget::eventFilter(watched, event);
}

void MainWindow::DrawTab()
{
    QPainter painter(ui->tab_3);
    painter.setPen(QPen(QColor (206, 206, 206),1));

    int rect_width = 700,p_size = 20; // 绘图窗口大小 点的大小
    painter.drawRect(0,0,rect_width,rect_width);
    int route_idx=-1;
    if(situation == 0){
        qDebug()<<"draw situation 0 !";
        // 分开文字和图形，避免文字被遮挡
//        painter.setPen(QPen(QColor (206, 206, 206),4));//outline color
        painter.setBrush(QColor (206, 206, 206));
        for (int i=0;i<CITY_COUNT+1;i++) {
            painter.drawEllipse(g_CityAry[i].dbX_draw*5+100,rect_width-g_CityAry[i].dbY_draw*5-100,p_size,p_size);
        }
        painter.setPen(QPen(QColor (20, 20, 20),4));//设置画笔形式
        for (int i=0;i<CITY_COUNT+1;i++) {
            QRectF rect(g_CityAry[i].dbX_draw*5+100,rect_width-g_CityAry[i].dbY_draw*5-100,20,p_size);
            painter.drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter, QString::number(i));
//            painter.drawText(g_CityAry[i].dbX_draw*5+100+7.5,rect_width-g_CityAry[i].dbY_draw*5-100+14,QString::number(i));
        }
    }
    if(situation==1)
    {
        // 绘制配送站
        painter.setPen(QPen(QColor (206, 206, 206),4));//设置画笔形式
        painter.setBrush(QColor (206, 206, 206));
        painter.drawEllipse(g_CityAry[0].dbX_draw*5+100,rect_width-g_CityAry[0].dbY_draw*5-100,p_size,p_size);
        qDebug()<< "X:"<<g_CityAry[0].dbX_draw<< " Y:"<<rect_width-g_CityAry[0].dbY_draw;
        QString strRoute = "0-";
        ui->tableWidget->setRowCount(best_ant_count-CITY_COUNT);
        int m,n=0,car_No;
        double weight=0.0;
        for (int j=1;j<best_ant_count;j++)
        {
            m=best_ant[j-1];
            n=best_ant[j];
            if (m>CITY_COUNT) //是车
            {
                route_idx++;
                car_No = ctst->GetCarNo(m);
                strRoute = "0-";
                // 设置单元格样式
                QTableWidgetItem *item = new QTableWidgetItem(QString::number(route_idx));
                item->setBackgroundColor(intColor(route_idx, best_ant_count-CITY_COUNT));
                item->setTextColor(QColor(20, 20, 20)); //设置文字颜色
                item->setTextAlignment(Qt::AlignCenter); // 设置居中
                ui->tableWidget->setItem(route_idx,0,item);//填入表格
                QTableWidgetItem *item_car_type = new QTableWidgetItem(ctst->GetCarType(m));
                item_car_type->setTextAlignment(Qt::AlignCenter); // 设置居中
                ui->tableWidget->setItem(route_idx,1,item_car_type);

                m=0;
            }
            else{ // 绘制配送点
//                painter.setPen(QPen(Qt::white));//outline color
                painter.setBrush(intColor(route_idx, best_ant_count-CITY_COUNT));
                painter.drawEllipse(g_CityAry[m].dbX_draw*5+100,rect_width-g_CityAry[m].dbY_draw*5-100,p_size,p_size);
                strRoute += QString::number(m)+"-";
            }
            if (n>CITY_COUNT) //是车
            {
                n=0;
                QTableWidgetItem *item_w = new QTableWidgetItem(QString::number(weight/g_CarAry[car_No-1].dbMaxWeight,'g',2));// 满载率
                item_w->setTextAlignment(Qt::AlignCenter); // 设置居中
                ui->tableWidget->setItem(route_idx,2,item_w);
                weight=0.0;
                strRoute += "0";
                ui->tableWidget->setItem(route_idx,3,new QTableWidgetItem(strRoute));//填入表格

            }
            else{ // 配送点
                weight=weight+g_CityAry[n].dbW;
            }
            // best_ant_count-CITY_COUNT 路线数量
            painter.setPen(QPen(intColor(route_idx, best_ant_count-CITY_COUNT),3));//设置画笔形式
            painter.drawLine(g_CityAry[m].dbX_draw*5+100+14,rect_width-g_CityAry[m].dbY_draw*5-100+14,g_CityAry[n].dbX_draw*5+100+14,rect_width-g_CityAry[n].dbY_draw*5-100+14);
        }

        //最后城市和配送站之间的信息素
        painter.setBrush(intColor(route_idx, best_ant_count-CITY_COUNT));
        painter.drawLine(g_CityAry[n].dbX_draw*5+100+14,rect_width-g_CityAry[n].dbY_draw*5-100+14,g_CityAry[0].dbX_draw*5+100+14,rect_width-g_CityAry[0].dbY_draw*5-100+14);
        painter.drawEllipse(g_CityAry[n].dbX_draw*5+100,rect_width-g_CityAry[n].dbY_draw*5-100,p_size,p_size);

        strRoute += QString::number(n)+"-0";
        ui->tableWidget->setItem(route_idx,3,new QTableWidgetItem(strRoute));//填入表格
        QTableWidgetItem *item_w = new QTableWidgetItem(QString::number(weight/g_CarAry[car_No-1].dbMaxWeight,'g',2)); // 满载率
        item_w->setTextAlignment(Qt::AlignCenter); // 设置居中
        ui->tableWidget->setItem(route_idx,2,item_w);

        for (int i=0;i<CITY_COUNT+1;i++) {
            painter.setPen(QPen(QColor (10, 10, 10)));//设置画笔形式
            QRectF rect(g_CityAry[i].dbX_draw*5+100,rect_width-g_CityAry[i].dbY_draw*5-100,20,p_size);
            painter.drawText(rect, Qt::AlignHCenter | Qt::AlignVCenter, QString::number(i));
//            painter.drawText(g_CityAry[i].dbX_draw*5+100+7.5,rect_width-g_CityAry[i].dbY_draw*5-100+14,QString::number(i));
        }
    }

}

void MainWindow::SetTableStyle()
{
    ui->tableWidget->verticalHeader()->setVisible(false); //隐藏列表头
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents); //把给定列设置为给定模式
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);

    ui->tableWidget_2->horizontalHeader()->setVisible(true);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);

    ui->tableWidget_pos->setEditTriggers(QAbstractItemView::NoEditTriggers); //设置不可编辑
    ui->tableWidget_pos->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget_pos->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget_pos->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->tableWidget_pos->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
}

void MainWindow::SetPosTable()
{
    qDebug()<<"row: "<< ui->tableWidget_pos->rowCount();
    ui->tableWidget_pos->removeRow(ui->tableWidget_pos->rowCount());
    ui->tableWidget_pos->setRowCount(CITY_COUNT+1);
    ui->tableWidget_pos->setItem(0,0,new QTableWidgetItem(QString::number(0)));
    ui->tableWidget_pos->setItem(0,1,new QTableWidgetItem(QString::number(g_CityAry[0].dbX)));
    ui->tableWidget_pos->setItem(0,2,new QTableWidgetItem(QString::number(g_CityAry[0].dbY)));
    ui->tableWidget_pos->setItem(0,3,new QTableWidgetItem(QString::number(g_CityAry[0].dbW)));
    for(int i=1;i<CITY_COUNT+1;i++)
    {
        ui->tableWidget_pos->setItem(i,0,new QTableWidgetItem(QString::number(i)));
        ui->tableWidget_pos->setItem(i,1,new QTableWidgetItem(QString::number(g_CityAry[i].dbX)));
        ui->tableWidget_pos->setItem(i,2,new QTableWidgetItem(QString::number(g_CityAry[i].dbY)));
        ui->tableWidget_pos->setItem(i,3,new QTableWidgetItem(QString::number(g_CityAry[i].dbW)));
    }
}

void MainWindow::MultiCarInit()
{
    CAR_COUNT=0;
    MAX_LENGTH=0;
    MAX_WEIGHT=0;
    TYPE_COUNT = ui->tableWidget_2->rowCount();
    for(int i=0;i<TYPE_COUNT;i++)
    {
        CAR_TYPE_NAME[i] = ui->tableWidget_2->item(i,0)->text();
        CAR_TYPE_MAX_LENGTH[i] = ui->tableWidget_2->item(i,1)->text().toDouble();
        if(CAR_TYPE_MAX_LENGTH[i]>MAX_LENGTH)
            MAX_LENGTH=CAR_TYPE_MAX_LENGTH[i];
        CAR_TYPE_MAX_WEIGHT[i] = ui->tableWidget_2->item(i,2)->text().toDouble();
        if(CAR_TYPE_MAX_WEIGHT[i]>MAX_WEIGHT)
            MAX_WEIGHT=CAR_TYPE_MAX_WEIGHT[i];
        CAR_TYPE_COUNT[i] = ui->tableWidget_2->item(i,3)->text().toInt();
        CAR_COUNT+=CAR_TYPE_COUNT[i];
    }
}

void MainWindow::on_pushButton_NewData_clicked()
{
    CITY_COUNT=ui->spinBox_ClientNum->text().toInt();
    ctst->SetParameterRandom();
    SetPosTable(); // 设置配送点信息表
    ui->tab_3->repaint(); // 重新描点
}

void MainWindow::on_pushButton_Search_clicked()
{
    clock_t  time_kp = clock();
    MultiCarInit();
    qDebug()<<"MAX_CITYWEIGHT:"<<MAX_CITYWEIGHT<<"CAR_WEIGHT"<<MAX_WEIGHT;
    if(CAR_COUNT==0)
    {
        QMessageBox::information(nullptr, "警告", "车辆数目应大于0", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    if(2*MAX_CITYLENGTH>MAX_LENGTH)
    {
        QMessageBox::information(nullptr, "警告", "车辆无法往返最远配送点，车辆最大行驶里程应大于"+QString::number(2*MAX_CITYLENGTH), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    if(MAX_CITYWEIGHT>MAX_WEIGHT)
    {
        qDebug()<<"MAX_CITYWEIGHT:"<<MAX_CITYWEIGHT<<"CAR_WEIGHT"<<MAX_WEIGHT;
        QMessageBox::information(nullptr, "警告", "车辆无法达到载重要求，车辆最大载重应大于"+QString::number(MAX_CITYWEIGHT), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    ANT_COUNT=ui->spinBox_antNum->text().toInt();
//    qDebug()<<"Ant Count: "<<ui->spinBox_antNum->text().toInt();
    IT_COUNT=ui->spinBox_maxGeneration->text().toInt();
//    qDebug()<<"IT_COUNT: "<<ui->spinBox_maxGeneration->text().toInt();

    //qDebug()<<"点击搜索按钮";
    ctst->GetCarData();
    ctst->Init();
    ui->label_minDist->setText(QString::number(ctst->Search(),'f', 4));
    ui->label_time->setText(QString::number( (clock() - time_kp) / (double)CLOCKS_PER_SEC,'f',2)+"s");
    situation=1;
    QEvent *event1=new QEvent(QEvent::WindowActivate);//发送WindowActivate事件来刷新绘图
    QApplication::postEvent(this, event1);
}


void MainWindow::on_pushButton_AddTableData_clicked()
{
    int row_count = ui->tableWidget_2->rowCount();
    qDebug()<<"row_count: "<< row_count;
    ui->tableWidget_2->setRowCount(row_count+1);

}

void MainWindow::on_pushButton_DeleteTableData_clicked()
{
    int row_index = ui->tableWidget_2->currentRow();//选中的行号
    if(row_index != -1){
        ui->tableWidget_2->removeRow(row_index);
    }
}

void MainWindow::on_pushButton_LoadData_clicked()
{
    QString FileName;
    FileName=QFileDialog::getOpenFileName(this,tr("文件"),".",tr("Excel(*.csv)"));
    if(!FileName.isNull())
    {
        QFile file(FileName);
        if(!file.open(QIODevice::ReadOnly))
            qDebug()<<"file open error";
        QTextStream *out=new QTextStream(&file);
        QStringList tempoption=out->readAll().split("\n");
        QStringList tempbar=tempoption.at(0).split(",");
        g_CityAry[0].dbX=tempbar.at(0).toDouble();
        g_CityAry[0].dbY=tempbar.at(1).toDouble();
        g_CityAry[0].dbW=0.0;
        int count = 0;
        for(int i=1;i<tempoption.count();i++)
        {
            tempbar=tempoption.at(i).split(",");
            if(tempbar.at(0) == "")// 跳过空行
            {
                continue;
            }
            g_CityAry[i].dbX=tempbar.at(0).toDouble();
            g_CityAry[i].dbY=tempbar.at(1).toDouble();
            g_CityAry[i].dbW=tempbar.at(2).toDouble();
            count++;
        }
        file.close();
        CITY_COUNT = count;
        situation = 0;
        // min—max标准化 美化GUI 让点落在中心区域
        int dbx_max=g_CityAry[0].dbX, dbx_min=g_CityAry[0].dbX,dby_max=g_CityAry[0].dbY, dby_min=g_CityAry[0].dbY;
        for(int i=0;i<=CITY_COUNT;i++)
        {
            if(g_CityAry[i].dbX<dbx_min)
                dbx_min = g_CityAry[i].dbX;
            if(g_CityAry[i].dbX>dbx_max)
                dbx_max = g_CityAry[i].dbX;
            if(g_CityAry[i].dbY<dby_min)
                dby_min = g_CityAry[i].dbY;
            if(g_CityAry[i].dbY>dby_max)
                dby_max = g_CityAry[i].dbY;
        }
        int dbx_d = dbx_max-dbx_min, dby_d = dby_max-dby_min;
        for(int i=0;i<=CITY_COUNT;i++)
        {
            g_CityAry[i].dbX_draw = (g_CityAry[i].dbX-dbx_min) / dbx_d * 100;
            g_CityAry[i].dbY_draw = (g_CityAry[i].dbY-dby_min) / dby_d * 100;
        }

        ctst->CalCityDistance();//计算两两城市间距离
        ctst->CalCityMaxWeight(); // 计算最大载重
        SetPosTable(); // 设置配送点信息表
        ui->tab_3->repaint();
    }


}

