#ifndef SQLSERIALIZZER_H
#define SQLSERIALIZZER_H

#include "stringserializer.h"

class SqlSerializer : public StringSerializer
{
public:
    SqlSerializer();

//private:
//    QString escapeString(const QString &str) const override;
//    QString unescapeString(const QString &str) const override;

//public:
//    QVariant escapeSql(const QString &value) const;
//    QString unescapeSql(const QString &value) const;

//    // AbstractSerializer interface
public:
    QVariant deserialize(const QString &value, const QMetaType::Type &type) const override;
    QString serialize(const QVariant &value) const override;
};

#endif // SQLSERIALIZZER_H
