#ifndef FOO_H
#define FOO_H

#include <QtCore/QLocale>
#include <QtCore/QObject>
#include <QtCore/QPoint>
#include <QtCore/QPointF>
#include <QtCore/QRect>
#include <QtCore/QRectF>
#include <QtCore/QRegularExpression>
#include <QtCore/QTime>
#include <QtCore/QUrl>
#include <QtCore/QUuid>
#include <QtGui/QPolygon>
#include <QtGui/QColor>
#include <QtGui/QFont>

class Foo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint point READ point WRITE setPoint NOTIFY pointChanged)
    Q_PROPERTY(QPointF pointF READ pointF WRITE setPointF NOTIFY pointFChanged)
    Q_PROPERTY(QRect rect READ rect WRITE setRect NOTIFY rectChanged)
    Q_PROPERTY(QRectF rectF READ rectF WRITE setRectF NOTIFY rectFChanged)
    Q_PROPERTY(QTime time READ time WRITE setTime NOTIFY timeChanged)
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)
    Q_PROPERTY(QDateTime dateTime READ dateTime WRITE setDateTime NOTIFY
                   dateTimeChanged)
    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged)
    Q_PROPERTY(QLocale locale READ locale WRITE setLocale NOTIFY localeChanged)
    Q_PROPERTY(QRegularExpression regularExpression READ regularExpression WRITE
                   setRegularExpression NOTIFY regularExpressionChanged)
    Q_PROPERTY(QUuid uuid READ uuid WRITE setUuid NOTIFY uuidChanged)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QPolygon polygon READ polygon WRITE setPolygon NOTIFY polygonChanged)
    Q_PROPERTY(QPolygonF polygonF READ polygonF WRITE setPolygonF NOTIFY polygonFChanged)

    QPoint m_point;
    QPointF m_pointF;
    QRect m_rect;
    QRectF m_rectF;
    QTime m_time;
    QDate m_date;
    QDateTime m_dateTime;
    QUrl m_url;
    QLocale m_locale;
    QRegularExpression m_regularExpression;
    QUuid m_uuid;
    QFont m_font;
    QColor m_color;
    QPolygon m_polygon;
    QPolygonF m_polygonF;

public:
    explicit Foo(QObject *parent = nullptr);
    void init();

    QPoint point() const;
    QPointF pointF() const;
    QRect rect() const;
    QRectF rectF() const;
    QTime time() const;
    QDate date() const;
    QDateTime dateTime() const;
    QUrl url() const;
    QLocale locale() const;
    QRegularExpression regularExpression() const;
    QUuid uuid() const;
    QFont font() const;
    QColor color() const;
    QPolygon polygon() const;
    QPolygonF polygonF() const;

Q_SIGNALS:
    void pointChanged(QPoint point);
    void pointFChanged(QPointF pointF);
    void rectChanged(QRect rect);
    void rectFChanged(QRectF rectF);
    void timeChanged(QTime time);
    void dateChanged(QDate date);
    void dateTimeChanged(QDateTime dateTime);
    void urlChanged(QUrl url);
    void localeChanged(QLocale locale);
    void regularExpressionChanged(QRegularExpression regularExpression);
    void uuidChanged(QUuid uuid);
    void fontChanged(QFont font);
    void colorChanged(QColor color);
    void polygonChanged(QPolygon polygon);
    void polygonFChanged(QPolygonF polygonF);

public Q_SLOTS:
    void setPoint(QPoint point);
    void setPointF(QPointF pointF);
    void setRect(QRect rect);
    void setRectF(QRectF rectF);
    void setTime(QTime time);
    void setDate(QDate date);
    void setDateTime(QDateTime dateTime);
    void setUrl(QUrl url);
    void setLocale(QLocale locale);
    void setRegularExpression(QRegularExpression regularExpression);
    void setUuid(QUuid uuid);
    void setFont(QFont font);
    void setColor(QColor color);
    void setPolygon(QPolygon polygon);
    void setPolygonF(QPolygonF polygonF);
};

#endif // FOO_H
