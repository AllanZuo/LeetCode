#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		return Helper(preorder, 0, preorder.size()-1,
			inorder, 0, inorder.size()-1);
	}

private:
	TreeNode* Helper(vector<int>& preorder, int prebegin, int preend, 
		vector<int>& inorder, int inbegin, int inend){
		if (prebegin > preend){
			return NULL;
		} else if (prebegin == preend){
			return new TreeNode(preorder[prebegin]);
		}

		TreeNode* root = new TreeNode(preorder[prebegin]); // ǰ���һ���ڵ�Ϊ���ڵ�
		int i = inbegin;
		for (; i <= inend; ++i){
			if (inorder[i] == preorder[prebegin]){  // ���������ҵ����ڵ�
				break;
			}
		}
		int leftlen = i - inbegin; // �������еĳ���

		root->left = Helper(preorder, prebegin + 1, prebegin + leftlen,  // ǰ������������г��Ƚ��л���
			inorder, inbegin, inbegin + leftlen - 1);  // ����ֱ������ڵ���л���

		root->right = Helper(preorder, prebegin + leftlen + 1, preend,
			inorder, inbegin + leftlen + 1, inend);

		return root;
	}
};

int main(int argc, char *argv[]){
	Solution s;
	s.buildTree(vector<int>{}, vector<int>{});
	system("pause");
	return 0;
}