#include "binaryserializer.h"

#include <QtCore/QMetaType>
#include <QtCore/QDataStream>
#include <QtCore/QJsonDocument>
#include <QtCore/QDebug>

QDataStream &operator<<(QDataStream &stream, const QJsonDocument &doc)
{
    stream << doc.toJson();
    return stream;
}

QDataStream &operator>>(QDataStream &stream, QJsonDocument &doc)
{
    QByteArray buffer;
    stream << buffer;
    doc = QJsonDocument::fromJson(buffer);
    return stream;
}

BinarySerializer::BinarySerializer() : AbstractSerializer ()
{

}

QVariant BinarySerializer::fromString(const QString &value, const QMetaType::Type &type) const
{
    QVariant copy;
    QVariant v;
    QByteArray data = QByteArray::fromBase64(value.toLocal8Bit());
    QDataStream ds(&data,QIODevice::ReadOnly);
    ds >> v;

    if (type == QMetaType::QJsonDocument)
        return QVariant(QJsonDocument::fromJson(v.toByteArray()));

    return v;
}

QString BinarySerializer::toString(const QVariant &value) const
{
    QVariant copy;
    auto type = static_cast<QMetaType::Type>(value.type());
    switch (type) {
    case QMetaType::QJsonDocument:
        copy = value.value<QJsonDocument>().toJson();
        break;

    default:
        copy = value;
    }

    QByteArray data;
    QDataStream ds(&data, QIODevice::WriteOnly);
    ds << copy;
    return QString::fromUtf8(data.toBase64());
}
