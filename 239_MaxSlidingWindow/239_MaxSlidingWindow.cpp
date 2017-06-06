#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>

using namespace std;

class Solution {
public:
	vector<int> maxSlidingWindowOld(vector<int>& nums, int k) {
		vector<int> maxvec(nums.size()-k+1, 0);
		priority_queue<int> pq;
		if (k < 2){
			return nums;
		}
		const int j = k - 1;
		for (int m = 0; m < maxvec.size(); ++m){
			maxvec[m] = *max_element(nums.begin() + m, nums.begin() + m + j);
		}
		return maxvec;
	}

	vector<int> maxSlidingWindow(vector<int>& nums, int k) { //DQ
		vector<int> res;
		deque<int> q; // ˫����б��������±�
		for (int i = 0; i < nums.size(); ++i) {
			if (!q.empty() && q.front() == i - k) {
				q.pop_front(); // ��������Ѿ������������ˣ�����ɾ��
			}
			while (!q.empty() && nums[q.back()] < nums[i]) { 
				q.pop_back(); // �����Ҫ������ֵ�ȶ�β��ֵ�����β��ֵ��ɾ��(��Щֵ���Ѿ�ʧЧ)����֤�����ֵ�ڶ�����ǰ��
			}
			q.push_back(i);
			if (i >= k - 1) {
				res.push_back(nums[q.front()]); // ����ǰ���ɸѡ֮�󣬶��׵�ֵ���������������ֵ
			}
		}
		return res;
	}
};

int main(int argc, char *argv[]){
	Solution s;
	vector<int> v{0, 1, 2, 5, 3, 5, 5, 6, 7};
	auto r = s.maxSlidingWindow(v, 3);
	for (auto t : r){
		cout << t << ", ";
	}
	system("pause");
	return 0;
}
