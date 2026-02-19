#pragma once

#include <QObject>

class Child;
class Parent : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<Child*> children READ children WRITE setChildren NOTIFY childrenChanged FINAL)

public:
    explicit Parent(QObject *parent = nullptr);

    QList<Child *> children() const;
    void setChildren(const QList<Child *> &newChildren);

signals:
    void childrenChanged();

private:
    QList<Child *> m_children;
};
