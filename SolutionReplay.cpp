#include <thread>
#include <chrono>
#include "SolutionReplay.hpp"
using namespace std;

SolutionReplay::SolutionReplay(vector<CubeMove> shuffle,vector<CubeMove> solution){
    this->shuffle = shuffle;
    this->solution = solution;
}

void SolutionReplay::SetSolution(vector<CubeMove> v){
    solution = v;
}

void SolutionReplay::SetShuffle(vector<CubeMove> v){
    shuffle = v;
}

void SolutionReplay::Replay(const int ms_delay){
    Cube c;
    c.Rotate(shuffle);
    c.View();
    cout << "Energija: " << c.Energy() << "\n";

    this_thread::sleep_for(chrono::milliseconds(ms_delay));

    for(const auto & move:solution){
        for(int i = 0; i < 11; i++)
        std::cout << "\x1b[2K\x1b[A";
        c.Rotate(move);
        c.View();
        cout << "Energija: " << c.Energy() << "\n";
        this_thread::sleep_for(chrono::milliseconds(ms_delay));
    }
}
