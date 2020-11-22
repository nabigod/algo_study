#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

const int M = 1000000000 + 100;
int nr_dot, nr_dash, k;
int idx;
int bino[201][201];

void reset_values()
{
    nr_dot = nr_dash = k = 0;
}

void get_inputs()
{
    scanf("%d %d %d \n", &nr_dash, &nr_dot, &k);
}

void calc_bino()
{
    memset(bino, 0, 201 * 201 * sizeof(int));

    for (int i = 0; i <= 200; ++i) {
        bino[i][0] = bino[i][i] = 1;
        if (i == 0) {
            continue;
        }

        for (int j = 1; j < i; ++j) {
            bino[i][j] = min(M, bino[i-1][j] + bino[i-1][j-1]);
        }
    }
}

string solve(int nr_dot, int nr_dash, int skip)
{
    if (nr_dash == 0) {
        return string(nr_dot, 'o');
    }

    if (skip <= bino[nr_dot + nr_dash - 1][nr_dash - 1]) {
        return '-' + solve(nr_dot, nr_dash - 1, skip);
    }

    return 'o' + solve(nr_dot - 1, nr_dash, skip - bino[nr_dot + nr_dash - 1][nr_dash - 1]);
}

int main()
{
    freopen("input.txt", "r", stdin);

    int tc;

    calc_bino();

    scanf("%d\n", &tc);

    for (int i = 0; i < tc; ++i) {
        reset_values();
        get_inputs();
        cout << solve(nr_dot, nr_dash, k) << '\n';
    }
}
