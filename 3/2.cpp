// Interleaving strings

#include <string>
#include <vector>
using namespace std;

/*

Идея: ДП по самой маленькой строке, далее двойной цикл.
Идем по символам большей строки во внешнем цикле, каждый раз заново заполняя dp.
dp[0] = true, далее
dp[j] = dp[j] && s1[i-1]==s3[i+j-1] || dp[j-1] && s2[j-1]==s3[i+j-1], с поправками на корректность индексов
то есть либо на предыдущей итерации внещнего цикла dp[j] было true и символ в большой строке подходит,
либо dp[j - 1] в предыдущей итерации внутреннего цикла стало true и символ в меньшей строке подходит.

Формулу преобразовал, оптимизировалось неплохо:
Runtime: 0 ms, faster than 100.00% of C++ online submissions for Interleaving String.
Memory Usage: 6.1 MB, less than 96.59% of C++ online submissions for Interleaving String.
*/
class Solution {
public:
    static bool isInterleave(const string& s1, const string& s2, const string& s3) {
        if (s3.size() != s1.size() + s2.size()) {
            return false;
        }
        const string& st1 = s1.size() < s2.size() ? s1 : s2;
        const string& st2 = s1.size() < s2.size() ? s2 : s1;

        vector<char> dp(st1.size() + 1, 0);
        for (int i = 0; i <= st2.size(); ++i) {
            for (int j = 0; j <= st1.size(); ++j) {
                dp[j] = (i == 0 && j == 0) ||
                        ((j != 0) && dp[j - 1] && st1[j - 1] == s3[i + j - 1]) ||
                        (dp[j] && st2[i - 1] == s3[i + j - 1]);

            }
        }
        return dp[st1.size()];
    }
};