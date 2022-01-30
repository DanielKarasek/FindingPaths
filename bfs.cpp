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
  //pozice cile gde?
  m_fin = map->get_special_tile(m_fin, Map::finish);
  // pomocne promenne vycistil
  m_checked.clear();
  m_to_check.clear();

  current_solution_state.checked.clear();
  current_solution_state.unchecked.clear();

  MapPosition current;
  // musim zacit na startu
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
  // vytahnu prvni ze seznamu
  current_pair = m_to_check.front();
  m_to_check.pop_front();
  // zjednodusim pristup na soucascnou poziti
  current = current_pair.current;
  // reknu ze jsem to zkontroval
  m_checked.push_back(current_pair);
  // presunu to v reseni pro vymalovani taky do zkontrolovany
  current_solution_state.from_unchecked2checked(current_pair.from, current_pair.current);
  // kam se z teto pozice muzu
  possible = m_map->get_next_possible(current, possible);
  // pro kazdou pozici
  for (auto &pos : possible)
  {
    // pokud je finalni upravim OUT reseni, aby mediator vedel ze konec
    if(pos == m_fin)
    {
      // musim m_checked dat finalni stav aby sel backtrack
      m_checked.push_back({current, pos});
      out->finished = true;
      out->found_way = true;
      //neni return, aby se pridali vsechny stavy do unchecked, aby se vyzobrazili
    }
    // pokud stav uz byl zkontrolovany nebo na to ceka -> tak ho nepridavej, jinak ho pridej do stavu na zkontrolovani
    // a aji do solution
    else if (!in_position_list(pos, m_checked) && !in_position_list(pos, m_to_check))
    {
      m_to_check.push_back({current, pos});
      current_solution_state.unchecked.push_back({{current, pos}, 10});
    }
  }


}
