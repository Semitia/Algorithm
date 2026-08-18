#include <algorithm>
#include <array>
#include <vector>

class Solution {
public:
    int largestInteger(std::vector<int>& nums, int k) {
        const int n = static_cast<int>(nums.size());

        if (k == n) {
            return *std::max_element(nums.begin(), nums.end());
        }

        std::array<int, 51> frequency{};
        for (int value : nums) {
            ++frequency[value];
        }

        if (k == 1) {
            for (int value = 50; value >= 0; --value) {
                if (frequency[value] == 1) {
                    return value;
                }
            }
            return -1;
        }

        int answer = -1;
        if (frequency[nums.front()] == 1) {
            answer = nums.front();
        }
        if (frequency[nums.back()] == 1) {
            answer = std::max(answer, nums.back());
        }
        return answer;
    }
};
