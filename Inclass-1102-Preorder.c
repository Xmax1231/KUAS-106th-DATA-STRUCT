#include <stdio.h>
#include <stdlib.h>
typedef struct _node{
	char data;
	struct _node *left, *right, *parent;
}_node;

int add(char,_node*,int);
void Preorder(_node*);
void Xorder(_node*);
int main(int argc, char *argv[]) {
	_node *root = (_node*)malloc(sizeof(_node));
	root->data = 'A';
	add('F', root, 0);
	add('B', root, 1);
	add('I', root->left, 0);
	add('G', root->left, 1);
	add('H', root->left->right, 1);
	add('E', root->right, 0);
	add('C', root->right, 1);
	add('D', root->right->right, 0);
	Preorder(root);
	printf("\n");
	Xorder(root);
	printf("\n");
	return 0;
}
int add(char d, _node *n, int choice){
	// choice = 0 is left node, choice = 1 is right node.
	_node *tmp = (_node*)malloc(sizeof(_node));
	tmp->data = d;
	switch(choice){
		case 0:
			tmp->parent = n;
			tmp->left = 0;
			tmp->right = 0;
			n->left = tmp;
			break;
		case 1:
			tmp->parent = n;
			tmp->left = 0;
			tmp->right = 0;
			n->right = tmp;
			break;
		default:
			return 1;
	}
	return 0;
} 
void Preorder(_node *root){
	printf("%c", root->data);
	if(root->left){
		Preorder(root->left);
	}
	if(root->right){
		Preorder(root->right);
	}
}
void Xorder(_node *root){
	printf("%c", root->data);
	if(root->right){
		Xorder(root->right);
	}
	if(root->left){
		Xorder(root->left);
	}
}
