#include "graphdrawwidget.h"

GraphDrawWidget::GraphDrawWidget(QWidget *parent) : QWidget(parent)
{

}

GraphDrawWidget::~GraphDrawWidget()
{

}

void GraphDrawWidget::drawByTickData(const MaxTickData& masterData, TickType ttype, int range/*=-1*/)
{
	if (ttype == TickType::FiveMinutes)
	{
		if (range < 0)
		{
			range = 3; // 3 days
		}

	}
}

void GraphDrawWidget::onScrollBarValueChanged(int value)
{

}

void GraphDrawWidget::onZoomInButtonClicked()
{

}

void GraphDrawWidget::onZoomOutButtonClicked()
{

}

