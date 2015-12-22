#pragma once
#include "Defines.h"

class PlayerBase;

class PlayerAction
{
public:
	PlayerAction();
	~PlayerAction() {};

	virtual void run() {};

protected:
	FW_SYNTHESIZE_WITHINIT(int, _price, Price, 0);
	FW_SYNTHESIZE_WITHINIT(ExchangeMethod, _method, Method, ExchangeMethod::BuyNew);
	FW_SYNTHESIZE_WITHINIT(int, _amount, Amount, 0);

	FW_SYNTHESIZE_WITHINIT(PlayerBase*, _player, Player, NULL);
};

class SleepAction : public PlayerAction
{
public:
	SleepAction(PlayerBase* player) {};
	virtual ~SleepAction();
};

class InstantAction : public PlayerAction
{
public:
	InstantAction(PlayerBase* player, int amount, ExchangeMethod method);
	virtual ~InstantAction() {};

	virtual void run() override;
};

class StandoutAction : public PlayerAction
{
public:
	StandoutAction(PlayerBase* player, int price, int amount, ExchangeMethod method);
	virtual ~StandoutAction() {};

	virtual void run() override;
};

class ChangeStandAction : public PlayerAction
{
	ChangeStandAction(PlayerBase* player, int price, int amount, ExchangeMethod method);
	virtual ~ChangeStandAction() {};

	virtual void run() override;
};

class LeaveBoardAction : public PlayerAction
{
	LeaveBoardAction(PlayerBase* player, int price, int amount, ExchangeMethod method);
	virtual ~LeaveBoardAction() {};

	virtual void run() override;
};