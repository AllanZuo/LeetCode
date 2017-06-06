#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
	bool isMatch(string s, string p){
		int slen = s.size(), plen = p.size();
		int i = 0, j = 0, is = -1, ip = -1;
		while (i < slen) {
			if (p[j] == '*'){ // {is, ip}Ϊ����*ͨ�����λ��
				is = i;
				ip = j++;
			} else{
				if (s[i] == p[j] || p[j] == '?'){
					i++;
					j++;
				} else if(ip == -1){
					return false;
				} else { // ���֮ǰ���ֹ�ͨ��������ҵ�ǰ����ͨ���λ�ã��е�ǰ�ַ���ƥ�䣬��ô���ϸ�ͨ�����ͨ��һ��λ�ã��Ӹ�λ�����¿�ʼ����
					i = ++is;  // ͨ�����ͨ��һ��λ��
					j = ip + 1; // ��ͨ���֮�����ƥ��
				}
			}
		}

		while (j < plen && p[j] == '*'){
			j++;
		}

		return j == plen;
	}

	bool isMatchMyDP(string s, string p) {
		const int n1 = s.size();
		const int n2 = p.size();
		if (!n1 || !n2){
			if (!n1 && !n2){
				return true;
			}
			if (n2 == 0){
				return false;
			}
			for (int j = 0; j < n2; ++j){
				if (p[j] != '*'){
					return false;
				}
			}
			return true;
		}
		vector<vector<bool>> m(n1, vector<bool>(n2));
		m[0][0] = ((s[0] == p[0]) || (p[0] == '?') || (p[0] == '*'));
		for (int i = 1; i < n1; ++i){
			m[i][0] = (p[0] == '*');
		}
		bool flag = ((p[0] == '?') || (p[0] == s[0]));
		for (int j = 1; j < n2; ++j){
			if (flag){
				m[0][j] = ((p[j] == '*') && m[0][j - 1]);
			}
			else{
				m[0][j] = (((p[j] == '*') || (p[j] == '?') || (p[j] == s[0])) && m[0][j - 1]);
				if (p[j] == '?' || p[j] == s[0]){
					flag = true;
				}
			}
		}
		for (int i = 1; i < n1; ++i){
			for (int j = 1; j < n2; ++j){
				m[i][j] = (m[i - 1][j - 1] && ((s[i] == p[j]) || p[j] == '?'))
					|| ((p[j] == '*') && (m[i - 1][j - 1] || m[i][j - 1] || m[i - 1][j]));
			}
		}
		return m[n1 - 1][n2 - 1];
	}
};

int main(int argc, char *argv[]){
	Solution s;
	cout << s.isMatch("aab", "a*b") << endl;
	system("pause");
	return 0;
}