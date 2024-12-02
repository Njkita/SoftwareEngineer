#include <benchmark/benchmark.h>

struct VirtualStruct {
  virtual void Func() const {
    int x = 0;
    for (int i = 0; i < 1000; ++i) {
      x += i;
    }
  }
  virtual ~VirtualStruct() = default;
};

void RegularFunction() {
  int x = 0;
  for (int i = 0; i < 1000; ++i) {
    x += i;
  }
}

static void Virtual(benchmark::State &state) {
  VirtualStruct obj;
  for (auto _ : state) {
    obj.Func();
  }
}

static void Regular(benchmark::State &state) {
  for (auto _ : state) {
    RegularFunction();
  }
}

BENCHMARK(Virtual);
BENCHMARK(Regular);

BENCHMARK_MAIN();