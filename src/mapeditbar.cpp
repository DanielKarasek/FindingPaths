#include "mapeditbar.h"
#include "map.h"
#include <QPushButton>

#include <QComboBox>
#include <QVBoxLayout>

MapEditBar::MapEditBar(QWidget *parent)
  : QWidget{parent}
{
  m_ret_button = new QPushButton("return to solve", this);
  m_tile_type = new QComboBox(this);
  m_tile_type->addItem("empty");
  m_tile_type->addItem("start");
  m_tile_type->addItem("finish");
  m_tile_type->addItem("border");

  QObject::connect(m_ret_button, &QPushButton::clicked, this, [this](){emit ret_button_clicked();});
  QObject::connect(m_tile_type, &QComboBox::currentTextChanged, this, &MapEditBar::combo_box_changed);

  m_layout = new QVBoxLayout(this);
  m_layout->addWidget(m_tile_type);
  m_layout->addStretch(10000);
  m_layout->addWidget(m_ret_button);
}

void MapEditBar::combo_box_changed(QString str)
{
  if (str == "empty") emit change_tile_type(Map::empty);
  if (str == "finish") emit change_tile_type(Map::finish);
  if (str == "start") emit change_tile_type(Map::start);
  if (str == "border") emit change_tile_type(Map::border);
}

void MapEditBar::set_combo_box_val(const QString &str)
{
  m_tile_type->setCurrentText(str);
}
