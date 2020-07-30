#ifndef BINARYSERIALIZER_H
#define BINARYSERIALIZER_H

#include "abstractserializer.h"
#include <QtCore/QJsonDocument>
#include <QtCore/QDebug>

class BinarySerializer : public AbstractSerializer
{
public:
    BinarySerializer();

    QVariant fromString(const QString &value, const QMetaType::Type &type) const;
    QString toString(const QVariant &value) const;
};


QDataStream &operator<<(QDataStream &stream, const QJsonDocument &doc);
QDataStream &operator>>(QDataStream &stream, QJsonDocument &doc);

Q_DECLARE_METATYPE(QJsonDocument)

#endif // BINARYSERIALIZER_H
