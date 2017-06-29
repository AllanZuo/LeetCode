#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
	int longestSubstring(string s, int k) { // �÷��η��������ǻ�������
		int total[26] = { 0 };
		for (int i = 0; i<s.size(); i++){ // ͳ�ƴ�Ƶ
			total[s[i] - 'a']++;
		}
		int i = 0;
		while (i < s.size() && total[s[i] - 'a'] >= k){ // ��0��ʼɨ��������������������
			i++;
		}
		if (i == s.size()) { // ˵���������ж�����
			return i;
		}
		int j = i;
		while (j < s.size() && total[s[j] - 'a'] < k){ // ���ж�λ�ÿ�ʼɨ�費������������У��ҵ����ζ˵�
			j++;
		}
		return max(longestSubstring(s.substr(0, i), k), longestSubstring(s.substr(j), k)); // �ֶ���֮
	}

	int longestSubstringDirect(string s, int k) {
		const int n = s.size();
		int i = 0, res = 0;
		while (i + k <= n) {
			int m[26] = { 0 }, mask = 0, max_idx = i;
			for (int j = i; j < n; ++j){
				int t = s[j] - 'a';
				++m[t];
				if (m[t] < k){
					mask |= (1 << t);
				} else{
					mask &= (~(1 << t));
				}
				if (mask == 0){
					res = max(res, j - i + 1);
					max_idx = j;
				}
			}
			i = max_idx + 1;
		}
		return res;
	}
};

int main(int argc, char *argv[]){
	Solution s;
	cout << s.longestSubstring("ababbc", 2) << endl;
	system("pause");
	return 0;
}