#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define INF (100000000) // 충분히 큰 수

using namespace std;

int d[51] = { 0, }; // 각 지점의 차수
int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int n; // 정점 개수
	vector<vector<int> > v; // 간선 정보
	cin >> n;
	v.resize(n + 1);
	for (int i = 1; i <= n; i++) {
		int vi; // 정점 번호
		cin >> vi;
		while (1) {
			int u;
			cin >> u;
			if (!u) break;
			v[vi].push_back(u);
		}
		d[vi] = v[vi].size(); // 정점 개수
	}
	// 최단 경로를 찾아서 각 지점까지 최단경로 중, 대기시간을 고려했을때
	// 가장 큰 값이 지름 후보가됨
	// 시작과 끝 정점의 차수는 시간 계산에 포함 안됨
	int ans = 0;
	for (int i = 1; i <= n; i++) {
		priority_queue < pair<int, int>, vector<pair<int, int> > > pq;
		int dist[51];
		fill(dist, dist + 51, INF); // 초기값을 상당히 큰 수로 
		dist[i] = 0; // 시작점 비용을 0
		pq.push(make_pair(0, i)); 

		while (!pq.empty()) { // i번쨰 노드에서 시작했을때 모든 노드로 가는 최소 비용을 구함
			int node = pq.top().second; // 방문된 노드 중 가장 비용이 적은 노드를 우선적으로 탐색 순회
			pq.pop();
			int _size = v[node].size();

			for (int j = 0; j < _size; j++) {
				int nxt = v[node][j];
				if (dist[nxt] > dist[node] + d[nxt] ) { 
					// nxt 로 가는 최단 경로가 node에서 nxt로 가는 최단 경로보다 큰 경우
					// 새로운 최단 경로를 찾았으므로
					dist[nxt] = dist[node] + d[nxt];
					pq.push(make_pair(-dist[nxt], nxt));
				}
			}
		}

		// 마지막으로 각 dist[i]에서 d[i]-1 을 다시 빼줌 
		for (int j = 1; j <= n; j++) {
			if (i != j) { // 다른 도착 지점
				dist[j] -= (d[j] - 1); // 마지막 지점의 차수를 다시한번 빼줌 // 위에서 더했으므로
				ans = max(ans, dist[j]);
			}
		}
	}
	cout << ans <<"\n";
}