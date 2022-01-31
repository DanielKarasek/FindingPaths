#include "solvingmethod.h"


SolvingMethod::SolvingMethod()
{

}

void Solution::from_unchecked2checked(MapPosition &from, MapPosition &to)
{

  for (int i=0; auto val_transition : unchecked)
  {
    if (val_transition.transition.from == from && val_transition.transition.current == to)
    {
      ValuedTransition tmp_trans = *(unchecked.begin()+i);
      unchecked.erase(unchecked.begin()+i);
      checked.push_back(tmp_trans);
      return;
    }
    i++;
  }
}


bool in_position_list(const MapPosition &pos, const SolvingMethod::PositionPairList &pos_vector)
{
  for (const auto &pos2check : pos_vector)
    if (pos2check.current == pos)
      return true;

  return false;
}

bool operator==(const ValuedTransition &first, const ValuedTransition &sec)
{
  return first.transition.from == sec.transition.from && first.transition.current == sec.transition.current;
}

void SolvingMethod::backtrack_result(PositionVector *out)
{
  MapPosition previous = m_checked.rbegin()->from;
  out->push_back(m_checked.rbegin()->current);
  out->push_back(m_checked.rbegin()->from);
  for(auto hist_iter = m_checked.rbegin(); hist_iter != m_checked.rend(); ++hist_iter)
  {
    if ((*hist_iter).current == previous)
    {
      if ((*hist_iter).from == m_checked.rbegin()->current)
        break;
      previous = (*hist_iter).from;
      out->push_back(previous);
    }
  }

  std::reverse(out->begin(), out->end());
}
