#include <iostream>
#include <cstring>
using namespace std;

#define MOD 1000000007

int n;
int dp[101];

void reset_values()
{
    memset(dp, -1, 101 * sizeof(int));

    n = 0;
}

void get_inputs()
{
    scanf("%d\n", &n);

    dp[1] = 1;
    dp[2] = 2;
}

int solve(int w)
{
    if (dp[w] != -1) {
        return dp[w];
    }

    return dp[w] = (solve(w-1) + solve(w-2)) % MOD;
}

int main()
{
    freopen("input.txt", "r", stdin);

    int tc;

    scanf("%d\n", &tc);

    for (int i = 0; i < tc; ++i) {
        reset_values();
        get_inputs();
        printf("%d\n", solve(n));
    }
}
