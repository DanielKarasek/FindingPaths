#include "solutionpaintdevice.h"
#include <QPainter>
#include <QPoint>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QImage>
#include <QColor>
#include <iostream>
#include <algorithm>


#include "map.h"
#include "solvingmethod.h"


SolutionPaintDevice::SolutionPaintDevice(int width, QWidget *parent)
  : QWidget{parent}
{
  resize_image(width);
  update();
}

void SolutionPaintDevice::get_position_stepper(const MapPosition &pos, PositionStepper *out)
{
  out->step_x = static_cast<double>(m_image_shape.x)/m_map_shape.x;
  out->step_y = static_cast<double>(m_image_shape.y)/m_map_shape.y;
  out->start_x = pos.x * out->step_x + 1;
  out->start_y = pos.y * out->step_y + 1;
}
void SolutionPaintDevice::paint_path(const PositionVector &path)
{
  PositionStepper pos_step_previous;
  get_position_stepper(path[0], &pos_step_previous);
  pos_step_previous.start_x += pos_step_previous.step_x*0.5;
  pos_step_previous.start_y += pos_step_previous.step_x*0.5;
  QPainter painter(&m_image);
  QPen pen(QColor{0,0,255});
  pen.setWidth(3);
  painter.setPen(pen);
  bool first = true;
  for (const auto &pos: path )
  {
    if (first)
    {
      first = false;
      continue;
    }
    PositionStepper pos_step_current;
    get_position_stepper(pos, &pos_step_current);
    pos_step_current.start_x += pos_step_current.step_x*0.5;
    pos_step_current.start_y += pos_step_current.step_x*0.5;
    painter.drawLine(pos_step_previous.start_x, pos_step_previous.start_y, pos_step_current.start_x, pos_step_current.start_y);
    pos_step_previous = pos_step_current;
  }
  update();
}
void SolutionPaintDevice::resize_image(int width)
{
  int height = static_cast<int>(width*(static_cast<double>(m_map_shape.y)/m_map_shape.x));

  m_image_shape = {width, height};
  m_image = QImage(m_image_shape.x, m_image_shape.y, QImage::Format_ARGB32);
  emit resize_event_issued();
}

void SolutionPaintDevice::draw_vertical(QPainter &painter)
{
  for(int i=0; i<=m_map_shape.y+1; i++)
  {
    double y_coord = (i)*static_cast<double>(m_image_shape.y)/m_map_shape.y;
    if (i==m_map_shape.y) y_coord-=1;
    painter.drawLine(0, y_coord, m_image_shape.x, y_coord);
  }
}

void SolutionPaintDevice::draw_horizontal(QPainter &painter)
{
  for(int i=0; i<=m_map_shape.x; i++)
  {
    double x_coord = (i)*static_cast<double>(m_image_shape.x)/m_map_shape.x;
    if (i==m_map_shape.x) x_coord-=1;
    painter.drawLine(x_coord, 0, x_coord, m_image_shape.y);
  }
}

void SolutionPaintDevice::draw_grid(QPainter &painter)
{
  draw_vertical(painter);
  draw_horizontal(painter);
}

void SolutionPaintDevice::fill_grid(const MapPosition &pos, QColor &color, QPainter &painter, bool should_update)
{
  PositionStepper pos_step;
  get_position_stepper(pos, &pos_step);
  QRect draw_rect{pos_step.start_x, pos_step.start_y, static_cast<int>(pos_step.step_x)-1, static_cast<int>(pos_step.step_y)-1};
  painter.fillRect(draw_rect, color);
  if(should_update) update(draw_rect);
}

void SolutionPaintDevice::repaint_map(const MapVectorRaw &raw_data)
{
  Shape new_shape;
  new_shape.x = raw_data[0].size();
  new_shape.y = raw_data.size();
  m_map_shape = new_shape;
  QPainter painter(&m_image);
  painter.fillRect(m_image.rect(), {255, 255, 255});
  draw_grid(painter);

  QColor start_color{0, 255, 0};
  QColor fin_color{255, 255, 0};
  QColor border_color{150, 150, 150};
  for (int y=0; const auto &row_data : raw_data)
  {
    for(int x=0; const auto tile : row_data)
    {
      MapPosition pos{x, y};
      if (tile==Map::TileType::start) fill_grid(pos, start_color, painter, true);
      if (tile==Map::TileType::finish) fill_grid(pos, fin_color, painter, true);
      if (tile==Map::TileType::border) fill_grid(pos, border_color, painter, true);
      x++;
    }
    y++;
  }
  update();
}

void SolutionPaintDevice::update_tile_view(const MapPosition &pos, Map::TileType tile_type)
{
  QPainter painter(&m_image);
  fill_grid(pos, m_color_map[tile_type], painter, true);
}

void SolutionPaintDevice::repaint_solution(Solution const *sol)
{
  for(const auto &val_trans : sol->unchecked)
  {
    QPainter painter(&m_image);
    QColor c = QColor(180, 90, 180);
    fill_grid(val_trans.transition.current, c, painter, true);

  }
  for(const auto &val_trans : sol->checked)
  {
    QPainter painter(&m_image);
    int r = 255;
    int g = std::min<double>(std::max<double>(0, 255-val_trans.value*3), 255);
    int b = std::min<double>(std::max<double>(0, 255-val_trans.value*3), 255);
    QColor c = QColor(r, g, b);
    fill_grid(val_trans.transition.current, c, painter, true);
  }

}


MapPosition &SolutionPaintDevice::get_MapPosition(int click_x, int click_y, MapPosition &out)
{

  if (click_x < 0 || click_y < 0 || click_x > m_image_shape.x || click_y > m_image_shape.y)
  {
    out.x = -1;
    out.y = -1;
    return out;
  }

  double step_x = static_cast<double>(m_image_shape.x)/(m_map_shape.x);
  double step_y = static_cast<double>(m_image_shape.y)/(m_map_shape.y);
  out.x = click_x/step_x;
  out.y = click_y/step_y;
  return out;
}


void SolutionPaintDevice::mousePressEvent(QMouseEvent *event)
{
  if (event->button() == Qt::LeftButton && m_modification_on)
  {
    m_last_modified_pos = get_MapPosition(event->pos().x(), event->pos().y(), m_last_modified_pos);
    if (m_last_modified_pos.x == -1) return;
    emit update_tile(m_last_modified_pos, m_modification_tile);
  }
}
void SolutionPaintDevice::mouseMoveEvent(QMouseEvent *event)
{
  if ((event->buttons()  & Qt::LeftButton) && m_modification_on)
  {
    MapPosition tmp_pos;
    tmp_pos = get_MapPosition(event->pos().x(), event->pos().y(), tmp_pos);
    if (tmp_pos.x == -1 || tmp_pos == m_last_modified_pos) return;
    m_last_modified_pos = tmp_pos;
    emit update_tile(m_last_modified_pos, m_modification_tile);
  }

}
void SolutionPaintDevice::mouseReleaseEvent(QMouseEvent *event)
{
  m_last_modified_pos = {-1, -1};
}

void SolutionPaintDevice::paintEvent(QPaintEvent *event)
{
  QPainter painter(this);
  QRect tmp_rect = event->rect();
  painter.drawImage(tmp_rect, m_image, tmp_rect);
}


void SolutionPaintDevice::resizeEvent(QResizeEvent *event)
{
  resize_image(event->size().width());
}
