#include <algorithm>
#include <array>
#include <string>

class Solution {
public:
    int maximumLengthSubstring(const std::string& s) {
        int n = static_cast<int>(s.size());
        int answer = 0;

        for (int length = 1; length <= n; ++length) {
            std::array<int, 26> count{};

            for (int i = 0; i < length; ++i) {
                ++count[s[i] - 'a'];
            }

            if (isValid(count)) {
                answer = length;
            }

            for (int start = 1; start + length <= n; ++start) {
                --count[s[start - 1] - 'a'];
                ++count[s[start + length - 1] - 'a'];

                if (isValid(count)) {
                    answer = length;
                }
            }
        }

        return answer;
    }

private:
    bool isValid(const std::array<int, 26>& count) {
        return std::all_of(count.begin(), count.end(),
                           [](int frequency) { return frequency <= 2; });
    }
};
