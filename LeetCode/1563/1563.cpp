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

        // dp[left][right] 表示只剩下区间 [left, right] 时，
        // Alice 从后续游戏中最多能获得的分数。
        std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

        for (int length = 2; length <= n; ++length) {
            for (int left = 0; left + length <= n; ++left) {
                const int right = left + length - 1;

                for (int middle = left; middle < right; ++middle) {
                    const int leftSum = rangeSum(prefixSum, left, middle);
                    const int rightSum = rangeSum(prefixSum, middle + 1, right);

                    if (leftSum <= rightSum) {
                        dp[left][right] = std::max(
                            dp[left][right], leftSum + dp[left][middle]);
                    }

                    if (rightSum <= leftSum) {
                        dp[left][right] = std::max(
                            dp[left][right], rightSum + dp[middle + 1][right]);
                    }
                }
            }
        }

        return dp[0][n - 1];
    }

private:
    int rangeSum(const std::vector<int>& prefixSum, int left, int right) {
        return prefixSum[right + 1] - prefixSum[left];
    }
};
