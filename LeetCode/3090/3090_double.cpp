#include <algorithm>
#include <array>
#include <string>

class Solution {
public:
    int maximumLengthSubstring(const std::string& s) {
        std::array<int, 26> count{};
        int left = 0;
        int answer = 0;

        for (int right = 0; right < static_cast<int>(s.size()); ++right) {
            int index = s[right] - 'a';
            ++count[index];

            while (count[index] > 2) {
                --count[s[left] - 'a'];
                ++left;
            }

            answer = std::max(answer, right - left + 1);
        }

        return answer;
    }
};