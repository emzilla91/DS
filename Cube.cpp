#include "Cube.hpp"
#ifdef __linux__
#define RED "\x1B[41m\x1B[30m"
#define GRN "\x1B[42m\x1B[30m"
#define YEL "\x1B[43m\x1B[30m"
#define BLU "\x1B[44m\x1B[30m"
#define MAG "\x1B[45m\x1B[30m"
#define CYN "\x1B[46m\x1B[30m"
#define WHT "\x1B[47m\x1B[30m"
#define RESET "\x1B[0m"
#elif defined(_WIN64) || defined(_WIN32)
#include <Windows.h>
#endif
#include <iostream>
#include <string>
using namespace std;

void postavi_boju(char letter);
int color(char letter);

Cube::Cube()
{
    char color[6];

    color[0] = 'G';
    color[1] = 'O';
    color[2] = 'W';
    color[3] = 'R';
    color[4] = 'B';
    color[5] = 'Y';

    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 9; j++){
            state[i][j] = color[i];
        }
    }
}

Cube::Cube(Cube &&) = default;
Cube::Cube(const Cube &) = default;
Cube &Cube::operator=(Cube &&) = default;
Cube &Cube::operator=(const Cube &) = default;
Cube::~Cube() = default;

void Cube::View(){
    int a;
    int b;
    for (int i = 2; i < 5; i++){
        if (i == 2 || i == 4){
            a = 0;
            while (a < 7){
                cout << "      ";
                for (int j = a; j < a + 3; j++){
                    postavi_boju(state[i][j]);
                    cout << "[]";
                    postavi_boju('X');
                }
                a = a + 3;
                cout << endl;
            }
        }
        else if (i == 3){
            a = 0;
            while (a < 7){
                b = 0;
                while (b < 4){
                    if (b == 0){
                        for (int j = a; j < a + 3; j++){
                            postavi_boju(state[5][j]);
                            cout << "[]";
                            postavi_boju('X');
                        }
                    }
                    else if (b == 1){
                        for (int j = a; j < a + 3; j++){
                            postavi_boju(state[0][j]);
                            cout << "[]";
                            postavi_boju('X');
                        }
                    }
                    else if (b == 2){
                        for (int j = a; j < a + 3; j++){
                            postavi_boju(state[3][j]);
                            cout << "[]";
                            postavi_boju('X');
                        }
                    }
                    else if (b == 3){
                        for (int j = a; j < a + 3; j++){
                            postavi_boju(state[1][j]);
                            cout << "[]";
                            postavi_boju('X');
                        }
                    }

                    b++;
                }
                a = a + 3;
                cout << endl;
            }
        }
    }
    postavi_boju('X');
    cout << endl;
}

void Cube::Rotate_front()
{
    tmp();

    state[3][0] = state_tmp[2][6];
    state[3][3] = state_tmp[2][7];
    state[3][6] = state_tmp[2][8];

    state[5][2] = state_tmp[4][0];
    state[5][5] = state_tmp[4][1];
    state[5][8] = state_tmp[4][2];

    state[2][6] = state_tmp[5][8];
    state[2][7] = state_tmp[5][5];
    state[2][8] = state_tmp[5][2];

    state[4][0] = state_tmp[3][6];
    state[4][1] = state_tmp[3][3];
    state[4][2] = state_tmp[3][0];

    state[0][0] = state_tmp[0][6];
    state[0][1] = state_tmp[0][3];
    state[0][2] = state_tmp[0][0];
    state[0][3] = state_tmp[0][7];
    state[0][5] = state_tmp[0][1];
    state[0][6] = state_tmp[0][8];
    state[0][7] = state_tmp[0][5];
    state[0][8] = state_tmp[0][2];

}

void Cube::Rotate_back()
{
    tmp();

    state[3][2] = state_tmp[4][8];
    state[3][5] = state_tmp[4][7];
    state[3][8] = state_tmp[4][6];

    state[5][0] = state_tmp[2][2];
    state[5][3] = state_tmp[2][1];
    state[5][6] = state_tmp[2][0];

    state[2][0] = state_tmp[3][2];
    state[2][1] = state_tmp[3][5];
    state[2][2] = state_tmp[3][8];

    state[4][6] = state_tmp[5][0];
    state[4][7] = state_tmp[5][3];
    state[4][8] = state_tmp[5][6];

    state[1][0] = state_tmp[1][6];
    state[1][1] = state_tmp[1][3];
    state[1][2] = state_tmp[1][0];
    state[1][3] = state_tmp[1][7];
    state[1][5] = state_tmp[1][1];
    state[1][6] = state_tmp[1][8];
    state[1][7] = state_tmp[1][5];
    state[1][8] = state_tmp[1][2];

}

void Cube::Rotate_left()
{
    tmp();

    state[0][0] = state_tmp[2][0];
    state[0][3] = state_tmp[2][3];
    state[0][6] = state_tmp[2][6];

    state[1][2] = state_tmp[4][6];
    state[1][5] = state_tmp[4][3];
    state[1][8] = state_tmp[4][0];

    state[2][0] = state_tmp[1][8];
    state[2][3] = state_tmp[1][5];
    state[2][6] = state_tmp[1][2];

    state[4][0] = state_tmp[0][0];
    state[4][3] = state_tmp[0][3];
    state[4][6] = state_tmp[0][6];

    state[5][0] = state_tmp[5][6];
    state[5][1] = state_tmp[5][3];
    state[5][2] = state_tmp[5][0];
    state[5][3] = state_tmp[5][7];
    state[5][5] = state_tmp[5][1];
    state[5][6] = state_tmp[5][8];
    state[5][7] = state_tmp[5][5];
    state[5][8] = state_tmp[5][2];

}

void Cube::Rotate_right()
{

    tmp();

    state[0][2] = state_tmp[4][2];
    state[0][5] = state_tmp[4][5];
    state[0][8] = state_tmp[4][8];

    state[1][0] = state_tmp[2][8];
    state[1][3] = state_tmp[2][5];
    state[1][6] = state_tmp[2][2];

    state[2][2] = state_tmp[0][2];
    state[2][5] = state_tmp[0][5];
    state[2][8] = state_tmp[0][8];

    state[4][2] = state_tmp[1][6];
    state[4][5] = state_tmp[1][3];
    state[4][8] = state_tmp[1][0];

    state[3][0] = state_tmp[3][6];
    state[3][1] = state_tmp[3][3];
    state[3][2] = state_tmp[3][0];
    state[3][3] = state_tmp[3][7];
    state[3][5] = state_tmp[3][1];
    state[3][6] = state_tmp[3][8];
    state[3][7] = state_tmp[3][5];
    state[3][8] = state_tmp[3][2];

}

void Cube::Rotate_up()
{
    tmp();

    for (int i = 0; i < 3; i++)
    {
        state[0][i] = state_tmp[3][i];
        state[1][i] = state_tmp[5][i];
        state[3][i] = state_tmp[1][i];
        state[5][i] = state_tmp[0][i];
    }

    state[2][0] = state_tmp[2][6];
    state[2][1] = state_tmp[2][3];
    state[2][2] = state_tmp[2][0];
    state[2][3] = state_tmp[2][7];
    state[2][5] = state_tmp[2][1];
    state[2][6] = state_tmp[2][8];
    state[2][7] = state_tmp[2][5];
    state[2][8] = state_tmp[2][2];

}

void Cube::Rotate_down()
{
    tmp();

    for (int i = 6; i < 9; i++)
    {
        state[0][i] = state_tmp[5][i];
        state[1][i] = state_tmp[3][i];
        state[3][i] = state_tmp[0][i];
        state[5][i] = state_tmp[1][i];
    }

    state[4][0] = state_tmp[4][6];
    state[4][1] = state_tmp[4][3];
    state[4][2] = state_tmp[4][0];
    state[4][3] = state_tmp[4][7];
    state[4][5] = state_tmp[4][1];
    state[4][6] = state_tmp[4][8];
    state[4][7] = state_tmp[4][5];
    state[4][8] = state_tmp[4][2];

}

void Cube::Rotate_back_ac()
{
    tmp();

    state[3][2] = state_tmp[2][0];
    state[3][5] = state_tmp[2][1];
    state[3][8] = state_tmp[2][2];

    state[5][0] = state_tmp[4][6];
    state[5][3] = state_tmp[4][7];
    state[5][6] = state_tmp[4][8];

    state[2][0] = state_tmp[5][6];
    state[2][1] = state_tmp[5][3];
    state[2][2] = state_tmp[5][0];

    state[4][6] = state_tmp[3][8];
    state[4][7] = state_tmp[3][5];
    state[4][8] = state_tmp[3][2];

    state[1][0] = state_tmp[1][2];
    state[1][1] = state_tmp[1][5];
    state[1][2] = state_tmp[1][8];
    state[1][3] = state_tmp[1][1];
    state[1][5] = state_tmp[1][7];
    state[1][6] = state_tmp[1][0];
    state[1][7] = state_tmp[1][3];
    state[1][8] = state_tmp[1][6];

}

void Cube::Rotate_front_ac()
{
    tmp();

    state[3][0] = state_tmp[4][2];
    state[3][3] = state_tmp[4][1];
    state[3][6] = state_tmp[4][0];

    state[5][2] = state_tmp[2][8];
    state[5][5] = state_tmp[2][7];
    state[5][8] = state_tmp[2][6];

    state[2][6] = state_tmp[3][0];
    state[2][7] = state_tmp[3][3];
    state[2][8] = state_tmp[3][6];

    state[4][0] = state_tmp[5][2];
    state[4][1] = state_tmp[5][5];
    state[4][2] = state_tmp[5][8];

    state[0][0] = state_tmp[0][2];
    state[0][1] = state_tmp[0][5];
    state[0][2] = state_tmp[0][8];
    state[0][3] = state_tmp[0][1];
    state[0][5] = state_tmp[0][7];
    state[0][6] = state_tmp[0][0];
    state[0][7] = state_tmp[0][3];
    state[0][8] = state_tmp[0][6];

}

void Cube::Rotate_up_ac()
{
    tmp();

    for (int i = 0; i < 3; i++)
    {
        state[0][i] = state_tmp[5][i];
        state[1][i] = state_tmp[3][i];
        state[3][i] = state_tmp[0][i];
        state[5][i] = state_tmp[1][i];
    }

    state[2][0] = state_tmp[2][2];
    state[2][1] = state_tmp[2][5];
    state[2][2] = state_tmp[2][8];
    state[2][3] = state_tmp[2][1];
    state[2][5] = state_tmp[2][7];
    state[2][6] = state_tmp[2][0];
    state[2][7] = state_tmp[2][3];
    state[2][8] = state_tmp[2][6];

}

void Cube::Rotate_right_ac()
{
    tmp();

    state[0][2] = state_tmp[2][2];
    state[0][5] = state_tmp[2][5];
    state[0][8] = state_tmp[2][8];

    state[1][0] = state_tmp[4][8];
    state[1][3] = state_tmp[4][5];
    state[1][6] = state_tmp[4][2];

    state[2][2] = state_tmp[1][6];
    state[2][5] = state_tmp[1][3];
    state[2][8] = state_tmp[1][0];

    state[4][2] = state_tmp[0][2];
    state[4][5] = state_tmp[0][5];
    state[4][8] = state_tmp[0][8];

    state[3][0] = state_tmp[3][2];
    state[3][1] = state_tmp[3][5];
    state[3][2] = state_tmp[3][8];
    state[3][3] = state_tmp[3][1];
    state[3][5] = state_tmp[3][7];
    state[3][6] = state_tmp[3][0];
    state[3][7] = state_tmp[3][3];
    state[3][8] = state_tmp[3][6];

}

void Cube::Rotate_down_ac()
{
    tmp();

    for (int i = 6; i < 9; i++)
    {
        state[0][i] = state_tmp[3][i];
        state[1][i] = state_tmp[5][i];
        state[3][i] = state_tmp[1][i];
        state[5][i] = state_tmp[0][i];
    }

    state[4][0] = state_tmp[4][2];
    state[4][1] = state_tmp[4][5];
    state[4][2] = state_tmp[4][8];
    state[4][3] = state_tmp[4][1];
    state[4][5] = state_tmp[4][7];
    state[4][6] = state_tmp[4][0];
    state[4][7] = state_tmp[4][3];
    state[4][8] = state_tmp[4][6];

}

void Cube::Rotate_left_ac()
{
    tmp();

    state[0][0] = state_tmp[4][0];
    state[0][3] = state_tmp[4][3];
    state[0][6] = state_tmp[4][6];

    state[1][2] = state_tmp[2][6];
    state[1][5] = state_tmp[2][3];
    state[1][8] = state_tmp[2][0];

    state[2][0] = state_tmp[0][0];
    state[2][3] = state_tmp[0][3];
    state[2][6] = state_tmp[0][6];

    state[4][0] = state_tmp[1][8];
    state[4][3] = state_tmp[1][5];
    state[4][6] = state_tmp[1][2];

    state[5][0] = state_tmp[5][2];
    state[5][1] = state_tmp[5][5];
    state[5][2] = state_tmp[5][8];
    state[5][3] = state_tmp[5][1];
    state[5][5] = state_tmp[5][7];
    state[5][6] = state_tmp[5][0];
    state[5][7] = state_tmp[5][3];
    state[5][8] = state_tmp[5][6];

}

void Cube::tmp()
{
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            state_tmp[i][j] = state[i][j];
        }
    }
}

int Cube::Energy() const
{
    int energy = 0;
    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            switch (i)
            {
            case (0):
                if (state[i][j] == 'G' && j != 4)
                {
                    energy--;
                }
                break;
            case (1):
                if (state[i][j] == 'O' && j != 4)
                {
                    energy--;
                }
                break;
            case (2):
                if (state[i][j] == 'W' && j != 4)
                {
                    energy--;
                }
                break;
            case (3):
                if (state[i][j] == 'R' && j != 4)
                {
                    energy--;
                }
                break;
            case (4):
                if (state[i][j] == 'B' && j != 4)
                {
                    energy--;
                }
                break;
            case (5):
                if (state[i][j] == 'Y' && j != 4)
                {
                    energy--;
                }
                break;
            }
        }
    }

    return energy+48;
}

void Cube::Rotate(const CubeMove &move)
{
    switch (move)
    {
    case (CubeMove::down_c):
        Rotate_down();
        break;

    case (CubeMove::down_ac):
        Rotate_down_ac();
        break;

    case (CubeMove::up_c):
        Rotate_up();
        break;

    case (CubeMove::up_ac):
        Rotate_up_ac();
        break;

    case (CubeMove::front_c):
        Rotate_front();
        break;

    case (CubeMove::front_ac):
        Rotate_front_ac();
        break;

    case (CubeMove::back_c):
        Rotate_back();
        break;

    case (CubeMove::back_ac):
        Rotate_back_ac();
        break;

    case (CubeMove::right_c):
        Rotate_right();
        break;

    case (CubeMove::right_ac):
        Rotate_right_ac();
        break;

    case (CubeMove::left_c):
        Rotate_left();
        break;

    case (CubeMove::left_ac):
        Rotate_left_ac();
        break;
    }
}

void Cube::Rotate(const std::vector<CubeMove> &moves)
{
    for (const auto &move : moves)
    {
        switch (move)
        {
        case (CubeMove::down_c):
            Rotate_down();
            break;

        case (CubeMove::down_ac):
            Rotate_down_ac();
            break;

        case (CubeMove::up_c):
            Rotate_up();
            break;

        case (CubeMove::up_ac):
            Rotate_up_ac();
            break;

        case (CubeMove::front_c):
            Rotate_front();
            break;

        case (CubeMove::front_ac):
            Rotate_front_ac();
            break;

        case (CubeMove::back_c):
            Rotate_back();
            break;

        case (CubeMove::back_ac):
            Rotate_back_ac();
            break;

        case (CubeMove::right_c):
            Rotate_right();
            break;

        case (CubeMove::right_ac):
            Rotate_right_ac();
            break;

        case (CubeMove::left_c):
            Rotate_left();
            break;

        case (CubeMove::left_ac):
            Rotate_left_ac();
            break;
        }
    }
    energy = Energy();
}

void postavi_boju(char letter)
{
#if defined(_WIN64) || defined(_WIN32)

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color(letter));

#else

    switch (letter)
    {
    case 'G':
        std::cout << GRN;
        break;
    case 'O':
        std::cout << MAG;
        break;
    case 'W':
        std::cout << WHT;
        break;
    case 'B':
        std::cout << BLU;
        break;
    case 'R':
        std::cout << RED;
        break;
    case 'Y':
        std::cout << YEL;
        break;
    default:
        std::cout << RESET;
        break;
    }

#endif
}

int color(char letter)
{

    switch (letter)
    {

#if defined(_WIN64) || defined(_WIN32)

    case 'G':
        return BACKGROUND_GREEN;
        break;
    case 'O':
        return BACKGROUND_RED | BACKGROUND_GREEN * (BACKGROUND_INTENSITY + 20);
        break;

    case 'W':
        return BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
        break;

    case 'B':
        return BACKGROUND_BLUE;
        break;

    case 'R':
        return BACKGROUND_RED;
        break;

    case 'Y':
        return BACKGROUND_RED | BACKGROUND_GREEN;
        break;

#endif

    default:
        return 7;
        break;
    }
}