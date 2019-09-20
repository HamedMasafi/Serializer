#include "boo.h"
#include "foo.h"

Foo::Foo(QObject *parent) : QObject(parent), m_foo(nullptr)
{

}

int Foo::n() const
{
    return m_n;
}

QString Foo::s() const
{
    return m_s;
}

float Foo::f() const
{
    return m_f;
}

QStringList Foo::strings() const
{
    return m_strings;
}

QVariantList Foo::variants() const
{
    return m_variants;
}

Foo *Foo::foo() const
{
    return m_foo;
}

QList<Boo *> Foo::fooList() const
{
    return m_fooList;
}

QVariantMap Foo::variantMap() const
{
    return m_variantMap;
}

Foo::BooMap Foo::booMap() const
{
    return m_booMap;
}

void Foo::setN(int n)
{
    if (m_n == n)
        return;

    m_n = n;
    emit nChanged(m_n);
}

void Foo::setS(QString s)
{
    if (m_s == s)
        return;

    m_s = s;
    emit sChanged(m_s);
}

void Foo::setF(float f)
{
    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_f, f))
        return;

    m_f = f;
    emit fChanged(m_f);
}

void Foo::setStrings(QStringList strings)
{
    if (m_strings == strings)
        return;

    m_strings = strings;
    emit stringsChanged(m_strings);
}

void Foo::setVariants(QVariantList variants)
{
    if (m_variants == variants)
        return;

    m_variants = variants;
    emit variantsChanged(m_variants);
}

void Foo::setFoo(Foo *foo)
{
    if (m_foo == foo)
        return;

    m_foo = foo;
    emit fooChanged(m_foo);
}

void Foo::setFooList(QList<Boo*> fooList)
{
    if (m_fooList == fooList)
        return;

    m_fooList = fooList;
    emit fooListChanged(m_fooList);
}

void Foo::setVariantMap(QVariantMap variantMap)
{
    if (m_variantMap == variantMap)
        return;

    m_variantMap = variantMap;
    emit variantMapChanged(m_variantMap);
}

void Foo::setBooMap(Foo::BooMap booMap)
{
    if (m_booMap == booMap)
        return;

    m_booMap = booMap;
    emit booMapChanged(m_booMap);
}
