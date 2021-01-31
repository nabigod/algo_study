#include <iostream>
#include <cstring>
using namespace std;

int n, m;
int lesson[100000];

void reset_values()
{
    memset(lesson, 0, sizeof(int) * 100000);
}

void get_inputs()
{
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        cin >> lesson[i];
    }
}

bool is_valid_size(int size)
{
    int remain = m;
    int sum = 0;

    for (int i = 0; i < n; ++i) {
        if (size < lesson[i]) {
            return false;
        } else if (sum + lesson[i] <= size) {
            sum += lesson[i];
        } else {
            --remain;
            sum = lesson[i];
        }
    }

    return remain > 0;
}

int solve()
{
    int l, m, r;

    l = 1;
    r = 10000 * n;

    while (l <= r) {
        m = (l + r) / 2;

        if (is_valid_size(m)) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    return l;
}

int main()
{
    freopen("input.txt", "r", stdin);

    reset_values();
    get_inputs();
    cout << solve() << '\n';

    return 0;
}
