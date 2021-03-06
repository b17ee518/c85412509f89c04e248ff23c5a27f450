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
//	SBIDataParser::getInstance().parseAllFiles("e:\\KabuSim\\c85412509f89c04e248ff23c5a27f450\\input\\", "Response*");
	//	SBIDataParser::getInstance().exportMasterToFiles("e:\\KabuSim\\c85412509f89c04e248ff23c5a27f450\\output");
	QString path = QCoreApplication::applicationDirPath() + "/";
	SBIDataParser::getInstance().readFromTableData(path + "../../input/ns2014_1min_partial.table", ValueDataType::Sakimono);
	SBIDataParser::getInstance().readFromTableData(path + "../../input/n2014_5min_partial.table", ValueDataType::NikkeiHeikin);
	SBIDataParser::getInstance().masterTicks.CalculateMACD();
	SBIDataParser::getInstance().exportMasterToFiles(path + "../../output");
}

MainWindow::~MainWindow()
{
    delete ui;
}
