#include <iostream>
#include <algorithm>
using namespace std;

int n;
int budget[10000];
int total;

void get_input()
{
    scanf("%d\n", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d \n", &budget[i]);
    }

    scanf("%d\n", &total);
}

bool is_ok(int req_max)
{
    int sum = 0;

    for (int i = 0; i < n; ++i) {
        sum += min(budget[i], req_max);
    }

    return total >= sum;
}


int solve()
{
    int l, m, r;

    sort(budget, budget + n);

    l = 1;
    r = budget[n-1];

    while (l < r) {
        m = (l + r + 1) / 2;

        if (is_ok(m)) {
            l = m;
        } else {
            r = m - 1;
        }
    }

    return l;
}

int main()
{
    freopen("input.txt", "r", stdin);

    get_input();

    printf("%d\n", solve());
}
