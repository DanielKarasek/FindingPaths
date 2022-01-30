#include "mediator.h"

#include "alphastar.h"
#include "bfs.h"
#include "dfs.h"

#include <QTimer>
#include <QObject>
#include <string>
#include <iostream>

Mediator::Mediator(std::shared_ptr<Map> map, QObject *parent)
  : QObject{parent}, m_map{map}
{
  m_methods.insert({"alphastar", std::make_shared<alphastar>()});
  m_methods.insert({"BFS", std::make_shared<BFS>()});
  m_methods.insert({"DFS", std::make_shared<DFS>()});

  m_current_method = m_methods["alphastar"];

  m_timer = new QTimer(this);
  QObject::connect(m_timer, &QTimer::timeout, this, &Mediator::solve_step);
}

void Mediator::set_method(const std::string &str)
{
  m_current_method = m_methods[str];
  reset_solve();
}

void Mediator::attach_solution_paint_dev(SolutionPaintDevice *dev2att)
{
  m_sol_device = dev2att;
  QObject::connect(m_sol_device, &SolutionPaintDevice::resize_event_issued, this, &Mediator::solution_paint_resize);
  QObject::connect(m_sol_device, &SolutionPaintDevice::update_tile, this, &Mediator::change_tile_type);

}

void Mediator::solution_paint_resize()
{
  m_sol_device->repaint_map(m_map->get_raw_data());
  if (m_sol_state != Mediator::empty)
    m_sol_device->repaint_solution(m_sol_dec.sol);
  if (m_sol_state == Mediator::solved)
  {
    PositionVector res;
    m_current_method->backtrack_result(&res);
    m_sol_device->paint_path(res);
  }
}


void Mediator::change_tile_type(const MapPosition &pos, Map::TileType tile_type)
{
  if(m_map->updateTile(pos, tile_type))
    m_sol_device->repaint_map(m_map->get_raw_data());
}
void Mediator::change_step_time(double new_step_time)
{
  if (m_solving)
  {
    m_timer->stop();
    m_timer->start(new_step_time);
  }
  m_step_time = new_step_time;
}



void Mediator::start_solve()
{
  reset_solve();
  m_solving = true;
  m_timer->start(m_step_time);
  m_sol_state = Mediator::solving;
}

void Mediator::reset_solve()
{
  if (m_solving) m_timer->stop();

  m_current_method->init(m_map);
  m_sol_device->repaint_map(m_map->get_raw_data());
  m_solving = false;
  m_sol_state = Mediator::empty;
}

void Mediator::solve_step()
{
  m_current_method->step(&m_sol_dec);
  m_sol_device->repaint_solution(m_sol_dec.sol);
  if (m_sol_dec.finished)
  {
    m_timer->stop();
    m_solving = false;
    PositionVector res;
    m_current_method->backtrack_result(&res);
    m_sol_device->paint_path(res);
    m_sol_state = Mediator::solved;
  }
}

void Mediator::toggle_pause_flag()
{
  m_solving = !m_solving;
  if (!m_solving) m_timer->stop();
  if (m_solving && m_sol_state == Mediator::solving) m_timer->start(m_step_time);
}
