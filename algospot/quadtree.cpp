#include <iostream>
#include <string>
using namespace std;

string str;

void get_input()
{
    cin >> str;
}

string reverse_tree(string input, int &idx) {
    char head = input[idx];

    idx++;

    if (head == 'b' || head == 'w') {
        return string(1, head);
    }

    string ul = reverse_tree(input, idx);
    string ur = reverse_tree(input, idx);
    string ll = reverse_tree(input, idx);
    string lr = reverse_tree(input, idx);

    return string("x") + ll + lr + ul + ur;
}

int main()
{
    //freopen("input.txt", "r", stdin);

    int tc;

    cin >> tc;

    for (int i = 0; i < tc; ++i) {
        int idx = 0;

        get_input();
        cout << reverse_tree(str, idx) << '\n';
    }


}
