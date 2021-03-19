#ifndef FOO_H
#define FOO_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariantList>

class Boo;
class Foo : public QObject
{
    Q_OBJECT

public:
    typedef QMap<QString, Boo*> BooMap;

private:
    Q_PROPERTY(Foo* foo READ foo WRITE setFoo NOTIFY fooChanged)
    Q_PROPERTY(QList<Boo*> fooList READ fooList WRITE setFooList NOTIFY fooListChanged)
    Q_PROPERTY(BooMap booMap READ booMap WRITE setBooMap NOTIFY booMapChanged)

    Foo* m_foo;
    QList<Boo*> m_fooList;
    BooMap m_booMap;

public:
    Q_INVOKABLE Foo(QObject *parent = nullptr);

    Foo* foo() const;
    QList<Boo*> fooList() const;
    BooMap booMap() const;

Q_SIGNALS:
    void fooChanged(Foo* foo);
    void fooListChanged(QList<Boo*> fooList);
    void booMapChanged(BooMap booMap);

public Q_SLOTS:
    void setFoo(Foo* foo);
    void setFooList(QList<Boo *> fooList);
    void setBooMap(BooMap booMap);
};

Q_DECLARE_METATYPE(Foo*)
Q_DECLARE_METATYPE(QList<Foo*>)

#endif // FOO_H
