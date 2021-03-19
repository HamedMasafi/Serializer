#ifndef FOO_H
#define FOO_H

#include <QtCore/QObject>
#include <QtCore/QSet>
#include <QtCore/QVariantList>

class Foo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList stringList READ stringList WRITE setStringList NOTIFY
                   stringListChanged)
    Q_PROPERTY(
        QList<int> listInt READ listInt WRITE setListInt NOTIFY listIntChanged)
    Q_PROPERTY(QVariantList variantList READ variantList WRITE setVariantList
                   NOTIFY variantListChanged)
    Q_PROPERTY(
        QSet<int> setInt READ setInt WRITE setSetInt NOTIFY setIntChanged)
    Q_PROPERTY(QVariantMap variantMap READ variantMap WRITE setVariantMap NOTIFY variantMapChanged)
    Q_PROPERTY(QVector<int> vectorInt READ vectorInt WRITE setVectorInt NOTIFY vectorIntChanged)

    QStringList m_stringList;
    QList<int> m_listInt;
    QVariantList m_variantList;
    QSet<int> m_setInt;
    QVariantMap m_variantMap;
    QVector<int> m_vectorInt;

public:
    explicit Foo(QObject *parent = nullptr);
    void init();

    QStringList stringList() const;
    QList<int> listInt() const;
    QVariantList variantList() const;
    QSet<int> setInt() const;
    QVariantMap variantMap() const;
    QVector<int> vectorInt() const;

public Q_SLOTS:
    void setStringList(QStringList stringList);
    void setListInt(QList<int> listInt);
    void setVariantList(QVariantList variantList);
    void setSetInt(QSet<int> setInt);
    void setVariantMap(QVariantMap variantMap);
    void setVectorInt(QVector<int> vectorInt);

Q_SIGNALS:
    void stringListChanged(QStringList stringList);
    void listIntChanged(QList<int> listInt);
    void variantListChanged(QVariantList variantList);
    void setIntChanged(QSet<int> setInt);
    void variantMapChanged(QVariantMap variantMap);
    void vectorIntChanged(QVector<int> vectorInt);
};

#endif // FOO_H
