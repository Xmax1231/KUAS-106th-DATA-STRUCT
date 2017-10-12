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
	seed = (unsigned)time(NULL); // ���o�ɶ��ǦC 
	srand(seed); // �H�ɶ��ǦC��üƺؤl 
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
	c->x = start_x;		// �N�H���y�Щ�b�_�l��} 
	c->y = start_y;
	
	s->stack = (node*)malloc(10*sizeof(node));	// �ӽ�10�Ӹ`�I�j�p���O���鵹���|�� 
	s->esp = 0;									// �N���|�_�Ϧ�}���V 0 
	
	o[0].dx = +0;	o[0].dy = -1;				// ���B�w�q�y�а��� 
	o[1].dx = +1;	o[1].dy = -1;				// �`�@�K�Ӥ�� 
	o[2].dx = +1;	o[2].dy = +0;				// �W�B�k�W�B�k�B�k�U�B�U�B���U�B���B���W 
	o[3].dx = +1;	o[3].dy = +1;				// 
	o[4].dx = +0;	o[4].dy = +1;				// 
	o[5].dx = -1;	o[5].dy = +1;				// 
	o[6].dx = -1;	o[6].dy = +0;				// 
	o[7].dx = -1;	o[7].dy = -1;				// 
	
	n->dir = n->x = n->y = 0;					// �N�U�Ӹ`�I��ƹw�]���� 
	makemaze();	//�H�����Ͱg�cFunction�]���ѱ��N�T�w�g�c�^ 
}

int main(int argc, char *argv[]) {
	int s_dx, s_dy;
	_stack s;         	// �`�I���|�ŧi 
	node now;			// �ثe�`�I�y�и�� 
	node next;			// �U�Ӹ`�I�y�и�� 
	Character man;		// �H�� 
	Offset offset[8];	// �y�а��� 
	
	init(&man, &s, offset, &now);	// ��l�� 
	
	printf("�H���y�СG(%d,%d)\n", man.x, man.y);	// Show�H����l�y�� 
	now.x = man.x;		// ��H����l�y�Щ�J�ثe�`�I 
	now.y = man.y;		// ���M�S��n���]�S�t 
	//printf("�H�����ʮy�СG(%d,%d)\n", now.x+offset[now.dir].dx, now.y+offset[now.dir].dy);
	for(;;){			// �L���j��]�g�c 
		while(maze[now.y+offset[now.dir].dy][now.x+offset[now.dir].dx]!=0 && now.dir < 8){	//���ثe�`�I������̦��� 
			now.dir++;
		}
		if(now.dir == 8){			// �p�G���S�����N��^ 
			maze[now.y][now.x] = 9;	// �⦺���w�q��9��ܨ��L�B���� 
			if((now.y == start_y) && (now.x == start_x)){	// �p�G�@�}�l�N�����N����break 
				printf("%s\n\n", "# error.");
				break;
			}
			next = pop(&s);			// �q���|�̮��X�W�@�Ӹ`�I 
			printf("%s (%d,%d) %s(%d,%d)\n", "X �z��", now.x, now.y, "�S��! �h�^", next.x, next.y);
			now.x = next.x;
			now.y = next.y;
			now.dir = next.dir;
		}else{
			maze[now.y][now.x] = 8;	// �p�G����D���N�⦹�`�I�w�q��8��ܨ��L�B������ 
			printf("%s (%d,%d) %s\n", "O �z��", now.x+offset[now.dir].dx, now.y+offset[now.dir].dy, "����!");
			push(&s ,now);			// �⦹�`�I��J���|�H�������� 
			now.x += offset[now.dir].dx;
			now.y += offset[now.dir].dy;
			now.dir = 0;
		}
		if((now.y == end_y) && (now.x == end_x)){	// ��ثe�y�Ь����I�y�Ю� 
			maze[now.y][now.x] = 8;					// �N��w�g�]���g�c�F 
			printf("%s (%d,%d)\n\n", "# done.", now.x, now.y);
			break;
		}else if((now.y == start_y) && (now.x == start_x)){ // ��ثe�y�Ь��_�I�y�Ю�  
			maze[now.y][now.x] = 9;							// �N��䤣����I�A��� 
			printf("%s\n\n", "# error.");
			break;			
		}
	}
	
	// �o��O��a�ϸ��Show�X�Ӫ��_���j�� 
	for(s_dy = 0; s_dy < max_y; s_dy++){
		for(s_dx = 0; s_dx < max_y; s_dx++){
			switch(maze[s_dy][s_dx]){
				case 0:					// 0��ܥ����L���� 
					printf("%s", "* ");
					break;
				case 1:					// 1���������o�樫 
					printf("%s", "| ");
					break;
				case 8:					// 8��ܤw���L�B���T���� 
					printf("%s", "O ");
					break;
				case 9:					// 9��ܤw���L�����~���� 
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
