#pragma once
#include <QDateTime>
#include <QMap>

enum class TickType
{
	// current
	Millisecond,
	Second,
	// history
	Minute,
	FiveMinutes,
	Day,
	Month,
	Max,
};

class TickDataBase
{
public:
	TickDataBase(){}
	virtual ~TickDataBase(){}

	int beginPrice = -1;
	int endPrice = -1;
	int highPrice = -1;
	int lowPrice = std::numeric_limits<int>::max();
	int amount = 0;

	int largerKey = 0;

	bool operator==(const TickDataBase & other) const;

	virtual void modified(){};

	bool isNull() const;

	void setValues(int begin, int end, int high, int low, int am, int lKey);
	void CopyFromTickDataBase(const TickDataBase& tickdatabase);

	virtual TickDataBase& operator=(const TickDataBase& right)
	{
		beginPrice = right.beginPrice;
		endPrice = right.endPrice;
		highPrice = right.highPrice;
		lowPrice = right.lowPrice;
		amount = right.amount;
		largerKey = right.largerKey;
		return *this;
	}
};

class SecondTickData;
class MinuteTickData;
class FiveMinuteTickData;
class DayTickData;
class MonthTickData;
class MaxTickData;

class TickData : public TickDataBase
{
public:
	void setTickData(int price, int am, SecondTickData* larger, int sec);

	SecondTickData* largerContainer = NULL;
	const int largerKeyMax = 1000;

	virtual TickData& operator=(const TickData& right)
	{
		TickDataBase::operator=(right);
		largerContainer = right.largerContainer;
		return *this;
	}
};

class SecondTickData : public TickDataBase
{
public:
	void addTick(int ms, const TickData& tick);
	QMap<int, TickData> ticks;

	MinuteTickData* largerContainer = NULL;
	const int largerKeyMax = 60;

	virtual SecondTickData& operator=(const SecondTickData& right)
	{
		TickDataBase::operator=(right);
		ticks = right.ticks;
		largerContainer = right.largerContainer;
		return *this;
	}

	TickData& getTickAdditional(int msec);
};

class MinuteTickData : public TickDataBase
{
public:
	QMap<int, SecondTickData> ticks;
	void addSecondTick(int sec, const SecondTickData& tick);

	FiveMinuteTickData* largerContainer = NULL;
	const int largerKeyMax = 5;

	virtual MinuteTickData& operator=(const MinuteTickData& right)
	{
		TickDataBase::operator=(right);
		ticks = right.ticks;
		largerContainer = right.largerContainer;
		return *this;
	}

	SecondTickData& getSecondTickAdditional(int sec);
};

class FiveMinuteTickData : public TickDataBase
{
public:
	QMap<int, MinuteTickData> ticks;
	void addMinuteTick(int min, const MinuteTickData& tick);

	DayTickData* largerContainer = NULL;
	const int largerKeyMax = 288;

	virtual FiveMinuteTickData& operator=(const FiveMinuteTickData& right)
	{
		TickDataBase::operator=(right);
		ticks = right.ticks;
		largerContainer = right.largerContainer;
		return *this;
	}

	MinuteTickData& getMinuteTickAdditional(int min);
};

class DayTickData : public TickDataBase
{
public:
	QMap<int, FiveMinuteTickData> ticks;
	void addFiveMinuteTick(int fivemin, const FiveMinuteTickData& tick);

	MonthTickData* largerContainer = NULL;
	const int largerKeyMax = 31;

	virtual DayTickData& operator=(const DayTickData& right)
	{
		TickDataBase::operator=(right);
		ticks = right.ticks;
		largerContainer = right.largerContainer;
		return *this;
	}

	FiveMinuteTickData& getFiveMinuteTickAdditional(int fivemin);
};

class MonthTickData : public TickDataBase
{
public:
	QMap<int, DayTickData> ticks;
	void addDayTick(int day, const DayTickData& tick);

	MaxTickData* largerContainer = NULL;
	const int largerKeyMax = 10000000;

	virtual MonthTickData& operator=(const MonthTickData& right)
	{
		TickDataBase::operator=(right);
		ticks = right.ticks;
		largerContainer = right.largerContainer;
		return *this;
	}

	DayTickData& getDayTickAdditional(int day);
};

class MaxTickData : public TickDataBase
{
public:
	QMap<int, MonthTickData> ticks;
	void addMonthTick(int month, const MonthTickData& tick);	// month index from 2000
	MonthTickData& getMonthTickAdditional(int month);
};