#include "jsonserializer.h"

#include <QtCore/QDataStream>
#include <QtCore/QDebug>
#include <QtCore/QJsonArray>
#include <QtCore/QMetaProperty>
#include <QtCore/QPoint>
#include <QtCore/QPointF>
#include <QtCore/QRect>
#include <QtCore/QRectF>
#include <QtCore/QRegularExpression>
#include <QtCore/QVariantList>
#include <QtGui/QFont>
#include <QtGui/QPolygon>
#include <QtGui/QPolygonF>

#define VARIANT_TYPE QStringLiteral("_type")
#define VARIANT_VALUE QStringLiteral("_value")
#define CLASS_NAME(x) QString::fromUtf8(#x)

template <typename T> bool registerQList()
{
    bool b1 = QMetaType::registerConverter<QList<T>, QVariantList>(
        [](const QList<T> &list) -> QVariantList {
            QVariantList l;
            l.reserve(list.size());
            for (const auto &v : list)
                l.append(QVariant::fromValue(v));
            return l;
        });
    bool b2 = QMetaType::registerConverter<QVariantList, QList<T>>(
        [](const QVariantList &list) -> QList<T> {
            QList<T> l;
            l.reserve(list.size());
            for (auto v : list) { // clazy:exclude=range-loop
                const auto vt = v.type();
                if (v.convert(qMetaTypeId<T>())) {
                    l.append(v.value<T>());
                    ;
                } else {
                    qWarning() << "Conversion to"
                               << QMetaType::typeName(qMetaTypeId<QList<T>>())
                               << "failed, could not convert element of type"
                               << QMetaType::typeName(vt);
                    //                    (l.*appendMethod)(TClass());
                }
            }
            return l;
        });
    return b1 && b2;
}
template <typename T> bool registerQSet()
{
    bool b1 = QMetaType::registerConverter<QSet<T>, QVariantList>(
        [](const QSet<T> &list) -> QVariantList {
            QVariantList l;
            l.reserve(list.size());
            for (const auto &v : list)
                l.append(QVariant::fromValue(v));
            return l;
        });
    bool b2 = QMetaType::registerConverter<QVariantList, QSet<T>>(
        [](const QVariantList &list) -> QSet<T> {
            QSet<T> l;
            l.reserve(list.size());
            for (auto v : list) { // clazy:exclude=range-loop
                const auto vt = v.type();
                if (v.convert(qMetaTypeId<T>())) {
                    l.insert(v.value<T>());
                } else {
                    qWarning() << "Conversion to"
                               << QMetaType::typeName(qMetaTypeId<QSet<T>>())
                               << "failed, could not convert element of type"
                               << QMetaType::typeName(vt);
                    //                    (l.*appendMethod)(TClass());
                }
            }
            return l;
        });
    return b1 && b2;
}
template <typename T> bool registerQVector()
{
    bool b1 = QMetaType::registerConverter<QVector<T>, QVariantList>(
        [](const QVector<T> &list) -> QVariantList {
            QVariantList l;
            l.reserve(list.size());
            for (const auto &v : list)
                l.append(QVariant::fromValue(v));
            return l;
        });
    bool b2 = QMetaType::registerConverter<QVariantList, QVector<T>>(
        [](const QVariantList &list) -> QVector<T> {
            QVector<T> l;
            l.reserve(list.size());
            for (auto v : list) { // clazy:exclude=range-loop
                const auto vt = v.type();
                if (v.convert(qMetaTypeId<T>())) {
                    l.append(v.value<T>());
                } else {
                    qWarning() << "Conversion to"
                               << QMetaType::typeName(qMetaTypeId<QVector<T>>())
                               << "failed, could not convert element of type"
                               << QMetaType::typeName(vt);
                    //                    (l.*appendMethod)(TClass());
                }
            }
            return l;
        });
    return b1 && b2;
}
template <typename K, typename V> bool registerQMap()
{
    auto b1 = QMetaType::registerConverter<QMap<K, V>, QVariantMap>(
        [](const QMap<K, V> &map) -> QVariantMap {
            QVariantMap m;
            for (auto it = map.constBegin(); it != map.constEnd(); ++it) {
                //                if (asMultiMap)
                //                    m.insertMulti(it.key(),
                //                    QVariant::fromValue(it.value()));
                //                else
                m.insert(QVariant::fromValue(it.key()).toString(),
                         QVariant::fromValue(it.value()));
            }
            return m;
        });
    auto b2 = QMetaType::registerConverter<QVariantMap, QMap<K, V>>(
        [](const QVariantMap &map) -> QMap<K, V> {
            QMap<K, V> m;
            for (auto it = map.constBegin(); it != map.constEnd(); ++it) {
                auto v        = it.value();
                const auto vt = v.type();
                if (v.convert(qMetaTypeId<V>()))
                    m.insert(v.value<K>(), v.value<V>());
                else {
                    qWarning()
                        << "Conversion to"
                        << QMetaType::typeName(qMetaTypeId<QMap<K, V>>())
                        << "failed, could not convert element value of type"
                        << QMetaType::typeName(vt);
                    //                    (m.*insertMethod)(it.key(), TClass());
                }
            }
            return m;
        });
    return b1 && b2;
}
#define REGISTER(type)                             \
    qDebug() << "Registering" << #type;            \
    qDebug() << "  list" << registerQList<type>(); \
    qDebug() << "  set" << registerQSet<type>();   \
    qDebug() << "  vector:" << registerQVector<type>();

JsonSerializer::JsonSerializer()
{
    REGISTER(qint8);
    REGISTER(qint16);
    REGISTER(qint32);
    REGISTER(qint64);
    REGISTER(quint8);
    REGISTER(quint16);
    REGISTER(quint32);
    REGISTER(quint64);
    REGISTER(qreal);
    REGISTER(float);
    registerQMap<int, int>();
}

QJsonObject JsonSerializer::serialize(QObject *obj)
{
    QJsonObject json;

    for (int i = 0; i < obj->metaObject()->propertyCount(); i++) {
        QMetaProperty prop = obj->metaObject()->property(i);
        QJsonValue val;
        auto v = prop.read(obj);
        QString pps = QString::fromUtf8((prop.name()));
        if (v.isValid()) {
            if (prop.isEnumType())
                val = toJson(prop.enumerator(), obj->property(prop.name()));
            else
                val = toJson(v);
        }

        if (val == QJsonValue())
            qDebug() << prop.name();
        json.insert(pps, val);
    } // for
    return json;
}

bool JsonSerializer::deserialize(const QJsonObject &json, QObject *obj)
{
    for (int i = 0; i < obj->metaObject()->propertyCount(); i++) {
        QMetaProperty prop   = obj->metaObject()->property(i);
        QJsonValue jsonValue = json.value(QString::fromUtf8(prop.name()));

        if (QString::fromUtf8(prop.typeName()).endsWith(QStringLiteral("*"))) {
            if (jsonValue == QJsonValue()) {
                prop.write(obj, QVariant::fromValue(nullptr));
                continue;
            }
            const QMetaObject *metaObject = QMetaType::metaObjectForType(
                QMetaType::type(prop.typeName()));
            auto o = metaObject->newInstance();
            if (!o)
                qDebug() << "Unable to create" << prop.typeName()
                         << prop.type();
            else
                deserialize(jsonValue.toObject(), o);

            bool ok = prop.write(obj, QVariant::fromValue(o));
            if (!ok)
                qDebug() << "Unable to write" << prop.name() << QVariant::fromValue(o);
            continue;
        }
        if (jsonValue == QJsonValue())
            continue;
        auto propertyValue = fromJson(
            static_cast<QMetaType::Type>(prop.userType()), jsonValue);

        QGenericArgument arg(prop.typeName(), propertyValue.data());
        QString pName = QString::fromUtf8(prop.name());
        pName[0] = pName[0].toUpper();
        pName.prepend(QStringLiteral("set"));
        if (pName == QStringLiteral("setObjectName")) {
            obj->setObjectName(propertyValue.toString());
        } else {
            //            bool ok = obj->metaObject()->invokeMethod(obj,
            //            pName.toLatin1().data(), arg);
            bool ok = prop.write(obj, propertyValue);
            if (!ok)
                qDebug() << "Unable to write" << prop.name() << propertyValue;
        }
    } // for

    obj->setObjectName(json.value(QStringLiteral("objectName")).toString());
    return true;
}

QJsonValue JsonSerializer::value(QVariant v) const
{
    return QJsonValue::fromVariant(v);
}

QVariant JsonSerializer::value(QJsonValue &v) const
{
    return v.toVariant();
}

QJsonValue JsonSerializer::toJson(const QMetaEnum &en, const QVariant &value)
{
    if (en.isFlag())
        return QString::fromUtf8(en.valueToKeys(value.toInt()));
    else
        return QString::fromUtf8(en.valueToKey(value.toInt()));
}

QJsonValue JsonSerializer::toJson(QVariant v)
{
    switch (v.type()) {
    case QVariant::Map: return toJson(v.toMap());
    case QVariant::StringList: return toJson(v.toStringList());
    case QVariant::List: return toJson(v.toList());

    case QVariant::Invalid: qWarning("QVariant type is Invalid!"); break;

    default:
        // disable compiler warning
        break;
    }

    QJsonObject o;

    QString typeName = QString::fromUtf8(v.typeName());

    if (typeName.endsWith(QStringLiteral("*"))) {
        auto obj = v.value<QObject *>();
        if (!obj)
            return QJsonValue();

        auto r = serialize(obj);
        return r;
    } else {
        if (v.canConvert(QMetaType::QVariantList)) {
            v.convert(qMetaTypeId<QVariantList>());
            QVariantList list = v.value<QVariantList>();
            return toJson(list);
        }
        if (v.canConvert(QMetaType::QVariantMap)) {
            QVariantMap map = v.value<QVariantMap>();
            return toJson(map);
        }

        switch (v.type()) {
        case QVariant::Point: {
            auto pt = v.toPoint();
            return QJsonObject{{ QStringLiteral("x"), pt.x()}, { QStringLiteral("y"), pt.y()}};
            break;
        }
        case QVariant::PointF: {
            auto pt = v.toPointF();
            return QJsonObject{{ QStringLiteral("x"), pt.x()}, { QStringLiteral("y"), pt.y()}};
            break;
        }
        case QVariant::Rect: {
            auto rc = v.toRect();
            return QJsonObject{{ QStringLiteral("x"), rc.x()},
                               { QStringLiteral("y"), rc.y()},
                               { QStringLiteral("width"), rc.width()},
                               { QStringLiteral("height"), rc.height()}};
            break;
        }
        case QVariant::RectF: {
            auto rc = v.toRectF();
            return QJsonObject{{ QStringLiteral("x"), rc.x()},
                               { QStringLiteral("y"), rc.y()},
                               { QStringLiteral("width"), rc.width()},
                               { QStringLiteral("height"), rc.height()}};
            break;
        }
        case QVariant::Locale: {
            auto lc = v.toLocale();
            return lc.name();
        }
        case QVariant::RegularExpression:
            return v.toRegularExpression().pattern();

        case QVariant::Font: return v.value<QFont>().toString();
        case QVariant::Polygon: {
            QJsonArray arr;
            QPolygon poly = v.value<QPolygon>();
            Q_FOREACH (QPoint pt, poly)
                arr.append(toJson(pt));
            return arr;
        }
        case QVariant::PolygonF: {
            QJsonArray arr;
            QPolygonF poly = v.value<QPolygonF>();
            Q_FOREACH (QPointF pt, poly)
                arr.append(toJson(pt));
            return arr;
        }

        default: break;
        }

        return QJsonValue::fromVariant(v);
    }
    return o;
}

QJsonValue JsonSerializer::toJson(QVariantList list)
{
    if (!list.count())
        return QJsonArray();

    QJsonArray array;
    Q_FOREACH (QVariant v, list) {
        array.append(toJson(v));
    }

    //    QJsonObject o;
    //    o.insert(VARIANT_TYPE, CLASS_NAME(QVariantList));
    //    o.insert(VARIANT_VALUE, array);
    return array;
}

QJsonValue JsonSerializer::toJson(QStringList list)
{
    QJsonArray array;
    Q_FOREACH (QVariant v, list) {
        array.append(toJson(v));
    }

    //    QJsonObject o;
    //    o.insert(VARIANT_TYPE, CLASS_NAME(QStringList));
    //    o.insert(VARIANT_VALUE, array);
    return array;
}

QJsonValue JsonSerializer::toJson(QVariantMap map)
{
    QJsonObject mapObject;
    Q_FOREACH (QString key, map.keys()) {
        mapObject.insert(key, toJson(map[key]));
    }

    //    QJsonObject o;
    //    o.insert(VARIANT_TYPE, CLASS_NAME(QVariantMap));
    //    o.insert(VARIANT_VALUE, mapObject);
    return mapObject;
}

QVariant JsonSerializer::fromJson(const QMetaType::Type &type,
                                  const QJsonValue &value)
{
    if (value == QJsonValue())
        return QVariant();

    QString typeName = QString::fromUtf8(QMetaType::typeName(type));

    switch (type) {
    case QMetaType::QPoint: {
        auto o = value.toObject();
        return QPoint(o.value(QStringLiteral("x")).toInt(), o.value(QStringLiteral("y")).toInt());
    }
    case QMetaType::QPointF: {
        auto o = value.toObject();
        return QPointF(o.value(QStringLiteral("x")).toDouble(),
                       o.value(QStringLiteral("y")).toDouble());
    }
    case QMetaType::QRect: {
        auto o = value.toObject();
        return QRect(o.value(QStringLiteral("x")).toInt(),
                     o.value(QStringLiteral("y")).toInt(),
                     o.value(QStringLiteral("width")).toInt(),
                     o.value(QStringLiteral("height")).toInt());
    }
    case QMetaType::QRectF: {
        auto o = value.toObject();
        return QRectF(o.value(QStringLiteral("x")).toDouble(),
                      o.value(QStringLiteral("y")).toDouble(),
                      o.value(QStringLiteral("width")).toDouble(),
                      o.value(QStringLiteral("height")).toDouble());
    }
    case QMetaType::QFont: {
        QFont f;
        f.fromString(value.toString());
        return f;
    }
    case QMetaType::QRegularExpression: {
        return QRegularExpression(value.toString());
    }
    case QMetaType::QLocale: {
        return QLocale(value.toString());
    }
    case QMetaType::QPolygon: {
        QPolygon poly;
        auto arr = value.toArray();
        Q_FOREACH (QJsonValue val, arr)
            poly << fromJson(QMetaType::QPoint, val).toPoint();
        return poly;
    }
    case QMetaType::QPolygonF: {
        QPolygonF poly;
        auto arr = value.toArray();
        Q_FOREACH (QJsonValue val, arr)
            poly << fromJson(QMetaType::QPointF, val).toPointF();
        return poly;
    }
    default: break;
    }
    if (value.isArray()) {
        if (typeName.startsWith(QStringLiteral("QList<"))) {
            auto name = typeName.replace(QStringLiteral("QList<"), QStringLiteral(""))
                            .replace(QStringLiteral(">"), QStringLiteral(""));
            auto keyType = static_cast<QMetaType::Type>(
                QMetaType::type(name.toLatin1().data()));
            return fromJson(keyType, value.toArray());
        }
        if (typeName == QStringLiteral("QStringList")) {
            auto keyType = static_cast<QMetaType::Type>(qMetaTypeId<QString>());
            return fromJson(keyType, value.toArray());
        }
        return fromJson(type, value.toArray());
    }

    if (value.isObject()) {
        if (typeName.endsWith(QStringLiteral("*"))) {
            const QMetaObject *metaObject = QMetaType::metaObjectForType(type);
            auto obj                      = metaObject->newInstance();
            deserialize(value.toObject(), obj);
            return QVariant::fromValue(obj);
        }

        if (typeName.startsWith(QStringLiteral("QMap<"))) {
            //            reinterpret_cast<QVariantMap*>(QMetaType::create(type));

            auto parts = typeName.replace(QStringLiteral("QMap<"), QStringLiteral(""))
                             .replace(QStringLiteral(">"), QStringLiteral(""))
                             .split(QStringLiteral(","));
            auto keyType = static_cast<QMetaType::Type>(
                QMetaType::type(parts.at(0).toLatin1().data()));
            auto valueType = static_cast<QMetaType::Type>(
                QMetaType::type(parts.at(1).toLatin1().data()));
            return mapFromJson(keyType, valueType, value.toObject());
        }
        return fromJson(type, value.toObject());
    }

    return value.toVariant();
}

QVariant JsonSerializer::fromJson(const QMetaType::Type &type,
                                  const QJsonObject &object)
{
    //    const QMetaObject *metaObject = QMetaType::metaObjectForType(type);
    //    auto obj = metaObject->newInstance();

    QString typeName = QString::fromUtf8(QMetaType::typeName(type));
    // = object[VARIANT_TYPE].toString();
                                     //    QVariant::Type type =
    //    QVariant::nameToType(typeName.toLatin1().data());

    //    if(type == QVariant::List)
    //        return fromJson(object[VARIANT_VALUE].toArray()).toList();

    //    if(type == QVariant::StringList)
    //        return fromJson(object[VARIANT_VALUE].toArray()).toStringList();

    //    if(type == QVariant::Map){
    QVariantMap map;
    //        QJsonObject mapObject = object[VARIANT_VALUE].toObject();
    Q_FOREACH (QString key, object.keys())
        map.insert(key, fromJson(type, object[key]));
    return map;
    //    }

    //    if(QMetaType::type(typeName.toLatin1().data())> 1024){
    if (typeName.endsWith(QStringLiteral("*"))) {
        QObject *obj;
        QVariantMap map;
        QJsonObject mapObject
            = object[VARIANT_VALUE].toObject().value(VARIANT_VALUE).toObject();

        Q_FOREACH (QString key, mapObject.keys())
            map.insert(key, fromJson(type, mapObject[key].toObject()));
        int typeCode = QMetaType::type(typeName.toLatin1().data());

        if (typeCode == QMetaType::UnknownType) {
            qWarning("Type %s is not registered!", qPrintable(typeName));
            return QVariant(QVariant::Invalid);
        }

        const QMetaObject *metaObject = QMetaType::metaObjectForType(typeCode);
        obj                           = metaObject->newInstance();

        if (!obj) {
            qWarning("Object type %s can not deserialized",
                     qPrintable(object[VARIANT_TYPE].toString()));
            return 0;
        }

        deserializeQObject(obj, map);

        QVariant ret = QVariant::fromValue(obj);
        ret.convert(typeCode);
        return ret;
    }

    QVariant v;
    QByteArray data = QByteArray::fromBase64(
        object[VARIANT_VALUE].toString().toLocal8Bit());
    QDataStream ds(&data, QIODevice::ReadOnly);
    ds >> v;
    return v;
}

QVariant JsonSerializer::fromJson(const QMetaType::Type &type,
                                  const QJsonArray &array)
{
    QVariantList list;
    Q_FOREACH (QJsonValue value, array)
        list.append(fromJson(type, value));
    return list;
}

QVariantMap JsonSerializer::mapFromJson(const QMetaType::Type &keyType,
                                        const QMetaType::Type &valueType,
                                        const QJsonObject &object)
{
    Q_UNUSED(keyType)
    //    QString typeName = QMetaType::typeName(type);// =
    //    object[VARIANT_TYPE].toString();
    QVariantMap map;
    Q_FOREACH (QString key, object.keys())
        map.insert(key, fromJson(valueType, object[key]));
    return map;
}

QVariantMap JsonSerializer::serializeQObject(QObject *obj)
{
    QVariantMap map;

    if (obj)
        for (int i = 0; i < obj->metaObject()->propertyCount(); i++) {
            QMetaProperty property = obj->metaObject()->property(i);
            if (property.isReadable() && property.isWritable())
                map.insert(QString::fromUtf8(property.name()), property.read(obj).toString());
        }

    return map;
}

void JsonSerializer::deserializeQObject(QObject *obj, QVariantMap map)
{
    for (int i = 0; i < obj->metaObject()->propertyCount(); i++) {
        QMetaProperty property = obj->metaObject()->property(i);
        if (property.isReadable() && property.isWritable())
            property.write(obj, map[QString::fromUtf8(property.name())].toString());
    }
}
