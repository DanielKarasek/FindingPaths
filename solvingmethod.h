#ifndef SOLVINGMETHOD_H
#define SOLVINGMETHOD_H

#include "map.h"
#include <vector>
#include <list>
#include <memory>
// dulezite pro backtracking, jak jsem se sem dostal
struct PositionPair{
  MapPosition from;
  MapPosition current;
};

// aby to slo obarvit
struct ValuedTransition
{
  PositionPair transition;
  double value;
  friend bool operator==(const ValuedTransition &first, const ValuedTransition &sec);
};
// reseni co je zkontrolovano co neni
struct Solution
{
  std::vector<ValuedTransition> unchecked;
  std::vector<ValuedTransition> checked;
  void from_unchecked2checked(MapPosition &from, MapPosition &to);
};

struct SolutionDecorator
{
  Solution const *sol; // reseni ^^
  bool finished; // metoda skoncila
  bool found_way; // naslo cestu nebo nezdar?
};


class SolvingMethod
{

public:

  using PositionPairList = std::list<PositionPair>;

  SolvingMethod();
  virtual void init(std::shared_ptr<Map> map) = 0;
  virtual void step(SolutionDecorator *out) = 0;

  virtual void backtrack_result(PositionVector *out);

protected:
  Solution current_solution_state;

  PositionPairList m_checked;
};

bool in_position_list(const MapPosition &pos, const SolvingMethod::PositionPairList &pos_vector);
#endif // SOLVINGMETHOD_H
