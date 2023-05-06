#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <QtCore/QVariant>
#include "serializer_global.h"

class AbstractSerializer
{

public:
    AbstractSerializer() = default;
    virtual ~AbstractSerializer() = default;
    virtual QVariant deserialize(const QString &value, const QMetaType::Type &type) const;
    virtual QString serialize(const QVariant &value) const;

private:
    virtual QString escapeString(const QString &str) const;
    virtual QString unescapeString(const QString &str) const;
    virtual QVariant fromString(const QString &value, const QMetaType::Type &type) const = 0;
    virtual QString toString(const QVariant &value) const = 0;
};


class AbstractSerializer2
{
protected:
    void begin(const QString &data);
    QVariant read(QMetaType::Type type);
};

#endif // SERIALIZER_H
