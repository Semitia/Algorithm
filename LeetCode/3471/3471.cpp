#include <array>
#include <vector>

class Solution {
public:
    int largestInteger(std::vector<int>& nums, int k) {
        constexpr int valueCount = 51;
        std::array<int, valueCount> windowFrequency{};
        std::array<int, valueCount> activeSince{};
        std::array<int, valueCount> windowCount{};

        for (int i = 0; i < k; ++i) {
            ++windowFrequency[nums[i]];
        }

        const int totalWindows = static_cast<int>(nums.size()) - k + 1;

        for (int start = 1; start < totalWindows; ++start) {
            int outgoing = nums[start - 1];
            if (--windowFrequency[outgoing] == 0) {
                windowCount[outgoing] += start - activeSince[outgoing];
            }

            int incoming = nums[start + k - 1];
            if (windowFrequency[incoming]++ == 0) {
                activeSince[incoming] = start;
            }
        }

        for (int value = 0; value < valueCount; ++value) {
            if (windowFrequency[value] > 0) {
                windowCount[value] += totalWindows - activeSince[value];
            }
        }

        for (int value = valueCount - 1; value >= 0; --value) {
            if (windowCount[value] == 1) {
                return value;
            }
        }

        return -1;
    }
};
