#include <vector>

class Solution {
    enum class Result {
        InvalidFirst,
        AliceWins,
        AliceLosesByEmpty,
        AliceLosesByMultipleOfThree,
    };

    // 先不考虑余数为 0 的石子，固定 Alice 的第一步后模拟游戏。
    // 此后每个余数状态都只有一种安全的非零选择：
    // 和为 1 时只能选 1，和为 2 时只能选 2。
    Result playWithoutZero(int count1, int count2, int first) {
        int count[3] = {0, count1, count2};
        if (count[first] == 0) {
            return Result::InvalidFirst;
        }

        --count[first];
        int sumMod = first;
        bool aliceTurn = false;  // Alice 已经完成第一步，现在轮到 Bob。

        while (true) {
            if (count[1] + count[2] == 0) {
                // 即使最后一步是 Alice 走的，只要安全取完，仍然是 Bob 获胜。
                return Result::AliceLosesByEmpty;
            }

            int safe = sumMod;
            if (count[safe] == 0) {
                // 还有石子却没有安全选择，当前玩家只能使总和变成 3 的倍数。
                return aliceTurn ? Result::AliceLosesByMultipleOfThree
                                 : Result::AliceWins;
            }

            --count[safe];
            sumMod = 3 - sumMod;  // 1 + 1 -> 2，2 + 2 -> 1（模 3）。
            aliceTurn = !aliceTurn;
        }
    }

public:
    bool stoneGameIX(std::vector<int>& stones) {
        int count[3] = {};
        for (int stone : stones) {
            ++count[stone % 3];
        }

        Result firstOne = playWithoutZero(count[1], count[2], 1);
        Result firstTwo = playWithoutZero(count[1], count[2], 2);

        if (count[0] % 2 == 0) {
            // 偶数个 0 两两抵消，寻找原本就能让 Alice 获胜的开局。
            return firstOne == Result::AliceWins ||
                   firstTwo == Result::AliceWins;
        }

        // 奇数个 0 留下一个有效的“换手”。Alice 要选择一个原本会因为
        // 被迫凑成 3 的倍数而输的分支；若原因为安全取完，则无法扭转。
        return firstOne == Result::AliceLosesByMultipleOfThree ||
               firstTwo == Result::AliceLosesByMultipleOfThree;
    }
};
