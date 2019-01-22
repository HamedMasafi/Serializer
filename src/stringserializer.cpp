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
#include <QUrl>
#include <QLineF>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QBitArray>
#include <QBuffer>

#ifdef QT_GUI_LIB
#include <QtGui/QFont>
#include <QtGui/QPolygon>
#include <QtGui/QPolygonF>
#include <QtGui/QColor>
#include <QtGui/QImage>
#endif

#define DATE_FORMAT "yyyy-MM-dd"
#define TIME_FORMAT "HH-mm-ss.zzz"
StringSerializer::StringSerializer()
{

}

QVariant StringSerializer::fromString(const QString &value, const QMetaType::Type &type) const
{
    switch (type) {
    case QMetaType::Char:
    case QMetaType::Int:        return value.toInt();
    case QMetaType::SChar:
    case QMetaType::UInt:       return value.toUInt();
    case QMetaType::Short:      return value.toShort();
    case QMetaType::UShort:     return value.toUShort();
    case QMetaType::Long:       return qVariantFromValue(value.toLong());
    case QMetaType::ULong:      return qVariantFromValue(value.toULong());
    case QMetaType::LongLong:   return value.toLongLong();
    case QMetaType::ULongLong:  return qVariantFromValue(value.toULongLong());
    case QMetaType::Float:      return value.toFloat();
    case QMetaType::Double:     return value.toDouble();
    case QMetaType::QString:    return value;
    case QMetaType::QDate:      return QDate::fromString(value, DATE_FORMAT);
    case QMetaType::QTime:      return QTime::fromString(value, TIME_FORMAT);
    case QMetaType::QDateTime:  return QDateTime::fromString(value, DATE_FORMAT " " TIME_FORMAT);
    case QMetaType::QUrl:       return QUrl(value);
    case QMetaType::QChar:      return value.at(0);
    case QMetaType::QStringList: {
        int pos = value.indexOf(" ");
        QList<int> lens = toListInt(value.left(pos));
        QStringList ret;
        pos++;
        foreach (int n, lens) {
            ret.append(value.mid(pos, n));
            pos += n;
        }
        return ret;
    }

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
    case QMetaType::QLine: {
        QList<int> parts = toListInt(value);
        if (parts.size() != 4)
            return QLine();

        return QLine(parts.at(0), parts.at(1), parts.at(2), parts.at(3));
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
    case QMetaType::QLineF: {
        QList<qreal> parts = toListReal(value);
        if (parts.size() != 4)
            return QLineF();

        return QLineF(parts.at(0), parts.at(1), parts.at(2), parts.at(3));
    }

    case QMetaType::QUuid:
        return QUuid::fromString(value);
    case QMetaType::QByteArray:
        return value.toUtf8();

    case QMetaType::QJsonDocument:
        return QJsonDocument::fromJson(value.toUtf8());

    case QMetaType::QBitArray: {
        QBitArray bita(value.size());
        for (int i = 0; i < value.size(); ++i) {
            if (value.at(i) == "0")
                bita.setBit(i, false);
            else
                bita.setBit(i, true);
        }
        return bita;
    }

#ifdef QT_GUI_LIB
    case QMetaType::QImage: {
        QImage image;
        image.loadFromData(QByteArray::fromBase64(value.toLocal8Bit()));
        return image;
    }

    case QMetaType::QColor:
        return QColor(value);

    case QMetaType::QPolygon: {
        QStringList parts = value.split(" ");
        QPolygon pol;
        for (int i = 0; i < parts.count(); i++)
            pol.append(fromString(parts.at(i), QMetaType::QPoint).toPoint());
        return pol;
    }
    case QMetaType::QPolygonF: {
        QStringList parts = value.split(" ");
        QPolygonF pol;
        for (int i = 0; i < parts.count(); i++)
            pol.append(fromString(parts.at(i), QMetaType::QPointF).toPointF());
        return pol;
    }
    case QMetaType::QFont: {
        QFont f;
        f.fromString(value);
        return f;
    }
#endif
    default:
        return QVariant();
    }
}

QString StringSerializer::toString(const QVariant &value) const
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
//    case QMetaType::QChar:
//        return value.toChar().digitValue();

    case QMetaType::QStringList: {
        QList<int> lens;
        QStringList sl = value.toStringList();
        foreach (QString s, sl)
            lens.append(s.length());

        return fromList(lens) + " " + sl.join("");
    }

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
    case QMetaType::QLine: {
        QLine rc = value.toLine();
        return fromList(QList<int>() << rc.x1() << rc.y1() << rc.x2() << rc.y2());
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
    case QMetaType::QLineF: {
        QLineF rc = value.toLineF();
        return fromList(QList<qreal>() << rc.x1() << rc.y1() << rc.x2() << rc.y2());
    }
    case QMetaType::QJsonDocument:
        return QString(value.toJsonDocument().toJson(QJsonDocument::Compact));

    case QMetaType::QBitArray: {
        QString ret;
        QBitArray bita = value.toBitArray();
        for (int i = 0; i < bita.size(); ++i)
            ret.append(bita.at(i) ? "1" : "0");
        return ret;
    }

#ifdef QT_GUI_LIB
    case QMetaType::QImage: {
        QImage image = value.value<QImage>();
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        image.save(&buffer, "PNG");
        QString base64 = QString::fromLatin1(byteArray.toBase64().data());
        return base64;
    }

    case QMetaType::QColor:
        return value.value<QColor>().name();

    case QMetaType::QPolygon: {
        QStringList list;
        QPolygon pol = value.value<QPolygon>();
        QPoint pt;
        for (int i = 0; i < pol.size(); ++i) {
            pt = pol.at(i);
            list.append(toString(pt));
        }

        return list.join(" ");
    }
    case QMetaType::QPolygonF: {
        QStringList list;
        QPolygonF pol = value.value<QPolygonF>();
        QPointF pt;
        for (int i = 0; i < pol.size(); ++i) {
            pt = pol.at(i);
            list.append(toString(pt));
        }

        return list.join(" ");
    }
    case QMetaType::QFont:
        return value.value<QFont>().toString();
#endif

    case QMetaType::QJsonArray:
    case QMetaType::QJsonValue:
    case QMetaType::QJsonObject:
    default:
        qWarning("The type (%s) does not supported",
                 QMetaType::typeName(type));
        return QString();
    }
}

QList<int> StringSerializer::toListInt(const QString &s) const
{
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

QString StringSerializer::fromList(const QList<int> &list) const
{
    QString ret;
    foreach (int n, list) {
        if (!ret.isEmpty())
            ret.append(",");
        ret.append(QString::number(n));
    }
    return ret;
}

QList<qreal> StringSerializer::toListReal(const QString &s) const
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

QString StringSerializer::fromList(const QList<qreal> &list) const
{
    QString ret;
    foreach (qreal n, list) {
        if (!ret.isEmpty())
            ret.append(",");
        ret.append(QString::number(n));
    }
    return ret;
}
