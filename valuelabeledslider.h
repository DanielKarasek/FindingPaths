#ifndef VALUELABELEDSLIDER_H
#define VALUELABELEDSLIDER_H

#include <QObject>
#include <QSlider>

class ValueLabeledSlider : public QSlider
{
  Q_OBJECT
public:
  explicit ValueLabeledSlider(QWidget *parent = nullptr);
  explicit ValueLabeledSlider(int min, int max, Qt::Orientation orientation, QWidget *parent = nullptr);

protected:
  int m_min{10};
  int m_max{1000};
  virtual void sliderChange(SliderChange change) override;

signals:

};

#endif // VALUELABELEDSLIDER_H
