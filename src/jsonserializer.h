#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H

#include <QtCore/QJsonObject>
#include <QtCore/QObject>
#include <QtCore/QVariant>

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
