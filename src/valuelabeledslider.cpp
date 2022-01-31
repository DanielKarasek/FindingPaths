#include "valuelabeledslider.h"
#include <QSlider>
#include <QStyleOptionSlider>
#include <QString>
#include <QToolTip>

ValueLabeledSlider::ValueLabeledSlider(QWidget *parent)
  : QSlider{parent}
{

}

ValueLabeledSlider::ValueLabeledSlider(int min, int max, Qt::Orientation orientation, QWidget *parent)
  : QSlider{orientation, parent},
    m_min{min},
    m_max{max}
{
  this->setMaximum(m_max);
  this->setMinimum(m_min);
  this->setTickInterval(1);
}


void ValueLabeledSlider::sliderChange(SliderChange change)
{
  QSlider::sliderChange(change);
  if(change == QAbstractSlider::SliderValueChange)
  {
    QStyleOptionSlider opt;
    initStyleOption(&opt);
    QRect sr = style()->subControlRect(QStyle::CC_Slider, &opt, QStyle::SC_SliderHandle, this);
    QPoint bottomRightCorner = sr.bottomLeft();

    QToolTip::showText(mapToGlobal(QPoint( bottomRightCorner.x(), bottomRightCorner.y())) , QString::number(value()), this);
  }
}


