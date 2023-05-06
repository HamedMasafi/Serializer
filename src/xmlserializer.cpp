#include "xmlserializer.h"

#include <QFont>
#include <QDateTime>
#include <QPoint>
#include <QPointF>
#include <QRect>
#include <QRectF>
#include <QPolygon>
#include <QPolygonF>
#include <QDomDocument>
#include <QDomElement>
#include <QRegularExpression>

#define createSimpleElement(name, value) QDomElement name; name.setNodeValue(value);
#define createSimpleElementInteger(name, value) QDomElement name; name.setNodeValue(QString::number(value));

XmlSerializer::XmlSerializer()
{

}

QDomElement XmlSerializer::toDomElement(const QVariant &v)
{
    DomWriter w;

    QDomElement element;
    switch (v.typeId()) {
    case QMetaType::Int: {
        auto tmp = v.toInt();
        w.append("int", tmp);
    }
    case QMetaType::QPoint: {
        auto pt = v.toPoint();
        w.append("x", pt.x());
        w.append("y", pt.y());
        return w.el();
    }
    case QMetaType::QPointF: {
        auto pt = v.toPointF();
        w.append("x", pt.x());
        w.append("y", pt.y());
        return w.el();
    }
    case QMetaType::QRect: {
        auto rc = v.toRect();
        w.append("x", rc.x());
        w.append("y", rc.y());
        w.append("width", rc.width());
        w.append("height", rc.height());
        return w.el();
    }
    case QMetaType::QRectF: {
        auto rc = v.toRectF();
        w.append("x", rc.x());
        w.append("y", rc.y());
        w.append("width", rc.width());
        w.append("height", rc.height());
        return w.el();
    }
    case QMetaType::QLocale: {
        auto lc = v.toLocale();
        element.setNodeValue(lc.name());
        return element;
    }
    case QMetaType::QRegularExpression:
        element.setNodeValue(v.toRegularExpression().pattern());
        return element;

    case QMetaType::QFont:
        element.setNodeValue(v.value<QFont>().toString());
        return element;
        //    case QMetaType::QPolygon: {
        //        QJsonArray arr;
        //        QPolygon poly = v.value<QPolygon>();
        //        Q_FOREACH (QPoint pt, poly)
        //            arr.append(toJson(pt));
        //        return arr;
        //    }
        //    case QMetaType::QPolygonF: {
        //        QJsonArray arr;
        //        QPolygonF poly = v.value<QPolygonF>();
        //        Q_FOREACH (QPointF pt, poly)
        //            arr.append(toJson(pt));
        //        return arr;
        //    }

    default:
        break;
    }

}

QVariant XmlSerializer::fromString(const QString &value, const QMetaType::Type &type) const
{
    QDomDocument doc;
    doc.setContent(value);
    return QVariant{};


    //        reader{value};

//    auto tokenType = reader.readNext();

//    while (reader.readNextStartElement()) {
//        auto type = QMetaType::fromName(QByteArrayView{reader.name().toLatin1().data()});
    //    }
}

QString XmlSerializer::toString(const QVariant &value) const
{
    return QString{};
}
/*
QVariant fromString2(const QString &value, const QMetaType::Type &type)
{
    switch (type) {
    case QMetaType::Bool:       return !value.compare(QStringLiteral("true"), Qt::CaseInsensitive) || value == QStringLiteral("1");
    case QMetaType::Char:
    case QMetaType::SChar:
    case QMetaType::Int:        return value.toInt();
    case QMetaType::UChar:
    case QMetaType::UInt:       return value.toUInt();
    case QMetaType::Short:      return value.toShort();
    case QMetaType::UShort:     return value.toUShort();
    case QMetaType::Long:       return QVariant::fromValue(value.toLong());
    case QMetaType::ULong:      return QVariant::fromValue(value.toULong());
    case QMetaType::LongLong:   return value.toLongLong();
    case QMetaType::ULongLong:  return QVariant::fromValue(value.toULongLong());
    case QMetaType::Float:      return value.toFloat();
    case QMetaType::Double:     return value.toDouble();
    case QMetaType::QString:    return unescapeString(value);
    case QMetaType::QDate:      return QDate::fromString(value, DATE_FORMAT);
    case QMetaType::QTime:      return QTime::fromString(value, TIME_FORMAT);
    case QMetaType::QDateTime:  return QDateTime::fromString(value, DATE_FORMAT + QStringLiteral(" ") + TIME_FORMAT);
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
        if (value == QStringLiteral("true"))
            return QJsonValue(true);
        else if (value == QStringLiteral("false"))
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
            if (value.at(i) == QStringLiteral("0"))
                bita.setBit(i, false);
            else
                bita.setBit(i, true);
        }
        return bita;
    }

    case QMetaType::QVariantMap: {
        QVariantMap ret;
        QStringList parts = value.split(QStringLiteral("\n"));
        Q_FOREACH (QString p, parts) {
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
        QStringList parts = value.split(QStringLiteral("\n"));
        Q_FOREACH (QString p, parts) {
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
        QStringList parts = value.split(QStringLiteral(" "));
        QPolygon pol;
        for (int i = 0; i < parts.count(); i++)
            pol.append(fromString(parts.at(i), QMetaType::QPoint).toPoint());
        return pol;
    }
    case QMetaType::QPolygonF: {
        QStringList parts = value.split(QStringLiteral(" "));
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
*/

void XmlSerializer::DomWriter::append(const QString &name, int value)
{
    QDomElement ch;
    ch.setNodeValue(QString::number(value));
    _el.appendChild(ch);
}

QDomElement XmlSerializer::DomWriter::el() const
{
    return _el;
}
