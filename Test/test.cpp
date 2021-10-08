#include "debug.h"

#include <Windows.h>
#include <iostream>
#include <fstream>

#include <string>
#include <map>
#include <vector>

//***C++11 Style:***
#include <chrono>
using std::chrono::steady_clock;
using namespace std;

float fastsqrt(int number)
{
    int sDist = number;

    int save = 0;

    for (int i = 0; i < 100; i++)
    {
        int dist = abs(i * i - number);

        if (dist < sDist)
        {
            sDist = dist;
            save = i;
        }

    }
    int part = number - save;
    float answer = save + part / (save * save);

    return answer;
}

float qsqrt(float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5f;

    x2 = number * .5f;
    y = number;
    i = *(long*)&y;
    i = 0x5f3759df - (i >> 1);
    y = *(float*)&i;
    y = y * (threehalfs - (x2 * y * y));
    y = y * (threehalfs - (x2 * y * y));

    return y;
}



int mainxx()
{
    steady_clock::time_point begin;
    steady_clock::time_point end;

    chrono::microseconds elapsedms = chrono::microseconds(0);
    chrono::nanoseconds elapsedns = chrono::nanoseconds(0);
    int times = 0;



    for (int i = 1; i < 5000; i++) {
        begin = steady_clock::now();
        float qsq = qsqrt(i);
        end = steady_clock::now();

        std::chrono::nanoseconds time = (std::chrono::nanoseconds)std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
        _M(i << " " << time.count() << "ns");
        elapsedns += time;
        times++;
        //float sqr = 1 / sqrt(i);
        //if (qsq != sqr)
        //{
        //    _M(i << " margin is " << abs(qsq-sqr))
        //}
    }

    //_M("Avg Extime = " << std::chrono::duration_cast<std::chrono::microseconds>(elapsedms / times).count() << "[µs]");
    _M("Avg Extime = " << std::chrono::duration_cast<std::chrono::nanoseconds> (elapsedns / times).count() << "[ns]");

    system("pause");
    return 0;
}