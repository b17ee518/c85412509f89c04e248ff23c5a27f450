#include "TickData.h"

bool TickDataBase::operator==(const TickDataBase & other) const
{
	if (lowPrice == other.lowPrice
		&& highPrice == other.highPrice
		&& beginPrice == other.beginPrice
		&& endPrice == other.endPrice
		&& amount == other.amount
		&& largerKey == other.largerKey)
	{
		return true;
	}
	return false;
}

bool TickDataBase::isNull() const
{
	if (lowPrice >= 0 && lowPrice < std::numeric_limits<int>::max() && highPrice >= 0 && beginPrice >= 0 && endPrice >= 0 && amount >= 0 && largerKey >= 0)
	{
		return false;
	}
	return true;
}

void TickDataBase::setValues(int begin, int end, int high, int low, int am, int lKey)
{
	lowPrice = low;
	highPrice = high;
	beginPrice = begin;
	endPrice = end;
	amount = am;

	largerKey = lKey;
}

void TickDataBase::CopyFromTickDataBase(const TickDataBase& tickdatabase)
{
	setValues(tickdatabase.beginPrice, tickdatabase.endPrice, tickdatabase.highPrice, tickdatabase.lowPrice, tickdatabase.amount, tickdatabase.largerKey);
}

void TickData::setTickData(int price, int am, SecondTickData* larger, int sec)
{
	lowPrice = price;
	highPrice = price;
	beginPrice = price;
	endPrice = price;
	amount = am;

	largerContainer = larger;
	largerKey = sec;
}

void SecondTickData::addTick(int t, const TickData& tick)
{
	if (t >= tick.largerKeyMax)
	{
		return;
	}
	auto it = ticks.find(t);
	if (it == ticks.end() || !(it.value() == tick) || it.value().isNull())
	{
		ticks.insert(t, tick);
		auto& v = ticks[t];
		v.largerContainer = this;
		v.largerKey = t;
		// update this and modify larger

		bool bBeginSet = false;
		this->amount = 0;
		Q_FOREACH(auto& jt, ticks)
		{
			if (jt.isNull())
			{
				continue;
			}
			if (!bBeginSet)
			{
				this->beginPrice = jt.beginPrice;
				bBeginSet = true;
			}
			if (this->lowPrice > jt.lowPrice)
			{
				this->lowPrice = jt.lowPrice;
			}
			if (this->highPrice < jt.highPrice)
			{
				this->highPrice = jt.highPrice;
			}
			this->endPrice = jt.endPrice;
			this->amount += jt.amount;
		}

		if (largerContainer)
		{
			largerContainer->addSecondTick(largerKey, *this);
		}
	}
}

TickData& SecondTickData::getTickAdditional(int t)
{
	auto it = ticks.find(t);
	if (it == ticks.end())
	{
		TickData data;
		addTick(t, data);
	}
	return ticks[t];

}

void MinuteTickData::addSecondTick(int t, const SecondTickData& tick)
{
	if (t >= tick.largerKeyMax)
	{
		return;
	}
	auto it = ticks.find(t);
	if (it == ticks.end() || !(it.value() == tick) || it.value().isNull())
	{
		ticks.insert(t, tick);
		auto& v = ticks[t];
		v.largerContainer = this;
		v.largerKey = t;
		// update this and modify larger

		bool bBeginSet = false;
		this->amount = 0;
		Q_FOREACH(auto& jt, ticks)
		{
			if (jt.isNull())
			{
				continue;
			}
			if (!bBeginSet)
			{
				this->beginPrice = jt.beginPrice;
				bBeginSet = true;
			}
			if (this->lowPrice > jt.lowPrice)
			{
				this->lowPrice = jt.lowPrice;
			}
			if (this->highPrice < jt.highPrice)
			{
				this->highPrice = jt.highPrice;
			}
			this->endPrice = jt.endPrice;
			this->amount += jt.amount;
		}

		if (largerContainer)
		{
			largerContainer->addMinuteTick(largerKey, *this);
		}
	}
}

SecondTickData& MinuteTickData::getSecondTickAdditional(int t)
{
	auto it = ticks.find(t);
	if (it == ticks.end())
	{
		SecondTickData data;
		addSecondTick(t, data);
	}
	return ticks[t];

}

void FiveMinuteTickData::addMinuteTick(int t, const MinuteTickData& tick)
{
	if (t >= tick.largerKeyMax)
	{
		return;
	}
	auto it = ticks.find(t);
	if (it == ticks.end() || !(it.value() == tick) || it.value().isNull())
	{
		ticks.insert(t, tick);
		auto& v = ticks[t];
		v.largerContainer = this;
		v.largerKey = t;
		// update this and modify larger

		bool bBeginSet = false;
		this->amount = 0;
		Q_FOREACH(auto& jt, ticks)
		{
			if (jt.isNull())
			{
				continue;
			}
			if (!bBeginSet)
			{
				this->beginPrice = jt.beginPrice;
				bBeginSet = true;
			}
			if (this->lowPrice > jt.lowPrice)
			{
				this->lowPrice = jt.lowPrice;
			}
			if (this->highPrice < jt.highPrice)
			{
				this->highPrice = jt.highPrice;
			}
			this->endPrice = jt.endPrice;
			this->amount += jt.amount;
		}

		if (largerContainer)
		{
			largerContainer->addFiveMinuteTick(largerKey, *this);
		}
	}

}

MinuteTickData& FiveMinuteTickData::getMinuteTickAdditional(int t)
{
	auto it = ticks.find(t);
	if (it == ticks.end())
	{
		MinuteTickData data;
		addMinuteTick(t, data);
	}
	return ticks[t];

}

void DayTickData::addFiveMinuteTick(int t, const FiveMinuteTickData& tick)
{
	if (t >= tick.largerKeyMax)
	{
		return;
	}
	auto it = ticks.find(t);
	if (it == ticks.end() || !(it.value() == tick) || it.value().isNull())
	{
		ticks.insert(t, tick);
		auto& v = ticks[t];
		v.largerContainer = this;
		v.largerKey = t;
		// update this and modify larger

		bool bBeginSet = false;
		this->amount = 0;
		Q_FOREACH(auto& jt, ticks)
		{
			if (jt.isNull())
			{
				continue;
			}
			if (!bBeginSet)
			{
				this->beginPrice = jt.beginPrice;
				bBeginSet = true;
			}
			if (this->lowPrice > jt.lowPrice)
			{
				this->lowPrice = jt.lowPrice;
			}
			if (this->highPrice < jt.highPrice)
			{
				this->highPrice = jt.highPrice;
			}
			this->endPrice = jt.endPrice;
			this->amount += jt.amount;
		}

		if (largerContainer)
		{
			largerContainer->addDayTick(largerKey, *this);
		}
	}

}

FiveMinuteTickData& DayTickData::getFiveMinuteTickAdditional(int t)
{
	auto it = ticks.find(t);
	if (it == ticks.end())
	{
		FiveMinuteTickData data;
		addFiveMinuteTick(t, data);
	}
	return ticks[t];
}

void MonthTickData::addDayTick(int t, const DayTickData& tick)
{
	if (t >= tick.largerKeyMax)
	{
		return;
	}
	auto it = ticks.find(t);
	if (it == ticks.end() || !(it.value() == tick) || it.value().isNull())
	{
		ticks.insert(t, tick);
		auto& v = ticks[t];
		v.largerContainer = this;
		v.largerKey = t;
		// update this and modify larger

		bool bBeginSet = false;
		this->amount = 0;
		Q_FOREACH(auto& jt, ticks)
		{
			if (jt.isNull())
			{
				continue;
			}
			if (!bBeginSet)
			{
				this->beginPrice = jt.beginPrice;
				bBeginSet = true;
			}
			if (this->lowPrice > jt.lowPrice)
			{
				this->lowPrice = jt.lowPrice;
			}
			if (this->highPrice < jt.highPrice)
			{
				this->highPrice = jt.highPrice;
			}
			this->endPrice = jt.endPrice;
			this->amount += jt.amount;
		}

		if (largerContainer)
		{
			largerContainer->addMonthTick(largerKey, *this);
		}
	}
}

DayTickData& MonthTickData::getDayTickAdditional(int t)
{
	auto it = ticks.find(t);
	if (it == ticks.end())
	{
		DayTickData data;
		addDayTick(t, data);
	}
	return ticks[t];

}

void MaxTickData::addMonthTick(int t, const MonthTickData& tick)
{
	if (t >= tick.largerKeyMax)
	{
		return;
	}
	auto it = ticks.find(t);
	if (it == ticks.end() || !(it.value() == tick) || it.value().isNull())
	{
		ticks.insert(t, tick);
		auto& v = ticks[t];
		v.largerContainer = this;
		v.largerKey = t;
		// update this and modify larger

		bool bBeginSet = false;
		this->amount = 0;
		Q_FOREACH(auto& jt, ticks)
		{
			if (jt.isNull())
			{
				continue;
			}
			if (!bBeginSet)
			{
				this->beginPrice = jt.beginPrice;
				bBeginSet = true;
			}
			if (this->lowPrice > jt.lowPrice)
			{
				this->lowPrice = jt.lowPrice;
			}
			if (this->highPrice < jt.highPrice)
			{
				this->highPrice = jt.highPrice;
			}
			this->endPrice = jt.endPrice;
			this->amount += jt.amount;
		}
	}

}

MonthTickData& MaxTickData::getMonthTickAdditional(int t)
{
	auto it = ticks.find(t);
	if (it == ticks.end())
	{
		MonthTickData data;
		addMonthTick(t, data);
	}
	return ticks[t];
}
