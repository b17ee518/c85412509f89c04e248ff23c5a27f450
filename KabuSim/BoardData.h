#pragma once
#include "Defines.h"
#include <QList>

class PlayerBase;

class HoldingBoardInfo
{
public:
	int amount;
	PlayerBase* player;
};

class BoardItem
{
public:
	int price;
	QList<HoldingBoardInfo> holders;

	int getAmount();
};

class BoardData
{
public:
	BoardData();
	~BoardData();

	int getMarginPrice(BoardSide side);
	void adjust();

	QList<BoardItem> sellers;
	QList<BoardItem> buyers;
};

