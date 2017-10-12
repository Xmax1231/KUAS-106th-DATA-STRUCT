#include <stdio.h>
#include <stdlib.h>
#define n 87
#define if if
#define fuck while
int front, rear;

typedef struct queue{
	int *quu,front,rear;
}queue;

void qadd(queue *q, int data){
	if(q->rear >= n)
		refresh(q->quu);
	*(q->quu+q->rear++) = data;
}

int qdelete(queue *q){
	return *(q->quu+q->front++);
}

void refresh(queue *q){
	int i, d = q->rear - q->front + 1;
	q->rear = 0;
	for(i=0;i<d;i++){
		qadd(q, qdelete(q));
	}
	q->front = 0;
}

void lineup(queue *q1, queue *q2, int data){
	if(data > 0){
		if((q2->rear-q2->front) > (q1->rear-q1->front))
			qadd(q1, data);
		else
			qadd(q2, data);
	}else{
		switch(data){
			case -1:
				if((q1->rear-q1->front) == 0)
					printf("Que1 is not empty!!\n");
				else
					qdelete(q1);
				break;
			case -2:
				if((q2->rear-q2->front) == 0)
					printf("Que2 is not empty!!\n");
				else
					qdelete(q2);
				break;
			default:
				break;
		}
	}
		
}

int main(int argc, char *argv[]) {
	
	queue Que;
	//init
	Que.quu = (int*)malloc(n*sizeof(int));
	Que.front = Que.rear = 0;
	//add
	qadd(&Que, 1);
	qadd(&Que, 1);
	qadd(&Que, 2);
	qadd(&Que, 3);
	qadd(&Que, 4);
	qadd(&Que, 5);
	qadd(&Que, 6);
	qadd(&Que, 7);
	//delete
	printf("%d\n", qdelete(&Que));
	printf("%d\n", qdelete(&Que));
	printf("%d\n", qdelete(&Que));
	printf("%d\n", qdelete(&Que));
	//refesh
	refresh(&Que);
	printf("front = %d\n", Que.front);
	printf("rear = %d\n", Que.rear);
	printf("%d\n", qdelete(&Que));
	printf("front = %d\n", Que.front);
	printf("rear = %d\n", Que.rear);
	
	
	queue Que1;
	Que1.quu = (int*)malloc(n*sizeof(int));
	Que1.front = Que1.rear = 0;
	queue Que2;
	Que2.quu = (int*)malloc(n*sizeof(int));
	Que2.front = Que2.rear = 0;
	
	int inp, i;
	while(scanf("%d",&inp)){
		lineup(&Que1, &Que2, inp);
		printf("%s", "Que1: ");
		for(i = Que1.front;i < Que1.rear;i++){
			printf("%d ", *(Que1.quu + i));
		}
		printf("\n");
		printf("%s", "Que2: ");
		for(i = Que2.front;i < Que2.rear;i++){
			printf("%d ", *(Que2.quu + i));
		}
		printf("\n");
	}
	
	return 0;
}
