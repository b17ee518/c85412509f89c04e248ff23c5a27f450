#include "BoardData.h"


BoardData::BoardData()
{
}


BoardData::~BoardData()
{
}

int BoardItem::getAmount()
{
	int totalAmount = 0;
	for (auto item : holders)
	{
		totalAmount += item.amount;
	}
	return totalAmount;
}

int BoardData::getMarginPrice(BoardSide side)
{
	switch (side)
	{
	case BoardSide::Buy:
		break;
	case BoardSide::Sell:
		break;
	}
	return 0;
}

void BoardData::adjust()
{

}
