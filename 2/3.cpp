// Parenthesis

#include <vector>
#include <string>
#include <stack>
using namespace std;

/*
Идея: закидываем в стек потенциальных кандидатов на нужные ПСП, запускаем бфс,
берем верхнее значение со стека, далее оперируя знаниями* о количестве открытых
и закрытых скобочек в этой строке(если можем добавить открытую - добавляем,
если закрытых меньше чем открытых - добавляем) добавляем новые варианты в стек.

* - снова немного обфусцировал этот процесс, чтобы реже пересчитывать эти вещи
*/

class Solution {
public:
    vector<string> generateParenthesis(int n) {
        string curr;
        curr.reserve(2 * n);
        stack<string> st;
        vector<string> result;
        st.push("(");
        int opened_cnt = 1, closed_cnt = 0;
        while(!st.empty()) {
            auto curr = st.top();
            st.pop();
            if (closed_cnt < opened_cnt) {
                if (curr.size() == 2 * n - 1) {
                    result.push_back(curr + ")");
                    if (!st.empty()) {
                        opened_cnt = CountOpened(st.top());
                        closed_cnt = CountClosed(st.top());
                    }
                    continue;
                } else {
                    st.push(curr + ")");
                }
            }
            if (opened_cnt < n) {
                st.push(curr + "(");
                ++opened_cnt;
            } else {
                ++closed_cnt;
            }
        }

        return result;
    }

    static int CountOpened(const string& s) {
       int count = 0;

        for (int i = 0; i < s.size(); i++)
            if (s[i] == '(') count++;
       return count;
    }

    static int CountClosed(const string& s) {
       int count = 0;

        for (int i = 0; i < s.size(); i++)
            if (s[i] == ')') count++;
       return count;
    }
};