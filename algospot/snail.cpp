#include <iostream>
#include <cstring>
using namespace std;

int n, m;
double dp[1001][2001];

void reset_values()
{
    for (int i = 0; i < 1001; ++i) {
        for (int j = 0; j < 2001; ++j) {
            dp[i][j] = -1;
        }
    }
    n = m = 0;
}

void get_inputs()
{
    scanf("%d %d\n", &n, &m);
}

double solve(int rdays, int climbed)
{
    if (rdays == 0) {
        return climbed >= n ? 1 : 0;
    }

    double ret;

    if (dp[rdays][climbed] != -1) {
        return dp[rdays][climbed];
    }

    ret = 0.25 * solve(rdays - 1, climbed + 1) + 0.75 * solve(rdays - 1, climbed + 2);

    dp[rdays][climbed] = ret;

    return ret;
}

int main()
{
    freopen("input.txt", "r", stdin);

    int tc;

    scanf("%d\n", &tc);

    for (int i = 0; i < tc; ++i) {
        reset_values();
        get_inputs();
        printf("%0.10lf\n", solve(m, 0));
    }
}
