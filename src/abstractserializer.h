#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <QVariant>
#include "serializer_global.h"

class SERIALIZERSHARED_EXPORT AbstractSerializer
{

public:
    AbstractSerializer();

    virtual QVariant fromString(const QString &value, const QMetaType::Type &type) = 0;
    virtual QString toString(const QVariant &value) = 0;
};

#endif // SERIALIZER_H
