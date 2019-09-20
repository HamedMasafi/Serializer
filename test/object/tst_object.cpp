#include "foo.h"
#include "boo.h"

#include <QtTest>

#include <QPoint>
#include <QDebug>
#include <QVector>
#include <QPolygon>
#include <binaryserializer.h>

#include <jsonserializer.h>
#include <stringserializer.h>

class object : public QObject
{
    Q_OBJECT

    void initFoo(Foo *);
public:
    object();
    ~object();

private slots:
    void initTestCase();
    void test();
    void cleanupTestCase();
};

void object::initFoo(Foo *f)
{
    f->setN(4);
    f->setF(3.14f);
    f->setS("Hi\"There");
    f->setStrings(QStringList() << "One" << "Two" << "Three");
    f->setVariants(QVariantList() << "One" << 2 << 3.14);
    QVariantMap vm;
    vm.insert("a", "hi");
    vm.insert("b", 2);
    vm.insert("c", 'a');
    f->setVariantMap(vm);
}

object::object()
{
}

object::~object()
{

}

void object::initTestCase()
{
//    qDebug() << "#" << qRegisterMetaType<Foo::FooList>();
    qRegisterMetaType<Foo*>("Foo*");
    qRegisterMetaType<Foo::BooMap>("BooMap");
    qRegisterMetaType<QList<Boo*> >("QList<Foo*>");
}

void object::test()
{
    JsonSerializer s;
    QScopedPointer<Foo> p(new Foo);
    initFoo(p.data());

    auto p2 = new Foo(p.data());
    initFoo(p2);
    p->setFoo(p2);

    QList<Boo*> booList;
    Foo::BooMap map;
    for (int i = 0; i < 3; ++i) {
        auto p3 = new Boo(p.data());
        p3->setName(QString("child #%1").arg(i));
        booList.append(p3);
        map.insert(p3->name(), p3);
    }
    p->setFooList(booList);
    p->setBooMap(map);
    qDebug() << "===================================";
    auto o1 = s.serialize(p.data());
    qDebug().noquote() << QJsonDocument(o1).toJson(QJsonDocument::Indented);

    auto pp2 = s.deserialize<Foo>(o1);
    auto o2 = s.serialize(pp2);

    qDebug().noquote() << QJsonDocument(o2).toJson(QJsonDocument::Indented);

    QTEST_ASSERT(o1 == o2);
}

void object::cleanupTestCase()
{

}

QTEST_APPLESS_MAIN(object)

#include "tst_object.moc"
