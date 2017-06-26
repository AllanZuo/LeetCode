#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
	int minPatches(vector<int>& nums, int n) { // ̰���㷨
		long miss = 1; // ��ǰ�����[0, miss)�������, ��Ϊ�ǿ����䣬����miss�������
		int ret = 0, i = 0; 
		while (miss <= n){
			if (i < nums.size() && nums[i] <= miss){ // nums[i] <= missʱ������nums[i],����ʹ��Ϸ�Χ����[0, miss+nums[i])
				miss += nums[i++];
			} else{ // nums[i] > miss ʱ������miss������ʹ��Χ����[0, 2*miss)
				miss <<= 1;
				++ret;
			}
		}
		return ret;
	}
};

int main(int argc, char *argv[]){
	Solution s;
	cout << s.minPatches(vector<int>{1, 5, 10}, 20) << endl;
	system("pause");
	return 0;
}
