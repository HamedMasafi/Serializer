#ifndef STRINGSERIALIZER_H
#define STRINGSERIALIZER_H

#include "abstractserializer.h"

class StringSerializer : public AbstractSerializer
{
public:
    StringSerializer();

    QVariant fromString(const QString &value, const QMetaType::Type &type);
    QString toString(const QVariant &value);

private:
    QList<int> toListInt(const QString &s);
    QString fromList(const QList<int> &list);

    QList<qreal> toListReal(const QString &s);
    QString fromList(const QList<qreal> &list);
};

#endif // STRINGSERIALIZER_H
