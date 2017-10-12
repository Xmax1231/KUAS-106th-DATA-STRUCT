#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define max_x 9
#define max_y 9
#define start_x 1
#define start_y 1
#define end_x max_x-2
#define end_y max_y-2
typedef struct Character{
	int x,y;
}Character;

typedef struct Offset{
	int dx,dy;
}Offset;

typedef struct node{
	int x,y,dir;
}node;

typedef struct _stack{
	node *stack;
	int esp;
}_stack;

void push(_stack *s, node n){
	*(s->stack+s->esp) = n;
	s->esp++;
}

node top(_stack *s){
	return *(s->stack+s->esp);
}

node pop(_stack *s){
	s->esp--;
	return top(s);
}

int maze[max_y][max_x] = {	{1,1,1,1,1,1,1,1,1},
				{1,0,1,1,0,1,1,1,1},
				{1,1,1,1,1,1,0,1,1},
				{1,1,0,1,1,0,1,0,1},
				{1,1,1,0,1,0,1,1,1},
				{1,1,0,1,0,0,1,0,1},
				{1,1,0,1,1,1,1,1,1},
				{1,1,1,0,0,0,0,0,1},
				{1,1,1,1,1,1,1,1,1}};
							
void makemaze(){
	int a, dx, dy;
	unsigned seed;
	seed = (unsigned)time(NULL); // 取得時間序列 
	srand(seed); // 以時間序列當亂數種子 
	for(dy=1; dy<max_y-1; dy++){
		for(dx=1; dx<max_x-1; dx++){
			if((dx==start_x && dy==start_y) || (dx==end_x && dy==end_y)){
				maze[dy][dx] = 0;
				continue;
			}
			a=(rand()%100)+1;
			a%=2;
			maze[dy][dx] = a;
		}
	}	
}
void init(Character *c, _stack *s, Offset *o, node *n){
	c->x = start_x;		// 將人物座標放在起始位址 
	c->y = start_y;
	
	s->stack = (node*)malloc(10*sizeof(node));	// 申請10個節點大小的記憶體給堆疊用 
	s->esp = 0;									// 將堆疊起使位址指向 0 
	
	o[0].dx = +0;	o[0].dy = -1;				// 此處定義座標偏移 
	o[1].dx = +1;	o[1].dy = -1;				// 總共八個方位 
	o[2].dx = +1;	o[2].dy = +0;				// 上、右上、右、右下、下、左下、左、左上 
	o[3].dx = +1;	o[3].dy = +1;				// 
	o[4].dx = +0;	o[4].dy = +1;				// 
	o[5].dx = -1;	o[5].dy = +1;				// 
	o[6].dx = -1;	o[6].dy = +0;				// 
	o[7].dx = -1;	o[7].dy = -1;				// 
	
	n->dir = n->x = n->y = 0;					// 將下個節點資料預設為空 
	makemaze();	//隨機產生迷宮Function（註解掉就固定迷宮） 
}

int main(int argc, char *argv[]) {
	int s_dx, s_dy;
	_stack s;         	// 節點堆疊宣告 
	node now;			// 目前節點座標資料 
	node next;			// 下個節點座標資料 
	Character man;		// 人物 
	Offset offset[8];	// 座標偏移 
	
	init(&man, &s, offset, &now);	// 初始化 
	
	printf("人物座標：(%d,%d)\n", man.x, man.y);	// Show人物初始座標 
	now.x = man.x;		// 把人物初始座標放入目前節點 
	now.y = man.y;		// 雖然沒放好像也沒差 
	//printf("人物移動座標：(%d,%d)\n", now.x+offset[now.dir].dx, now.y+offset[now.dir].dy);
	for(;;){			// 無限迴圈跑迷宮 
		while(maze[now.y+offset[now.dir].dy][now.x+offset[now.dir].dx]!=0 && now.dir < 8){	//找到目前節點附近哪裡有路 
			now.dir++;
		}
		if(now.dir == 8){			// 如果都沒找到路就返回 
			maze[now.y][now.x] = 9;	// 把死路定義為9表示走過且死路 
			if((now.y == start_y) && (now.x == start_x)){	// 如果一開始就死路就直接break 
				printf("%s\n\n", "# error.");
				break;
			}
			next = pop(&s);			// 從堆疊裡拿出上一個節點 
			printf("%s (%d,%d) %s(%d,%d)\n", "X 哇嗚", now.x, now.y, "沒路! 退回", next.x, next.y);
			now.x = next.x;
			now.y = next.y;
			now.dir = next.dir;
		}else{
			maze[now.y][now.x] = 8;	// 如果有找道路就把此節點定義為8表示走過且為死路 
			printf("%s (%d,%d) %s\n", "O 哇嗚", now.x+offset[now.dir].dx, now.y+offset[now.dir].dy, "有路!");
			push(&s ,now);			// 把此節點放入堆疊以之後找路用 
			now.x += offset[now.dir].dx;
			now.y += offset[now.dir].dy;
			now.dir = 0;
		}
		if((now.y == end_y) && (now.x == end_x)){	// 當目前座標為終點座標時 
			maze[now.y][now.x] = 8;					// 代表已經跑完迷宮了 
			printf("%s (%d,%d)\n\n", "# done.", now.x, now.y);
			break;
		}else if((now.y == start_y) && (now.x == start_x)){ // 當目前座標為起點座標時  
			maze[now.y][now.x] = 9;							// 代表找不到終點，嗚嗚 
			printf("%s\n\n", "# error.");
			break;			
		}
	}
	
	// 這邊是把地圖資料Show出來的巢狀迴圈 
	for(s_dy = 0; s_dy < max_y; s_dy++){
		for(s_dx = 0; s_dx < max_y; s_dx++){
			switch(maze[s_dy][s_dx]){
				case 0:					// 0表示未走過的路 
					printf("%s", "* ");
					break;
				case 1:					// 1表示牆壁不得行走 
					printf("%s", "| ");
					break;
				case 8:					// 8表示已走過且正確的路 
					printf("%s", "O ");
					break;
				case 9:					// 9表示已走過但錯誤的路 
					printf("%s", "X ");
					break;
				default:
					break;
			}
		}
		printf("\n");
	}
	
	int stop;
	while(scanf("%d", &stop)){}
	return 0;
}
