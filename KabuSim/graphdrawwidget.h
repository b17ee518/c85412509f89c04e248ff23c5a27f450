#ifndef GRAPHDRAWWIDGET_H
#define GRAPHDRAWWIDGET_H

#include <QWidget>
#include "TickData.h"

class TickGraphData
{
public:
	TickDataBase data;
	double polinTop = -1;
	double polinBottom = -1;
	double macdVal = -1;
	double macdIndicatorVal = -1;
	double macdVolume = 0;
};

class GraphDrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GraphDrawWidget(QWidget *parent = 0);
    ~GraphDrawWidget();

	void drawByTickData(const MaxTickData& masterData, TickType ttype, int range=-1);

signals:

public slots :
	void onScrollBarValueChanged(int value);
	void onZoomInButtonClicked();
	void onZoomOutButtonClicked();

private:

};

#endif // GRAPHDRAWWIDGET_H
