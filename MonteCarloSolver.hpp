#ifndef MONTECARLO_SOLVER_H
#define MONTECARLO_SOLVER_H

#include "Cube.hpp"
#include "CubeMove.hpp"
#include <vector>

class MonteCarloSolver
{
  public:
    MonteCarloSolver(const std::vector<CubeMove> &moves);
    MonteCarloSolver(const Cube &c);
    MonteCarloSolver(MonteCarloSolver &&);
    MonteCarloSolver(const MonteCarloSolver &);
    MonteCarloSolver &operator=(MonteCarloSolver &&);
    MonteCarloSolver &operator=(const MonteCarloSolver &);
    ~MonteCarloSolver();

    std::vector<CubeMove> Solve();

    bool Check_cube(std::vector<CubeMove> moves);

  private:
    Cube starting_cube, tmp_cube;
    bool cube_solved;
};

#endif // MONTECARLO_SOLVER_H
