#include <stdio.h>
#include <stdbool.h> 	//bool C99up
#include <string.h>
#include <stdlib.h>	//malloc()

#define debug 1
#define Morder 3
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

#include "debug.h"

void init_btree(struct btnode * root);
void print_btree(struct btnode * root);
int search_btnode(struct btnode * node,keytype key);
struct result search_btree(struct btnode * root,keytype key);
void split_btnode(struct btnode * node);
void insert_btnode(struct btnode * node,int pos,keytype key);
bool insert_btree(struct btnode ** root,keytype key);
void new_root(btree ** root);

void init_btree(struct btnode * root)
{
	memset(root,0,sizeof(struct btnode));
}

void print_btree(struct btnode * root) 
{
	struct btnode * node = root;

	if (node != NULL) {
		printf("<");
		for (int i = 0; i < node->keynum; i++) {
                	printf(" %d",node->key[i]);
        	}
		printf(" >\n");

		if (node->child[0] != NULL) {
			for (int i = 0; i < node->keynum + 1; i++) {
                		print_btree(node->child[i]);
        		}
		}

	}
}

int search_btnode(struct btnode * node,keytype key)
{
	//printf("%s(): node:%p, key:%d.\n",__func__,node,key);
	
	int i;

	if (node->keynum == 0) {
		return 0;
	}

	for (i = 0; i < node->keynum && node->key[i] <= key; i++) {
	}
	
	return i;
}

struct result search_btree(struct btnode * root,keytype key)
{
	//printf("%s(): root:%p, key:%d.\n",__func__,root,key);

	struct btnode * cur = root;
	struct btnode * pro;
	struct result res;

	int found_tag = 0;
	int i;
	
	//seek in a node and iteration of node
	while (cur != NULL && found_tag == 0) {
		 i = search_btnode(cur,key);

		 if (i > 0 && cur->key[i - 1] == key) {
		 	found_tag = 1;
		 } else {
		 	pro = cur; 
			cur = cur->child[i];
		 }
	}
	
	//result of seeking
	if (found_tag == 1) {
		res.node = cur;
		res.i = i - 1;
		res.found_tag = 1;
	} else {
		res.node = pro;
		res.i = i;
		res.found_tag = 0;
	}

	return res;
}

void split_btnode(struct btnode * node) 
{		
	//printf("%s(): node: %p.\n",__func__,node);
	
	//split node
	struct btnode *bro_node = malloc(sizeof(struct btnode));

	keytype k = node->key[(Morder)/2];      //front more than back

        int pos = search_btnode(node->parent,k);

	//copy key
	for (int i = (Morder)/2 + 1; i < Morder; i++ ) {
		bro_node->key[i - (Morder)/2 - 1] = node->key[i];
		node->key[i] = 0;
	}
	//copy child
	for (int i = (Morder)/2 + 1; i < Morder + 1; i++) {
		bro_node->child[i - (Morder)/2 - 1] = node->child[i];
		node->child[i] = NULL;

		if (bro_node->child[i - (Morder)/2 - 1] != NULL) 
			bro_node->child[i - (Morder)/2 - 1]->parent = bro_node;
	}
	//copy parent
	bro_node->parent = node->parent;
	//assign keynum
        bro_node->keynum = (Morder - 1)/2;
        node->keynum = (Morder)/2;
	
	//change node->parent
	struct btnode * parent = node->parent;
	//insert k to parent
        for (int i = parent->keynum - 1; i > pos - 1; i--) {
        	parent->key[i + 1] = parent->key[i];
        }
        parent->key[pos] = k;

        //insert new node to parent
        for (int i = parent->keynum; i > pos; i--) {
                parent->child[i + 1] = parent->child[i];
        }
	parent->child[pos + 1] = bro_node;
        //assign keynum
        parent->keynum += 1;
}

void insert_btnode(struct btnode * node,int pos,keytype key)
{
	//printf("%s(): node:%p,pos:%d,key:%d.\n",__func__,node,pos,key);
	
	for(int i = pos; i < node->keynum; i++) {
		node->key[i + 1] = node->key[i]; 
	}
	node->key[pos] = key;

	node->keynum++;
}

bool insert_btree(btree ** root,keytype key)
{
	//printf("%s(): root:%p,key:%d.\n",__func__,*root,key);
	
	btree * tree = *root;	

	struct result res = search_btree(tree,key);
	int pos = res.i;
	int tkey = key;
	struct btnode * node = res.node;
	
	int end_flag = 0;

	if (res.found_tag) {
		printf("key:%d already exist!",key);

		return false;
	} else {
		insert_btnode(node,pos,key);
		
		while(node != tree && end_flag == 0) {
			if (node->keynum == Morder) {
				split_btnode(node);
			} else {
				end_flag = 1;
			}

			node = node->parent;
		}
		if (node == tree && end_flag == 0) {
			if (node->keynum == Morder) {
				new_root(root);
			} else {

			}
		}
	}
	
	return true;
}

void new_root(btree ** root) {
	//printf("%s(): root: %p.\n",__func__,*root);

	struct btnode * new_root = malloc(sizeof(struct btnode));
	memset(new_root,0,sizeof(struct btnode));

	(*root)->parent = new_root;
	new_root->child[0] = *root;
	new_root->keynum = 0;

	split_btnode(*root);

	*root = new_root;
}
