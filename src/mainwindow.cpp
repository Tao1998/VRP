#include"mainwindow.h"
#include"ui_mainwindow.h"
#include"ant.h"
#include"common.h"
#include"tsp.h"
#include<QPainter>
#include<QDebug>
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

    int rect_width = 700; // 绘图窗口大小
    painter.drawRect(0,0,rect_width,rect_width);
    int route_idx=-1;
    if(situation == 0){
        qDebug()<<"draw situation 0 !";
        // 分开文字和图形，避免文字被遮挡
//        painter.setPen(QPen(QColor (206, 206, 206),4));//outline color
        painter.setBrush(QColor (206, 206, 206));
        for (int i=0;i<CITY_COUNT+1;i++) {
            painter.drawEllipse(g_CityAry[i].dbX_draw*5+100,rect_width-g_CityAry[i].dbY_draw*5-100,30,30);
        }
        painter.setPen(QPen(QColor (20, 20, 20),4));//设置画笔形式
        for (int i=0;i<CITY_COUNT+1;i++) {
            painter.drawText(g_CityAry[i].dbX_draw*5+100+7.5,rect_width-g_CityAry[i].dbY_draw*5-100+14,QString::number(i));
        }
    }
    if(situation==1)
    {
        // 绘制配送站
        painter.setPen(QPen(QColor (206, 206, 206),4));//设置画笔形式
        painter.setBrush(QColor (206, 206, 206));
        painter.drawEllipse(g_CityAry[0].dbX_draw*5+100,rect_width-g_CityAry[0].dbY_draw*5-100,30,30);
        qDebug()<< "X:"<<g_CityAry[0].dbX_draw<< " Y:"<<rect_width-g_CityAry[0].dbY_draw;
        QString strRoute = "0-";
        ui->tableWidget->setRowCount(best_ant_count-CITY_COUNT);
        int m,n=0,car_No;
        double weight=0.0;
        for (int j=1;j<best_ant_count;j++)
        {
            m=best_ant[j-1];
            n=best_ant[j];
            if (m>CITY_COUNT) //是配送站
            {
                route_idx++;
                car_No = ctst->GetCarNo(m);
                weight=0.0;
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
                weight=weight+g_CityAry[m].dbW;
//                painter.setPen(QPen(Qt::white));//outline color
                painter.setBrush(intColor(route_idx, best_ant_count-CITY_COUNT));
                painter.drawEllipse(g_CityAry[m].dbX_draw*5+100,rect_width-g_CityAry[m].dbY_draw*5-100,30,30); 
                strRoute += QString::number(m)+"-";
            }
            if (n>CITY_COUNT) //是配送站
            {
                n=0;
                QTableWidgetItem *item_w = new QTableWidgetItem(QString::number(weight/g_CarAry[car_No-1].dbMaxWeight,'g',2));// 满载率
                item_w->setTextAlignment(Qt::AlignCenter); // 设置居中
                ui->tableWidget->setItem(route_idx,2,item_w);
                weight=0.0;
                strRoute += "0";
                ui->tableWidget->setItem(route_idx,3,new QTableWidgetItem(strRoute));//填入表格

            }
            // best_ant_count-CITY_COUNT 路线数量
            painter.setPen(QPen(intColor(route_idx, best_ant_count-CITY_COUNT),3));//设置画笔形式
            painter.drawLine(g_CityAry[m].dbX_draw*5+100+14,rect_width-g_CityAry[m].dbY_draw*5-100+14,g_CityAry[n].dbX_draw*5+100+14,rect_width-g_CityAry[n].dbY_draw*5-100+14);
        }

        //最后城市和配送站之间的信息素
        painter.setBrush(intColor(route_idx, best_ant_count-CITY_COUNT));
        painter.drawLine(g_CityAry[n].dbX_draw*5+100+14,rect_width-g_CityAry[n].dbY_draw*5-100+14,g_CityAry[0].dbX_draw*5+100+14,rect_width-g_CityAry[0].dbY_draw*5-100+14);
        painter.drawEllipse(g_CityAry[n].dbX_draw*5+100,rect_width-g_CityAry[n].dbY_draw*5-100,30,30);

        strRoute += QString::number(n)+"-0";
        ui->tableWidget->setItem(route_idx,3,new QTableWidgetItem(strRoute));//填入表格
        QTableWidgetItem *item_w = new QTableWidgetItem(QString::number(weight/g_CarAry[car_No-1].dbMaxWeight,'g',2)); // 满载率
        item_w->setTextAlignment(Qt::AlignCenter); // 设置居中
        ui->tableWidget->setItem(route_idx,2,item_w);

        for (int i=0;i<CITY_COUNT+1;i++) {
            painter.setPen(QPen(QColor (10, 10, 10)));//设置画笔形式
            painter.drawText(g_CityAry[i].dbX_draw*5+100+7.5,rect_width-g_CityAry[i].dbY_draw*5-100+14,QString::number(i));
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
}

void MainWindow::MultiCarInit()
{
    CARA_COUNT=ui->spinBox_NumberOfA->text().toInt();
    CARB_COUNT=ui->spinBox_NumberOfB->text().toInt();
    CAR_COUNT=CARA_COUNT+CARB_COUNT;
    MAX_LENGTH=ui->spinBox_maxDist->text().toDouble();
    MAXA_WEIGHT=ui->spinBox_maxAWeight->text().toDouble();
    MAXB_WEIGHT=ui->spinBox_maxBWeight->text().toDouble();
}

void MainWindow::on_pushButton_NewData_clicked()
{
    MultiCarInit();
    CITY_COUNT=ui->spinBox_ClientNum->text().toInt();
    ctst->SetParameterRandom();
    ui->tab_3->repaint(); // 重新描点
}

void MainWindow::on_pushButton_Search_clicked()
{
    ANT_COUNT=ui->spinBox_antNum->text().toInt();
//    qDebug()<<"Ant Count: "<<ui->spinBox_antNum->text().toInt();
    IT_COUNT=ui->spinBox_maxGeneration->text().toInt();
//    qDebug()<<"IT_COUNT: "<<ui->spinBox_maxGeneration->text().toInt();

    //qDebug()<<"点击搜索按钮";
    ctst->Init();
    ui->label_minDist->setText(QString::number(ctst->Search(),'f', 4));
    situation=1;
    QEvent *event1=new QEvent(QEvent::WindowActivate);//发送WindowActivate事件来刷新绘图
    QApplication::postEvent(this, event1);
}

