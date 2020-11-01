#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define INF         987654321

int n, s;
int seq[101];
int dp[101][11];

void reset_values()
{
    memset(seq, 0, 101 * sizeof(int));
    memset(dp, -1, 101 * 11 * sizeof(int));

    n = s = 0;
}

void get_inputs()
{
    scanf("%d %d\n", &n, &s);

    for (int i = 0; i < n; ++i) {
        scanf("%d  \n", &seq[i]);
    }
}

int get_errorsum(int l, int range)
{
    int ret = INF;
    int minidx = -1;

    for (int i = seq[l]; i <= seq[l + range - 1]; ++i) {

        int sum = 0;
        for (int j = l; j < l + range; ++j) {
            sum += (seq[j] - i) * (seq[j] - i);
        }

        ret = min(ret, sum);
    }

    return ret;
}

int solve(int start, int parts)
{
    int ret = INF;

    if (start == n) {
        return 0;
    }

    if (parts == 0) {
        return INF;
    }

    if (dp[start][parts] != -1) {
        return dp[start][parts];
    }

    for (int i = 1; i + start <= n; ++i) {
        ret = min(ret, solve(i + start, parts - 1) +
                        get_errorsum(start, i));
    }

    dp[start][parts] = ret;

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
        sort(seq, seq+n);
        printf("%d\n", solve(0, s));
    }
}
