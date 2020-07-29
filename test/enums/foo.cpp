#include "foo.h"

#include <QWidget>

Foo::Foo(QObject *parent) : QObject(parent)
{
}
void Foo::init()
{
    setSampleEnum(Two);
    setSampleFlag(Five | Seven);
}

Foo::Sample Foo::sampleEnum() const
{
    return m_sampleEnum;
}

Foo::SampleFlags Foo::sampleFlag() const
{
    return m_sampleFlag;
}

void Foo::setSampleEnum(Foo::Sample sampleEnum)
{
    if (m_sampleEnum == sampleEnum)
        return;

    m_sampleEnum = sampleEnum;
    emit sampleEnumChanged(m_sampleEnum);
}

void Foo::setSampleFlag(Foo::SampleFlags sampleFlag)
{
    if (m_sampleFlag == sampleFlag)
        return;

    m_sampleFlag = sampleFlag;
    emit sampleFlagChanged(m_sampleFlag);
}
