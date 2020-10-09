#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int n;
int fence[20000];

void refresh()
{
    memset(fence, 0, sizeof(int) * 20000);
    n = 0;
}

void get_input()
{
    scanf("%d\n", &n);

    for (int i = 0; i < n; ++i) {
        scanf("%d\n", &fence[i]);
    }
}

int solve(int l, int r)
{
    int mid = (l + r) / 2;
    int ret = 0;
    int nh, nl, nr;

    if (l > r) {
        return 0;
    }

    if (l == r) {
        return fence[l] * 1;
    }

    ret = max(solve(l, mid), solve(mid + 1, r));

    nl = mid;
    nr = mid + 1;
    nh = min(fence[nl], fence[nr]);

    ret = max(ret, nh*(nr-nl+1));

    while ((nl >= l) && (nr <= r)) {
        int lh = (nl - 1 < l) ? 0 : fence[nl-1];
        int rh = (nr + 1 > r) ? 0 : fence[nr+1];

        if (lh < rh) {
            nr++;
            nh = min(rh, nh);
        } else {
            nl--;
            nh = min(lh, nh);
        }

        ret = max(ret, nh*(nr-nl+1));
    }

    return ret;
}

int main()
{
    freopen("input.txt", "r", stdin);

    int tc;

    scanf("%d\n", &tc);

    for (int i = 0; i < tc; ++i) {
        refresh();
        get_input();
        printf("%d\n", solve(0, n-1));
    }
}
