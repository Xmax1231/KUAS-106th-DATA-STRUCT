#include <stdio.h>
#include <stdlib.h>
#define max 9487
typedef struct term{
	int n;
	struct term *next;
}term;
term *rear;
void add_term(int data){
	term *tmp = (term*)malloc(sizeof(term));
	rear->next = tmp;
	tmp->n = data-'0';
	rear = tmp;
	tmp->next = 0;
}
void show(term *tm){
	term *c;
	c=tm;
	while(c){
		printf("%d",c->n);
		c = c->next;
	}
	printf("\n");
}

int main(int argc, char *argv[]) {
	// char tmp_a[9487], tmp_b[9487];
	// init
	int i;
	int *c = (int*)calloc(max,sizeof(int));
	char *tmp_a = (char*)malloc(max*sizeof(char));
	char *tmp_b = (char*)malloc(max*sizeof(char));
	term *a = (term*)malloc(sizeof(term));
	term *b = (term*)malloc(sizeof(term));
	a->next = b->next = 0;
	// ----------------------------------------------------
	// scanf a
	printf("%s", "a= ");
	scanf("%s",tmp_a);
	for(i=0;i<max&&tmp_a[i]!='\0';i++){/* a 的長度為 i */}
	rear = a;
	a->n = tmp_a[--i]-'0';
	while(i>0)
		add_term(tmp_a[--i]);
	// ----------------------------------------------------
	// scanf b
	printf("%s", "b= ");
	scanf("%s",tmp_b);
	for(i=0;i<max&&tmp_b[i]!='\0';i++){/* b 的長度為 i */}
	rear = b;
	b->n = tmp_b[--i]-'0';
	while(i>0)
		add_term(tmp_b[--i]);
	// ----------------------------------------------------

	int n = -1, l = 0, temp; //
	term *ap, *bp;
	int carry=0;
	ap = a;	bp = b;
	while(bp){
		ap = a;
		l=0; n++;
		while(ap){
			temp = c[n+l];
			c[n+l] = ((ap->n)*(bp->n)+carry+c[n+l])%10;
			carry = ((ap->n)*(bp->n)+carry+temp)/10;
			l++;
			ap=ap->next;
		}
		if(carry!=0){
			c[n+l] += carry;
			if(c[n+l]>10){
				c[n+l+1] = c[n+l]/10;
				c[n+l] = c[n+l]%10;
			}
			carry = 0;
		}
		bp=bp->next;
	}
	int x=c[n+l]==0?n+l-1:n+l;  //別問，這很複雜 
	printf("%s", "axb= ");
	while(x>=0)
		printf("%d",c[x--]);
	return 0;
}
