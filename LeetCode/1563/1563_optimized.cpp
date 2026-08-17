#include <algorithm>
#include <vector>

class Solution {
public:
    int stoneGameV(std::vector<int>& stoneValue) {
        const int n = static_cast<int>(stoneValue.size());

        std::vector<int> prefixSum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefixSum[i + 1] = prefixSum[i] + stoneValue[i];
        }

        // dp[left][right] 表示区间 [left, right] 能获得的最大后续得分。
        // bestLeft[left][right] 维护 sum(left, end) + dp[left][end] 的前缀最大值；
        // bestRight[left][right] 维护 sum(begin, right) + dp[begin][right] 的后缀最大值。
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));
        std::vector<std::vector<int>> bestLeft(n, std::vector<int>(n, 0));
        std::vector<std::vector<int>> bestRight(n, std::vector<int>(n, 0));

        for (int left = n - 1; left >= 0; --left) {
            bestLeft[left][left] = stoneValue[left];
            bestRight[left][left] = stoneValue[left];

            // 对固定的 left，middle 是第一个满足左侧和 >= 右侧和的位置。
            // right 右移时 middle 只会右移，所以一整行只需移动 O(n) 次。
            int middle = left;
            for (int right = left + 1; right < n; ++right) {
                const int total = rangeSum(prefixSum, left, right);
                while (middle < right
                       && 2 * rangeSum(prefixSum, left, middle) < total) {
                    ++middle;
                }

                if (middle == right) {
                    // 所有合法切分的左侧和都小于右侧和，只可能保留左侧。
                    dp[left][right] = bestLeft[left][right - 1];
                } else {
                    // 从 middle 开始，切分后的右侧可以被保留。
                    dp[left][right] = bestRight[middle + 1][right];

                    const int leftSum = rangeSum(prefixSum, left, middle);
                    if (2 * leftSum == total) {
                        // 两侧相等时，middle 对应的左、右区间都可以保留。
                        dp[left][right] = std::max(
                            dp[left][right], bestLeft[left][middle]);
                    } else if (middle > left) {
                        // 严格左大右小时，middle 不能作为可保留左侧的切分点。
                        dp[left][right] = std::max(
                            dp[left][right], bestLeft[left][middle - 1]);
                    }
                }

                const int score = total + dp[left][right];
                bestLeft[left][right] = std::max(
                    bestLeft[left][right - 1], score);
                bestRight[left][right] = std::max(
                    bestRight[left + 1][right], score);
            }
        }

        return dp[0][n - 1];
    }

private:
    int rangeSum(const std::vector<int>& prefixSum, int left, int right) {
        return prefixSum[right + 1] - prefixSum[left];
    }
};
