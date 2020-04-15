#include "MonteCarloSolver.hpp"
#include <functional>
#include <iostream>
#include <random>

#ifdef DS_MPI
#include <mpi.h>
#endif // DS_MPI

using namespace std;

MonteCarloSolver::MonteCarloSolver(const std::vector<CubeMove> &moves)
{
    starting_cube.Rotate(moves);
}

MonteCarloSolver::MonteCarloSolver(const Cube &c)
{
    starting_cube = c;
    tmp_cube = c;

    if (c.Energy() == 0)
    {
        cube_solved = true;
    }
    else
    {
        cube_solved = false;
    }
}

MonteCarloSolver::MonteCarloSolver(MonteCarloSolver &&) = default;
MonteCarloSolver::MonteCarloSolver(const MonteCarloSolver &) = default;
MonteCarloSolver &MonteCarloSolver::operator=(MonteCarloSolver &&) = default;
MonteCarloSolver &MonteCarloSolver::operator=(const MonteCarloSolver &) = default;
MonteCarloSolver::~MonteCarloSolver() = default;

std::vector<CubeMove> MonteCarloSolver::Solve()
{
    bool check = false;
    std::vector<CubeMove> moves, final_moves;

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 11);
    auto random = std::bind(dist, mt);

    moves.reserve(20);
    final_moves.reserve(20);
    auto tmp = starting_cube;
    auto energy = tmp.Energy();
    bool lower = false;

#ifdef DS_MPI
    MPI_Request req;
    int done = 0;
    int recieved_done = 0;
    MPI_Status status;
    MPI_Irecv(&done, 1, MPI_INT, 0, 8, MPI_COMM_WORLD, &req);
#endif // DS_MPI

    while (tmp.Energy())
    {

#ifdef DS_MPI
        MPI_Test(&req, &recieved_done, &status);
        if (recieved_done)
            return std::vector<CubeMove>();
#endif // DS_MPI

        tmp = starting_cube;
        tmp.Rotate(final_moves);
        energy = tmp.Energy();
        moves.clear();
        lower = false;
        do
        {
            auto move = (CubeMove)random();
            moves.push_back(move);
            tmp.Rotate(move);
            lower = tmp.Energy() == 0;
        } while (!lower && moves.size() < 20);

        if (lower == true)
        {
            for (const auto &move : moves)
            {
                final_moves.push_back(move);
            }
        }
    }

#ifdef DS_MPI
    MPI_Test(&req, &recieved_done, &status);
    if (!recieved_done)
        MPI_Cancel(&req);
#endif // DS_MPI

    return final_moves;
}

bool MonteCarloSolver::Check_cube(std::vector<CubeMove> moves)
{
    starting_cube.Rotate(moves);

    /*
    cout << "STARTING: " << starting_cube.Energy() << endl;
    cout << "TMP:      " << tmp_cube.Energy() << endl;
    cout << "BROJAC:   " << b << endl;
    */

    if (starting_cube.Energy() >= tmp_cube.Energy())
    {
        return false;
    }
    else if (starting_cube.Energy() == 0)
    {
        cube_solved = true;
        return true;
    }
    else
    {
        return true;
    }
}
