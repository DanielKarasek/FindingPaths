#ifndef MEDIATOR_H
#define MEDIATOR_H

#include "map.h"
#include "solutionpaintdevice.h"
#include "solvingmethod.h"
#include "alphastar.h"

#include <QObject>
#include <map>
#include <string>
#include <memory>
#include <chrono>
#include <vector>


class Mediator : public QObject
{
  Q_OBJECT
public:
  explicit Mediator(std::shared_ptr<Map> map, QObject *parent = nullptr);

  void attach_solution_paint_dev(SolutionPaintDevice *dev2att);
public slots:
  void solution_paint_resize();
  void change_tile_type(const MapPosition &pos, Map::TileType tile_type);
  void start_solve();
  void reset_solve();
  void toggle_pause_flag();
  void solve_step();

  void change_step_time(double new_step_time);
  void set_method(const std::string &method_name);

protected:
  enum SolutionState
  {
    empty,
    solving,
    solved
  };

  std::shared_ptr<Map> m_map;
  SolutionPaintDevice *m_sol_device;

  double m_step_time{1000};
  SolutionState m_sol_state{empty};

  SolutionDecorator m_sol_dec;

  std::map<std::string, std::shared_ptr<SolvingMethod>> m_methods;
  std::shared_ptr<SolvingMethod> m_current_method;

  bool m_solving {false};

  QTimer *m_timer;
  void _toggle_pause_flag(){m_solving = true;}
signals:

};

#endif // MEDIATOR_H
