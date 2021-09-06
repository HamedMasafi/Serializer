#include "foo.h"

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

class variants : public QObject
{
    Q_OBJECT

public:
    variants();
    ~variants();

private Q_SLOTS:
    void initTestCase();
    void test();
    void cleanupTestCase();
};

variants::variants()
{
}

variants::~variants()
{

}

void variants::initTestCase()
{
    qRegisterMetaType<Foo*>("Foo*");
}

void variants::test()
{
    JsonSerializer s;
    QScopedPointer<Foo> p(new Foo);
    p->init();

    auto o1 = s.serialize(p.data());
    qDebug().noquote() << QJsonDocument(o1).toJson(QJsonDocument::Indented);

    auto ds = s.deserialize<Foo>(o1);
    auto o2 = s.serialize(ds);
    qDebug().noquote() << QJsonDocument(o2).toJson(QJsonDocument::Indented);

    Q_FOREACH (QString key, o1.keys()) {
        if (o1.value(key) != o2.value(key))
            qDebug() << "Values are not equals" <<
                o1.value(key) << o2.value(key);

    }
    QTEST_ASSERT(o1 == o2);
}

void variants::cleanupTestCase()
{

}

QTEST_APPLESS_MAIN(variants)

#include "tst_variants.moc"
