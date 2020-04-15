#include "Cube.hpp"
#include "MonteCarloSolver.hpp"
#include "mpi.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include "SolutionReplay.hpp"
using namespace std;
using namespace std::chrono;

int main(int argc, char **argv)
{
    int rank, size, in;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    vector<CubeMove> shuffle;
    Cube kocka;

    std::vector<MPI_Request> requests;

    if (rank == 0)
    {
        cout << "****************************************************" <<endl;
        cout << "*  1 ... dolje u smjeru kazaljke sata              *" <<endl;
        cout << "*  2 ... dolje u suprotnom smjeru kazaljke sata    *" <<endl;
        cout << "*  3 ... gore u smjeru kazaljke sata               *" <<endl;
        cout << "*  4 ... gore u suprotnom smjeru kazaljke sata     *" <<endl;
        cout << "*  5 ... naprijed u smjeru kazaljke sata           *" <<endl;
        cout << "*  6 ... naprijed u suprotnom smjeru kazaljke sata *" <<endl;
        cout << "*  7 ... natrag u smjeru kazaljke sata             *" <<endl;
        cout << "*  8 ... natrag u suprotnom smjeru kazaljke sata   *" <<endl;
        cout << "*  9 ... desno u smjeru kazaljke sata              *" <<endl;
        cout << "* 10 ... desno u suprotnom smjeru kazaljke sata    *" <<endl;
        cout << "* 11 ... lijevo u smjeru kazaljke sata             *" <<endl;
        cout << "* 12 ... lijevo suprotno od smjera kazaljke sata   *" <<endl;
        cout << "****************************************************" <<endl;
        cout << "\n..UNESITE ROTACIJE ZA MJEŠANJE KOCKE ODVOJENE RAZMACIMA I NULU ZA KRAJ.." <<endl;

        while(cin >> in){
            if(in > 0 && in < 13)
                shuffle.push_back((CubeMove)(in - 1));
            else{
                break;
            }
        }
        auto start = high_resolution_clock::now();

        int array_size = shuffle.size();
        for (int i = 1; i < size; i++){
            MPI_Send(&array_size, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(shuffle.data(), array_size, MPI_INT, i, 1, MPI_COMM_WORLD);
        }

        kocka.Rotate(shuffle);
        kocka.View();

        vector<int> counts;
        counts.resize(size - 1);

        MPI_Request req;
        for(int i = 1; i < size; i++){
            MPI_Irecv(counts.data() + (i - 1), 1, MPI_INT, i, 3, MPI_COMM_WORLD, &req);
            requests.push_back(req);
        }
        vector<CubeMove> solution;

        int got_solution = 0;
        MPI_Status status;
        int index = 1, index_rez = 0, dot = 0;
        while(!got_solution){
            index = 0;
            for(auto request : requests){
                MPI_Test(&request, &got_solution, &status);
                if (!index_rez && got_solution){
                    solution.resize(counts[index]);
                    MPI_Recv(solution.data(), counts[index], MPI_INT, index + 1, 4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                    index_rez = index;
                    break;
                }
                index++;
            }
            if(!index_rez){
                cout << "\x1b[2KRjesavam";
                for (int i = 0; i < dot % 4; i++){
                    cout << ".";
                }
                cout << "\r" << std::flush;
                dot++;
            }

            this_thread::sleep_for(1000ms);
        }
        auto stop = high_resolution_clock::now();

        cout << "\x1b[2K\r";

        vector<MPI_Request> reqs;
        int msg1 = 0, msg2 = 0;
        reqs.resize(size - 1);
        for (int i = 1; i < size; i++){
            MPI_Isend(&msg1, 1, MPI_INT, i, 8, MPI_COMM_WORLD, reqs.data() + i - 1);
            MPI_Send(&msg2, 1, MPI_INT, i, 9, MPI_COMM_WORLD);
        }

        for (auto &req : reqs){
            MPI_Status status;
            int done = 0;
            MPI_Test(&req, &done, &status);
            if (!done)
                MPI_Cancel(&req);
        }

        cout << "Rješenje (proces-" << index_rez + 1 << "): "<<endl;
        for (const auto &move : solution)
            cout << (int)move + 1 << " ";
        auto duration = duration_cast<seconds>(stop - start);
        cout << "\n\nVRIJEME IZVOĐENJA PARALELNO IZNOSI: " << duration.count() << "s" <<endl;
        
        start = high_resolution_clock::now();
        MonteCarloSolver cube_solver = MonteCarloSolver(shuffle);
        auto solutionSerial = cube_solver.Solve();
        stop = high_resolution_clock::now();
        duration = duration_cast<seconds>(stop - start);
        cout << "VRIJEME IZVOĐENJA SERIJSKI IZNOSI: " << duration.count() << "s" <<endl;

        kocka.Rotate(solution);
        SolutionReplay s{solution, shuffle};
        s.Replay(1000);
    }
    else{
        int count = 0;
        MPI_Recv(&count, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        shuffle.resize(count);
        MPI_Recv(shuffle.data(), count, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        MonteCarloSolver cube_solver = MonteCarloSolver(shuffle);
        auto solution = cube_solver.Solve();

        count = solution.size();

        MPI_Request req1;
        MPI_Request req2;

        if (count){
            MPI_Isend(&count, 1, MPI_INT, 0, 3, MPI_COMM_WORLD, &req1);
            MPI_Isend(solution.data(), count, MPI_INT, 0, 4, MPI_COMM_WORLD, &req2);
        }

        MPI_Recv(&count, 1, MPI_INT, 0, 9, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        if (count){
            int done = 0;
            MPI_Status status;
            MPI_Test(&req1, &done, &status);
            if (!done)
                MPI_Cancel(&req1);
            MPI_Test(&req2, &done, &status);
            if (!done)
                MPI_Cancel(&req2);
        }
    }
    MPI_Finalize();

    return 0;
}
