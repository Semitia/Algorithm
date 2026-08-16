#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> c(n + 1);
    for (int i = 1; i <= n; ++i) cin >> c[i];

    const size_t blocks = (static_cast<size_t>(n) + 63) / 64;

    // bits[j * blocks ... (j + 1) * blocks) represents S_j.
    vector<uint64_t> bits((static_cast<size_t>(n) + 1) * blocks);
    vector<int> set_size(n + 1);

    int answer = 0;
    for (int j = n; j >= 1; --j) {
        const int next_double = (2 * j <= n ? 2 * j : 0);
        const int next_add = (j + c[j] <= n ? j + c[j] : 0);
        uint64_t* current = bits.data() + static_cast<size_t>(j) * blocks;

        if (next_double == 0 && next_add == 0) {
            set_size[j] = 0;
        } else if (next_add == 0 || next_add == next_double) {
            const uint64_t* source =
                bits.data() + static_cast<size_t>(next_double) * blocks;
            memcpy(current, source, blocks * sizeof(uint64_t));
            set_size[j] = set_size[next_double];
        } else if (next_double == 0) {
            const uint64_t* source =
                bits.data() + static_cast<size_t>(next_add) * blocks;
            memcpy(current, source, blocks * sizeof(uint64_t));
            set_size[j] = set_size[next_add];
        } else {
            const uint64_t* left =
                bits.data() + static_cast<size_t>(next_double) * blocks;
            const uint64_t* right =
                bits.data() + static_cast<size_t>(next_add) * blocks;

            int count = 0;
            for (size_t k = 0; k < blocks; ++k) {
                current[k] = left[k] | right[k];
                count += __builtin_popcountll(current[k]);
            }
            set_size[j] = count;
        }

        const size_t value = static_cast<size_t>(c[j] - 1);
        const uint64_t mask = uint64_t{1} << (value & 63);
        if ((current[value >> 6] & mask) == 0) {
            current[value >> 6] |= mask;
            ++set_size[j];
        }

        answer = max(answer, set_size[j]);
    }

    cout << answer << '\n';
    return 0;
}
