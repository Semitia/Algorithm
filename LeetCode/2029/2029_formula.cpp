#include <cstdlib>
#include <vector>

class Solution {
public:
    bool stoneGameIX(std::vector<int>& stones) {
        int count[3] = {};
        for (int stone : stones) {
            ++count[stone % 3];
        }

        if (count[0] % 2 == 0) {
            // 没有额外的换手：Alice 选择数量较少的一类开局。
            return count[1] > 0 && count[2] > 0;
        }

        // 有一次额外的换手：Alice 选择数量较多的一类开局。
        // 必须至少多 3 个；只多 2 个会安全地取完，仍然是 Bob 获胜。
        return std::abs(count[1] - count[2]) > 2;
    }
};
