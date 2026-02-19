#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtCore/QVariant>

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

class JsonSerializer
{
public:
    JsonSerializer();

    QJsonObject serialize(QObject *obj);
//    template<class T>
//    QJsonObject serialize(T *obj) {
//            QJsonObject json;

//            for (int i = 0; i < obj->metaObject()->propertyCount(); i++) {
//                QMetaProperty prop = obj->metaObject()->property(i);
//        //        json.insert(prop.name(), toJson(prop.read(obj)));
//                if (QString(prop.typeName()).contains("QList"))
//                    qDebug() << prop.name() << prop.read(obj) << obj->property(prop.name());
//            }//for
//            return json;
//    }

    bool deserialize(const QJsonObject &json, QObject *obj);
    template<class T>
    T *deserialize(const QJsonObject &json) {
        auto o = new T;
        deserialize(json, o);
        return o;
    }

    QJsonValue value(QVariant v) const;
    QVariant value(QJsonValue &v) const;

    QJsonValue toJson(const QMetaEnum &en, const QVariant &value);
    QJsonValue toJson(QVariant v);
    QJsonValue toJson(QVariantList list);
    QJsonValue toJson(QStringList list);
    QJsonValue toJson(QVariantMap map);

    QVariant fromJson(const QMetaType::Type &type, const QJsonValue &object);
    QVariant fromJson(const QMetaType::Type &type, const QJsonObject &object);
    QVariant fromJson(const QMetaType::Type &type, const QJsonArray &array);
    QVariantMap mapFromJson(const QMetaType::Type &keyType,
                            const QMetaType::Type &valueType,
                            const QJsonObject &object);

    QVariantMap serializeQObject(QObject *obj);
    void deserializeQObject(QObject *obj, QVariantMap jsonObject);

};

#endif // JSONSERIALIZER_H
