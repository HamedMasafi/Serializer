#include "boo.h"
#include "foo.h"

Foo::Foo(QObject *parent) : QObject(parent), m_foo(nullptr)
{

}

Foo *Foo::foo() const
{
    return m_foo;
}

QList<Boo *> Foo::fooList() const
{
    return m_fooList;
}

Foo::BooMap Foo::booMap() const
{
    return m_booMap;
}

void Foo::setFoo(Foo *foo)
{
    if (m_foo == foo)
        return;

    m_foo = foo;
    Q_EMIT fooChanged(m_foo);
}

void Foo::setFooList(QList<Boo*> fooList)
{
    if (m_fooList == fooList)
        return;

    m_fooList = fooList;
    Q_EMIT fooListChanged(m_fooList);
}

void Foo::setBooMap(Foo::BooMap booMap)
{
    if (m_booMap == booMap)
        return;

    m_booMap = booMap;
    Q_EMIT booMapChanged(m_booMap);
}
