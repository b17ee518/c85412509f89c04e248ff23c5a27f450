#pragma once
#include "Defines.h"

class MarketManager
{
public:
	static MarketManager& getInstance() {
		static MarketManager instance;
		return instance;
	}

private:
	MarketManager();
	virtual ~MarketManager();
	MarketManager(MarketManager const&);
	void operator=(MarketManager const&);
	
public:
	
};
