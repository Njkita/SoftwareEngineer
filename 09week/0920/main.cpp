#include "IAllocator.h"
#include "AllocatorV1.h"
#include "AllocatorV2.h"
#include "AllocatorV3.h"
#include "AllocatorV4.h"
#include <benchmark/benchmark.h>

void test_v1(benchmark::State& state)
{
    auto kb = 1'024uz, mb = kb * kb, gb = kb * kb * kb;

    for (auto element : state)
    {
        AllocatorV1 allocator(gb);

        for (auto i = 0uz; i < kb; ++i)
        {
            benchmark::DoNotOptimize(allocator.allocate(mb));
        }
    }
}

BENCHMARK(test_v1);

int main()
{
    {
        AllocatorV1 allocator(1'024);

        allocator.test();

        [[maybe_unused]] auto ptr_1 = allocator.allocate(1, 1); allocator.test();
        [[maybe_unused]] auto ptr_2 = allocator.allocate(2, 2); allocator.test();
        [[maybe_unused]] auto ptr_3 = allocator.allocate(4, 4); allocator.test();
        [[maybe_unused]] auto ptr_4 = allocator.allocate(8, 8); allocator.test();
    }

    benchmark::RunSpecifiedBenchmarks();
}
