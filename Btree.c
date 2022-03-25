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
	my_tree->key[1] = 21;
	print_btree(my_tree);
	printf("\n");
	
	insert_btree(&my_tree,1);
	print_btree(my_tree);
	printf("\n");

	insert_btree(&my_tree,9);
	print_btree(my_tree);
	printf("\n");

	insert_btree(&my_tree,18);
	print_btree(my_tree);
	printf("\n");

	insert_btree(&my_tree,11);
	print_btree(my_tree);
	printf("\n");

	insert_btree(&my_tree,22);
	print_btree(my_tree);
	printf("\n");

	insert_btree(&my_tree,10);
	print_btree(my_tree);
	printf("\n");

	insert_btree(&my_tree,2);
	print_btree(my_tree);
	printf("\n");

	delete_btree(&my_tree,2);
	print_btree(my_tree);
	printf("\n");

	delete_btree(&my_tree,1);
	print_btree(my_tree);
	printf("\n");
	
	delete_btree(&my_tree,10);
	print_btree(my_tree);
	printf("\n");

	delete_btree(&my_tree,9);
	print_btree(my_tree);
	printf("\n");
	
	delete_btree(&my_tree,11);
	print_btree(my_tree);
	printf("\n");

	return 0;
}	
