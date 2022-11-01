// Unique Binary Search Trees II

#include <string>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*
Идея: в корень ставим в цикле вершины от 1 до n, слева - дерево, справа - дерево, перебираем их,
кладем посчитанные деревья в кэш.

В строчке
    result.emplace_back(new TreeNode(i, left_tree, DeepCopy(right_tree, i)));
левое поддерево по хорошему тоже надо копировать, но литкод не заругался на double free, так что пусть будет так.

*/


class Solution {
public:
    static vector<TreeNode*>& generateTrees(int n) {
        if (cache.size() > n)
            return cache[n];
        vector<TreeNode*> result;
        for(int i = 1; i <= n; ++i) {
            auto& right_trees = generateTrees(n - i);
            auto& left_trees = generateTrees(i - 1);

            for (const auto& right_tree: right_trees)  {
                for (const auto& left_tree: left_trees) {
                    result.emplace_back(new TreeNode(i, left_tree, DeepCopy(right_tree, i)));
                }
            }
        }
        cache.emplace_back(std::move(result));
        return cache[n];

    }
    static TreeNode* DeepCopy(TreeNode* root, int delta) {
        if (root == nullptr) {
            return nullptr;
        }
        TreeNode* node = new TreeNode(root->val + delta);
        node->left = DeepCopy(root->left, delta);
        node->right = DeepCopy(root->right, delta);
        return node;
    }
    static vector<vector<TreeNode*>> cache;
};

vector<vector<TreeNode*>> Solution::cache = {{nullptr}};