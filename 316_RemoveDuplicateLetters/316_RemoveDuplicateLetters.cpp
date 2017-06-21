#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
	string removeDuplicateLetters(string s) {
		int ahead[256] = {};
		bool inresult[256] = {}; // ��Ӧ�ַ��Ƿ������result��
		for (auto c : s){
			ahead[c]++;
		}
		string result = " ";
		for (auto c : s) {
			ahead[c]--;
			if (inresult[c]){ // ����ôʳ����ڽ���У���˵�����Ѿ�����������ȷ��λ����
				continue;
			}
			while (c < result.back() && ahead[result.back()]) { // ���result���һ����ĸ��cΥ�棬�򲻶Ͻ���ɾ����ֱ��c������ȷ
				inresult[result.back()] = false; // ���whileѭ��������̰��
				result.pop_back();
			}
			result += c;
			inresult[c] = true;
		}
		return result.substr(1);
	}
};

int main(int argc, char *argv[]){
	Solution s;
	cout << s.removeDuplicateLetters("cbacdcbc") << endl;
	system("pause");
	return 0;
}