#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
//1 - 인접 행렬을 이용한 DFS, BFS

#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 10
#define MAX_VERTICES 50

typedef int element;
typedef struct { // 큐 타입
	element  queue[MAX_QUEUE_SIZE];
	int  front, rear;
} QueueType;

// 오류 함수
void error(char* message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

// 공백 상태 검출 함수
void queue_init(QueueType* q)
{
	q->front = q->rear = 0;
}

// 공백 상태 검출 함수
int is_empty(QueueType* q)
{
	return (q->front == q->rear);
}

// 포화 상태 검출 함수
int is_full(QueueType* q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// 삽입 함수
void enqueue(QueueType* q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}

// 삭제 함수
element dequeue(QueueType* q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}


typedef struct GraphType {
	int n;	// 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;
int dfs_visited[MAX_VERTICES];		//깊이우선탐색 방문여부기록
int bfs_visited[MAX_VERTICES];		//너비우선탐색 방문여부기록

// 그래프 초기화 
void graph_init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}
// 정점 삽입 연산
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}
// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}
void dfs_mat(GraphType* g, int v)		//깊이우선탐색
{
	int w;
	dfs_visited[v] = TRUE;		// 정점 v의 방문 표시 
	printf("정점 %d -> ", v);		// 방문한 정점 출력
	for (w = 0; w < g->n; w++) 		// 인접 정점 탐색
		if (g->adj_mat[v][w] && !dfs_visited[w])		//정점 v와w가 인접하고 정점 w가 아직 방문되지 않았으면
			dfs_mat(g, w);	//정점 w에서 DFS 새로 시작
}

void bfs_mat(GraphType* g, int v)			//너비우선탐색
{
	int w;
	QueueType q;

	queue_init(&q);     // 큐 초기화 
	bfs_visited[v] = TRUE;          // 정점 v 방문 표시 
	printf("정점 %d -> ", v);
	enqueue(&q, v);			// 시작 정점을 큐에 저장 
	while (!is_empty(&q)) {
		v = dequeue(&q);		// 큐에 정점 추출 
		for (w = 0; w < g->n; w++)	// 인접 정점 탐색 
			if (g->adj_mat[v][w] && !bfs_visited[w]) {
				bfs_visited[w] = TRUE;    // 방문 표시
				printf("정점 %d -> ", w);
				enqueue(&q, w); 	// 방문한 정점을 큐에 저장
			}
	}
}


int main(void)
{
	int v;		//정점의 수
	int e;		//간선의 수
	int find_node;	//탐색 시작 노드 번호
	int n1, n2;		//연결할 노드 번호


	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);				//그래프 초기화

	printf("정점의 수 입력 :");
	scanf("%d", &v);
	printf("간선의 수 입력 :");
	scanf("%d", &e);
	printf("탐색 시작 노드 번호: ");
	scanf("%d", &find_node);
	for (int i = 0; i < v; i++)		//입력한 정점의 수만큼 정점 삽입 연산
		insert_vertex(g, i);
	for (int i = 0; i < e; i++)		//입력한 간선의 수만큼
	{
		printf("연결할 노드 번호 입력 :");
		scanf("%d %d", &n1, &n2);
		insert_edge(g, n1, n2);			//간선 삽입 연산

	}
	printf("깊이 우선 탐색\n");
	dfs_mat(g, find_node);
	printf("\n");

	printf("너비 우선 탐색\n");
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
	int n;	// 정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;
int visited[MAX_VERTICES];

// 그래프 초기화 
void graph_init(GraphType* g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;
}
// 정점 삽입 연산
void insert_vertex(GraphType* g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES) {
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;
}
// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end)
{
	if (start >= g->n || end >= g->n) {
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}

void dfs_mat(GraphType* g, int v)			//깊이 우선 탐색
{
	int w;
	visited[v] = TRUE;		// 정점 v의 방문 표시 
	for (w = 0; w < g->n; w++) 		// 인접 정점 탐색
		if (g->adj_mat[v][w] && !visited[w]) {
			dfs_mat(g, w);	//정점 w에서 DFS 새로 시작
		}
}

int main(void)
{
	int v;		//정점의 수
	int e;		//간선의 수
	int n1, n2;		//연결할 노드 번호
	int cnt = 0;


	GraphType* g;
	g = (GraphType*)malloc(sizeof(GraphType));
	graph_init(g);

	printf("정점의 수 입력 :");
	scanf("%d", &v);
	printf("간선의 수 입력 :");
	scanf("%d", &e);
	for (int i = 0; i < v; i++)
		insert_vertex(g, i);
	for (int i = 0; i < e; i++)
	{
		printf("연결할 노드 번호 입력 :");
		scanf("%d %d", &n1, &n2);
		insert_edge(g, n1, n2);

	}
	for (int i = 0; i < v; i++)
		for (int j = 0; j < v; j++)
			if (g->adj_mat[i][j] && !visited[j]) {			//정점 방문하지 않았고 
				dfs_mat(g, j);	//정점 w에서 DFS 새로 시작
				cnt++;
			}
	for (int i = 0; i < v; i++)
		if (!visited[i])
			cnt++;
	printf("연결 그래프의 수 : %d", cnt);

	free(g);
	return 0;
}