#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
	// �ȶ��ַ������д���ʹ���䲻�ٺ��зǷ������ţ�Ȼ���䷭ת�Ժ��ټ���Ƿ��зǷ��������ţ�����������Ŷ������֮�󶼺Ϸ���������Ҫ�Ĵ��� http://lib.csdn.net/article/datastructure/18481
	vector<string> removeInvalidParentheses(string s) { 
		dfs(s, ')', 0);
		return ans;
	}
private:
	void dfs(string s, char ch, int last){
		for (int i = 0, cnt = 0; i < s.size(); ++i){
			if (s[i] == '(' || s[i] == ')'){
				s[i] == ch ? cnt++ : cnt--; // cnt��Ҫɾ�������ľ�������
			}
			if (cnt <= 0){
				continue;
			}
			for (int j = last; j <= i; j++){ // Ϊ��֤��������ظ�ֵ����Ҫ��¼һ�����ɾ����λ��
				if (s[j] == ch && (j == last || s[j - 1] != ch)){ // ע�����ﱣ֤���ظ����ж�
					dfs(s.substr(0,j) + s.substr(j+1), ch, j); 
				}
			}
			return; // ����ڴ�λ�ý��й���ɾ��DFS����û�б�Ҫ�ٽ���ѭ��
		}
		reverse(s.begin(), s.end());  // 
		if (ch == ')'){
			return dfs(s, '(', 0);
		}
		ans.push_back(s);
	}
	vector<string> ans;
};

int main(int argc, char *argv[]){
	Solution s;
	auto vs = s.removeInvalidParentheses("(a)())()");
	for (auto v : vs){
		cout << v << endl;
	}
	system("pause");
	return 0;
}