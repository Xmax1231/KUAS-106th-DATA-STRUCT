#include <stdio.h>
char data[100] = {0 ,'B', 'C', 'E', 'F', 'A', 'P', 'L', 'G', 'J', 'Z', 'Q'};
int link[100] = {0 ,9, 4, 2, 7, 1, 5, 6, 3, 11, 0, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
int first = 8;
/* link 指向下一個 data array 的 Index
 * -1 代表 Null, 0 代表 GND 
 */
void show();
void delete(int index);
void insert(char data, int index);
int search_p(char d);
int main(int argc, char *argv[]) {
	show();
	
	delete(5);
	show();
	
	insert('#', 4);
	show();
	
	char s;
	while(scanf("%c",&s)){
		if(s!='\n' && s!='\r')
			printf("link[%d] => %d => %c\n", search_p(s), link[search_p(s)], s);
	}
	return 0;
}
void show() {
	int i;
	i = first;
	printf("\nindex\tdata\tlink\n");
	while(link[i]!=0){
		printf("%d\t", i);
		printf("%c\t", data[i]);
		printf("%d\t", link[i]);
		i = link[i];
		printf("\n");
	}
	printf("\n\n");
}
void delete(int index) {
	int n,t;
	n=first;
	while(link[n]!=0){
		if(link[n]==index){
			printf("link[%d] = %d -> link[%d] = %d\n", n, link[n], n, link[index]);
			link[n] = link[index];
			link[index] = -1;
		}else
			n = link[n];
	}
}
void insert(char _data, int index) {
	int n;
	n=1;
	while(link[n]!=-1){
		n++;
	}
	data[n] = _data;
	link[n] = link[index];
	link[index] = n;
	printf("link[%d] = %d , link[%d] = %d\n", index, link[index], n, link[n]);
}
int search_p(char d) {
	int n;
	n = first;
	while(link[n]!=0){
		if(data[link[n]]==d)
			return n;
		n = link[n];
	}
}
