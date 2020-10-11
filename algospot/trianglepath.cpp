#include <iostream>
#include <cstring>
using namespace std;

#define _MAX(a, b) ((a>b) ? a : b)

int n;
int triangle[101][101];
int dp[101][101];

void refresh_values()
{
    memset(triangle, 0, sizeof(int)*101*101);
    memset(dp, -1, sizeof(int)*101*101);
    n = 0;
}

void get_input()
{
    scanf("%d\n", &n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i+1; ++j) {
            int temp;

            scanf("%d  \n", &temp);
            triangle[i][j] = temp;
        }
    }
}

void set_dp(int x, int y)
{
    if (y == n-1) {
        dp[y][x] = triangle[y][x];
        return;
    }

    dp[y][x] = triangle[y][x] + _MAX(dp[y+1][x], dp[y+1][x+1]);
}

void solve()
{
    for (int i = n-1; i >= 0; --i) {
        for (int j = n-1; j >= 0; --j) {
            set_dp(j, i);
        }
    }

}

int main()
{
    freopen("input.txt", "r", stdin);

    int tc;

    scanf("%d\n", &tc);

    for (int i = 0; i < tc; ++i) {
        refresh_values();
        get_input();
        solve();

        printf("%d\n", dp[0][0]);
    }
}
