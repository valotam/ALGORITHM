#include<stdio.h>

#ifndef DISASTERMANAGEMENT_CONST
#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "output.txt"
#define MAX_M 100
#define MAX_N 100
#define FIRE_MAX MAX_M * MAX_N
#define FALSE 0
#define TRUE (!FALSE)
#endif // DISASTERMANAGEMENT_CONST

typedef int BOOL;

int M, N, X;
int Building[MAX_M][MAX_N], Path[MAX_M][MAX_N];
int path[MAX_M][MAX_N];
char dir[5] = {' ', 'U', 'L', 'R', 'D' };
int res_n, res_y, res_x;
char res[FIRE_MAX];

BOOL found;
int stx, sty;
int MyQueue[FIRE_MAX][2];
int rear, front;

void Input_data(){
	char ch;
	FILE *inf;
	inf = fopen(INPUT_FILE, "r");
	fscanf(inf, "%d %d %d\n", &M, &N, &X);

	for(size_t i = 0; i < M; i++){
		for(size_t j = 0; j < N; j++){
			fscanf(inf, "%c", &ch);

			if(ch == 'F')
				Building[i][j] = FIRE_MAX;

			if(ch == 'Y'){
				sty = i;
				stx = j;
			}

			if (ch == 'E') Building[i][j] = -1;
		}

		fscanf(inf, "\n");
	}

	fclose(inf);
}

void InsertData(int y, int x, int dir, int count){
	MyQueue[rear][0] = y;
	MyQueue[rear][1] = x;

	if(Building[y][x] == -1){
		found = true;
		res_y = y;
		res_x = x;
	}

	Building[y][x] = count;

	path[y][x] = dir;
	rear++;
}

void RemoveData(int *y, int *x){
	*y = MyQueue[front][0];
	*x = MyQueue[front][1];
	front++;
}

void Fire(){
	for(size_t i = 0; i < M; i++)
		for(size_t j = 0; j < N; j++)
			if(Building[i][j] == FIRE_MAX){
				if(i > 0)		Path[i - 1][j] = FIRE_MAX;
				if(j > 0)		Path[i][j - 1] = FIRE_MAX;
				if(i < M - 1)	Path[i + 1][j] = FIRE_MAX;
				if(j < N - 1)	Path[i][j + 1] = FIRE_MAX;
			}

	for(size_t i = 0; i < M; i++)
		for(size_t j = 0; j < N; j++)
			if(Path[i][j] == FIRE_MAX)	Building[i][j] = FIRE_MAX;
}

void SearchPath(){
	int y, x;
	int bound;
	int count = 0;
	InsertData(sty, stx, 0, count + 1);
	bound = rear + 1;
	while(rear >= front){
		RemoveData(&y, &x);
		if(front >= bound){
			count++;
			if((count > X)&&((count - 1) % X == 0))
				Fire();

			bound = rear + 1;
		}

		if(Building[y][x] == FIRE_MAX)
			continue;

		if((y > 0) && (Building[y - 1][x] <= 0))
			InsertData(y - 1, x, 4, count + 2);

		if((y < M -1) && (Building[y + 1][x] <= 0))
			InsertData(y + 1, x, 1, count + 2);

		if((x > 0) && (Building[y][x - 1] <= 0))
			InsertData(y, x - 1, 3, count + 2);

		if((x < N - 1) && (Building[y][x + 1] <= 0))
			InsertData(y, x + 1, 2, count + 2);

		if(found){
			res_n = count + 1;
			break;
		}
	}
}

void next(int *y, int *x){
	int temp = path[*y][*x];
	switch(temp){
		case 1 :
			(*y)--;
			break;
		case 2 :
			(*x)--;
			break;
		case 3 :
			(*x)++;
			break;
		case 4 :
			(*y)++;
	}
}

void Output_result(){
	int i;
	FILE *outf;
	outf = fopen(OUTPUT_FILE, "w");

	if(!found)
		fprintf(outf, "Impossible\n");
	else{
		fprintf(outf, "%d\n", res_n);
		res[res_n]  = '\0';

		for(i = res_n - 1; i >= 0; i--){
			res[i] = dir[5 - path[res_y][res_x]];
			next(&res_y, &res_x);
		}

		fprintf(outf, "%s\n", res);
	}

	fclose(outf);
}


int main(){
	Input_data();
	SearchPath();
	Output_result();
}
