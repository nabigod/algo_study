#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int n;
int seq[500];
int dp[500];

void reset_values()
{
    memset(dp, -1, 500*sizeof(int));
    memset(seq, -1, 500*sizeof(int));

    n = 0;
}

void get_inputs()
{
    scanf("%d\n", &n);

    for (int i = 0; i < n; ++i) {
        int temp;

        scanf("%d\n", &temp);

        seq[i] = temp;
    }

}

int solve(int idx)
{
    int ret = 1;

    if (dp[idx] != -1) {
        return dp[idx];
    }

    for (int i = idx + 1; i < n; ++i) {
        if (seq[idx] < seq[i]) {
            ret = max(ret, solve(i) + 1);
        }
    }

    dp[idx] = ret;

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

        int ans = 0;
        for (int j = 0; j < n; ++j) {
            ans = max(ans, solve(j));
        }

        printf("%d\n", ans);
    }
}
