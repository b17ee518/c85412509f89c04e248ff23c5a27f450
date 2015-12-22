#pragma once
#include <QDataStream>
#include <QFile>
#include <QString>
#include <QMap>
#include <QDateTime>
#include "TickData.h"
#include "Defines.h"

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

	void addTick(const QDateTime& dt, TickType ttype, const TickDataBase& data);

	int getMonthCountFromDateTime(const QDateTime& dt);
	int getFiveMinuteCountFromDateTime(const QDateTime& dt);

	MaxTickData masterTicks;

	void exportMasterToFiles(const QString& path);

private:
	QByteArray _remainingChunk;
};