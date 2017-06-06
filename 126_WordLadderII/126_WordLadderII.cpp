#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// Solution: https://discuss.leetcode.com/topic/82880/c-two-end-bfs-and-backtracking-45ms-clearly-commented

class Solution {
/*
	Idea :
	1. use two-end bfs to iteratively find the shortest path
	2. use a map of [nextNode, curNodeList] to record all possible paths to the nextNode for the purpose of backtracing
	3. use a boolean to represent the end of bfs, a boolean to represent the swap of head and tail
	4. use dfs to recursivlely backtrace

	Caution and more ideas : see comments
*/
public:
	vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList){
		unordered_set<string> s;
		for (auto item : wordList){
			s.insert(item);
		}
		if (s.find(endWord) == s.end()){
			return{};
		}

		unordered_map<string, unordered_set<string>> backtrace;
		unordered_set<string> head({ beginWord }), tail({endWord});
		bool reverse = false, finish = false;

		s.erase(beginWord); s.erase(endWord);
		while (!head.empty() && !tail.empty() && !finish){
			// two-end bfs: swap head and tail to reach balence of two sets
			// for optimized performance
			if (head.size() > tail.size()){
				reverse = !reverse;
				swap(head, tail);
			}
			// temp will contain neighbors of the current level nodes, so this is bfs
			unordered_set<string> temp;
			for (auto item : head){
				for (int l = 0; l < item.size(); ++l){ // �Ե�����ÿ����ĸ����26����ĸ���滻
					string ori = item;
					// O(26 * size of item)
					for (char c = 'a'; c <= 'z'; ++c){
						item[l] = c;
						if (tail.find(item) != tail.end()){  // ��Ѱ����β���ڵ�
							if (!reverse){
								backtrace[item].insert(ori); // backtrace ��������¼·�����ڽ����� map<string,vec<string>>�� string�е�ÿ��Ԫ�ض���vec<string>�е�Ԫ�����һ���ַ�����������Ǵ��з���ģ���֤��dfsʱ�����ָ������ַ���
							} else{
								backtrace[ori].insert(item);
							}
							finish = true;
						} else if (s.find(item) != s.end()){ // ��û�в��ҵ�β���ڵ�������,�ڴʵ��в���
							temp.insert(item);               // ���������
							if (!reverse){
								backtrace[item].insert(ori); // backtrace��������¼·������ʽΪ�ڽ�����
							} else{
								backtrace[ori].insert(item); 
							}
						}
					}
					item = ori;  // ��ǰ��ori=item���Ӧ��������е���item�Ļ�ԭ
				}
			}
			// only delete items after we finish iterating the current level
			// if we delete while iterating, it is possible that we delete a
			// node whice has two sources to reach it
			for (auto item : temp){ // because all temp are visited������ע�⣬��������ʶvisitied�����ڷ�����һ��֮���ʶvisited������Ϊ����bfsʱ��������һЩ·���Ķ�ʧ,finish Ҳ��һ��֮�����Ч�����������ҵ�������̵Ľ��
				s.erase(item);
			}
			head = temp;
		}

		vector<vector<string>> ret;
		vector<string> temp({endWord});
		backtrack(ret, backtrace, temp, endWord, beginWord);  // recover paths

		return ret;
	}

private:
	void backtrack(vector<vector<string>> &ret,
		unordered_map<string, unordered_set<string>>& backtrace,
		vector<string>& temp,
		string endWord,
		string beginWord){

		if (endWord == beginWord){   // ��֦����
			vector<string> rev = temp;
			reverse(rev.begin(), rev.end());
			ret.push_back(rev);
			return;
		}

		for (auto item : backtrace[endWord]){ // ����󵽴�endWord�����н������DFS����
			temp.push_back(item);
			backtrack(ret, backtrace, temp, item, beginWord); // endWord��������������ı仯��
			temp.pop_back();
		}
		return;
	}

	vector<vector<string>> findLaddersMyNotFinished(string beginWord, string endWord, vector<string>& wordList) {
		vector<vector<string>> res;
		const int n = wordList.size();
		if (n == 0){
			return res;
		}
		const int m = wordList[0].size();

		// build connect map;
		vector<vector<int>> connect(n);
		for (int i = 0; i < n; ++i){
			for (int j = i + 1; j < n; ++j){
				int cnt = 0;
				for (int k = 0; k < m; ++k){
					if (wordList[i][m] != wordList[j][m]){
						cnt++;
					}
				}
				if (cnt == 1){
					connect[i].push_back(j);
					connect[j].push_back(i);
				}
			}
		}

		vector<bool> toend(n, false);

		queue<int> q;
		for (int i = 0; i < n; ++i){
			int cnt1 = 0, cnt2 = 0;
			for (int k = 0; k < n; ++k){
				if (wordList[m][k] != beginWord[k]){
					cnt1++;
				}
				if (wordList[m][k] != endWord[k]){
					cnt2++;
				}
			}
			if (cnt1 == 1){
				q.push(i);
			}
			if (cnt2 == 1){
				toend[i] = true;
			}
		}

		vector<bool> visited(n + 1, false);

		while (!q.empty()){
			int nd = q.front(); q.pop();
			if (toend[nd]){
				// get
				continue;
			}
			for (int i = 0; i < connect[nd].size(); ++i){
				int id = connect[nd][i];
				if (toend[id]){
					// get
					continue;
				}
				if (visited[connect[nd][i]]){
					continue;
				}
				visited[connect[nd][i]] = true;
				q.push(id);
			}
		}

	}

};

int main(int argc, char *argv[]){
	Solution s;
	auto rs = s.findLadders("hit", "cog", vector<string>{ "hot", "dot", "dog", "lot", "log", "cog" });
	for (auto vstr : rs){
		for (auto str : vstr){
			cout << str << ", ";
		}
		cout << endl;
	}
	system("pause");
	return 0;
}