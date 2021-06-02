#include "benchmark.cpp"

struct Puzz
{
    int bench()
    {
        return bench_main();
    }
};

int main()
{
    return Puzz().bench();
}
