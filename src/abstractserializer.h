#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <QVariant>
#include "serializer_global.h"

class AbstractSerializer
{

public:
    AbstractSerializer();
    virtual ~AbstractSerializer();

    virtual QVariant fromString(const QString &value, const QMetaType::Type &type) const = 0;
    virtual QString toString(const QVariant &value) const = 0;
};

#endif // SERIALIZER_H
