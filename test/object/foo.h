#ifndef FOO_H
#define FOO_H

#include <QObject>
#include <QString>
#include <QVariantList>

class Boo;
class Foo : public QObject
{
    Q_OBJECT

public:
    typedef QMap<QString, Boo*> BooMap;

private:
//    Q_PROPERTY(int n READ n WRITE setN NOTIFY nChanged)
//    Q_PROPERTY(QString s READ s WRITE setS NOTIFY sChanged)
//    Q_PROPERTY(float f READ f WRITE setF NOTIFY fChanged)
    Q_PROPERTY(QStringList strings READ strings WRITE setStrings NOTIFY stringsChanged)
//    Q_PROPERTY(QVariantList variants READ variants WRITE setVariants NOTIFY variantsChanged)
//    Q_PROPERTY(Foo* foo READ foo WRITE setFoo NOTIFY fooChanged)
//    Q_PROPERTY(QList<Boo*> fooList READ fooList WRITE setFooList NOTIFY fooListChanged)
//    Q_PROPERTY(QVariantMap variantMap READ variantMap WRITE setVariantMap NOTIFY variantMapChanged)
//    Q_PROPERTY(BooMap booMap READ booMap WRITE setBooMap NOTIFY booMapChanged)

    int m_n;

    QString m_s;

    float m_f;

    QStringList m_strings;

    QVariantList m_variants;

    Foo* m_foo;

    QList<Boo*> m_fooList;

    QVariantMap m_variantMap;

    BooMap m_booMap;

public:
    Q_INVOKABLE Foo(QObject *parent = nullptr);

    int n() const;

    QString s() const;

    float f() const;

    QStringList strings() const;

    QVariantList variants() const;

    Foo* foo() const;

    QList<Boo*> fooList() const;

    QVariantMap variantMap() const;

    BooMap booMap() const;

signals:

    void nChanged(int n);

    void sChanged(QString s);

    void fChanged(float f);

    void stringsChanged(QStringList strings);

    void variantsChanged(QVariantList variants);

    void fooChanged(Foo* foo);

    void fooListChanged(QList<Boo*> fooList);

    void variantMapChanged(QVariantMap variantMap);

    void booMapChanged(BooMap booMap);

public slots:
    void setN(int n);
    void setS(QString s);
    void setF(float f);
    void setStrings(QStringList strings);
    void setVariants(QVariantList variants);
    void setFoo(Foo* foo);
    void setFooList(QList<Boo *> fooList);
    void setVariantMap(QVariantMap variantMap);
    void setBooMap(BooMap booMap);
};

Q_DECLARE_METATYPE(Foo*)
Q_DECLARE_METATYPE(QList<Foo*>)

#endif // FOO_H
