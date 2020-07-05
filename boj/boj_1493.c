#include <stdio.h>
#include <stdbool.h>

int len, wid, hei, n;
int remain_box[21] = {0,};

long long sum = 0;
bool can_fill = true;

void get_input(void)
{
    freopen("input.txt", "r", stdin);

    scanf("%d %d %d\n", &len, &wid, &hei);
    scanf("%d\n", &n);

    for (int i = 0; i < n; ++i) {
        int a, b;
        scanf("%d %d\n", &a, &b);

        remain_box[a] = b;
    }
}

void fill_box(int l, int w, int h)
{
    if (l == 0 || w == 0 || h == 0 ) {
        return;
    }
    if (can_fill == false) {
        return;
    }

    int len = -1;

    for (int i = 19; i >= 0; --i) {

        len = 1<<i;

        if ((remain_box[i] > 0) && (len <= l) && (len <= w) && (len <= h)) {
            remain_box[i]--;
            sum++;

            fill_box(l-len, w, len);
            fill_box(len, w-len, len);
            fill_box(l, w, h-len);

            return;
        }
    }

    can_fill = false;

    return;
}

int main(void)
{
    get_input();

    fill_box(len, wid, hei);

    printf("%lld\n", can_fill ? sum : -1);

    return 0;
}
