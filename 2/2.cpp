// Subsets

#include <vector>
using namespace std;

/*
Идея: сортируем подсчетом, нам хорошо подходит массив counts.
Далее, идя в рекурсивную версию subsetsWithDup ищем первое число с
ненулевым count'ом, последовательно вставляем в текущую последовательность
всевозможные количества этого числа(от 0 до curr_count), зануляем
это значение в массиве, чтоб в следующих вызовах его не учитывать, и
запускаемся рекурсивно.
*/
class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<int> counts(21, 0);
        for(auto num: nums) {
            ++counts[num + 10];
        }
        vector<int> curr;
        vector<vector<int>> result;
        subsetsWithDup(counts, curr, result);
        return result;


    }

    void subsetsWithDup(vector<int>& counts, vector<int>& curr, vector<vector<int>>& result) {
        bool found_not_zero = false;
        for(int i = 0; i < counts.size(); ++i) {
            int curr_count = counts[i];
            if (curr_count == 0) {
                continue;
            }
            counts[i] = 0;
            found_not_zero = true;
            subsetsWithDup(counts, curr, result);
            for (size_t j = 0; j < curr_count; ++j) {
                curr.push_back(i - 10);
                subsetsWithDup(counts, curr, result);
            }
            for (size_t j = 0; j < curr_count; ++j) {
                curr.pop_back();
            }
            counts[i] = curr_count;
            break;
        }
        if (!found_not_zero) {
            result.push_back(curr);
        }
    }
};