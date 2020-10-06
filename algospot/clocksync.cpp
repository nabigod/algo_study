#include <iostream>
#include <vector>
using namespace std;

int min_val;
vector <int> clocks;
vector <vector <int>> button({
        vector <int> ({ 0, 1, 2 }),
        vector <int> ({ 3, 7, 9, 11 }),
        vector <int> ({ 4, 10, 14, 15 }),
        vector <int> ({ 0, 4, 5, 6, 7 }),
        vector <int> ({ 6, 7, 8, 10, 12 }),
        vector <int> ({ 0, 2, 14, 15 }),
        vector <int> ({ 3, 14, 15 }),
        vector <int> ({ 4, 5, 7, 14, 15 }),
        vector <int> ({ 1, 2, 3, 4, 5 }),
        vector <int> ({ 3, 4, 5, 9, 13 })
});

void get_input()
{
    int temp;

    for (int i = 0; i < 16; ++i) {
        scanf("%d ", &temp);

        clocks.push_back(temp%12);
    }
}

void click_button(int button_num, int cnt)
{
    for (int i = 0; i < button[button_num].size(); ++i) {
        clocks[button[button_num][i]] += 3*cnt;
        clocks[button[button_num][i]] %= 12;
    }
}

bool is_done()
{
    for (int i = 0; i < 16; ++i) {
        if (clocks[i] != 0) {
            return false;
        }
    }

    return true;
}

void solve(int button_idx, int cnt)
{
    if (is_done()) {
        min_val = (min_val > cnt) ? cnt : min_val;
        return;
    }

    if (button_idx == 10)
        return;


    vector <int> temp;

    for (int j = 0; j < 4; ++j) {
        temp = clocks;

        click_button(button_idx, j);

        solve(button_idx + 1, cnt + j);

        clocks = temp;
    }

    return;
}


int main()
{
    freopen("input.txt", "r", stdin);

    int tc;

    scanf("%d\n", &tc);

    for (int i = 0; i < tc; ++i) {
        min_val = 987654321;
        clocks.clear();
        get_input();
        solve(0, 0);

        printf("%d\n", (min_val == 987654321) ? -1 : min_val);
    }

    return 0;
}
