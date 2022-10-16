
// Permutations

#include <vector>
using namespace std;

/*

Идея: сортируем входной массив, далее идем в рекурсивную permuteUnique().
Далее проходимся по всем числам в массиве и смотрим, если предыдущее
такое же число было "отвергнуто" на предыдущих рекурсивных вызовах, то
мы так же его не включаем в текущую рассматриваемую комбинацию, далее
делаем рекурсивный вызов.
Это корректно, так как если есть число x, повторяющееся k раз, то
флаги в массиве used будут выставляться последовательно, "устойчиво"(в терминологии
сортировок), а значит не будет дубликатов перестановок.

Различные обфускации наподобие вот этих:
*/
static vector<int> nums;
static vector<bool> used(8, false);
static vector<int> curr(8);
static size_t curr_idx = 0;
static vector<vector<int>> result;
/*
как и сортировка подсчетом, были написаны исключительно в целях
получения более красивых процентов на литкоде
*/

class Solution {

public:
    static vector<vector<int>> permuteUnique(vector<int>& nums_) {
        nums = nums_;
        vector<int> counts(21, 0);
        for(auto num: nums) {
            ++counts[num + 10];
        }
        size_t j = 0;
        for(int i = 0; i < 21; ++i) {
            while(counts[i]-- > 0) {
                nums[j++] = i - 10;
            }
        }
        curr.resize(nums_.size());
        used = vector<bool>(nums.size(), false);
        permuteUnique();

        return result;
    }

    static void permuteUnique() {
        for(size_t i = 0; i < nums.size(); ++i) {
            if (!used[i] && !(i > 0 && nums[i] == nums[i - 1] && !used[i - 1])) {
                used[i] = true;
                curr[curr_idx++] = nums[i];
                if (curr_idx == nums.size()) {
                    result.push_back(curr);
                } else {
                    permuteUnique();
                }
                --curr_idx;
                used[i] = false;
            }
        }
    }

    ~Solution() {
        result = {};
    }
};
