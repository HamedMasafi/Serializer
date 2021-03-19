#include "foo.h"

Foo::Foo(QObject *parent) : QObject(parent)
{

}

QPoint Foo::point() const
{
    return m_point;
}

void Foo::init()
{
    setPoint(QPoint(1, 2));
    setPointF(QPointF(1.2, 3.4));
    setRect(QRect(1, 2, 3, 4));
    setRectF(QRectF(1.2, 2.3, 3.4, 4.5));
    setDate(QDate::currentDate());
    setTime(QTime::currentTime());
    setDateTime(QDateTime::currentDateTime());
    setUrl(QUrl("http://google.com"));
    setLocale(QLocale("fa-IR"));
    setRegularExpression(QRegularExpression(".*"));
    setUuid(QUuid::createUuid());
    QFont f("Tahoma");
    f.setBold(true);
    f.setItalic(true);
    f.setPointSize(14);
    setFont(f);
    setColor(QColor(Qt::green));
    setPolygon(QPolygon() << QPoint(1, 2) << QPoint(3, 4) << QPoint(5, 6));
    setPolygonF(QPolygonF() << QPointF(1.2, 2.3) << QPointF(3.4, 4.5) << QPointF(5.6, 6.7));
}

QPointF Foo::pointF() const
{
    return m_pointF;
}

QRect Foo::rect() const
{
    return m_rect;
}

QRectF Foo::rectF() const
{
    return m_rectF;
}

QTime Foo::time() const
{
    return m_time;
}

QDate Foo::date() const
{
    return m_date;
}

QDateTime Foo::dateTime() const
{
    return m_dateTime;
}

QUrl Foo::url() const
{
    return m_url;
}

QLocale Foo::locale() const
{
    return m_locale;
}

QRegularExpression Foo::regularExpression() const
{
    return m_regularExpression;
}

QUuid Foo::uuid() const
{
    return m_uuid;
}

QFont Foo::font() const
{
    return m_font;
}

QColor Foo::color() const
{
    return m_color;
}

QPolygon Foo::polygon() const
{
    return m_polygon;
}

QPolygonF Foo::polygonF() const
{
    return m_polygonF;
}

void Foo::setPoint(QPoint point)
{
    if (m_point == point)
        return;

    m_point = point;
    Q_EMIT pointChanged(m_point);
}

void Foo::setPointF(QPointF pointF)
{
    if (m_pointF == pointF)
        return;

    m_pointF = pointF;
    Q_EMIT pointFChanged(m_pointF);
}

void Foo::setRect(QRect rect)
{
    if (m_rect == rect)
        return;

    m_rect = rect;
    Q_EMIT rectChanged(m_rect);
}

void Foo::setRectF(QRectF rectF)
{
    if (m_rectF == rectF)
        return;

    m_rectF = rectF;
    Q_EMIT rectFChanged(m_rectF);
}

void Foo::setTime(QTime time)
{
    if (m_time == time)
        return;

    m_time = time;
    Q_EMIT timeChanged(m_time);
}

void Foo::setDate(QDate date)
{
    if (m_date == date)
        return;

    m_date = date;
    Q_EMIT dateChanged(m_date);
}

void Foo::setDateTime(QDateTime dateTime)
{
    if (m_dateTime == dateTime)
        return;

    m_dateTime = dateTime;
    Q_EMIT dateTimeChanged(m_dateTime);
}

void Foo::setUrl(QUrl url)
{
    if (m_url == url)
        return;

    m_url = url;
    Q_EMIT urlChanged(m_url);
}

void Foo::setLocale(QLocale locale)
{
    if (m_locale == locale)
        return;

    m_locale = locale;
    Q_EMIT localeChanged(m_locale);
}

void Foo::setRegularExpression(QRegularExpression regularExpression)
{
    if (m_regularExpression == regularExpression)
        return;

    m_regularExpression = regularExpression;
    Q_EMIT regularExpressionChanged(m_regularExpression);
}

void Foo::setUuid(QUuid uuid)
{
    if (m_uuid == uuid)
        return;

    m_uuid = uuid;
    Q_EMIT uuidChanged(m_uuid);
}

void Foo::setFont(QFont font)
{
    if (m_font == font)
        return;

    m_font = font;
    Q_EMIT fontChanged(m_font);
}

void Foo::setColor(QColor color)
{
    if (m_color == color)
        return;

    m_color = color;
    Q_EMIT colorChanged(m_color);
}

void Foo::setPolygon(QPolygon polygon)
{
    if (m_polygon == polygon)
        return;

    m_polygon = polygon;
    Q_EMIT polygonChanged(m_polygon);
}

void Foo::setPolygonF(QPolygonF polygonF)
{
    if (m_polygonF == polygonF)
        return;

    m_polygonF = polygonF;
    Q_EMIT polygonFChanged(m_polygonF);
}
