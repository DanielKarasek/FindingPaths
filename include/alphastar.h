#ifndef ALPHASTAR_H
#define ALPHASTAR_H

#include "solvingmethod.h"
#include "map.h"
#include <list>

struct AStarValuedTransition
{
  PositionPair transition;
  double value_f;
  double value_h;
  double total_value()const{return value_f+value_h;}
  friend std::ostream &operator<<(std::ostream &os, const ValuedTransition &val_trans);
};


class alphastar : public SolvingMethod
{

public:

  using AStarValuedTransitionList = std::list<AStarValuedTransition>;

  alphastar(){};
  virtual void init(std::shared_ptr<Map> map) override;
  virtual void step(SolutionDecorator *out) override;
protected:
  std::shared_ptr<Map> m_map;

  MapPosition m_fin;
  AStarValuedTransitionList m_to_check;

};

#endif // ALPHASTAR_H
