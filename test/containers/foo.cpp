#include "foo.h"

Foo::Foo(QObject *parent) : QObject(parent)
{

}
void Foo::init()
{
    setStringList(QStringList() << "One" << "Two" << "Three");
    setVariantList(QVariantList() << "One" << 2 << 3.14);
    QVariantMap vm;
    vm.insert("a", "hi");
    vm.insert("b", 2);
    vm.insert("c", 'a');
    setVariantMap(vm);
    setListInt(QList<int>() << 1 << 2 << 3);
    setSetInt(QSet<int>() << 1 << 2 << 3);
    setVectorInt(QVector<int>() << 1 << 2 << 3);
}

QStringList Foo::stringList() const
{
    return m_stringList;
}

QList<int> Foo::listInt() const
{
    return m_listInt;
}

QVariantList Foo::variantList() const
{
    return m_variantList;
}

QSet<int> Foo::setInt() const
{
    return m_setInt;
}

QVariantMap Foo::variantMap() const
{
    return m_variantMap;
}

QVector<int> Foo::vectorInt() const
{
    return m_vectorInt;
}

void Foo::setStringList(QStringList stringList)
{
    if (m_stringList == stringList)
        return;

    m_stringList = stringList;
    Q_EMIT stringListChanged(m_stringList);
}

void Foo::setListInt(QList<int> listInt)
{
    if (m_listInt == listInt)
        return;

    m_listInt = listInt;
    Q_EMIT listIntChanged(m_listInt);
}

void Foo::setVariantList(QVariantList variantList)
{
    if (m_variantList == variantList)
        return;

    m_variantList = variantList;
    Q_EMIT variantListChanged(m_variantList);
}

void Foo::setSetInt(QSet<int> setInt)
{
    if (m_setInt == setInt)
        return;

    m_setInt = setInt;
    Q_EMIT setIntChanged(m_setInt);
}

void Foo::setVariantMap(QVariantMap variantMap)
{
    if (m_variantMap == variantMap)
        return;

    m_variantMap = variantMap;
    Q_EMIT variantMapChanged(m_variantMap);
}

void Foo::setVectorInt(QVector<int> vectorInt)
{
    if (m_vectorInt == vectorInt)
        return;

    m_vectorInt = vectorInt;
    Q_EMIT vectorIntChanged(m_vectorInt);
}
