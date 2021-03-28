#include <iostream>
#include <algorithm>
using namespace std;

#define MOD 1000000007

string e, price;
int m;
unsigned int used;

void reset_values()
{
    e = price = "";
    m = 0;
}

void get_inputs()
{
    cin >> e >> m;
    price = e;

    sort(price.begin(), price.end());
}

bool is_multiple_of(string num, int q)
{
    return (stoull(num) % q) == 0 ? true : false;
}

int solve()
{
    long long cnt = 0;

    while (price < e) {
        if (is_multiple_of(price, m)) {
            cnt++;
        }

        next_permutation(price.begin(), price.end());
    }

    cout << cnt % MOD << endl;

    return 0;
}

int main()
{
    struct timespec start, end;
    freopen("input.txt", "r", stdin);

    int tc;

    scanf("%d\n", &tc);

    for (int i = 0; i < tc; ++i) {
        clock_gettime(CLOCK_MONOTONIC, &start);
        reset_values();
        get_inputs();
        solve();

        clock_gettime(CLOCK_MONOTONIC, &end);

        long long res = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec);
        cout << res << "(ns)" << endl;
    }
}
