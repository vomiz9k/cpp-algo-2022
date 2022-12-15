/*
Даже зная решение аналогичной задачи с 1 числом, додуматься до такого самому мне интеллекта не хватило.
Решение гениальное конечно, разбить числа на 2 группы по значению ненулевого бита в xor'e всего массива
*/


class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        unsigned acc_xor = 0;
        for(const int num: nums) {
            acc_xor ^= num;
        }
        unsigned bit = acc_xor & (-acc_xor);
        std::vector<int> result{0, 0};
        for(const int num: nums) {
           if (num & bit) {
               result[0] ^= num;
           } else {
               result[1] ^= num;
           }
        }
        return result;
    }
};