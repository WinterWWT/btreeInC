#include "Btree.h"

int main()
{
	btree * my_tree = malloc(sizeof(btree));
	init_btree(my_tree);

	struct btnode child1,child2,child3;
	memset(&child1,0,sizeof(child1));
	memset(&child2,0,sizeof(child2));
	memset(&child3,0,sizeof(child3));
	
	my_tree->keynum = 2;
	my_tree->key[0] = 7;
	my_tree->key[1] = 18;

	my_tree->child[0] = &child1;
	my_tree->child[1] = &child2;
	my_tree->child[2] = &child3;

	child1.keynum = 2;
	child1.key[0] = 1;
	child1.key[1] = 2;
	child1.parent = my_tree;

	child2.keynum = 2,
        child2.key[0] = 9,
        child2.key[1] = 10,
        child2.parent = my_tree;

	child3.keynum = 2,
        child3.key[0] = 21,
        child3.key[1] = 22,
        child3.parent = my_tree;

	print_node("my_tree",my_tree);
        print_node("child1",my_tree->child[0]);
        print_node("child2",my_tree->child[1]);
        print_node("child3",my_tree->child[2]);

	insert_btree(&my_tree,23);

	//printf("mt_tree:%p.\n",my_tree);

	print_node("my_tree",my_tree);
	print_node("child1",my_tree->child[0]);
	print_node("child2",my_tree->child[1]);
	
	struct btnode child11,child12,child21,child22;
       	
	print_node("child1.1",my_tree->child[0]->child[0]);
	print_node("child1.2",my_tree->child[0]->child[1]);
	print_node("child2.1",my_tree->child[1]->child[0]);
	print_node("child2.2",my_tree->child[1]->child[1]);

	return 0;
}
