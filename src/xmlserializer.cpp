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
#include <QUrl>
#include <QMetaProperty>

#define createSimpleElement(name, value) QDomElement name; name.setNodeValue(value);
#define createSimpleElementInteger(name, value) QDomElement name; name.setNodeValue(QString::number(value));

XmlSerializer::XmlSerializer()
{

}

QDomElement XmlSerializer::toDomElement(QDomDocument &doc, const QString &name, const QVariant &v) const
{

    QDomElement element = doc.createElement(name);

    element.setAttribute("type", v.typeName());

    switch (v.typeId()) {
    case QMetaType::Int:
    case QMetaType::Short:
    case QMetaType::Long:
    case QMetaType::LongLong:
        element.appendChild(doc.createTextNode(QString::number(v.toLongLong())));
        return element;

    case QMetaType::UInt:
    case QMetaType::UShort:
    case QMetaType::ULong:
    case QMetaType::ULongLong:
        element.appendChild(doc.createTextNode(QString::number(v.toLongLong())));
        return element;

    case QMetaType::Bool:
        element.appendChild(doc.createTextNode(v.toBool() ? "true" : "false"));
        return element;

    case QMetaType::Char:
        element.appendChild(doc.createTextNode(v.toChar()));
        return element;

    case QMetaType::QString:
        element.appendChild(doc.createTextNode(v.toString()));
        return element;

    case QMetaType::QPoint: {
        auto pt = v.toPoint();
        addToElement(doc, element, "x", pt.x());
        addToElement(doc, element, "y", pt.y());
        return element;
    }
    case QMetaType::QPointF: {
        auto pt = v.toPointF();
        addToElement(doc, element, "x", pt.x());
        addToElement(doc, element, "y", pt.y());
        return element;
    }
    case QMetaType::QRect: {
        auto rc = v.toRect();
        addToElement(doc, element, "x", rc.x());
        addToElement(doc, element, "y", rc.y());
        addToElement(doc, element, "width", rc.width());
        addToElement(doc, element, "height", rc.height());
        return element;
    }
    case QMetaType::QRectF: {
        auto rc = v.toRectF();
        addToElement(doc, element, "x", rc.x());
        addToElement(doc, element, "y", rc.y());
        addToElement(doc, element, "width", rc.width());
        addToElement(doc, element, "height", rc.height());
        return element;
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

    case QMetaType::QUrl:
        element.setNodeValue(v.value<QUrl>().toString());
        return element;

    case QMetaType::QPolygon: {
        auto poly = v.value<QPolygon>();
        for (auto &pt : poly) {
            auto child = toDomElement(doc, "value", pt);
            element.appendChild(child);
        }
        return element;
    }
    case QMetaType::QPolygonF: {
        auto poly = v.value<QPolygonF>();
        for (auto &pt : poly) {
            auto child = toDomElement(doc, "value", pt);
            element.appendChild(child);
        }
        return element;
    }

    default:
        break;
    }
    return element;
}

QDomElement XmlSerializer::toDomElement(QDomDocument &doc, const QString &name, QVariantList list) const
{
    QDomElement element = doc.createElement(name);
    element.setAttribute("type", "QVariantList");
    for (auto &v:list) {
        element.appendChild(toDomElement(doc, "item", v));
    }
    return element;
}

QVariant XmlSerializer::fromDomElement(const QMetaType::Type &type, const QDomElement &element) const
{
    switch (type) {
    case QMetaType::Short:
        return elementText(element).toShort();

    case QMetaType::UShort:
        return elementText(element).toUShort();

    case QMetaType::Int:
        return elementText(element).toInt();

    case QMetaType::UInt:
        return elementText(element).toUInt();

    case QMetaType::Long:
        return QVariant::fromValue(elementText(element).toLong());

    case QMetaType::ULong:
        return QVariant::fromValue(elementText(element).toULong());

    case QMetaType::LongLong:
        return elementText(element).toLongLong();

    case QMetaType::ULongLong:
        return elementText(element).toULongLong();

    case QMetaType::QString:
        return elementText(element);

    case QMetaType::QPoint: {
        QPoint pt;
        pt.setX(elementChildText(element, "x").toInt());
        pt.setY(elementChildText(element, "y").toInt());
        return pt;
    }
    case QMetaType::QPointF: {
        QPointF pt;
        pt.setX(elementChildText(element, "x").toDouble());
        pt.setY(elementChildText(element, "y").toDouble());
        return pt;
    }
    case QMetaType::QRect: {
        QRect rc;
        rc.setX(elementChildText(element, "x").toInt());
        rc.setY(elementChildText(element, "y").toInt());
        rc.setWidth(elementChildText(element, "width").toInt());
        rc.setHeight(elementChildText(element, "height").toInt());
        return rc;
    }
    case QMetaType::QRectF: {
        QRectF rc;
        rc.setX(elementChildText(element, "x").toDouble());
        rc.setY(elementChildText(element, "y").toDouble());
        rc.setWidth(elementChildText(element, "width").toDouble());
        rc.setHeight(elementChildText(element, "height").toDouble());
        return rc;
    }
    case QMetaType::QPolygon:{
        QPolygon poly;
        for (int i = 0; i < element.childNodes().count(); ++i)
            poly << fromDomElement(QMetaType::QPoint, element.childNodes().at(i).toElement()).toPoint();
        return poly;
    }
    case QMetaType::QPolygonF:{
        QPolygonF poly;
        for (int i = 0; i < element.childNodes().count(); ++i)
            poly << fromDomElement(QMetaType::QPointF, element.childNodes().at(i).toElement()).toPoint();
        return poly;
    }
    default:
        break;
    }

    return QVariant{};
}

QString XmlSerializer::serializeObject(QObject *object)
{
    if (!object)
        return QString{};

    QDomDocument doc;
    auto rootElement = doc.createElement(object->metaObject()->className());

    for (int i = 0; i < object->metaObject()->propertyCount(); i++) {
        QMetaProperty property = object->metaObject()->property(i);
        if (property.isReadable() && property.isWritable()) {
            auto value = property.read(object);

            rootElement.appendChild(toDomElement(doc, QString::fromUtf8(property.name()), value));
        }
    }

    doc.appendChild(rootElement);
    return doc.toString();
}

bool XmlSerializer::deserializeQObject(QObject *obj, const QString &content)
{
    QDomDocument doc;
    doc.setContent(content);
    auto rootElement = doc.documentElement();

    if (rootElement.isNull())
        return false;

    for (int i = 0; i < obj->metaObject()->propertyCount(); i++) {
        QMetaProperty property = obj->metaObject()->property(i);
        if (property.isReadable() && property.isWritable()) {
            auto propertyName = QString::fromUtf8(property.name());
            auto nodes = rootElement.elementsByTagName(propertyName);
            if (!nodes.size())
                continue;

            auto element = nodes.at(0).toElement();
            auto v = fromDomElement((QMetaType::Type)property.typeId(), element);
            property.write(obj, v);
        }
    }
    return true;
}

QVariant XmlSerializer::fromString(const QString &value, const QMetaType::Type &type) const
{
    QDomDocument doc;
    doc.setContent(value);
    return fromDomElement(type, doc.documentElement());


    //        reader{value};

//    auto tokenType = reader.readNext();

//    while (reader.readNextStartElement()) {
//        auto type = QMetaType::fromName(QByteArrayView{reader.name().toLatin1().data()});
    //    }
}

QString XmlSerializer::toString(const QVariant &value) const
{
    QDomDocument doc;
    QDomElement el;

    if (value.typeId() == QMetaType::QVariantList)
        el = toDomElement(doc, "value", value.toList());
    else
        el = toDomElement(doc, "value", value);
    doc.appendChild(el);
    return doc.toString();
}

void XmlSerializer::addToElement(QDomDocument &doc, QDomElement &element, const QString &name, int n) const
{
    auto child = doc.createElement(name);
    child.appendChild(doc.createTextNode(QString::number(n)));
    element.appendChild(child);
}

QString XmlSerializer::elementText(const QDomElement &element) const
{
    if (element.childNodes().size() != 1)
        return QString{};

    auto node = element.childNodes().at(0);
    if (node.nodeType() != QDomNode::TextNode)
        return QString{};

    return node.toText().data();
}

QString XmlSerializer::elementChildText(const QDomElement &element, const QString &name) const
{
    auto el = element.firstChildElement(name);
    if (el == QDomElement{})
        return QString{};

    return elementText(el);
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

XmlSerializer::DomWriter::DomWriter(const QDomElement &element)
    : _el{element}
{

}

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
