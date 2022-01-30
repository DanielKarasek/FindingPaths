#ifndef SOLUTIONPAINTDEVICE_H
#define SOLUTIONPAINTDEVICE_H

#include <QWidget>
#include <QColor>

#include "map.h"
#include "solvingmethod.h"
#include <map>



class SolutionPaintDevice : public QWidget
{
  using Shape = MapPosition;
  using Position = MapPosition;
  Q_OBJECT
public:

  explicit SolutionPaintDevice(int width, QWidget *parent = nullptr);

public slots:
  void repaint_map(const MapVectorRaw &raw_data);
  void repaint_solution(Solution const *sol);
  void paint_path(const PositionVector &path);
  void set_modification(bool new_val=true){m_modification_on = new_val;}
  void set_modification_tile_type(Map::TileType type){m_modification_tile = type;}
  void update_tile_view(const MapPosition &pos, Map::TileType tile_type);

protected:    

  struct PositionStepper
  {
    int start_x;
    int start_y;
    double step_x;
    double step_y;
  };

  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void paintEvent(QPaintEvent *event) override;
  void resizeEvent(QResizeEvent *event) override;

  MapPosition &get_MapPosition(int click_x, int click_y, MapPosition &out);
  void draw_vertical(QPainter &painter);
  void draw_horizontal(QPainter &painter);
  void draw_grid(QPainter &painter);
  void fill_grid(const MapPosition &pos, QColor &color, QPainter &painter, bool should_update=true);
  void resize_image(int new_width);

  void get_position_stepper(const MapPosition &pos, PositionStepper *out);

  QImage m_image;

  std::map<Map::TileType, QColor> m_color_map{{Map::empty, {255, 255, 255}},{Map::finish, {255, 255, 0}},{Map::start, {0, 255, 0}},{Map::border, {150, 150, 150}}};

  Shape m_map_shape{5, 2};
  Shape m_image_shape;

  bool m_modification_on{false};
  Map::TileType m_modification_tile{Map::TileType::empty};

  MapPosition m_last_modified_pos{-1, -1};

signals:
  void resize_event_issued();
  void update_tile(const MapPosition &pos, Map::TileType tile_type);
};

#endif // SOLUTIONPAINTDEVICE_H
