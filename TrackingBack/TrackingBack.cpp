#include <stdio.h>
#include <stdlib.h>
#ifndef TRACKING_BACK_CONST
#define MAX_N 100
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
#define TRUE 1
#define FALSE (!TRUE)
#endif // TRACKING_BACK_CONST

typedef struct _pList{
	int x1;
	int y1;
	int x2;
	int y2;
	struct _pList* next;
} pList;

int n;
int Board[MAX_N][MAX_N + 1];
int CounterBoard[MAX_N + 1][MAX_N + 1];
int visited[MAX_N + 1][MAX_N + 1];
pList* PositionList[MAX_N + 1][MAX_N + 1];
pList* header[MAX_N + 1][MAX_N + 1];
int dir[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
int Result[MAX_N][MAX_N + 1];
int res_n;
int found = FALSE;
int RC = 0;

void Input_data();
void AddPositionList(int, int, int, int, int, int);
int out(int, int);
void decrease(int, int);
void increase(int, int);
void Output_result(void);
void find_solution(void);
void Solve(void);

void Input_data(){
	FILE *inf;
	inf = fopen(INPUT_FILE, "r");
	fscanf(inf, "%d\n", &n);

	for(size_t i = 0; i < n; i++)
		for(size_t j = 0; j < n + 1; j++)
			fscanf(inf, "%d", &Board[i][j]);

	fclose(inf);
}

void AddPositionList(int p, int q, int y1, int x1, int y2, int x2){
	int temp;
	if (p > q){
		temp = p;
		p = q;
		q = temp;
	}

	CounterBoard[p][q]++;
	PositionList[p][q]->next = (pList*) malloc(sizeof(pList));
	PositionList[p][q] = PositionList[p][q]->next;

	PositionList[p][q]->y1 = y1;
	PositionList[p][q]->x1 = x1;
	PositionList[p][q]->y2 = y2;
	PositionList[p][q]->x2 = x2;
	PositionList[p][q]->next = NULL;
}

void preprocess(void){
	for(size_t i = 1; i <= n; i++){
		for(size_t j = i; j <= n; j++){
			PositionList[i][j] = (pList*) malloc(sizeof(pList));
			PositionList[i][j]->next = NULL;
			header[i][j] = PositionList[i][j];
		}
	}

	for(size_t i = 0; i < n; i++){
		int p = Board[i][0];

		for(size_t j = 1; j < n + 1; j++){
			int q = Board[i][j];
			AddPositionList(p, q, i, j - 1, i, j);
		}
	}

	for(size_t i = 0; i < n + 1; i++){
		int p = Board[0][i];

		for(size_t j = 1; j < n; j++){
			int q = Board[j][i];
			AddPositionList(p, q, j - 1, i, j, i);
		}
	}
}

int out(int y, int x){
	if((y < 0) || (x < 0) || (y >= n) || (x > n))
		return TRUE;

	else
		return FALSE;
}

void increase(int n1, int n2){
	if(n1 < n2)
		CounterBoard[n1][n2]++;

	else
		CounterBoard[n2][n1]++;
}

void decrease(int n1, int n2){
	if(n1 < n2)
		CounterBoard[n1][n2]--;

	else
		CounterBoard[n2][n1]--;
}

void Output_result(void){
	FILE *outf;
	outf = fopen(OUTPUT_FILE, "w");

	if(!found)
		fprintf(outf, "Impossible\n");
	else
		for(size_t i = 0; i < n; i++){
			for(size_t j = 0; j < n + 1; j++)
				fprintf(outf, "%d ", Result[i][j]);

			fprintf(outf, "\n");
		}
}

void find_solution(void){
	int i, j;
	int p, q, min;
	pList* PositionList;
	int y1, x1, y2, x2;
	int yy, xx;
	RC++;

	p = q = -1;

	if(RC == MAX_N * (MAX_N + 1) / 2){
		found = TRUE;
		Output_result();
		exit(0);
	}

	min = MAX_N * MAX_N * 2 + 1;

	for(size_t i = 1; i <= n; i++){
		for(size_t j = i; j <= n; j++){
			if((!visited[i][j]) && (CounterBoard[i][j] < min)){
				min = CounterBoard[i][j];
				p = i;
				q = j;
			}
		}

		if(min == 0)
			return;

		if(p < 0 || p < 0){
			found = TRUE;
			Output_result();
			exit(0);
		}

		PositionList = header[p][q];
		visited[p][q] = TRUE;

		while(PositionList->next != NULL){
			PositionList = PositionList->next;
			y1 = PositionList->y1;
			x1 = PositionList->x1;
			y2 = PositionList->y2;
			x2 = PositionList->x2;

			if(Result[y1][x1] ||Result[y2][x2])
				continue;

			for(size_t i = 0; i < 4; i++){
				yy = y1 + dir[i][0];
				xx = x1 + dir[i][1];

				if(out(yy, xx) || (yy == y2) && (xx == x2))
					continue;

				if(!(Result[yy][xx]))
					decrease(Board[y1][x1], Board[yy][xx]);
			}

			for(size_t i = 0; i < 4; i++){
				yy = y2 + dir[i][0];
				xx = x2 + dir[i][1];

				if(out(yy, xx) || (yy == y1) && (xx == x1))
					continue;

				if(!(Result[yy][xx]))
					decrease(Board[y2][x2], Board[yy][xx]);
			}

			res_n++;
			Result[y1][x1] = res_n;
			Result[y2][x2] = res_n;

			find_solution();

			res_n--;
			Result[y1][x1] = 0;
			Result[y2][x2] = 0;

			for(size_t i = 0; i < 4; i++){
				yy = y1 + dir[i][0];
				xx = x1 + dir[i][1];

				if(out(yy, xx) || (yy == y2) && (xx == x2))
					continue;

				if(!(Result[yy][xx]))
					increase(Board[y1][x1], Board[yy][xx]);
			}

			for(size_t i = 0; i < 4; i++){
				yy = y2 + dir[i][0];
				xx = x2 + dir[i][1];

				if(out(yy, xx) || (yy == y1) && (xx == x1))
					continue;

				if(!(Result[yy][xx]))
					increase(Board[y2][x2], Board[yy][xx]);
			}

			visited[p][q] = FALSE;
		}
	}
}

void Solve(void){
	preprocess();
	find_solution();
	Output_result();
}

int main(int argc, char const *argv[]) {
	Input_data();
	Solve();
	return 0;
}

//int PlaceCompulsoryBlock(){
//	return 0;
//}
