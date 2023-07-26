#ifndef E9DE6CA2_D33E_427E_B8BB_1C95C6ED1084
#define E9DE6CA2_D33E_427E_B8BB_1C95C6ED1084

#include <chrono>

class Benchmark
{
private:
    std::chrono::_V2::system_clock::time_point start;
    std::chrono::_V2::system_clock::time_point end;
public:
    Benchmark(){};
    ~Benchmark(){};
    inline void Start()
    {
        start = std::chrono::high_resolution_clock::now();
    };
    inline void Stop()
    {
        end = std::chrono::high_resolution_clock::now();
    };
    inline uint64_t GetTimeNano()
    {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    };
    inline uint64_t GetTimeMicro()
    {
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    };
    inline uint64_t GetTimeMili()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    };
};


#endif /* E9DE6CA2_D33E_427E_B8BB_1C95C6ED1084 */
