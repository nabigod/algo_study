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
}

int solve(int w)
{
    if (w <= 1) {
        return 1;
    }

    if (dp[w] != -1) {
        return dp[w];
    }

    return dp[w] = (solve(w-1) + solve(w-2)) % MOD;
}

int asym(int w) {
    if (w % 2 == 1) {
        return (solve(w) - solve(w/2) + MOD) % MOD;
    }

    int ret = solve(w);

    ret = (ret - solve(n/2 - 1) + MOD) % MOD;
    ret = (ret - solve(n/2) + MOD) % MOD;

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
        printf("%d\n", asym(n));
    }
}
