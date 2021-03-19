#include "boo.h"

Boo::Boo(QObject *parent) : QObject(parent)
{

}

QString Boo::name() const
{
    return m_name;
}

void Boo::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    Q_EMIT nameChanged(m_name);
}
