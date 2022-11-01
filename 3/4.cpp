// Trapping Rain Water

#include <string>
#include <vector>
using namespace std;

/*

Идея: две каретки, слева и справа.
Смотрим, где высота меньше (то есть точно будет более высокая граница с другой стороны)
и или обновляем максимум, или добавляем несколько капель в ответ, двигаем каретку.


*/



class Solution {
public:
    static int trap(const vector<int>& height) {
        int l = 0, r = height.size() - 1;
        int l_max = 0, r_max = 0;
        int result = 0;
        while (l < r) {
            if (height[l] < height[r]) {
                if (height[l] >= l_max) {
                    l_max = height[l];
                } else {
                    result += l_max - height[l];
                }
                ++l;
            } else {
                if (height[r] >= r_max) {
                    r_max = height[r];
                } else {
                    result += r_max - height[r];
                }
                --r;
            }
        }
        return result;
    }
};