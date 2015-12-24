#pragma once
#include <QDataStream>
#include <QFile>
#include <QString>
#include <QMap>
#include <QDateTime>
#include "TickData.h"
#include "Defines.h"

enum class ValueDataType
{
	NikkeiHeikin,
	Sakimono,
};

class SBIDataParser
{
public:
	static SBIDataParser& getInstance() {
		static SBIDataParser instance;
		return instance;
	}

private:
	SBIDataParser();
	virtual ~SBIDataParser();
	SBIDataParser(SBIDataParser const&);
	void operator=(SBIDataParser const&);
	
public:
	
	bool parseData(const QByteArray& data);
	bool parseFile(const QString& filename);
	bool parseAllFiles(const QString& path, const QString& filenameBase);

	void addTick(const QDateTime& dt, TickType ttype, const TickDataBase& data, MaxTickData* pMasterData);

	int getMonthCountFromDateTime(const QDateTime& dt);
	int getFiveMinuteCountFromDateTime(const QDateTime& dt);

	bool readFromTableData(const QString& filename, ValueDataType vdt);
	bool readFromAllTableData(const QString& path, const QString& filenameBase, ValueDataType vdt);

	void preHeat(const QDateTime& dtBegin, const QDateTime& dtEnd,  ValueDataType vdt, TickType ttype);

	MaxTickData masterTicks;
	MaxTickData masterNikkeiTicks;

	void exportMasterToFiles(const QString& path);

private:
	QByteArray _remainingChunk;
	int _endIndex = 0;
	int _deadIndex = 0;
	int _dataLength = 0;
	QString _flag;
};