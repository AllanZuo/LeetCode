#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
	void reverseWords(string &s) { // ���η�ת��, ����ȥ������Ŀո�
		const int n = s.size();
		if (n == 0){
			return;
		}
		int left = 0, right = 0, i = 0;
		while (i < n){
			while (i < n && s[i] == ' '){
				i++;
			}
			if (i >= n){
				break;
			}
			if (left != right){
				s[right++] = ' ';
			}
			left = right;
			while (i < n && s[i] != ' '){
				s[right++] = s[i++]; // ƽ��ȥ��ͷ���ո�
			}
			reverse(s.begin() + left, s.begin() + right); // ִ�з�ת
		}
		s.resize(right);
		reverse(s.begin(), s.end());
		return;
	}
};

int main(int argc, char *argv[]){
	Solution s;
	string str(" the sky  is blue ");
	s.reverseWords(str);
	cout << str << endl;
	system("pause");
	return 0;
}