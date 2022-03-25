#include <stdio.h>
#include <stdbool.h> 	//bool C99up
#include <string.h>
#include <stdlib.h>	//malloc()

#define debug 1
#define Morder 3
#define keytype int	//type of key

#define MaxKeyNum (Morder - 1)
//#define MinKeyNum (int)(ceil((double)Morder/2) - 1)
#define MinKeyNum ((Morder - 1)/2)

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
void new_root(btree ** root);

bool insert_btree(struct btnode ** root,keytype key);

struct btnode * find_pro(struct btnode * node);
struct btnode * find_suc(struct btnode * node);
void movetoright(struct btnode * node);
void movetoleft(struct btnode * node);
void merge(struct btnode * node);

void delete_btnode(btree ** tree,struct btnode * node,int pos,keytype key);

bool delete_btree(btree ** tree,keytype key);

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
	
	for(int i = node->keynum - 1; i >= pos; i--) {
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
	//printf("pos: %d.\n",res.i);
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

void new_root(btree ** root) 
{
	//printf("%s(): root: %p.\n",__func__,*root);
	struct btnode * new_root = malloc(sizeof(struct btnode));
	memset(new_root,0,sizeof(struct btnode));

	(*root)->parent = new_root;
	new_root->child[0] = *root;
	new_root->keynum = 0;

	split_btnode(*root);

	*root = new_root;
}

struct btnode * find_pro(struct btnode * node) 
{
	struct btnode * tar = node;
	while(node != NULL) {
		tar = node;
		node = node->child[node->keynum];
	}

	return tar;
}

struct btnode * find_suc(struct btnode * node)
{
	struct btnode * tar = node;
	while(node != NULL) {
		tar = node;
		node = node->child[0];
	}

	return tar;
}

//leftbro -> node
void movetoright(struct btnode * node) {
	struct btnode * parent = node->parent;
	//find pos of node in parent.
	int pos = 0;
	for (int i = 0; i <= parent->keynum; i++) {
		if (parent->child[i] == node) {
			pos = i;
			break;
		}
	}
	struct btnode * leftbro = parent->child[pos - 1];
	
	//node->key
	for(int i = node->keynum - 1; i >= 0; i--) {
		node->key[i + 1] = node->key[i];
	}
	node->key[0] = parent->key[pos - 1];

	//node->child
	if (leftbro->child[leftbro->keynum]) {
		for (int i = node->keynum; i >= 0; i--) {
			node->child[i + 1] = node->child[i];
		}
		node->child[0] = leftbro->child[leftbro->keynum];
		leftbro->child[leftbro->keynum] = NULL;
	}

	//parent->key
	node->keynum++;
	parent->key[pos - 1] = leftbro->key[leftbro->keynum - 1];
	leftbro->keynum--;
}

//node <- rightbro
void movetoleft(struct btnode * node) {
	//printf("----%s(): 1----.\n",__func__);
	struct btnode * parent = node->parent;
	//find pos of node in parent.
	int pos = 0;
	for (int i = 0; i <= parent->keynum; i++) {
		if (parent->child[i] == node) {
			pos = i;
			break;
		}
	}
	//printf("----%s(): 2----pos:%d,node->keynum:%d.\n",__func__,pos,node->keynum);
	struct btnode * rightbro = parent->child[pos + 1];

	//node->key
	node->key[node->keynum] = parent->key[pos];
	node->keynum++;

	//parent->key
	parent->key[pos] = rightbro->key[0];

	//rightbro->key
	for(int i = 0; i < rightbro->keynum - 1; i++) {
		rightbro->key[i] = rightbro->key[i + 1];
	}
	rightbro->key[rightbro->keynum - 1] = 0;
	rightbro->keynum--;
	
	//rightbro->child
	if (rightbro->child[0]) {
		node->child[node->keynum] = rightbro->child[0];
		for (int i = 0;i < rightbro->keynum; i++) {
			rightbro->child[i] = rightbro->child[i + 1];
		}
	}
}

void merge(struct btnode * node) {
	//printf("----%s(): 1----.\n",__func__);

	struct btnode * parent = node->parent;
	//find pos of node in parent.
        int pos = 0;
        for (int i = 0; i <= parent->keynum; i++) {
        	if (parent->child[i] == node) {
                	pos = i;
			break;
		}
        }
	//printf("----%s(): 2----pos:%d.\n",__func__,pos);
	
	if (pos == 0) {
		//printf("----%s(): 3.1----.\n",__func__);

		//node <- node + parent + rightbro
		struct btnode * rightbro = parent->child[pos + 1];
		
		//node->key
		node->key[node->keynum] = parent->key[pos];
		for (int i = 0;i < rightbro->keynum; i++) {
			node->key[node->keynum + 1 + i] = rightbro->key[i];
		}
		//node->child
		if (node->child[0]) {
			//printf("----%s():3.1.1----.\n",__func__);

			for (int i = 0; i < rightbro->keynum + 1; i++) {
				node->child[node->keynum + 1 + i] = rightbro->child[i];
				rightbro->child[i]->parent = node;
			}
		}
		node->keynum = node->keynum + 1 + rightbro->keynum;

		//parent->key
		for(int i = pos; i < parent->keynum - 1; i++) {
                        parent->key[i] = parent->key[i + 1];
                }
		parent->key[parent->keynum - 1] = 0;
		//parent->child
		for(int i = pos + 1; i < parent->keynum; i++) {
			parent->child[i] = parent->child[i + 1];
		}
		parent->child[parent->keynum] = NULL;
		parent->keynum--;

		free(rightbro);

	} else {
		//printf("----%s(): 3.2----.\n",__func__);
		
		//node <- leftbro + parent + node
		struct btnode * leftbro = parent->child[pos - 1];
		//node->key
		for (int i = node->keynum - 1; i >= 0; i--) {
			node->key[leftbro->keynum + 1 + i] = node->key[i];
		}
		node->key[leftbro->keynum] = parent->key[pos - 1];
		for(int i = 0; i < leftbro->keynum; i++) {
			node->key[i] = leftbro->key[i];
		}

		//node->child
		if (node->child[0]) {
			for (int i = node->keynum; i >= 0; i--) {
				node->child[leftbro->keynum + 1 + i] = node->child[i];
			}

			for (int i = 0; i < leftbro->keynum + 1; i++) {
				node->child[i] = leftbro->child[i];
				leftbro->child[i]->parent = node;
			}
		}
		node->keynum = node->keynum + 1 + leftbro->keynum;

		//parent->key
		for(int i = pos - 1; i < parent->keynum - 1; i++) {
                        parent->key[i] = parent->key[i + 1];
                }
		parent->key[parent->keynum - 1] = 0;
		//parent->child
		for(int i = pos; i < parent->keynum; i++) {
			parent->child[i] = parent->child[i + 1];
		}
		parent->child[parent->keynum] = NULL;
		parent->keynum--;

		free(leftbro);
	}
}

void delete_btnode(btree **tree, struct btnode * node,int pos,keytype key) 
{	
	if (node->child[0]) {
	//内部节点
		//printf("----%s(): 1.1----.\n",__func__);
		//前驱
		struct btnode * pronode = find_pro(node->child[pos]);
		int pro_key = pronode->key[pronode->keynum - 1];	//copy key
		//printf("----%s(): 1.1a----prokey:%d.\n",__func__,pro_key);
		//后驱 
		struct btnode * sucnode = find_suc(node->child[pos + 1]);
		int suc_key = sucnode->key[0];    //copy key
		//printf("----%s(): 1.1b----suckey:%d.\n",__func__,suc_key);

	       	if (pronode->keynum > MinKeyNum) {
			//直接前驱节点替换
			//printf("----%s(): 1.1.1.----.\n",__func__);

			node->key[pos] = pro_key;
			pronode->key[pronode->keynum - 1] = 0;
			pronode->keynum--;
		} else {
			//printf("----%s(): 1.1.2----.\n",__func__);
			if (sucnode->keynum > MinKeyNum) {
				//直接后驱节点替换
				//printf("----%s(): 1.1.2.1----.\n",__func__);
				node->key[pos] = suc_key;
				for (int i = 0; i < sucnode->keynum - 1; i++) {
					sucnode->key[i] = sucnode->key[i + 1];
				}
				sucnode->keynum--;
			} else {
				//printf("----%s(): 1.1.2.2----.\n",__func__);
				if (pronode->parent->child[pronode->parent->keynum - 1]->keynum > MinKeyNum) {
					//前驱节点替换 -> 叶子节点右旋转
					//printf("----%s(): 1.1.2.2.1----.\n",__func__);
                                 	node->key[pos] = pro_key;
                                	pronode->key[pronode->keynum - 1] = 0;
					pronode->keynum--;

					movetoright(pronode);
				} else if (sucnode->parent->child[1]->keynum > MinKeyNum) {
					//后驱节点替换 -> 叶子节点左旋转
					//printf("----%s(): 1.1.2.2.2----.\n",__func__);
					node->key[pos] = suc_key;
					for (int i = 0; i < sucnode->keynum - 1; i++) {
						sucnode->key[i] = sucnode->key[i + 1];
					}
					sucnode->key[sucnode->keynum - 1] = 0;
					sucnode->keynum--;
						
					movetoleft(sucnode);
				} else {
					//printf("----%s(): 1.1.2.2.3----.\n",__func__);
					if (pronode->parent->keynum > MinKeyNum) {
						//前驱节点合并
						node->key[pos] = pro_key;
                                        	pronode->key[pronode->keynum - 1] = 0;
						pronode->keynum--;

						merge(pronode);
					} else if (sucnode->parent->keynum > MinKeyNum) {
						//后驱节点合并 
						node->key[pos] = suc_key;
                                                sucnode->key[sucnode->keynum - 1] = 0;
						sucnode->keynum--;
							
						merge(sucnode);	
					} else {
						//前驱节点合并-循环合并
						node->key[pos] = pro_key;
                                        	pronode->key[pronode->keynum - 1] = 0;
						pronode->keynum--;
					
						node = pronode;
						struct btnode * root = *tree;
						while(node->keynum < MinKeyNum && node != root) {
							int position = 0;
				                 	for (int i = 0; i < node->parent->keynum; i++) {
				                        	if (node->parent->child[i] == node) {
				                                	position = i;
				                                 	break;
				                        	}
				                 	}
							
							if (position != 0 && node->parent->child[position - 1]->keynum > MinKeyNum) {
								//右旋转
								//printf("----%s(): 2.1----.\n",__func__);
				
								movetoright(node);
								break;
							} else if (position != node->keynum && node->parent->child[position + 1]->keynum > MinKeyNum) {
								//左旋转
								//printf("----%s(): 2.2----.\n",__func__);
				
								movetoleft(node);
								break;
							} else {
								//合并
								//printf("----%s(): 2.3----.\n",__func__);
								merge(node);
								
								node = node->parent;
							}
						}
						
						if (node == root && node->keynum == 0) {
							//printf("----%s(): 2.4----,old_root:%p,new_root:%p.\n",__func__,root,node->child[0]);
							
							*tree = node->child[0];
						}
					}
				}
			}
		}
	} else {
	//叶子节点
		//直接删除
		//printf("----%s(): 1.2----.\n",__func__);
		for (int i = pos; i < node->keynum - 1; i++) {
			node->key[i] = node->key[i + 1];
		}
		node->key[node->keynum - 1] = 0;
		node->keynum--;

		struct btnode * root = *tree;
		while(node->keynum < MinKeyNum && node != root) {
			int position = 0;
                 	for (int i = 0; i < node->parent->keynum; i++) {
                        	if (node->parent->child[i] == node) {
                                	position = i;
                                 	break;
                        	}
                 	}
			
			if (position != 0 && node->parent->child[position - 1]->keynum > MinKeyNum) {
				//右旋转
				//printf("----%s(): 2.1----.\n",__func__);

				movetoright(node);
				break;
			} else if (position != node->keynum && node->parent->child[position + 1]->keynum > MinKeyNum) {
				//左旋转
				//printf("----%s(): 2.2----.\n",__func__);

				movetoleft(node);
				break;
			} else {
				//合并
				//printf("----%s(): 2.3----.\n",__func__);

				merge(node);
				
				node = node->parent;
			}
		}
		
		if (node == root && node->keynum == 0) {
			//printf("----%s(): 2.4----,old_root:%p,new_root:%p.\n",__func__,root,node->child[0]);
			
			*tree = node->child[0];
		}
	}
}

bool delete_btree(btree ** tree,keytype key) 
{
	struct btnode * root = *tree;
	struct result res = search_btree(root,key);

	int found_tag = res.found_tag;
	int pos = res.i;
	struct btnode * node = res.node;

	if (!found_tag) {
		printf("key:%d doesn't exist!.\n",key);	

		return false;
	} else {
		delete_btnode(tree,node,pos,key);
	}

	return true;
}
