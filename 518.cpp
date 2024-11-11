#include <iostream>

template <typename Strategy> class Entity {
public:
  explicit Entity(const Strategy &strategy) : m_strategy(strategy) {}

  void test() const { m_strategy.test(); }

private:
  const Strategy &m_strategy;
};

struct Fast {
  void test() const { std::clog << "Fast::test\n"; }
};

struct Slow {
  void test() const { std::clog << "Slow::test\n"; }
};

int main() {
  Fast fast_strategy;
  Entity<Fast> fast_entity(fast_strategy);
  fast_entity.test();

  Slow slow_strategy;
  Entity<Slow> slow_entity(slow_strategy);
  slow_entity.test();

  return 0;
}