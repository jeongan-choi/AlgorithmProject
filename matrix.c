#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
//1 - ���� ����� �̿��� DFS, BFS

#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 10
#define MAX_VERTICES 50

typedef int element;
typedef struct { // ť Ÿ��
	element  queue[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

// ���� �Լ�
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// ���� ���� ���� �Լ�
void queue_init(QueueType* q)
{
	q->front = q->rear = 0;
}

// ���� ���� ���� �Լ�
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

// ��ȭ ���� ���� �Լ�
int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// ���� �Լ�
void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

// ���� �Լ�
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}


typedef struct GraphType {
	int n;	// ������ ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;
int dfs_visited[MAX_VERTICES];		//���̿켱Ž�� �湮���α��
int bfs_visited[MAX_VERTICES];		//�ʺ�켱Ž�� �湮���α��

// �׷��� �ʱ�ȭ 
void graph_init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}
// ���� ���� ����
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}
// ���� ���� ����
void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}
void dfs_mat(GraphType* g, int v)		//���̿켱Ž��
{
	int w;
	dfs_visited[v] = TRUE;		// ���� v�� �湮 ǥ�� 
	printf("���� %d -> ", v);		// �湮�� ���� ���
	for (w = 0; w < g->n; w++) 		// ���� ���� Ž��
		if (g->adj_mat[v][w] && !dfs_visited[w])		//���� v��w�� �����ϰ� ���� w�� ���� �湮���� �ʾ�����
			dfs_mat(g, w);	//���� w���� DFS ���� ����
}

void bfs_mat(GraphType* g, int v)			//�ʺ�켱Ž��
{
	int w;
	QueueType q;

	queue_init(&q);     // ť �ʱ�ȭ 
	bfs_visited[v] = TRUE;          // ���� v �湮 ǥ�� 
	printf("���� %d -> ", v);
	enqueue(&q, v);			// ���� ������ ť�� ���� 
	while (!is_empty(&q)) {
		v = dequeue(&q);		// ť�� ���� ���� 
		for (w = 0; w < g->n; w++)	// ���� ���� Ž�� 
			if (g->adj_mat[v][w] && !bfs_visited[w]) {
				bfs_visited[w] = TRUE;    // �湮 ǥ��
				printf("���� %d -> ", w);
				enqueue(&q, w); 	// �湮�� ������ ť�� ����
			}
	}
}


int main(void)
{
	int v;		//������ ��
	int e;		//������ ��
	int find_node;	//Ž�� ���� ��� ��ȣ
	int n1, n2;		//������ ��� ��ȣ


	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);				//�׷��� �ʱ�ȭ

	printf("������ �� �Է� :");
	scanf("%d", &v);
	printf("������ �� �Է� :");
	scanf("%d", &e);
	printf("Ž�� ���� ��� ��ȣ: ");
	scanf("%d", &find_node);
	for (int i = 0; i < v; i++)		//�Է��� ������ ����ŭ ���� ���� ����
		insert_vertex(g, i);
	for (int i = 0; i < e; i++)		//�Է��� ������ ����ŭ
	{
		printf("������ ��� ��ȣ �Է� :");
		scanf("%d %d", &n1, &n2);
		insert_edge(g, n1, n2);			//���� ���� ����

	}
	printf("���� �켱 Ž��\n");
	dfs_mat(g, find_node);
	printf("\n");

	printf("�ʺ� �켱 Ž��\n");
	bfs_mat(g, find_node);
	printf("\n");

	free(g);
	return 0;
}

//2
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50
int cnt = 0;
typedef struct GraphType {
	int n;	// ������ ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;
int visited[MAX_VERTICES];

// �׷��� �ʱ�ȭ 
void graph_init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}
// ���� ���� ����
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}
// ���� ���� ����
void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

void dfs_mat(GraphType* g, int v)			//���� �켱 Ž��
{
	int w;
	visited[v] = TRUE;		// ���� v�� �湮 ǥ�� 
	for (w = 0; w < g->n; w++) 		// ���� ���� Ž��
		if (g->adj_mat[v][w] && !visited[w]) {
			dfs_mat(g, w);	//���� w���� DFS ���� ����
		}
}

int main(void)
{
	int v;		//������ ��
	int e;		//������ ��
	int n1, n2;		//������ ��� ��ȣ
	int cnt = 0;


	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	printf("������ �� �Է� :");
	scanf("%d", &v);
	printf("������ �� �Է� :");
	scanf("%d", &e);
	for (int i = 0; i < v; i++)
		insert_vertex(g, i);
	for (int i = 0; i < e; i++)
	{
		printf("������ ��� ��ȣ �Է� :");
		scanf("%d %d", &n1, &n2);
		insert_edge(g, n1, n2);

	}
	for (int i = 0; i < v; i++)
		for (int j = 0; j < v; j++)
			if (g->adj_mat[i][j] && !visited[j]) {			//���� �湮���� �ʾҰ� 
				dfs_mat(g, j);	//���� w���� DFS ���� ����
				cnt++;
			}
	for (int i = 0; i < v; i++)
		if (!visited[i])
			cnt++;
	printf("���� �׷����� �� : %d", cnt);

	free(g);
	return 0;
}