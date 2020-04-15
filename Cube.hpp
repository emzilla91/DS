#ifndef CUBE_H_INCLUDED
#define CUBE_H_INCLUDED

#include "CubeMove.hpp"
#include <vector>

class Cube
{
  private:
    char state[6][9];
    char state_tmp[6][9];
    int energy;

  public:
    Cube();
    Cube(Cube &&);
    Cube(const Cube &);
    Cube &operator=(Cube &&);
    Cube &operator=(const Cube &);
    ~Cube();

    void Rotate_right();
    void Rotate_back();
    void Rotate_front();
    void Rotate_left();
    void Rotate_up();
    void Rotate_down();
    void Rotate_right_ac();
    void Rotate_back_ac();
    void Rotate_front_ac();
    void Rotate_left_ac();
    void Rotate_up_ac();
    void Rotate_down_ac();

    void Rotate(const CubeMove &move);
    void Rotate(const std::vector<CubeMove> &moves);

    int Energy() const;

    void tmp();
    void View();
};

#endif // CUBE_H_INCLUDED
