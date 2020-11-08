#include <iostream>
#include <cstring>
using namespace std;

#define MOD 10000000

int n;
int cache[101][101];

void reset_values()
{
    n = 0;
    memset(cache, -1, 101 * 101 * sizeof(int));
}

void get_inputs()
{
    scanf("%d \n", &n);
}

int solve(int remain, int first)
{
    int ret = 0;

    if (remain == first) {
        return 1;
    }

    if (cache[remain][first] != -1) {
        return cache[remain][first];
    }

    for (int i = 1; i <= remain - first; ++i) {
        int temp = first + i - 1;

        temp *= solve(remain - first, i) % MOD;
        temp %= MOD;
        ret += temp;
        ret %= MOD;
    }

    cache[remain][first] = ret;

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

        int sum = 0;
        for (int j = 1; j <= n; ++j) {
            sum += solve(n, j);
            sum %= MOD;
        }
        printf("%d\n", sum);
    }
}
