#include <stdio.h>
#define NextLine printf("\n\n")
typedef struct node{
	int data;
	struct node *link;
}node;
node *rear;
void dump(node* dummy);
void qadd(int data);
void show();
int main(int argc, char *argv[]) {
	node *dummy = (node*)malloc(sizeof(node));
	rear = dummy;
	dummy->data = -1;
	dummy->link = dummy;
	dump(dummy);
	qadd(87);
	qadd(99);
	qadd(22);
	qadd(666);
	qadd(22);
	show();
	
	dump(dummy);
	NextLine;
	printf("%d\n", qdelete());
	printf("%d\n", qdelete());
	show();
	
	dump(dummy);
	NextLine;
	qadd(9487);
	qadd(9453);
	qadd(878787);
	show();
	return 0;
}
void dump(node* dummy){
	printf("\ndummy = 0x%x", dummy);
	printf("\nrear = 0x%x\n", rear);
}
void show(){
	node *now = rear->link->link;
	while(now->data != -1){
		printf("%d, ", now->data);
		now = now->link; 
	}
}
void qadd(int data){
	node *tmp = (node*)malloc(sizeof(node));
	tmp->data = data;
	tmp->link = rear->link;
	rear->link = tmp;
	rear = tmp;
}
int qdelete(){
	if(rear->link != rear){
		int ret;
		node *tmp = rear->link->link;
		rear->link->link = tmp->link;
		ret = tmp->data;
		free(tmp);
		return ret;
	}
}
