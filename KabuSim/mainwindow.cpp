#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "SBIDataParser.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	//	SBIDataParser::getInstance().parseFile("e:\\KabuSim\\c85412509f89c04e248ff23c5a27f450\\input\\Response20151220_210512_342_0120.data");
	//	SBIDataParser::getInstance().parseFile("e:\\KabuSim\\c85412509f89c04e248ff23c5a27f450\\input\\Response20151220_210548_212_0130.data");
	SBIDataParser::getInstance().parseAllFiles("e:\\KabuSim\\c85412509f89c04e248ff23c5a27f450\\input\\", "Response*");
	SBIDataParser::getInstance().exportMasterToFiles("e:\\KabuSim\\c85412509f89c04e248ff23c5a27f450\\output");

}

MainWindow::~MainWindow()
{
    delete ui;
}
