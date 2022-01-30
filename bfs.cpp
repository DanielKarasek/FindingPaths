#include "bfs.h"
#include "map.h"
#include "solvingmethod.h"
#include <list>


using PositionPairList = std::list<PositionPair>;




BFS::BFS()
{

}

void BFS::init(std::shared_ptr<Map> map)
{
  m_map = map;

  m_fin = map->get_special_tile(m_fin, Map::finish);
  m_checked.clear();
  m_to_check.clear();

  current_solution_state.checked.clear();
  current_solution_state.unchecked.clear();

  MapPosition current;
  current = map->get_special_tile(current, Map::start);

  m_to_check.push_back({m_fin, current});
}

void BFS::step(SolutionDecorator *out)
{
  PositionVector possible;
  MapPosition current;

  PositionPair current_pair;
  out->sol = &current_solution_state;
  out->finished = false;
  out->found_way = false;

  if(m_to_check.empty())
  {
    out->finished = true;
    out->found_way = false;
    return;
  }

  current_pair = m_to_check.front();
  m_to_check.pop_front();
  current = current_pair.current;
  m_checked.push_back(current_pair);

  current_solution_state.from_unchecked2checked(current_pair.from, current_pair.current);

  possible = m_map->get_next_possible(current, possible);
  for (auto &pos : possible)
  {
    if(pos == m_fin)
    {
      m_checked.push_back({current, pos});
      out->finished = true;
      out->found_way = true;
    }
    else if (!in_position_list(pos, m_checked) && !in_position_list(pos, m_to_check))
    {
      m_to_check.push_back({current, pos});
      current_solution_state.unchecked.push_back({{current, pos}, 10});
    }
  }


}
