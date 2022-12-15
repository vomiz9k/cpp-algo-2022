/*
Идем линейно, поддерживаем три переменные: минимальную цену до этого момента*, максимальную цену до этого момента* и максимальную прибыль.
Если пришла цена больше чем максимум до этого момента, обновляем максимум и максимальную прибыль.
Если пришла цена меньше минимума до этого момента, то считаем, что на массиве слева максимальная прибыль лежит в max_profit и забываем про него.
*/

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int min_price_before = std::numeric_limits<int>::max();
        int max_price_before = std::numeric_limits<int>::min();
        int max_profit = 0;
        for(const int price: prices) {
            if (price > max_price_before) {
                max_price_before = price;
                max_profit = max(max_profit, price - min_price_before);
            }
            if (price < min_price_before) {
                min_price_before = price;
                max_price_before = price;
            }
        }
        return max_profit;
    }
};