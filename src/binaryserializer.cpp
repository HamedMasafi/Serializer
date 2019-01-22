#include "binaryserializer.h"

#include <QDataStream>
#include <QJsonDocument>
#include <QDebug>

QDataStream &operator<<(QDataStream &stream, const QJsonDocument &doc)
{
    qDebug() << "<<" << doc;
    stream << doc.toJson();
    return stream;
}

QDataStream &operator>>(QDataStream &stream, QJsonDocument &doc)
{
    qDebug() << ">>" << doc;
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
    Q_UNUSED(type);
    QVariant v;
    QByteArray data = QByteArray::fromBase64(value.toLocal8Bit());
    QDataStream ds(&data,QIODevice::ReadOnly);
    ds >> v;
    return v;
}

QString BinarySerializer::toString(const QVariant &value) const
{
    QByteArray data;
    QDataStream ds(&data, QIODevice::WriteOnly);
    ds << value;
    return QString(data.toBase64());
}
