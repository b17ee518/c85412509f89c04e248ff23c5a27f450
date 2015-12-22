#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "SBIDataParser.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	SBIDataParser::getInstance().parseFile("e:\\KabuSim\\input\\Response20151213_145228_367_0079.data");
//	SBIDataParser::getInstance().exportMasterToFiles("e:\\KabuSim\\output");

}

MainWindow::~MainWindow()
{
    delete ui;
}
