#include "SBIDataParser.h"
#include <QDir>
#include <QDirIterator>
#include <QTextStream>

SBIDataParser::SBIDataParser()
{
}


SBIDataParser::~SBIDataParser()
{
}

bool SBIDataParser::parseData(const QByteArray& data)
{
	// data
	if (!data.size())
	{
		return false;
	}
	if (data[0] == 0x00)
	{
		// ended
		return true;
	}
	if (data[0] == 0x02)
	{
		if (data.size() < 0x32)
		{
			return false;
		}
		int dataLength = data.mid(1, 8).toInt();
		if (data.size() < 8+dataLength)
		{
			return false;
		}

		int endIndex = data.indexOf('\03', 8 + dataLength);
		if (endIndex < 0)
		{
			return false;
		}

		QByteArray thisChunk = data.left(endIndex+1);

		bool bRet = false;
		// parse this full chunck

		// DLT/ flag
		QString flag = thisChunk.mid(0x0b, 0x12 - 0x0b);
		if (flag.startsWith("DLT1825"))
		{
			// macro data
			bRet = true;
		}
		else if (flag.startsWith("AL"))
		{
			// ping data
			bRet = true;
		}

		else if (flag.startsWith("DFT1508") || flag.startsWith("DMT1508") || flag.startsWith("DLT1508"))
		{
			bool isFirstPart = flag.startsWith("DFT");
			if (isFirstPart)
			{
				_remainingChunk.clear();
			}
			bool isLastPart = flag.startsWith("DLT");

			int headerSize = 0x014c;
			if (!isFirstPart)
			{
				headerSize = 0x00c9;
			}

			if (data.size() < headerSize)
			{
				return false;
			}
			if (isLastPart)
			{
				thisChunk = thisChunk.left(thisChunk.length() - 0x2c);
			}
			QByteArray rawData = thisChunk.right(thisChunk.length() - headerSize);

			if (_remainingChunk.size())
			{
				rawData = _remainingChunk + rawData;
			}
			while (rawData.size() >= 0x50)
			{
				int amount = rawData.left(0x0d).toInt();
				QString dateTimeStr = rawData.mid(0x0d, 0x13);
				dateTimeStr = dateTimeStr.trimmed();
				// no way to distinguish one min/ five min
				QDateTime dt;

				// begin
				int beginPrice = rawData.mid(0x21, 0x0b).toInt();
				// high
				int highPrice = rawData.mid(0x21 + 0x0b, 0x0b).toInt();
				// low
				int lowPrice = rawData.mid(0x21 + 0x0b * 2, 0x0b).toInt();
				// end
				int endPrice = rawData.mid(0x21 + 0x0b * 3, 0x0b).toInt();

				TickDataBase tickdata;
				tickdata.setValues(beginPrice, endPrice, highPrice, lowPrice, amount, 0);
				if (dateTimeStr.length() == 6)
				{
					// month
					dt = QDateTime::fromString(dateTimeStr, "yyyyMMdd");
					addTick(dt, TickType::Month, tickdata);
				}
				else if (dateTimeStr.length() == 8)
				{
					// day
					dt = QDateTime::fromString(dateTimeStr, "yyyyMMddHH");
					addTick(dt, TickType::Day, tickdata);
				}
				else if (dateTimeStr.length() == 12)
				{
					// minute
					dt = QDateTime::fromString(dateTimeStr, "yyyyMMddHHmm");
					addTick(dt, TickType::Minute, tickdata);
				}
				else if (dateTimeStr.length() == 14)
				{
					// second
					dt = QDateTime::fromString(dateTimeStr, "yyyyMMddHHmmss");
					addTick(dt, TickType::Second, tickdata);
				}
				else if (dateTimeStr.length() >= 16)
				{
					// second
					dt = QDateTime::fromString(dateTimeStr, "yyyyMMddHHmmssfff");
					addTick(dt, TickType::Millisecond, tickdata);
				}

				//
				rawData = rawData.right(rawData.length() - 0x50);
			}
			if (rawData.size())
			{
				_remainingChunk = rawData.left(rawData.length()-1);
				if (_remainingChunk.size() < 4)
				{
					_remainingChunk.clear();
				}
			}
		}

		QByteArray nextChunk = data.right(data.length() - endIndex - 1);
		if (nextChunk.size() >= 0x32)
		{
			return parseData(nextChunk);
		}
		else
		{
			return bRet;
		}
	}
	return false;
}

bool SBIDataParser::parseFile(const QString& filename)
{
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly))
	{
		return false;
	}
	QByteArray data = file.readAll();
	file.close();
	return parseData(data);
}

bool SBIDataParser::parseAllFiles(const QString& path, const QString& filenameBase)
{
	QDirIterator it(path, QStringList() << filenameBase, QDir::Files, QDirIterator::Subdirectories);
	bool bRet = false;
	while (it.hasNext()) {
		if (!parseFile(it.filePath()))
		{
			return false;
		}
		else
		{
			bRet = true;
		}
	}
	return bRet;
}

void SBIDataParser::addTick(const QDateTime& dt, TickType ttype, const TickDataBase& data)
{
	if (ttype == TickType::Max)
	{
		return;
	}
	else if (ttype == TickType::Month)
	{
		int monthCount = getMonthCountFromDateTime(dt);
		MonthTickData monthData = masterTicks.getMonthTickAdditional(monthCount);
		monthData.CopyFromTickDataBase(data);
		masterTicks.addMonthTick(monthCount, monthData);
	}
	else if (ttype == TickType::Day)
	{
		int monthCount = getMonthCountFromDateTime(dt);
		int dayCount = dt.date().day();
		MonthTickData& monthData = masterTicks.getMonthTickAdditional(monthCount);
		DayTickData dayData = monthData.getDayTickAdditional(dayCount);
		dayData.CopyFromTickDataBase(data);
		monthData.addDayTick(dayCount, dayData);
	}
	else if (ttype == TickType::FiveMinutes)
	{
		int monthCount = getMonthCountFromDateTime(dt);
		int dayCount = dt.date().day();
		int fiveminCount = getFiveMinuteCountFromDateTime(dt);
		MonthTickData& monthData = masterTicks.getMonthTickAdditional(monthCount);
		DayTickData& dayData = monthData.getDayTickAdditional(dayCount);
		FiveMinuteTickData fiveminData = dayData.getFiveMinuteTickAdditional(fiveminCount);
		fiveminData.CopyFromTickDataBase(data);
		dayData.addFiveMinuteTick(fiveminCount, fiveminData);
	}
	else if (ttype == TickType::Minute)
	{
		int monthCount = getMonthCountFromDateTime(dt);
		int dayCount = dt.date().day();
		int fiveminCount = getFiveMinuteCountFromDateTime(dt);
		int minCount = dt.time().minute() % 5;
		MonthTickData& monthData = masterTicks.getMonthTickAdditional(monthCount);
		DayTickData& dayData = monthData.getDayTickAdditional(dayCount);
		FiveMinuteTickData& fiveminData = dayData.getFiveMinuteTickAdditional(fiveminCount);
		MinuteTickData minData = fiveminData.getMinuteTickAdditional(minCount);
		minData.CopyFromTickDataBase(data);
		fiveminData.addMinuteTick(minCount, minData);
	}
	else if (ttype == TickType::Second)
	{
		int monthCount = getMonthCountFromDateTime(dt);
		int dayCount = dt.date().day();
		int fiveminCount = getFiveMinuteCountFromDateTime(dt);
		int minCount = dt.time().minute() % 5;
		int secondCount = dt.time().second();
		MonthTickData& monthData = masterTicks.getMonthTickAdditional(monthCount);
		DayTickData& dayData = monthData.getDayTickAdditional(dayCount);
		FiveMinuteTickData& fiveminData = dayData.getFiveMinuteTickAdditional(fiveminCount);
		MinuteTickData& minData = fiveminData.getMinuteTickAdditional(minCount);
		SecondTickData secData = minData.getSecondTickAdditional(secondCount);
		secData.CopyFromTickDataBase(data);
		minData.addSecondTick(secondCount, secData);
	}
	else if (ttype == TickType::Millisecond)
	{
		int monthCount = getMonthCountFromDateTime(dt);
		int dayCount = dt.date().day();
		int fiveminCount = getFiveMinuteCountFromDateTime(dt);
		int minCount = dt.time().minute() % 5;
		int secondCount = dt.time().second();
		int msCount = dt.time().msec();
		MonthTickData& monthData = masterTicks.getMonthTickAdditional(monthCount);
		DayTickData& dayData = monthData.getDayTickAdditional(dayCount);
		FiveMinuteTickData& fiveminData = dayData.getFiveMinuteTickAdditional(fiveminCount);
		MinuteTickData& minData = fiveminData.getMinuteTickAdditional(minCount);
		SecondTickData& secData = minData.getSecondTickAdditional(secondCount);
		TickData tickData = secData.getTickAdditional(msCount);
		tickData.CopyFromTickDataBase(data);
		secData.addTick(msCount, tickData);
	}

}

int SBIDataParser::getMonthCountFromDateTime(const QDateTime& dt)
{
	int year = dt.toString("yyyy").toInt();
	int month = dt.toString("MM").toInt();
	int diffMonth = (year - 2000) * 12 + month;
	if (diffMonth > 0)
	{
		return diffMonth;
	}
	return 0;
}

int SBIDataParser::getFiveMinuteCountFromDateTime(const QDateTime& dt)
{
	int hour = dt.time().hour();
	int minute = dt.time().minute();
	int fivemin = (hour * 60 + minute) / 5;
	if (fivemin > 0)
	{
		return fivemin;
	}
	return 0;
}

void SBIDataParser::exportMasterToFiles(const QString& path)
{
	QDateTime ct = QDateTime::currentDateTime();
	QFile monthFile(path + "/" + ct.toString("yyyyMMdd_HHmmss") + "_month.table");
	QFile dayFile(path + "/" + ct.toString("yyyyMMdd_HHmmss") + "_day.table");
	QFile fiveminFile(path + "/" + ct.toString("yyyyMMdd_HHmmss") + "_fivemin.table");
	QFile minFile(path + "/" + ct.toString("yyyyMMdd_HHmmss") + "_min.table");
	QFile secFile(path + "/" + ct.toString("yyyyMMdd_HHmmss") + "_sec.table");

	if (!monthFile.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		return;
	}
	if (!dayFile.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		return;
	}
	if (!fiveminFile.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		return;
	}
	if (!minFile.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		return;
	}
	if (!secFile.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		return;
	}

	QTextStream monthStream(&monthFile);
	QTextStream dayStream(&dayFile);
	QTextStream fiveminStream(&fiveminFile);
	QTextStream minStream(&minFile);
	QTextStream secStream(&secFile);

	QString titleStr = "-\tDateTime\tBegin\tHigh\tLow\tEnd\tAmount";
	monthStream << titleStr
		<< endl;
	dayStream << titleStr
		<< endl;
	fiveminStream << titleStr
		<< endl;
	minStream << titleStr
		<< endl;
	secStream << titleStr
		<< endl;

	QDateTime dt;
	QDate date;
	QTime time;
	Q_FOREACH(auto& month, masterTicks.ticks)
	{
		int MMcount = month.largerKey-1 + 2000 * 12;
		int yyyy = MMcount / 12;
		int MM = MMcount % 12 + 1;
		date.setDate(yyyy, MM, 1);
		monthStream 
			<< "-\t"
			<< date.toString("yyyy/MM")
			<< "\t"
			<< month.beginPrice
			<< "\t"
			<< month.highPrice
			<< "\t"
			<< month.lowPrice
			<< "\t"
			<< month.endPrice
			<< "\t"
			<< month.amount
			<< endl;

		Q_FOREACH(auto& day, month.ticks)
		{
			int dd = day.largerKey;
			date.setDate(yyyy, MM, dd);
			dayStream
				<< "-\t"
				<< date.toString("yyyy/MM/dd")
				<< "\t"
				<< day.beginPrice
				<< "\t"
				<< day.highPrice
				<< "\t"
				<< day.lowPrice
				<< "\t"
				<< day.endPrice
				<< "\t"
				<< day.amount
				<< endl;
			Q_FOREACH(auto& fivemin, day.ticks)
			{
				int mmfive = fivemin.largerKey * 5;
				int HH = mmfive / 60;
				dt.setDate(date);
				time.setHMS(HH, mmfive%60, 0);
				dt.setTime(time);
				fiveminStream
					<< "-\t"
					<< dt.toString("yyyy/MM/dd HH:mm")
					<< "\t"
					<< fivemin.beginPrice
					<< "\t"
					<< fivemin.highPrice
					<< "\t"
					<< fivemin.lowPrice
					<< "\t"
					<< fivemin.endPrice
					<< "\t"
					<< fivemin.amount
					<< endl;
				Q_FOREACH(auto& min, fivemin.ticks)
				{
					int mm = (mmfive + min.largerKey)%60;
					time.setHMS(HH, mm, 0);
					dt.setTime(time);
					minStream
						<< "-\t"
						<< dt.toString("yyyy/MM/dd HH:mm")
						<< "\t"
						<< min.beginPrice
						<< "\t"
						<< min.highPrice
						<< "\t"
						<< min.lowPrice
						<< "\t"
						<< min.endPrice
						<< "\t"
						<< min.amount
						<< endl;
					Q_FOREACH(auto& sec, min.ticks)
					{
						int ss = sec.largerKey;
						time.setHMS(HH, mm, ss);
						dt.setTime(time);
						secStream
							<< "-\t"
							<< dt.toString("yyyy/MM/dd HH:mm:ss")
							<< "\t"
							<< sec.beginPrice
							<< "\t"
							<< sec.highPrice
							<< "\t"
							<< sec.lowPrice
							<< "\t"
							<< sec.endPrice
							<< "\t"
							<< sec.amount
							<< endl;
					}
				}
			}
		}
	}

	minFile.close();
	dayFile.close();
	fiveminFile.close();
	minFile.close();
	secFile.close();
}

