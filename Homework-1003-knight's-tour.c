#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#define start_x 1 - 1
#define start_y 1 - 1
#define max_x 8 
#define max_y 8 
#define ts(Name, content) typedef struct Name{content}Name
ts(Node,
	int x;
	int y;
	int dir;);

ts(Stack,
	Node *base;
	int esp;);

ts(Offset,
	int dx;
	int dy;);	

void init(Node *n, Stack *s, Offset *o);
void push(Stack *s, Node n);
Node pop(Stack *s);
void show();

int map[max_y][max_x] = {{0}};

int main(int argc, char *argv[]) {
	Stack stack;
	Node nd;
	Offset offset[8];
	char stop;
	int _index=1;
	
	init(&nd, &stack, offset);
	for(;;){
		while((map[nd.y+offset[nd.dir].dy][nd.x+offset[nd.dir].dx]!=0  || (nd.y+offset[nd.dir].dy) < 0 || (nd.y+offset[nd.dir].dy) >= max_y || (nd.x+offset[nd.dir].dx) < 0 || (nd.x+offset[nd.dir].dx) >= max_x ) && nd.dir < 8){
			nd.dir++;
		}
		if(nd.dir < 8)	{
			push(&stack, nd);
			nd.x += offset[nd.dir].dx;
			nd.y += offset[nd.dir].dy;
			nd.dir = 0;
			//printf("找到第%d個節點為 (%d,%d) !\n", _index, nd.x, nd.y);
			map[nd.y][nd.x] = ++_index;
		}else{
			nd.dir = 0;
			map[nd.y][nd.x] = 0;
			_index--;
			nd = pop(&stack);
			//printf("返回上一個節點 (%d,%d) !\n", nd.x, nd.y);
			nd.dir++;
		}
		//show();
		//while(stop=getchar() != 'n'){}
		//system("cls");
		if(_index == max_x*max_y){
			map[nd.y][nd.x] = _index;
			printf("# done. 共找到%d個節點!!\n\n", _index);
			break;
		}
		if(nd.y==start_y && nd.x == start_x){
			printf("# failed. \n\n", _index);
			break;
		}
	}
		
	show();
	//while(stop=getchar() != 'n'){}
	return 0;
}

void init(Node *n, Stack *s, Offset *o){
	n->x = start_x;
	n->y = start_y;
	n-> dir = 0;
	
	s->base = (Node*)malloc(max_x*max_y*sizeof(Node));	// 申請10個節點大小的記憶體給堆疊用 
	s->esp = 0;									// 將堆疊起使位址指向 0 
	
	o[0].dx = +1;	o[0].dy = -2;
	o[1].dx = +2;	o[1].dy = -1;
	o[2].dx = +2;	o[2].dy = +1;
	o[3].dx = +1;	o[3].dy = +2;
	o[4].dx = -1;	o[4].dy = +2;
	o[5].dx = -2;	o[5].dy = +1;
	o[6].dx = -2;	o[6].dy = -1;
	o[7].dx = -1;	o[7].dy = -2;
	
	map[n->y][n->x] = 1;
}

void push(Stack *s, Node n){
	*(s->base+s->esp) = n;
	s->esp++;
}

Node pop(Stack *s){
	return *(s->base+--s->esp);
}

void show(){
	int dx,dy;
	for(dy=0;dy<max_y;dy++){
		for(dx=0;dx<max_x;dx++){
			if(map[dy][dx] < 10)
				printf(" %d ", map[dy][dx]);
			else
				printf("%d ", map[dy][dx]);
		}
		printf("\n");
	}
	printf("\n");
}
