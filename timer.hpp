#pragma once

#include <chrono>

class Timer{
    public:
    Timer() : start {std::chrono::high_resolution_clock::now()}{}
    void reset(){
        start=std::chrono::high_resolution_clock::now();
    }
    double elapsed() const{
        return duration (std::chrono::high_resolution_clock::now()-start).count();
    }

    private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    using duration=std::chrono::duration<double>;
};
