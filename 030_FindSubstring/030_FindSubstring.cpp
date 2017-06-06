#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

class Solution {
public:
	vector<int> findSubstring(string s, vector<string>& words) {
		vector<int> res;
		map<string, int> traits;
		if (s.empty() || words.empty()){
			return res;
		}

		for (auto word : words){
			traits[word]++;
		}
		int len = words[0].size();

		for (int i = 0; i < len; ++i){ // �൱�������������ڶ���ѭ���Ͳ���Ҫ��������ˣ����巨�� 0,1,2 ö�ٹ�֮�󣬾Ͳ���ö��3��
			map<string, int> window;

			int l = i; // left \ right ��ָ��ָ���������߽�
			int r = i; 
			while (r < s.size()){ // ����ʼ�߽�����
				while (r < s.size()){ // ��չ����
					auto word = s.substr(r, len);
					r += len;
					if (traits.find(word) == traits.end()){  // û�ҵ�����ô��������len
						window.clear();
						l = r;
					} else{ // �ҵ���
						window[word]++;
						if (window[word] >= traits[word]){
							break;
						}
					}
				}
				while (l < r){  // �������ڣ���β���ĵ��ʶ��ˣ���Ϊ��һ��while����Ϊβ���ĵ��ʶ����break��
					auto head = s.substr(l, len); // ������ַ���
					auto tail = s.substr(r - len, len);  // ���ҵ��ַ���
					if (window[tail] == traits[tail]){
						break;
					}
					l += len;
					window[head]--;
				} // ����
				if ((r - l) == len * words.size()){
					res.push_back(l);
				}
			}
		}
		return res;
	}
};

int main(int argc, char *argv[]){
	Solution s;
	vector<string> vstr = {"foo" , "bar"};
	auto vv = s.findSubstring("barfoobarfoobar", vstr);
	for (auto v : vv){
		cout << v << ", ";
	}
	system("pause");
	return 0;
}
