#include<iostream>
#include<cstdio>
#include<vector>
using namespace std;

class TRI {
public:
	int a, b, w;
	//a���� b�� �־���
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
		if (i * 2 > n) {//���� �ڽ��� ���� ��� : �ڽ��� ���� ���
			break;
		}
		else if (i * 2 + 1 > n) {//���� �ڽĸ� �ִ� ���
			if (Arr[i * 2].w < Arr[i].w) {//���� �ڽ��� ������ �۴�
				swap(Arr[i * 2], Arr[i]);
				i = i * 2;
			}
			else {//���� ���� �ڽĺ��� �۴�
				break;
			}
		}
		else {//�ڽ��� �Ѵ� �ִ� ���
			if ((Arr[i].w > Arr[i * 2].w) && (Arr[i].w > Arr[i * 2 + 1].w)) {//���� �� �ڽĺ��� ũ��.
				if (Arr[i * 2].w < Arr[i * 2 + 1].w) {//������ ������ �ڽĺ��� �� ���� ���
					j = i * 2;
				}
				else {//�������� ���� �ڽĺ��� �� ���� ���
					j = i * 2 + 1;
				}
				swap(Arr[i], Arr[j]);
				i = j;
			}
			else if ((Arr[i].w > Arr[i * 2].w) && (Arr[i].w <= Arr[i * 2 + 1].w)) {//���� ������ �ڽĺ��� �۴�
				j = i * 2;
				swap(Arr[i], Arr[j]);
				i = j;
			}
			else if ((Arr[i].w <= Arr[i * 2].w) && (Arr[i].w > Arr[i * 2 + 1].w)) {//���� ���� �ڽĺ��� �۴�
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
vector<pair<int, int>> Edges[1000];//���� ����ġ�� ������ ���Ϳ� ����
//�������� �׷��� �Է� �ޱ�

int marking[1000];//shortest Path ����
//int previous[1000];//previous Node(���� ���� ���)
vector<int> previous[1000];//��� ��θ� �� ��� (���� ������ ��� ����)

int main() {
	int c, a, b, w;
	TRI x, y;
	scanf("%d %d", &n, &m);
	//����� ������ n, ������ ������ m

	for (int i = 0; i < m; i++) {//������ ������ŭ �ݺ�
		scanf("%d %d %d", &a, &b, &w);
		Edges[a].push_back(make_pair(b, w));//a ��忡 ����� b ���� w�� ������ �ֱ�
		//��� ��帶�� pair�� ���͸� ���� (���, ����ġ)
		Edges[b].push_back(make_pair(a, w));//b ��忡 ����� a ���� w�� ������ �ֱ�
	}
	for (int i = 1; i <= n; i++) {
		marking[i] = 100000;
		//�ʱⰪ�� ���� ���Ѵ�
	}
	c = 1;
	marking[c] = 0;

	for (int i = 0; i < Edges[c].size(); i++) {//a���� ����� ������ ������ŭ �ݺ�
		x.a = c;//a ���
		x.b = Edges[c][i].first;//a ���� ����� ���
		x.w = marking[c] + Edges[c][i].second;//a ���� ����� ��尣 ����ġ ������Ʈ
		Q.insert(x);//PQ�� ����
	}
	while (!Q.isEmpty()) {
		y = Q.Delete();//Q�� ���� ������ y�� ����
		if (marking[y.b] < 100000) {//������ ������Ʈ �Ǿ��ٸ�
			//���� ���� ª�� ������ ���� ��尡 y
			//�װͰ� ����� ��尡 y.b
			//100000���� �۴ٴ� �ǹ̴� �̹� ���� ã������ ã�� �ʿ䰡 ���ٴ� ��
			//������ ���� ���� ���� ���� ���� �װ��� ���ͽ�Ʈ�� ����

			if (marking[y.b]==y.w) {//���� ����� ����
				printf("Edge from Node %d to Node %d of Total Path Length %d Added. Previous node %d.\n", y.a, y.b, y.w, y.a);
				previous[y.b].push_back(y.a);
			}
			else {
				printf("Ignored Edge from Node %d to Node %d of Total Path Length %d.\n", y.a, y.b, y.w);
				//�������� ���� üũ
			}
		}
		else {//������Ʈ �Ǿ����� �ʾ� ������ 100000 ���� ���´ٸ�
			printf("Edge from Node %d to Node %d of Total Path Length %d Selected. Previous node %d.\n", y.a, y.b, y.w, y.a);
			c = y.b;
			//c�� ���� a ���� ����� �������� ũ�Ⱑ ���� ���� ��� ���
			marking[c] = y.w;
			//����� ��� ��忡 ��ŷ
			//previous[c] = y.a;
			previous[c].push_back(y.a);
			//a ���� ����� ��� ����� ���� ��带 ���� ����

			for (int i = 0; i < Edges[c].size(); i++) {//��� ����� ���� ������ŭ �ݺ�
				x.a = c;//��� ��带 �ش� ���� ����
				x.b = Edges[c][i].first;//��� ���� ����� ��� ����
				x.w = marking[c] + Edges[c][i].second;//��� ���� ����� ��� ���� ����ġ ������Ʈ
				Q.insert(x);//��� ��� ���� PQ�� ����
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

������ �׷����� PQ�� �� �� ��� ������� ���ϰ� ������.
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

����� ���̰� ���� ��� : ���� ���� �� ���� ���
*/