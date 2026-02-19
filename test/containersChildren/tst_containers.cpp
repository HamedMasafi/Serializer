#include "child.h"
#include "foo.h"
#include "parent.h"

#include <QtTest>

#include <QtCore/QPoint>
#include <QtCore/QDebug>
#include <QtCore/QVector>

#include <binaryserializer.h>
#include <jsonserializer.h>
#include <stringserializer.h>

#ifdef QT_GUI_LIB
#include <QtGui/QPolygon>
#endif

class containers : public QObject
{
    Q_OBJECT

public:
    containers();
    ~containers();

private Q_SLOTS:
    void initTestCase();
    void test();
    void cleanupTestCase();

private:
    Parent *_parent;
};

void containers::test() {
    JsonSerializer s;
    auto serializedData = s.serialize(_parent);
    qDebug().nospace().noquote() << serializedData;
    auto newParent = s.deserialize<Parent>(serializedData);
    QCOMPARE(_parent->children().size(), newParent->children().size());

    QCOMPARE(_parent->children().at(0)->name(), newParent->children().at(0)->name());
    QCOMPARE(_parent->children().at(1)->name(), newParent->children().at(1)->name());
}

containers::containers()
{
}

containers::~containers()
{

}

void containers::initTestCase()
{
    qRegisterMetaType<Parent *>();
    qRegisterMetaType<Child *>();
    registerQList<Child*>();

    _parent = new Parent;
    QList<Child *> children;

    auto child1 = new Child;
    child1->setName("child1");
    child1->setPoint(QPointF{1.2, 3.4});
    children << child1;

    auto child2 = new Child;
    child2->setName("child2");
    child2->setPoint(QPointF{5.6, 7.8});
    children << child2;

    _parent->setChildren(children);
}

void containers::cleanupTestCase()
{

}

QTEST_APPLESS_MAIN(containers)

#include "tst_containers.moc"
