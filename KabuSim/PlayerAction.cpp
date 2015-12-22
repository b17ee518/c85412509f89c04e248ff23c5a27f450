#include "PlayerAction.h"


PlayerAction::PlayerAction()
{
}

InstantAction::InstantAction(PlayerBase* player, int amount, ExchangeMethod method)
{
	_player = player;
	_price = -1;
	_amount = amount;
	_method = method;
}

void InstantAction::run()
{

}

StandoutAction::StandoutAction(PlayerBase* player, int price, int amount, ExchangeMethod method)
{
	_player = player;
	_price = price;
	_amount = amount;
	_method = method;
}

void StandoutAction::run()
{

}

ChangeStandAction::ChangeStandAction(PlayerBase* player, int price, int amount, ExchangeMethod method)
{
	_player = player;
	_price = price;
	_amount = amount;
	_method = method;
}

void ChangeStandAction::run()
{

}

LeaveBoardAction::LeaveBoardAction(PlayerBase* player, int price, int amount, ExchangeMethod method)
{
	_player = player;
	_price = price;
	_amount = amount;
	_method = method;
}

void LeaveBoardAction::run()
{

}
