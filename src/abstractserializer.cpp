#include "abstractserializer.h"


AbstractSerializer::AbstractSerializer()
{
}

AbstractSerializer::~AbstractSerializer()
{

}

QVariant AbstractSerializer::deserialize(const QString &value, const QMetaType::Type &type) const
{
    return fromString(unescapeString(value), type);
}

QString AbstractSerializer::serialize(const QVariant &value) const
{
    return escapeString(toString(value));
}

QString AbstractSerializer::escapeString(const QString &str) const
{
    return str;
}

QString AbstractSerializer::unescapeString(const QString &str) const
{
    return str;
}
