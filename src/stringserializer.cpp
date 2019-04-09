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
#include <QtGui/QVector2D>
#include <QtGui/QVector3D>
#include <QtGui/QVector4D>
#endif

#define DATE_FORMAT "yyyy-MM-dd"
#define TIME_FORMAT "HH-mm-ss.zzz"
StringSerializer::StringSerializer() : AbstractSerializer ()
{

}

QVariant StringSerializer::fromString(const QString &value, const QMetaType::Type &type) const
{
    switch (type) {
    case QMetaType::Bool:       return !value.compare("true", Qt::CaseInsensitive) || value == "1";
    case QMetaType::Char:
    case QMetaType::SChar:
    case QMetaType::Int:        return value.toInt();
    case QMetaType::UChar:
    case QMetaType::UInt:       return value.toUInt();
    case QMetaType::Short:      return value.toShort();
    case QMetaType::UShort:     return value.toUShort();
    case QMetaType::Long:       return qVariantFromValue(value.toLong());
    case QMetaType::ULong:      return qVariantFromValue(value.toULong());
    case QMetaType::LongLong:   return value.toLongLong();
    case QMetaType::ULongLong:  return qVariantFromValue(value.toULongLong());
    case QMetaType::Float:      return value.toFloat();
    case QMetaType::Double:     return value.toDouble();
    case QMetaType::QString:    return unescapeString(value);
    case QMetaType::QDate:      return QDate::fromString(value, DATE_FORMAT);
    case QMetaType::QTime:      return QTime::fromString(value, TIME_FORMAT);
    case QMetaType::QDateTime:  return QDateTime::fromString(value, DATE_FORMAT " " TIME_FORMAT);
    case QMetaType::QUrl:       return QUrl(value);
    case QMetaType::QChar:      return value.at(0);
    case QMetaType::QStringList: {
        QStringList ret;
        QString copy(value);
        QString out;

        while (readString(copy, out) )
            ret.append(out);

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
        return QUuid(value);

    case QMetaType::QByteArray:
        return value.toUtf8();

    case QMetaType::QJsonDocument:
        return QJsonDocument::fromJson(value.toUtf8());

    case QMetaType::QJsonObject:
        return QJsonDocument::fromJson(value.toUtf8()).object();

    case QMetaType::QJsonArray:
        return QJsonDocument::fromJson(value.toUtf8()).array();

    case QMetaType::QJsonValue: {
        if (value == "true")
            return QJsonValue(true);
        else if (value == "false")
            return QJsonValue(false);
        bool ok;
        int n = value.toInt(&ok);
        if (ok)
            return QJsonValue(n);

        double d = value.toDouble(&ok);
        if (ok)
            return QJsonValue(d);

        return QJsonValue(value);
    }

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

    case QMetaType::QVariantMap: {
        QVariantMap ret;
        QStringList parts = value.split("\n");
        foreach (QString p, parts) {
            if (p.isEmpty())
                continue;
            QString name;
            QString value;
            if (readString(p, name) && readString(p, value))
                ret.insert(name, value);
        }
        return ret;
    }

    case QMetaType::QVariantList: {
        QVariantMap ret;
        QStringList parts = value.split("\n");
        foreach (QString p, parts) {
            if (p.isEmpty())
                continue;
            QString name;
            QString value;
            if (readString(p, name) && readString(p, value))
                ret.insert(name, value);
        }
        return ret;
    }

#ifdef QT_GUI_LIB
    case QMetaType::QVector2D: {
        QList<float> parts = toListFloat(value);
        if (parts.size() != 2)
            return QVector2D();

        return QVector2D(parts.at(0), parts.at(1));
    }
    case QMetaType::QVector3D: {
        QList<float> parts = toListFloat(value);
        if (parts.size() != 3)
            return QVector3D();

        return QVector3D(parts.at(0), parts.at(1), parts.at(2));
    }
    case QMetaType::QVector4D: {
        QList<float> parts = toListFloat(value);
        if (parts.size() != 4)
            return QVector4D();

        return QVector4D(parts.at(0), parts.at(1), parts.at(2), parts.at(3));
    }

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
    auto type = static_cast<QMetaType::Type>(value.type());
    switch (type) {
    case QMetaType::Bool:
    case QMetaType::Char:
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
    case QMetaType::QChar:
    case QMetaType::QUrl:
        return value.toString();

    case QMetaType::UChar:
    case QMetaType::SChar:
        return QString::number(value.toInt());

    case QMetaType::QString:
        return escapeString(value.toString());

    case QMetaType::QStringList: {
        QString ret;
        QStringList sl = value.toStringList();
        foreach (QString s, sl) {
            if (!ret.isEmpty())
                ret.append(" ");

            ret.append("\"" + escapeString(s) + "\"");
        }

        return ret;
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

    case QMetaType::QJsonObject: {
        QJsonDocument doc;
        doc.setObject(value.toJsonObject());
        return doc.toJson(QJsonDocument::Compact);
    }

    case QMetaType::QJsonArray: {
        QJsonDocument doc;
        doc.setArray(value.toJsonArray());
        return doc.toJson(QJsonDocument::Compact);
    }

    case QMetaType::QJsonValue:
        return value.toJsonValue().toVariant().toString();

    case QMetaType::QBitArray: {
        QString ret;
        QBitArray bita = value.toBitArray();
        for (int i = 0; i < bita.size(); ++i)
            ret.append(bita.at(i) ? "1" : "0");
        return ret;
    }
    case QMetaType::QVariantMap: {
        QString ret;
        QVariantMap map = value.toMap();
        foreach (QString k, map.keys()) {
            if (!ret.isEmpty())
                ret.append("\n");
            QVariant v = map.value(k);
            QString str = toString(v);
            ret.append(QString("\"%1\" \"%2\"")
                       .arg(escapeString(k), escapeString(str)));

        }
        return ret;
    }

#ifdef QT_GUI_LIB
    case QMetaType::QVector2D: {
        QVector2D vec = value.value<QVector2D>();
        return fromList(QList<float>() << vec.x() << vec.y());
    }
    case QMetaType::QVector3D: {
        QVector3D vec = value.value<QVector3D>();
        return fromList(QList<float>() << vec.x() << vec.y() << vec.z());
    }
    case QMetaType::QVector4D: {
        QVector4D vec = value.value<QVector4D>();
        return fromList(QList<float>() << vec.x() << vec.y() << vec.z() << vec.w());
    }

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

    default:
        qWarning("The type (%s) does not supported",
                 QMetaType::typeName(type));
        return QString();
    }
}

QList<int> StringSerializer::toListInt(const QString &s) const
{
    return toListInt(s, ",");
}

QList<int> StringSerializer::toListInt(const QString &s, const QString &sep) const
{
    auto parts = s.split(sep);
    QList<int> ret;
    foreach (QString p, parts) {
        bool ok;
        ret.append(p.toInt(&ok));
        if (!ok)
            return ret;
    }

    return ret;
}

QList<qreal> StringSerializer::toListReal(const QString &s) const
{
    return toListReal(s, ",");
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

QList<qreal> StringSerializer::toListReal(const QString &s, const QString &sep) const
{
    auto parts = s.split(sep);
    QList<qreal> ret;
    foreach (QString p, parts) {
        bool ok;
        ret.append(p.toDouble(&ok));
        if (!ok)
            return ret;
    }

    return ret;
}

QList<float> StringSerializer::toListFloat(const QString &s) const
{
    auto parts = s.split(",");
    QList<float> ret;
    foreach (QString p, parts) {
        bool ok;
        ret.append(p.toFloat(&ok));
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

QString StringSerializer::fromList(const QList<float> &list) const
{
    QString ret;
    foreach (float n, list) {
        if (!ret.isEmpty())
            ret.append(",");
        ret.append(QString::number(static_cast<double>(n)));
    }
    return ret;
}

#define CASE_W(o, r) \
    case o:                  \
        ret.append(r);     \
        break;
QString StringSerializer::escapeString(const QString &str) const
{
    QString ret;
    for (int i = 0; i < str.length(); ++i) {
        switch (str.at(i).cell()) {
        CASE_W('\\', "\\\\")
        CASE_W('\r', "\\r")
        CASE_W('\n', "\\n")
        CASE_W('\a', "\\a")
        CASE_W('\b', "\\b")
        CASE_W('\f', "\\f")
        CASE_W('\'', "\\'")
        CASE_W('\t', "\\t")
        CASE_W('\v', "\\v")
        CASE_W('\"', "\\\"")

        default:
            ret.append(str.at(i));
        }
    }
    return ret;
}

QString StringSerializer::unescapeString(const QString &str) const
{
    QString ret;
    for (int i = 0; i < str.length(); ++i) {
        if (str.at(i) == '\\' && str.length() > i) {
            switch (str.at(++i).cell()) {
            case '\\':
                ret.append("\\");
                break;
            case 'r':
                ret.append("\r");
                break;
            case 'n':
                ret.append("\n");
                break;
            case 'a':
                ret.append("\a");
                break;
            case 'b':
                ret.append("b");
                break;
            case 'f':
                ret.append("\f");
                break;
            case '\'':
                ret.append("\\'");
                break;
            case 't':
                ret.append("\t");
                break;
            case 'v':
                ret.append("\v");
                break;
            case '"':
                ret.append("\\\"");
                break;

            default:
                ret.append(str.at(i));
            }
        } else {
            ret.append(str.at(i));
        }
    }

    return ret;
}

bool StringSerializer::readString(QString &text, QString &out) const
{
    int start = -1;
    int end = -1;

    for (int i = 0; i < text.length(); ++i) {
        if (text.at(i) == '"' && (i == 0 || text.at(i - 1) != "\\")) {
            if (start == -1)
                start = i;
            else
                end = i;
        }
        if (end != -1){
            out = text.mid(start + 1, end - start - 1);
            text = text.mid(end + 1);
            return true;
        }
    }
    return false;
}

