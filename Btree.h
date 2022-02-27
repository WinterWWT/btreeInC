#include <stdio.h>
#include <stdbool.h> 	//bool C99up
#include <string.h>
#include <stdlib.h>	//malloc()

#define Morder 5
#define keytype int	//type of key

#define MaxKeyNum (Morder - 1)
//#define MinKeyNum (int)(ceil((double)Morder/2) - 1)
#define MinKeyNum (Morder/2)

#define keytype int

struct btnode {
	int keynum;
	keytype key[Morder];
	struct btnode * child[Morder + 1];
	struct btnode * parent;
};

typedef struct btnode btree;

struct result {
	struct btnode * node;
	int i;
	int found_tag;
};

void init_btree(struct btnode * root);
int search_btnode(struct btnode * node,keytype key);
struct result * search_btree(struct btnode * root,keytype key);
void split_btnode(struct btnode * node);
bool insert_btnode(struct btnode * node,int pos,keytype key);
bool insert_btree(struct btnode * root,keytype key);

void init_btree(struct btnode * root)
{
	memset(root,0,sizeof(struct btnode));
	root->parent = root;
}

int search_btnode(struct btnode * node,keytype key)
{
	int i;

	for (i = 0; i < node->keynum && node->key[i] <= key; i++)
		;
	
	printf("in %s, keynum is %d.\n",__func__,node->keynum);

	return i;
}

struct result * search_btree(struct btnode * root,keytype key)
{
	static int a = 1;
	
	printf("I am here, the %dth.\n",a++);
	
	struct btnode * cur;
	struct btnode * pro;
	struct result * res = malloc(sizeof(struct result));

	int found_tag = 0;
	int i = 0;

	cur = root;

	printf("cur is %p.\n",cur);
	printf("1:cur->keynum is %d.\n",cur->keynum);

	while (cur != NULL && found_tag == 0) {
		 i = search_btnode(cur,key);
		 
		 printf("i is %d.\n",i);

		 if (i > 0 && cur->key[i - 1] == key) {
		 	found_tag = 1;
			
			printf("should be here.\n");
		 } else {
		 	pro = cur; 
			cur = cur->child[i];
			
			printf("should not be here.\n");
		 }
	}

	//printf("2.1:cur->keynum is %d.\n",cur->keynum);

	if (found_tag == 1) {
		res->node = cur;
		res->i = i;
		res->found_tag = 1;

		printf("2.2:cur->keynum is %d.\n",cur->keynum);

	} else {
		res->node = pro;
		res->i = i;
		res->found_tag = 0;
	}

	//printf("3.1:cur->keynum is %d.\n",cur->keynum);

	//printf("res is %p.\n",res);
	printf("res->node is %p.\n",res->node);
	printf("res->node->keynum is %d.\n",res->node->keynum);
	//printf("3.2:cur->keynum is %d.\n",cur->keynum);

	return res;
}

void split_btnode(struct btnode * node) 
{	
	node->parent = NULL;
}

bool insert_btnode(struct btnode * node,int pos,keytype key)
{
	for(int i = pos; i < node->keynum; i++) {
		node->key[i + 1] = node->key[i]; 
	}
	node->key[pos] = key;

	node->keynum++;
	if (node->keynum == Morder) {
		split_btnode(node);
	}

	return true;
}

bool insert_btree(struct btnode * root,keytype key)
{
	
}


