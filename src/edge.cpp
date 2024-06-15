#include "edge.hpp"
#include "activept.hpp"

#include <QPainter>

edge::edge(activePt* src, activePt* dst) : m_src{src}, m_dst{dst}
{
    setAcceptedMouseButtons(Qt::NoButton);
    m_src->addEdge(this);
    m_dst->addEdge(this);
    adjust();
}

activePt* edge::srcPt() const { return m_src; }
activePt* edge::dstPt() const { return m_dst; }

void edge::adjust()
{
    if (!m_src || !m_dst) return;

    QLineF line(mapFromItem(m_src, 0, 0), mapFromItem(m_dst, 0, 0));

    m_srcPt = line.p1();
    m_dstPt = line.p2();
}

QRectF edge::boundingRect() const
{
    if (!m_src || !m_dst) return QRectF();

    qreal penWidth = 1;
    qreal extra = (penWidth + m_arrowSize) / 2.0;

    return QRectF(m_srcPt, QSizeF(m_dstPt.x() - m_srcPt.x(), m_dstPt.y() - m_srcPt.y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

void edge::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    if (!m_src || !m_dst) return;

    QLineF line(m_srcPt, m_dstPt);
    if (qFuzzyCompare(line.length(), qreal(0.))) return;

    // Draw the line itself
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

    // Draw the arrows
    double angle = std::atan2(-line.dy(), line.dx());

    QPointF sourceArrowP1 = m_srcPt + QPointF(sin(angle + M_PI / 3) * m_arrowSize,
                                              cos(angle + M_PI / 3) * m_arrowSize);
    QPointF sourceArrowP2 = m_srcPt + QPointF(sin(angle + M_PI - M_PI / 3) * m_arrowSize,
                                              cos(angle + M_PI - M_PI / 3) * m_arrowSize);
    QPointF destArrowP1 = m_dstPt + QPointF(sin(angle - M_PI / 3) * m_arrowSize,
                                            cos(angle - M_PI / 3) * m_arrowSize);
    QPointF destArrowP2 = m_dstPt + QPointF(sin(angle - M_PI + M_PI / 3) * m_arrowSize,
                                            cos(angle - M_PI + M_PI / 3) * m_arrowSize);

    painter->setBrush(Qt::black);
    painter->drawPolygon(QPolygonF() << line.p1() << sourceArrowP1 << sourceArrowP2);
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
}
