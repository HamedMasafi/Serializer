#ifndef SQLSERIALIZZER_H
#define SQLSERIALIZZER_H

#include "stringserializer.h"

class SqlSerializer : public StringSerializer
{
public:
    SqlSerializer();

public:
    QString unescapeString(const QString &str) const override;
    QString escapeString(const QString &str) const override;
};

#endif // SQLSERIALIZZER_H
