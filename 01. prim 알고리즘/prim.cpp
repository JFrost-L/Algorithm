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
			if ((Arr[i].w>Arr[i * 2].w) && (Arr[i].w> Arr[i * 2+1].w)) {//내가 두 자식보다 크다.
				if (Arr[i * 2].w < Arr[i * 2 + 1].w) {//왼쪽이 오른쪽 자식보다 더 작은 경우
					j = i * 2;
				}
				else {//오른쪽이 왼쪽 자식보다 더 작은 경우
					j = i * 2 + 1;
				}
				swap(Arr[i], Arr[j]);
				i = j;
			}
			else if((Arr[i].w > Arr[i * 2].w) &&(Arr[i].w <= Arr[i * 2 + 1].w)) {//내가 오른쪽 자식보다 작다
				j = i * 2;
				swap(Arr[i], Arr[j]);
				i = j;
			}
			else if ((Arr[i].w <= Arr[i * 2].w) && (Arr[i].w > Arr[i * 2 + 1].w)) {//내가 왼쪽 자식보다 작다
				j = i * 2+1;
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

int marking[1000];
int main() {
	int c, a, b, w;
	TRI x, y;
	scanf("%d %d",&n,&m);
	//노드의 개수가 n, 간선의 개수가 m

	for (int i = 0; i < m; i++) {//간선의 개수만큼 반복
		scanf("%d %d %d", &a, &b, &w);
		Edges[a].push_back(make_pair(b, w));//a 노드에 연결된 b 노드와 w를 쌍으로 넣기
		//모든 노드마다 pair의 벡터를 놓고 (노드, 가중치)
		Edges[b].push_back(make_pair(a, w));//b 노드에 연결된 a 노드와 w를 쌍으로 넣기
	}
	c = 1;
	marking[1] = 1;
	//a 노드를 마킹

	for (int i = 0; i < Edges[c].size(); i++) {//a노드와 연결된 간선의 개수만큼 반복
		x.a = c;//a 노드
		x.b = Edges[c][i].first;//a 노드와 연결된 노드
		x.w = Edges[c][i].second;//a 노드와 연결된 노드간 가중치
		Q.insert(x);//PQ에 삽입
	}
	while (!Q.isEmpty()) {
		y = Q.Delete();//Q를 꺼낼 때마다 y에 대입
		if (marking[y.a] == 1 && marking[y.b] == 1) {
			//가장 짧은 간선을 가진 노드가 y
			//가장 짧은 간선을 가진 두 노드 모두 마킹 체크
			//둘 다 1이면 사이클을 형성하니 버린다.
			//사실 marking[y.a]은 항상 1
			continue;
		}
		else {
			printf("Edge form Node %d to Node %d of Weight %d Selected.\n", y.a, y.b, y.w);
			c = y.b;
			//c는 현재 a 노드와 연결된 간선들의 크기가 가장 작은 상대 노드
			marking[c] = 1;
			//연결된 상대 노드에 마킹
			for (int i = 0; i < Edges[c].size(); i++) {//상대 노드의 간선 개수만큼 반복
				x.a = c;//상대 노드를 해당 노드로 대입
				x.b = Edges[c][i].first;//상대 노드와 연결된 노드 대입
				x.w = Edges[c][i].second;//상대 노드와 연결된 노드 간의 가중치 대입
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