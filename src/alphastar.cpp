#include "alphastar.h"
#include "map.h"
#include "solvingmethod.h"

#include <memory>
#include <cmath>

#include <list>

#include <algorithm>

using AStarValuedTransitionList = std::list<AStarValuedTransition>;
using PositionPairList = std::list<PositionPair>;
std::ostream &operator<<(std::ostream &os, const AStarValuedTransition &val_trans)
{
  os << "Transition from: " << val_trans.transition.from << "to: " << val_trans.transition.current
     << "has value: " << val_trans.total_value() << '\n';
  return os;
}

bool in_valued_transition_list(const MapPosition &pos, const AStarValuedTransitionList &trans_list)
{
  for (const auto &valued_transition : trans_list)
    if (valued_transition.transition.current == pos)
      return true;

  return false;
}

auto get_best_transition_iter(AStarValuedTransitionList &transitions)
{
  double val_min = transitions.begin()->total_value();
  auto iter_min = transitions.begin();
  for (auto trans_iter = transitions.begin(); trans_iter != transitions.end(); ++trans_iter)
  {
    if ((*trans_iter).total_value() < val_min)
    {
      val_min = (*trans_iter).total_value();
      iter_min = trans_iter;
    }
  }
  return iter_min;
}

double base_heuristic(const MapPosition &current, const MapPosition &fin)
{
  double x_dif = current.x - fin.x;
  double y_dif = current.y - fin.y;
  x_dif *= x_dif;
  y_dif *= y_dif;
  return std::sqrt(x_dif+y_dif);
}

void alphastar::init(std::shared_ptr<Map> map)
{
  m_map = map;

  m_checked.clear();
  m_to_check.clear();
  current_solution_state.checked.clear();
  current_solution_state.unchecked.clear();

  MapPosition current;

  m_fin = map->get_special_tile(m_fin, Map::TileType::finish);
  current = map->get_special_tile(current, Map::TileType::start);

  m_to_check.push_back({{m_fin, current}, 0,base_heuristic(current, m_fin)});
//  current_solution_state.unchecked.push_back({{m_fin, current}, (*m_to_check.begin()).total_value()});
}


void alphastar::step(SolutionDecorator *out)
{
  out->sol = &current_solution_state;
  out->finished = false;
  out->found_way = false;
  MapPosition current;
  PositionVector possible;
  AStarValuedTransition current_transition;
  if (m_to_check.empty())
  {
    out->finished = true;
    out->found_way = false;
    return;
  }

  auto best_iter = get_best_transition_iter(m_to_check);
  current_transition = (*best_iter);
  current = current_transition.transition.current;

  m_to_check.erase(best_iter);
  m_checked.push_back(current_transition.transition);
  current_solution_state.from_unchecked2checked(current_transition.transition.from, current_transition.transition.current);


  possible = m_map->get_next_possible(current, possible);
  for (auto &pos:possible)
  {
    if (pos == m_fin)
    {
      m_checked.push_back({current, pos});
      out->finished = true;
      out->found_way = true;
    }
    else if (!in_position_list(pos, m_checked) && !in_valued_transition_list(pos, m_to_check))
    {
      double f = current_transition.value_f + 1;
      double h = base_heuristic(pos, m_fin);
      PositionPair pair = {current, pos};
      m_to_check.push_back({pair, f, h});
      current_solution_state.unchecked.push_back({pair, f+h});
    }
  }


}


