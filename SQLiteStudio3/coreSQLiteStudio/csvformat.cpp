#include "csvformat.h"
#include <QtGlobal>

const CsvFormat CsvFormat::DEFAULT = {{","}, {"\r\n", "\n", "\r"}};

CsvFormat::CsvFormat()
{
}

CsvFormat::CsvFormat(const QString& columnSeparator, const QString& rowSeparator) :
    columnSeparator(columnSeparator), rowSeparator(rowSeparator)
{
    calculateSeparatorMaxLengths();
}

CsvFormat::CsvFormat(const QStringList &columnSeparators, const QStringList &rowSeparators)
{
    if (rowSeparators.size() > 1)
    {
        this->rowSeparators = rowSeparators;
        multipleRowSeparators = true;
        strictRowSeparator = true;
    }
    else if (rowSeparators.size() > 0)
        this->rowSeparator = rowSeparators.first();

    if (columnSeparators.size() > 1)
    {
        this->columnSeparators = columnSeparators;
        multipleColumnSeparators = true;
        strictColumnSeparator = true;
    }
    else if (columnSeparators.size() > 0)
        this->columnSeparator = columnSeparators.first();

    calculateSeparatorMaxLengths();
}

CsvFormat::CsvFormat(const QString& columnSeparator, const QString& rowSeparator, bool strictRowSeparator, bool strictColumnSeparator) :
    columnSeparator(columnSeparator), rowSeparator(rowSeparator), strictColumnSeparator(strictColumnSeparator), strictRowSeparator(strictRowSeparator)
{
    calculateSeparatorMaxLengths();
}

void CsvFormat::calculateSeparatorMaxLengths()
{
    maxColumnSeparatorLength = columnSeparator.length();
    for (const QString& sep : columnSeparators)
        maxColumnSeparatorLength = qMax(sep.length(), maxColumnSeparatorLength);

    maxRowSeparatorLength = rowSeparator.length();
    for (const QString& sep : rowSeparators)
        maxRowSeparatorLength = qMax(sep.length(), maxRowSeparatorLength);
}
