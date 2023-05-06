#pragma once

#include "abstractserializer.h"
#include <QDomElement>

class XmlSerializer : public AbstractSerializer
{
public:
    XmlSerializer();

//    QDomElement toDomElement(const QMetaEnum &en, const QVariant &value);
    QDomElement toDomElement(const QVariant &v);
//    QDomElement toDomElement(QVariantList list);
//    QDomElement toDomElement(QStringList list);
//    QDomElement toDomElement(QVariantMap map);

private:

    struct DomWriter {
        void append(const QString &name, int value);


    public:
        QDomElement el() const;

    private:
        QDomElement _el;
    };

    QVariant fromString(const QString &value, const QMetaType::Type &type) const;
    QString toString(const QVariant &value) const;
};

