#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
	int minSubArrayLen(int s, vector<int>& nums) {
		const int n = nums.size();
		if (n == 0){
			return 0;
		}
		vector<int> itg(n+1);
		itg[0] = 0;
		for (int i = 0; i < n; ++i){
			itg[i+1] = itg[i] + nums[i];
		}
		int minstep = INT_MAX;
		for (int i = n - 1; i >= 0; --i){
			int l = 0, r = i;
			int target = itg[i+1] - s;
			if (target < itg[0]){
				continue;
			}
			int idx = -1;
			while (l <= r){  // �����������ҵ�С�ڵ���target��������
				int m = (l + r) / 2;
				int mv = itg[m];
				if (mv < target){
					idx = m;
					l = m + 1;
				} else if (mv > target){
					r = m - 1;
				} else{ // if (mv == target�� �϶�������Ҫ��������
					idx = m;
					break;
				}
			}
			if (idx == -1){
				continue;
			}
			minstep = min(minstep, i - idx + 1);
		}
		if (minstep == INT_MAX){
			return 0;
		}
		return minstep;
	}

	int minSubArrayLenON(int s, vector<int>& nums){
		int n = nums.size(), start = 0, sum = 0, minlen = INT_MAX;
		for (int i = 0; i < n; ++i){
			sum += nums[i];
			while (sum >= s){  // ��Ϊ�ڲ�ѭ����O(1)�ģ���������O(n)
				minlen = min(minlen, i - start + 1); // start++,�൱��min--�� sum�Ƕ�̬��Χ����
				sum -= nums[start++];
			}
		}
		return minlen == INT_MAX ? 0 : minlen;
	}
};

int main(int argc, char *argv[]){
	Solution s;
	cout << s.minSubArrayLenON(15, vector<int>{1, 2, 3, 4, 5}) << endl;
	system("pause");
	return 0;
}
