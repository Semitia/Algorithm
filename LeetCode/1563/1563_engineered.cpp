#include <algorithm>
#include <cstddef>
#include <memory>
#include <vector>

class Solution {
public:
    int stoneGameV(std::vector<int>& stoneValue) {
        const int n = static_cast<int>(stoneValue.size());
        if (n == 1) {
            return 0;
        }

        // dp[i][j] 只会用于立刻生成 sum(i, j) + dp[i][j]，不必整表保存。
        // left 和 right 使用同一块连续且无须清零的内存，减少分配和缓存开销。
        const std::size_t cellCount = static_cast<std::size_t>(n) * n;
        std::unique_ptr<int[]> states(new int[cellCount * 2]);
        int* const bestLeft = states.get();
        int* const bestRight = bestLeft + cellCount;

        int answer = 0;
        for (int left = n - 1; left >= 0; --left) {
            int* const leftRow = bestLeft + left * n;
            int* const rightRow = bestRight + left * n;
            int* const nextRightRow = rightRow + n;

            leftRow[left] = stoneValue[left];
            rightRow[left] = stoneValue[left];

            int middle = left;
            int leftSum = stoneValue[left];
            int total = stoneValue[left];

            // 指向 bestRight[middle + 1]；middle 右移时直接移动行指针。
            int* splitRightRow = nextRightRow;

            for (int right = left + 1; right < n; ++right) {
                total += stoneValue[right];

                while (middle < right && 2 * leftSum < total) {
                    ++middle;
                    leftSum += stoneValue[middle];
                    splitRightRow += n;
                }

                if (middle == right) {
                    answer = leftRow[right - 1];
                } else {
                    answer = splitRightRow[right];

                    // 相等时 middle 仍可作为左侧结尾；严格左大时只能取到 middle - 1。
                    const int leftEnd = middle - (2 * leftSum != total);
                    if (leftEnd >= left) {
                        answer = std::max(answer, leftRow[leftEnd]);
                    }
                }

                const int score = total + answer;
                leftRow[right] = std::max(leftRow[right - 1], score);
                rightRow[right] = std::max(nextRightRow[right], score);
            }
        }

        // [0, n - 1] 是上述遍历顺序中的最后一个区间。
        return answer;
    }
};
