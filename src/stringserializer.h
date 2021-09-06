#ifndef STRINGSERIALIZER_H
#define STRINGSERIALIZER_H

#include "abstractserializer.h"

class StringSerializer : public AbstractSerializer
{
public:
    StringSerializer();

    bool readString(QString &text, QString &out) const;

    QVariant fromString(const QString &value, const QMetaType::Type &type) const override;
    QString toString(const QVariant &value) const override;
    QList<int> toListInt(const QString &s) const;
    QList<int> toListInt(const QString &s, const QString &sep) const;
    QList<qreal> toListReal(const QString &s) const;
    QList<qreal> toListReal(const QString &s, const QString &sep) const;
    QList<float> toListFloat(const QString &s) const;

    QString fromList(const QList<int> &list) const;
    QString fromList(const QList<qreal> &list) const;
    QString fromList(const QList<float> &list) const;
    QString fromVariantList(const QVariantList &list) const;

private:
    virtual QString escapeString(const QString &str) const override;
    virtual QString unescapeString(const QString &str) const override;
};

#endif // STRINGSERIALIZER_H
