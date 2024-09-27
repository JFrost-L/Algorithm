#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;

class TRI {
public:
	int a, b, w;
	//a에서 b를 넣었음
};

class PQ {
public:
	int n;
	TRI Arr[1000];

	PQ();
	TRI Delete();
	void insert(TRI x);
	bool isEmpty();
};
PQ::PQ() {
	n = 0;
}

bool PQ::isEmpty() {
	return n == 0;
}

void PQ::insert(TRI x) {
	int i;
	Arr[n + 1] = x;
	i = n + 1;
	n = n + 1;
	while (i > 1 && Arr[i].w < Arr[i / 2].w) {
		swap(Arr[i], Arr[i / 2]);
		i = i / 2;
	}
}

TRI PQ::Delete() {
	TRI ret = Arr[1];
	int i, j;
	if (n == 1) {
		n = 0;
		return ret;
	}
	Arr[1] = Arr[n];
	i = 1;
	n = n - 1;

	while (1) {
		if (i * 2 > n) {//왼쪽 자식이 없는 경우 : 자식이 없는 경우
			break;
		}
		else if (i * 2 + 1 > n) {//왼쪽 자식만 있는 경우
			if (Arr[i * 2].w < Arr[i].w) {//왼쪽 자식이 나보다 작다
				swap(Arr[i * 2], Arr[i]);
				i = i * 2;
			}
			else {//내가 왼쪽 자식보다 작다
				break;
			}
		}
		else {//자식이 둘다 있는 경우
			if ((Arr[i].w > Arr[i * 2].w) && (Arr[i].w > Arr[i * 2 + 1].w)) {//내가 두 자식보다 크다.
				if (Arr[i * 2].w < Arr[i * 2 + 1].w) {//왼쪽이 오른쪽 자식보다 더 작은 경우
					j = i * 2;
				}
				else {//오른쪽이 왼쪽 자식보다 더 작은 경우
					j = i * 2 + 1;
				}
				swap(Arr[i], Arr[j]);
				i = j;
			}
			else if ((Arr[i].w > Arr[i * 2].w) && (Arr[i].w <= Arr[i * 2 + 1].w)) {//내가 오른쪽 자식보다 작다
				j = i * 2;
				swap(Arr[i], Arr[j]);
				i = j;
			}
			else if ((Arr[i].w <= Arr[i * 2].w) && (Arr[i].w > Arr[i * 2 + 1].w)) {//내가 왼쪽 자식보다 작다
				j = i * 2 + 1;
				swap(Arr[i], Arr[j]);
				i = j;
			}
			else {
				break;
			}
		}
	}
	return ret;
}


PQ Q;

int n, m;
vector<pair<int, int>> Edges[1000];//노드와 가중치를 쌍으로 벡터에 저장
//전형적인 그래프 입력 받기

int marking[1000];//shortest Path 길이
//int previous[1000];//previous Node(이전 노드들 기억)
vector<int> previous[1000];//모든 경로를 다 기억 (같은 길이의 경로 유의)

int main() {
	int c, a, b, w;
	TRI x, y;
	scanf("%d %d", &n, &m);
	//노드의 개수가 n, 간선의 개수가 m

	for (int i = 0; i < m; i++) {//간선의 개수만큼 반복
		scanf("%d %d %d", &a, &b, &w);
		Edges[a].push_back(make_pair(b, w));//a 노드에 연결된 b 노드와 w를 쌍으로 넣기
		//모든 노드마다 pair의 벡터를 놓고 (노드, 가중치)
		Edges[b].push_back(make_pair(a, w));//b 노드에 연결된 a 노드와 w를 쌍으로 넣기
	}
	for (int i = 1; i <= n; i++) {
		marking[i] = 100000;
		//초기값을 거의 무한대
	}
	c = 1;
	marking[c] = 0;

	for (int i = 0; i < Edges[c].size(); i++) {//a노드와 연결된 간선의 개수만큼 반복
		x.a = c;//a 노드
		x.b = Edges[c][i].first;//a 노드와 연결된 노드
		x.w = marking[c] + Edges[c][i].second;//a 노드와 연결된 노드간 가중치 업데이트
		Q.insert(x);//PQ에 삽입
	}
	while (!Q.isEmpty()) {
		y = Q.Delete();//Q를 꺼낼 때마다 y에 대입
		if (marking[y.b] < 100000) {//이전에 업데이트 되었다면
			//현재 가장 짧은 간선을 가진 노드가 y
			//그것과 연결된 노드가 y.b
			//100000보다 작다는 의미는 이미 답을 찾았으니 찾을 필요가 없다는 것
			//무조건 지금 나온 것이 제일 작음 그것이 다익스트라 증명

			if (marking[y.b]==y.w) {//같은 경로의 길이
				printf("Edge from Node %d to Node %d of Total Path Length %d Added. Previous node %d.\n", y.a, y.b, y.w, y.a);
				previous[y.b].push_back(y.a);
			}
			else {
				printf("Ignored Edge from Node %d to Node %d of Total Path Length %d.\n", y.a, y.b, y.w);
				//버려지는 간선 체크
			}
		}
		else {//업데이트 되어있지 않아 여전히 100000 값을 갖는다면
			printf("Edge from Node %d to Node %d of Total Path Length %d Selected. Previous node %d.\n", y.a, y.b, y.w, y.a);
			c = y.b;
			//c는 현재 a 노드와 연결된 간선들의 크기가 가장 작은 상대 노드
			marking[c] = y.w;
			//연결된 상대 노드에 마킹
			//previous[c] = y.a;
			previous[c].push_back(y.a);
			//a 노드와 연결된 상대 노드의 이전 노드를 현재 노드로

			for (int i = 0; i < Edges[c].size(); i++) {//상대 노드의 간선 개수만큼 반복
				x.a = c;//상대 노드를 해당 노드로 대입
				x.b = Edges[c][i].first;//상대 노드와 연결된 노드 대입
				x.w = marking[c] + Edges[c][i].second;//상대 노드와 연결된 노드 간의 가중치 업데이트
				Q.insert(x);//상대 노드 정보 PQ에 삽입
			}
		}
	}
	return 0;
}

/*
3 7
1 2 1
2 3 4
1 3 2
1 2 7

4 5 2
4 5 1
4 5 3

끊어진 그래프는 PQ에 들어갈 수 없어서 계산하지 못하고 끝난다.
*/

/*
5 10
1 2 10
2 3 1
1 5 6
1 4 5
2 4 4
2 4 3
4 5 2
3 4 9
3 5 4
5 3 6
*/

/*
5 10
1 2 10
2 3 1
1 5 7
1 4 5
2 4 4
2 4 3
4 5 2
3 4 9
3 5 2
5 3 6

경로의 길이가 같은 경우 : 답이 여러 개 나올 경우
*/