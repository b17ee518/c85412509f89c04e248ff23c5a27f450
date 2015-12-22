/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "boardtablewidget.h"
#include "graphdrawwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QWidget *widget;
    QGridLayout *gridLayout_2;
    GraphDrawWidget *graphDrawWidget;
    QScrollBar *dwScrollBar;
    QPushButton *dwPlusButton;
    QPushButton *dwMinusButton;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QFrame *controlFrame;
    BoardTableWidget *boardTableWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1057, 678);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setMinimumSize(QSize(480, 260));
        gridLayout_2 = new QGridLayout(widget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        graphDrawWidget = new GraphDrawWidget(widget);
        graphDrawWidget->setObjectName(QStringLiteral("graphDrawWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphDrawWidget->sizePolicy().hasHeightForWidth());
        graphDrawWidget->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(graphDrawWidget, 0, 0, 1, 3);

        dwScrollBar = new QScrollBar(widget);
        dwScrollBar->setObjectName(QStringLiteral("dwScrollBar"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(dwScrollBar->sizePolicy().hasHeightForWidth());
        dwScrollBar->setSizePolicy(sizePolicy1);
        dwScrollBar->setMinimumSize(QSize(0, 20));
        dwScrollBar->setMaximumSize(QSize(16777215, 20));
        dwScrollBar->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(dwScrollBar, 1, 0, 1, 1);

        dwPlusButton = new QPushButton(widget);
        dwPlusButton->setObjectName(QStringLiteral("dwPlusButton"));
        dwPlusButton->setMinimumSize(QSize(20, 20));
        dwPlusButton->setMaximumSize(QSize(20, 20));

        gridLayout_2->addWidget(dwPlusButton, 1, 1, 1, 1);

        dwMinusButton = new QPushButton(widget);
        dwMinusButton->setObjectName(QStringLiteral("dwMinusButton"));
        dwMinusButton->setMinimumSize(QSize(20, 20));
        dwMinusButton->setMaximumSize(QSize(20, 20));

        gridLayout_2->addWidget(dwMinusButton, 1, 2, 1, 1);


        gridLayout->addWidget(widget, 0, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout->addItem(verticalSpacer, 1, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 1, 1, 1);

        controlFrame = new QFrame(centralWidget);
        controlFrame->setObjectName(QStringLiteral("controlFrame"));
        controlFrame->setMinimumSize(QSize(0, 200));
        controlFrame->setFrameShape(QFrame::StyledPanel);
        controlFrame->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(controlFrame, 2, 2, 1, 1);

        boardTableWidget = new BoardTableWidget(centralWidget);
        if (boardTableWidget->columnCount() < 3)
            boardTableWidget->setColumnCount(3);
        if (boardTableWidget->rowCount() < 28)
            boardTableWidget->setRowCount(28);
        boardTableWidget->setObjectName(QStringLiteral("boardTableWidget"));
        boardTableWidget->setMinimumSize(QSize(290, 600));
        boardTableWidget->setMaximumSize(QSize(290, 16777215));
        boardTableWidget->setRowCount(28);
        boardTableWidget->setColumnCount(3);
        boardTableWidget->horizontalHeader()->setDefaultSectionSize(90);
        boardTableWidget->horizontalHeader()->setMinimumSectionSize(90);
        boardTableWidget->verticalHeader()->setVisible(false);
        boardTableWidget->verticalHeader()->setDefaultSectionSize(20);
        boardTableWidget->verticalHeader()->setMinimumSectionSize(20);

        gridLayout->addWidget(boardTableWidget, 0, 0, 3, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1057, 24));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(dwScrollBar, SIGNAL(valueChanged(int)), graphDrawWidget, SLOT(onScrollBarValueChanged(int)));
        QObject::connect(dwPlusButton, SIGNAL(clicked()), graphDrawWidget, SLOT(onZoomInButtonClicked()));
        QObject::connect(dwMinusButton, SIGNAL(clicked()), graphDrawWidget, SLOT(onZoomOutButtonClicked()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        dwPlusButton->setText(QApplication::translate("MainWindow", "+", 0));
        dwMinusButton->setText(QApplication::translate("MainWindow", "-", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
