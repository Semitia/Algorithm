#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>

using namespace std;

constexpr uint64_t MOD = 2933256077ULL;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    string s;
    cin >> n >> m >> s;

    // 从字典序最小的合法串开始，枚举所有含 m 个 0、n 个 1 的 T。
    string t(m, '0');
    t.append(n, '1');

    uint64_t answer = 0;
    do {
        int matched = 0;
        for (char c : t) {
            if (c == s[matched]) {
                ++matched;
            }
        }
        answer = (answer + matched) % MOD;
    } while (next_permutation(t.begin(), t.end()));

    cout << answer << '\n';
    return 0;
}
