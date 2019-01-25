#ifndef STRINGSERIALIZER_H
#define STRINGSERIALIZER_H

#include "abstractserializer.h"

class StringSerializer : public AbstractSerializer
{
public:
    StringSerializer();

    QVariant fromString(const QString &value, const QMetaType::Type &type) const;
    QString toString(const QVariant &value) const;

private:
    QList<int> toListInt(const QString &s) const;
    QList<qreal> toListReal(const QString &s) const;
    QList<float> toListFloat(const QString &s) const;

    QString fromList(const QList<int> &list) const;
    QString fromList(const QList<qreal> &list) const;
    QString fromList(const QList<float> &list) const;

    QString escapeString(QString &str) const;
    QString unescapeString(QString &str) const;
    void readString(QString &text, QString &out);
};

#endif // STRINGSERIALIZER_H
