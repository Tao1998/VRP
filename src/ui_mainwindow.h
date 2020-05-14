/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget_2;
    QWidget *tab_3;
    QWidget *tab_4;
    QTableWidget *tableWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QSpinBox *spinBox_ClientNum;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_NewData;
    QSpacerItem *verticalSpacer_4;
    QFrame *line_5;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_LoadData;
    QSpacerItem *verticalSpacer_13;
    QFrame *line;
    QSpacerItem *verticalSpacer_15;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButton_Search;
    QSpacerItem *verticalSpacer_16;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QLabel *label_minDist;
    QSpacerItem *verticalSpacer_14;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_5;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_3;
    QSpinBox *spinBox_maxAWeight;
    QSpinBox *spinBox_maxBWeight;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_10;
    QSpinBox *spinBox_maxDist;
    QSpacerItem *verticalSpacer_8;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label_8;
    QSpinBox *spinBox_maxGeneration;
    QLabel *label_9;
    QSpinBox *spinBox_antNum;
    QSpacerItem *verticalSpacer_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(957, 775);
        QIcon icon;
        icon.addFile(QStringLiteral(":/img/images/map.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("*{font: 9pt \"\345\215\216\346\226\207\347\273\206\351\273\221\";\n"
"background: rgb(51, 51, 51);\n"
"	color: rgb(247, 252, 246);}\n"
"QRadioButton{\n"
"	background: outset;\n"
"    height: 25px;\n"
"	font-size:16px;\n"
"}\n"
"\n"
"QRadioButton::indicator::unchecked {\n"
"    background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(92, 92, 92, 255), stop:0.567164 rgba(87, 87, 87, 255), stop:0.791045 rgba(70, 70, 70, 255), stop:0.870647 rgba(0, 0, 0, 0))\n"
"}\n"
"\n"
"QRadioButton::indicator::unchecked:hover {\n"
"    background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(74, 74, 74, 255), stop:0.567164 rgba(77, 77, 77, 255), stop:0.791045 rgba(54, 54, 54, 255), stop:0.870647 rgba(0, 0, 0, 0))\n"
"}\n"
"\n"
"QRadioButton::indicator:unchecked:pressed {\n"
"    background: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(68, 68, 68, 255), stop:0.567164 rgba(68, 68, 68, 255), stop:0.791045 rgba(43, "
                        "43, 43, 255), stop:0.870647 rgba(0, 0, 0, 0))\n"
"}\n"
"\n"
"QRadioButton::indicator::checked {\n"
"    background:qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 254, 254, 255), stop:0.288557 rgba(255, 254, 254, 255), stop:0.378109 rgba(61, 97, 216, 255), stop:0.820896 rgba(60, 100, 223, 255), stop:0.870647 rgba(0, 0, 0, 0))\n"
"}\n"
"\n"
"QRadioButton::indicator:checked:hover {\n"
"    background:qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(235, 234, 234, 255), stop:0.288557 rgba(228, 227, 227, 255), stop:0.378109 rgba(51, 81, 181, 255), stop:0.820896 rgba(55, 91, 204, 255), stop:0.870647 rgba(0, 0, 0, 0))\n"
"}\n"
"\n"
"QRadioButton::indicator:checked:pressed {\n"
"    background:qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(206, 205, 205, 255), stop:0.298507 rgba(231, 230, 230, 255), stop:0.378109 rgba(61, 65, 178, 255), stop:0.820896 rgba(42, 71, 161, 255), stop:0.870647 rgba(0, 0, 0, 0))\n"
""
                        "}\n"
"QTabWidget::pane {\n"
"    border: none;\n"
"    /*border-top: 3px solid qlineargradient(spread:pad, y1:0, y2:1, stop:0 rgba(106, 106, 106),stop:1 rgba(99, 99, 99));*/\n"
"}\n"
"QTabWidget::tab-bar {\n"
"	alignment: center;\n"
"    border: none;\n"
"}\n"
"QTabBar::tab {\n"
"    border: none;\n"
"    border-top-left-radius: 4px;\n"
"    border-top-right-radius: 4px;\n"
"    background: qlineargradient(spread:pad, y1:0, y2:1, stop:0 rgba(106, 106, 106),stop:1 rgba(99, 99, 99));\n"
"	color: rgb(247, 252, 246);	\n"
"    height: 28px;\n"
"    min-width: 90px;\n"
"    margin-right: 2px;\n"
"    padding-left: 2px;\n"
"    padding-right: 2px;\n"
"}\n"
"QTabBar::tab:hover {\n"
"	background: rgb(255, 255, 255, 40);\n"
"}\n"
"QTabBar::tab:selected {\n"
"    background: qlineargradient(spread:pad, y1:0, y2:1, stop:0 rgba(206, 206, 206),stop:1 rgba(193, 193, 193));\n"
"	color:rgb(61, 65, 69);\n"
"}\n"
"QPushButton {\n"
"    background-color: rgb(101,101,101);\n"
"    border-radius: 8px;\n"
"    text-align: center;\n"
""
                        "    text-decoration: none;\n"
"    font-size: 16px;\n"
"	padding: 8px;\n"
"    margin: 4px;\n"
"	min-width: 6em;\n"
"	border: 1px solid rgb(44, 44, 44);\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"        background-color: qlineargradient(spread:pad, y1:0, y2:1, stop:0 rgba(78, 122, 231),stop:1 rgba(56, 97, 203));\n"
"	color:(241, 248, 247);/*\n"
"    border: 2px solid rgb(17, 29, 207);*/\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"            background-color: qlineargradient(spread:pad, y1:0, y2:1, stop:0 rgba(64, 90, 157),stop:1 rgba(55, 79, 143));\n"
"	color:(137, 146, 166);}\n"
"QWidget#tab_2 {\n"
"	background: rgb(60, 60, 60);\n"
"	font-size: 16px;\n"
"	min-width: 187px;\n"
"}\n"
"\n"
"QWidget#tab {\n"
"	background: rgb(60, 60, 60);\n"
"	font-size: 16px;\n"
"	min-width: 187px;\n"
"}\n"
"QLabel{\n"
"	background: outset;\n"
"	font-size:16px;\n"
"    spacing: 5px;\n"
"	min-width: 80px;\n"
"	margin: 4px;\n"
"}\n"
"QGroupBox > QLabel{\n"
"	min-width: 40px;\n"
"}\n"
"QSpinBox {\n"
"	font-size:16px;\n"
"}\n"
"QDoubleSp"
                        "inBox {\n"
"	font-size:16px;\n"
"}\n"
"QGroupBox{\n"
"	background: outset;\n"
"}\n"
"\n"
"/*\n"
"tabelwidget*/\n"
"QTableWidget{\n"
"color:#DCDCDC;\n"
"background:#444444;\n"
"border:1px solid #242424;\n"
"alternate-background-color:#525252;/*\344\272\244\351\224\231\351\242\234\350\211\262*/\n"
"gridline-color:#242424;\n"
"}\n"
"\n"
"/*\351\200\211\344\270\255item*/\n"
"QTableWidget::item:selected{\n"
"color:#DCDCDC;\n"
"background:qlineargradient(spread:pad,x1:0,y1:0,x2:0,y2:1,stop:0 #484848,stop:1 #383838);\n"
"}\n"
"\n"
"/*\n"
"\346\202\254\346\265\256item*/\n"
"QTableWidget::item:hover{\n"
"background:#5B5B5B;\n"
"}\n"
"/*\350\241\250\345\244\264*/\n"
"QHeaderView::section{\n"
"text-align:center;\n"
"background:#5E5E5E;\n"
"padding:3px;\n"
"margin:0px;\n"
"color:#DCDCDC;\n"
"border:1px solid #242424;\n"
"border-left-width:0;\n"
"}\n"
"\n"
"/*\350\241\250\345\217\263\344\276\247\347\232\204\346\273\221\346\235\241*/\n"
"QScrollBar:vertical{\n"
"background:#484848;\n"
"padding:0px;\n"
"border-radius:6px;\n"
""
                        "max-width:12px;\n"
"}\n"
"\n"
"/*\346\273\221\345\235\227*/\n"
"QScrollBar::handle:vertical{\n"
"background:#CCCCCC;\n"
"}\n"
"/*\n"
"\346\273\221\345\235\227\346\202\254\346\265\256\357\274\214\346\214\211\344\270\213*/\n"
"QScrollBar::handle:hover:vertical,QScrollBar::handle:pressed:vertical{\n"
"background:#A7A7A7;\n"
"}\n"
"/*\n"
"\346\273\221\345\235\227\345\267\262\347\273\217\345\210\222\350\277\207\347\232\204\345\214\272\345\237\237*/\n"
"QScrollBar::sub-page:vertical{\n"
"background:444444;\n"
"}\n"
"\n"
"/*\n"
"\346\273\221\345\235\227\350\277\230\346\262\241\346\234\211\345\210\222\350\277\207\347\232\204\345\214\272\345\237\237*/\n"
"QScrollBar::add-page:vertical{\n"
"background:5B5B5B;\n"
"}\n"
"\n"
"/*\351\241\265\351\235\242\344\270\213\347\247\273\347\232\204\346\214\211\351\222\256*/\n"
"QScrollBar::add-line:vertical{\n"
"background:none;\n"
"}\n"
"/*\351\241\265\351\235\242\344\270\212\347\247\273\347\232\204\346\214\211\351\222\256*/\n"
"QScrollBar::sub-line:vertical{\n"
"background:none;\n"
""
                        "}\n"
"\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setStyleSheet(QStringLiteral(""));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tabWidget_2 = new QTabWidget(centralwidget);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        tabWidget_2->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        tableWidget = new QTableWidget(tab_4);
        if (tableWidget->columnCount() < 4)
            tableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignCenter);
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignCenter);
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(11, 11, 691, 671));
        tabWidget_2->addTab(tab_4, QString());

        horizontalLayout->addWidget(tabWidget_2);

        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setFocusPolicy(Qt::TabFocus);
        tabWidget->setContextMenuPolicy(Qt::NoContextMenu);
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setAutoFillBackground(false);
        tabWidget->setStyleSheet(QStringLiteral(""));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\215\216\346\226\207\347\273\206\351\273\221"));
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        tab->setFont(font);
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setSpacing(7);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(tab);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        spinBox_ClientNum = new QSpinBox(tab);
        spinBox_ClientNum->setObjectName(QStringLiteral("spinBox_ClientNum"));
        spinBox_ClientNum->setMinimum(4);
        spinBox_ClientNum->setMaximum(500);
        spinBox_ClientNum->setValue(20);

        horizontalLayout_5->addWidget(spinBox_ClientNum);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton_NewData = new QPushButton(tab);
        pushButton_NewData->setObjectName(QStringLiteral("pushButton_NewData"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_NewData->sizePolicy().hasHeightForWidth());
        pushButton_NewData->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(pushButton_NewData);


        verticalLayout_2->addLayout(horizontalLayout_2);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);

        line_5 = new QFrame(tab);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_5);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_7);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pushButton_LoadData = new QPushButton(tab);
        pushButton_LoadData->setObjectName(QStringLiteral("pushButton_LoadData"));
        sizePolicy.setHeightForWidth(pushButton_LoadData->sizePolicy().hasHeightForWidth());
        pushButton_LoadData->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(pushButton_LoadData);


        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalSpacer_13 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_13);

        line = new QFrame(tab);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        verticalSpacer_15 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_15);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        pushButton_Search = new QPushButton(tab);
        pushButton_Search->setObjectName(QStringLiteral("pushButton_Search"));
        sizePolicy.setHeightForWidth(pushButton_Search->sizePolicy().hasHeightForWidth());
        pushButton_Search->setSizePolicy(sizePolicy);
        pushButton_Search->setMinimumSize(QSize(128, 0));

        horizontalLayout_7->addWidget(pushButton_Search);


        verticalLayout_2->addLayout(horizontalLayout_7);

        verticalSpacer_16 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_16);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_6 = new QLabel(tab);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_6->addWidget(label_6);

        label_minDist = new QLabel(tab);
        label_minDist->setObjectName(QStringLiteral("label_minDist"));

        horizontalLayout_6->addWidget(label_minDist);


        verticalLayout_2->addLayout(horizontalLayout_6);

        verticalSpacer_14 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_14);

        verticalLayout_2->setStretch(1, 1);
        verticalLayout_2->setStretch(2, 1);
        verticalLayout_2->setStretch(6, 1);
        verticalLayout_2->setStretch(10, 1);
        verticalLayout_2->setStretch(12, 1);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tab_2->setLayoutDirection(Qt::LeftToRight);
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalSpacer_5 = new QSpacerItem(20, 231, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_5);

        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_3 = new QGridLayout(groupBox_2);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        spinBox_maxAWeight = new QSpinBox(groupBox_2);
        spinBox_maxAWeight->setObjectName(QStringLiteral("spinBox_maxAWeight"));
        spinBox_maxAWeight->setMinimum(20);
        spinBox_maxAWeight->setMaximum(200);
        spinBox_maxAWeight->setSingleStep(10);
        spinBox_maxAWeight->setValue(100);

        gridLayout_3->addWidget(spinBox_maxAWeight, 1, 1, 1, 1);

        spinBox_maxBWeight = new QSpinBox(groupBox_2);
        spinBox_maxBWeight->setObjectName(QStringLiteral("spinBox_maxBWeight"));
        spinBox_maxBWeight->setMinimum(20);
        spinBox_maxBWeight->setMaximum(200);
        spinBox_maxBWeight->setSingleStep(10);
        spinBox_maxBWeight->setValue(100);

        gridLayout_3->addWidget(spinBox_maxBWeight, 2, 1, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_3->addWidget(label_3, 1, 0, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_3->addWidget(label_4, 2, 0, 1, 1);

        label_10 = new QLabel(groupBox_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_3->addWidget(label_10, 0, 0, 1, 1);

        spinBox_maxDist = new QSpinBox(groupBox_2);
        spinBox_maxDist->setObjectName(QStringLiteral("spinBox_maxDist"));
        spinBox_maxDist->setMinimum(20);
        spinBox_maxDist->setMaximum(200);
        spinBox_maxDist->setSingleStep(10);
        spinBox_maxDist->setValue(100);

        gridLayout_3->addWidget(spinBox_maxDist, 0, 1, 1, 1);


        verticalLayout_3->addWidget(groupBox_2);

        verticalSpacer_8 = new QSpacerItem(20, 231, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_8);

        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_2->addWidget(label_8, 0, 0, 1, 1);

        spinBox_maxGeneration = new QSpinBox(groupBox);
        spinBox_maxGeneration->setObjectName(QStringLiteral("spinBox_maxGeneration"));
        spinBox_maxGeneration->setMinimum(100);
        spinBox_maxGeneration->setMaximum(10000);
        spinBox_maxGeneration->setSingleStep(10);
        spinBox_maxGeneration->setValue(1000);
        spinBox_maxGeneration->setDisplayIntegerBase(10);

        gridLayout_2->addWidget(spinBox_maxGeneration, 0, 1, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_2->addWidget(label_9, 1, 0, 1, 1);

        spinBox_antNum = new QSpinBox(groupBox);
        spinBox_antNum->setObjectName(QStringLiteral("spinBox_antNum"));
        spinBox_antNum->setMinimum(1);
        spinBox_antNum->setMaximum(200);
        spinBox_antNum->setSingleStep(1);
        spinBox_antNum->setValue(12);
        spinBox_antNum->setDisplayIntegerBase(10);

        gridLayout_2->addWidget(spinBox_antNum, 1, 1, 1, 1);


        verticalLayout_3->addWidget(groupBox);

        verticalSpacer_6 = new QSpacerItem(20, 231, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_6);

        verticalLayout_3->setStretch(0, 1);
        verticalLayout_3->setStretch(2, 1);
        verticalLayout_3->setStretch(4, 1);
        tabWidget->addTab(tab_2, QString());

        horizontalLayout->addWidget(tabWidget);

        horizontalLayout->setStretch(0, 5);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 957, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget_2->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QApplication::translate("MainWindow", "\347\273\230\345\233\276", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "\350\267\257\347\272\277\347\274\226\345\217\267", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "\350\275\246\350\276\206\347\261\273\345\236\213", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "\346\273\241\350\275\275\347\216\207", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "\350\267\257\345\276\204", Q_NULLPTR));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QApplication::translate("MainWindow", "\350\267\257\347\272\277\350\257\246\346\203\205", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "\351\205\215\351\200\201\347\202\271\346\225\260\351\207\217", Q_NULLPTR));
        pushButton_NewData->setText(QApplication::translate("MainWindow", "\347\224\237\346\210\220\351\232\217\346\234\272\346\225\260\346\215\256", Q_NULLPTR));
        pushButton_LoadData->setText(QApplication::translate("MainWindow", "\345\257\274\345\205\245\346\225\260\346\215\256", Q_NULLPTR));
        pushButton_Search->setText(QApplication::translate("MainWindow", "\346\220\234\347\264\242", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "\346\234\200\347\237\255\350\267\257\345\276\204", Q_NULLPTR));
        label_minDist->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "\344\270\273\350\217\234\345\215\225", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "\350\275\246\350\276\206\345\217\202\346\225\260", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "A\350\275\246\346\234\200\345\244\247\350\275\275\351\207\215", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "B\350\275\246\346\234\200\345\244\247\350\275\275\351\207\215", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "\346\234\200\345\244\247\350\277\220\350\276\223\350\267\235\347\246\273", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "\347\256\227\346\263\225\345\217\202\346\225\260", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "\350\277\255\344\273\243\346\254\241\346\225\260", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "\350\232\202\350\232\201\346\225\260\351\207\217", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\347\263\273\347\273\237\345\217\202\346\225\260", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
