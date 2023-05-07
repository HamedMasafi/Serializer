#pragma once

#include "abstractserializer.h"
#include <QDomElement>

class XmlSerializer : public AbstractSerializer
{
public:
    XmlSerializer();

//    QDomElement toDomElement(const QMetaEnum &en, const QVariant &value);
    QDomElement toDomElement(QDomDocument &doc, const QString &name, const QVariant &v) const;
    QDomElement toDomElement(QDomDocument &doc, const QString &name, QVariantList list) const;
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

    void addToElement(QDomElement &element, int n);
//    void addToElement(QDomElement &element, cnst QDomElement &child);
};

