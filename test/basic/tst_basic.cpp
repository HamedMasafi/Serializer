#include <QtTest>

#include <QDebug>
#include <stringserializer.h>

class basic : public QObject
{
    Q_OBJECT

public:
    basic();
    ~basic();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

basic::basic()
{

}

basic::~basic()
{

}

void basic::initTestCase()
{

}

void basic::cleanupTestCase()
{

}

#define TEST(type, value) \
    do{ \
    v = QVariant(value); \
    tmp = ser.toString(v); \
    deserialized = ser.fromString(tmp, type); \
    qDebug() << v << deserialized; \
    QVERIFY2(deserialized == v, "verfy faild for" #type); \
    } while (false)

void basic::test_case1()
{
    StringSerializer ser;
    QVariant v;
    QString tmp;
    QVariant deserialized;

    TEST(QMetaType::Int, 5);
    TEST(QMetaType::Short, 6);
    TEST(QMetaType::Long, 6);
    TEST(QMetaType::LongLong, 6);
    TEST(QMetaType::Float, 3.14f);
    TEST(QMetaType::Double, 1024.2048);
    TEST(QMetaType::QString, "test");
    TEST(QMetaType::QDate, QDate::currentDate());
    TEST(QMetaType::QTime, QTime::currentTime());
    TEST(QMetaType::QDateTime, QDateTime::currentDateTime());
    TEST(QMetaType::QPoint, QPoint(12, 34));
    TEST(QMetaType::QSize, QSize(12, 34));
    TEST(QMetaType::QRect, QRect(3, 4, 6, 7));
    TEST(QMetaType::QPointF, QPointF(12.98, 34.87));
    TEST(QMetaType::QSizeF, QSizeF(12.98, 34.87));
    TEST(QMetaType::QRectF, QRectF(3.4, 4.5, 6.001, 7.54));
    TEST(QMetaType::QUuid, QUuid::createUuid());
}

QTEST_APPLESS_MAIN(basic)

#include "tst_basic.moc"
