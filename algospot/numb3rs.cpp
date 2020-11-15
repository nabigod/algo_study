#include <iostream>
#include <cstring>
using namespace std;

int n, d, p, q;
int map[51][51];
int edges[51];
double dp[51][101];

void reset_values()
{
    for (int i = 0; i < 51; ++i) {
        for (int j = 0; j < 101; ++j) {
            dp[i][j] = -1;
        }
    }

    memset(edges, 0, 51 * sizeof(int));
    memset(map, 0, 51 * 51 * sizeof(int));
    n = d = p = q = 0;
}

void get_inputs()
{
    scanf("%d %d %d\n", &n, &d, &p);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d ", &map[i][j]);

            if (map[i][j]) {
                ++edges[i];
            }
        }
    }
}

double calc(int here, int days)
{
    double ret = 0;

    if (days == 0) {
        return (here == p) ? 1.0 : 0.0;
    }

    if (dp[here][days] != -1) {
        return dp[here][days];
    }

    for (int i = 0; i < n; ++i) {
        if (map[here][i]) {
            ret += calc(i, days-1)/edges[i];
        }
    }

    return dp[here][days] = ret;
}

void solve()
{
    int t;

    scanf("%d\n", &t);

    for (int i = 0; i < t; ++i) {
        scanf("%d ", &q);

        printf("%0.8lf ", calc(q, d));
    }
    printf("\n");

}

int main()
{
    freopen("input.txt", "r", stdin);

    int tc;

    scanf("%d\n", &tc);

    for (int i = 0; i < tc; ++i) {
        reset_values();
        get_inputs();
        solve();
    }
}
