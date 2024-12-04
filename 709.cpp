#include <benchmark/benchmark.h>

struct VirtualStruct {
  virtual void Func() const __attribute__((noinline)) {
    int x = 0;
    for (int i = 0; i < 10000; ++i) {
      x += i;
    }
  }
  virtual ~VirtualStruct() = default;
};

struct VirtualStructDerived : public VirtualStruct {
  void Func() const override __attribute__((noinline)) {
    int x = 0;
    for (int i = 0; i < 10000; ++i) {
      x += i;
    }
  }
};

void RegularFunction() {
  int x = 0;
  for (int i = 0; i < 10000; ++i) {
    x += i;
  }
}

static void Virtual(benchmark::State &state) {
  VirtualStructDerived obj;
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
