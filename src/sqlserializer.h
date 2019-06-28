#ifndef SQLSERIALIZZER_H
#define SQLSERIALIZZER_H

#include "stringserializer.h"

class SqlSerializer : public StringSerializer
{
public:
    SqlSerializer();

public:
    QVariant deserialize(const QString &value, const QMetaType::Type &type) const override;
    QString serialize(const QVariant &value) const override;
};

#endif // SQLSERIALIZZER_H
