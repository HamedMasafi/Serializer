#include "stringserializer.h"

#include <QUuid>
#include <QPoint>
#include <QPointF>
#include <QSizeF>
#include <QSize>
#include <QRect>
#include <QRectF>
#include <QDate>
#include <QTime>
#include <QDateTime>
#include <QDebug>

#define DATE_FORMAT "yyyy-MM-dd"
#define TIME_FORMAT "HH-mm-ss.zzz"
StringSerializer::StringSerializer()
{

}

QVariant StringSerializer::fromString(const QString &value, const QMetaType::Type &type)
{
    switch (type) {
    case QMetaType::Int:        return value.toInt();
    case QMetaType::Short:      return value.toShort();
    case QMetaType::Long:       return qVariantFromValue(value.toLong());
    case QMetaType::LongLong:   return value.toLongLong();
    case QMetaType::Float:      return value.toFloat();
    case QMetaType::Double:     return value.toDouble();
    case QMetaType::QString:
        return value;

    case QMetaType::QDate:
        return QDate::fromString(value, DATE_FORMAT);

    case QMetaType::QTime:
        return QTime::fromString(value, TIME_FORMAT);

    case QMetaType::QDateTime:
        return QDateTime::fromString(value, DATE_FORMAT " " TIME_FORMAT);

    case QMetaType::QPoint: {
        QList<int> parts = toListInt(value);
        if (parts.size() != 2)
            return QPoint();

        return QPoint(parts.at(0), parts.at(1));
    }
    case QMetaType::QSize: {
        QList<int> parts = toListInt(value);
        if (parts.size() != 2)
            return QSize();

        return QSize(parts.at(0), parts.at(1));
    }
    case QMetaType::QRect: {
        QList<int> parts = toListInt(value);
        if (parts.size() != 4)
            return QRect();

        return QRect(parts.at(0), parts.at(1), parts.at(2), parts.at(3));
    }
    case QMetaType::QPointF: {
        QList<qreal> parts = toListReal(value);
        if (parts.size() != 2)
            return QPointF();

        return QPointF(parts.at(0), parts.at(1));
    }
    case QMetaType::QSizeF: {
        QList<qreal> parts = toListReal(value);
        if (parts.size() != 2)
            return QSizeF();

        return QSizeF(parts.at(0), parts.at(1));
    }
    case QMetaType::QRectF: {
        QList<qreal> parts = toListReal(value);
        if (parts.size() != 4)
            return QRectF();

        return QRectF(parts.at(0), parts.at(1), parts.at(2), parts.at(3));
    }
    }
}

QString StringSerializer::toString(const QVariant &value)
{
    QMetaType::Type type = static_cast<QMetaType::Type>(value.type());
    switch (type) {
    case QMetaType::Bool:
    case QMetaType::Char:
    case QMetaType::UChar:
    case QMetaType::Short:
    case QMetaType::UShort:
    case QMetaType::Int:
    case QMetaType::UInt:
    case QMetaType::Long:
    case QMetaType::ULong:
    case QMetaType::LongLong:
    case QMetaType::ULongLong:
    case QMetaType::Double:
    case QMetaType::Float:
    case QMetaType::SChar:
    case QMetaType::QChar:
    case QMetaType::QUrl:
    case QMetaType::QString:
        return value.toString();

    case QMetaType::QUuid:
        return value.toUuid().toString();

    case QMetaType::QByteArray:
        return QString(value.toByteArray());

    case QMetaType::QDate:          return value.toDate().toString(DATE_FORMAT);
    case QMetaType::QTime:          return value.toTime().toString(TIME_FORMAT);
    case QMetaType::QDateTime:      return value.toDateTime().toString(DATE_FORMAT " " TIME_FORMAT);

    case QMetaType::QPoint: {
        QPoint pt = value.toPoint();
        return fromList(QList<int>() << pt.x() << pt.y());
    }
    case QMetaType::QSize: {
        QSize pt = value.toSize();
        return fromList(QList<int>() << pt.width() << pt.height());
    }
    case QMetaType::QRect: {
        QRect rc = value.toRect();
        return fromList(QList<int>() << rc.x() << rc.y() << rc.width() << rc.height());
    }
    case QMetaType::QPointF: {
        QPointF pt = value.toPointF();
        return fromList(QList<qreal>() << pt.x() << pt.y());
    }
    case QMetaType::QSizeF: {
        QSizeF pt = value.toSizeF();
        return fromList(QList<qreal>() << pt.width() << pt.height());
    }
    case QMetaType::QRectF: {
        QRectF rc = value.toRectF();
        return fromList(QList<qreal>() << rc.x() << rc.y() << rc.width() << rc.height());
    }

    case QMetaType::QJsonArray:
    case QMetaType::QJsonValue:
    case QMetaType::QJsonObject:
    case QMetaType::QJsonDocument:
    default:
        qWarning("The type (%s) does not supported",
                 QMetaType::typeName(type));
        return QString();
    }
}

QList<int> StringSerializer::toListInt(const QString &s){
    auto parts = s.split(",");
    QList<int> ret;
    foreach (QString p, parts) {
        bool ok;
        ret.append(p.toInt(&ok));
        if (!ok)
            return ret;
    }

    return ret;
}

QString StringSerializer::fromList(const QList<int> &list)
{
    QString ret;
    foreach (int n, list) {
        if (!ret.isEmpty())
            ret.append(",");
        ret.append(QString::number(n));
    }
    return ret;
}

QList<qreal> StringSerializer::toListReal(const QString &s)
{
    auto parts = s.split(",");
    QList<qreal> ret;
    foreach (QString p, parts) {
        bool ok;
        ret.append(p.toDouble(&ok));
        if (!ok)
            return ret;
    }

    return ret;
}

QString StringSerializer::fromList(const QList<qreal> &list)
{
    QString ret;
    foreach (qreal n, list) {
        if (!ret.isEmpty())
            ret.append(",");
        ret.append(QString::number(n));
    }
    return ret;
}
