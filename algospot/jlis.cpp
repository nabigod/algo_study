#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int n, m;
int seqa[100];
int seqb[100];
int dp[101][101];

void reset_values()
{
    memset(dp, -1, 101*101*sizeof(int));
    memset(seqa, -1, 100*sizeof(int));
    memset(seqb, -1, 100*sizeof(int));

    n = m = 0;
}

void get_inputs()
{
    int temp;

    scanf("%d %d\n", &n, &m);

    for (int i = 0; i < n; ++i) {
        scanf("%d \n", &temp);

        seqa[i] = temp;
    }

    for (int i = 0; i < m; ++i) {
        scanf("%d \n", &temp);

        seqb[i] = temp;
    }
}

int solve(int idxa, int idxb)
{
    int ret = 0;

    if (dp[idxa+1][idxb+1] != -1) {
        return dp[idxa+1][idxb+1];
    }

    int val_a = (idxa == -1) ? (1<<31) : seqa[idxa];
    int val_b = (idxb == -1) ? (1<<31) : seqb[idxb];

    int mmax = max(val_a, val_b);

    for (int i = idxa + 1; i < n; ++i) {
        if (mmax < seqa[i]) {
            ret = max(ret, solve(i, idxb) + 1);
        }
    }

    for (int i = idxb + 1; i < m; ++i) {
        if (mmax < seqb[i]) {
            ret = max(ret, solve(idxa, i) + 1);
        }
    }

    dp[idxa+1][idxb+1] = ret;

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
        printf("%d\n", solve(-1, -1));
    }
}
