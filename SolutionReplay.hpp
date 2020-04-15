#include <iostream>
#include "Cube.hpp"
#include "CubeMove.hpp"
#include <vector>

class SolutionReplay
{
    private:
    std::vector<CubeMove> shuffle;
    std::vector<CubeMove> solution;

    public:
    SolutionReplay() = default;
    SolutionReplay(SolutionReplay &&) = default;
    SolutionReplay(const SolutionReplay &) = default;
    SolutionReplay &operator=(SolutionReplay &&) = default;
    SolutionReplay &operator=(const SolutionReplay &) = default;
    ~SolutionReplay() = default;
    SolutionReplay(std::vector<CubeMove> shuffle, std::vector<CubeMove> solution);

    void SetSolution(std::vector<CubeMove> solution);
    void SetShuffle(std::vector<CubeMove> shuffle);
    void Replay(const int ms_delay);
};
