#include "Btree.h"

int main()
{
	btree * my_tree = malloc(sizeof(btree));
	init_btree(my_tree);

	insert_btree(&my_tree,1);
	print_btree(my_tree);
	printf("\n");	
	
	insert_btree(&my_tree,2);
	print_btree(my_tree);	
	printf("\n");	

	insert_btree(&my_tree,3);
	print_btree(my_tree);	
	printf("\n");

	insert_btree(&my_tree,4);
	print_btree(my_tree);	
	printf("\n");

	insert_btree(&my_tree,5);
	print_btree(my_tree);	
	printf("\n");

	insert_btree(&my_tree,6);
	print_btree(my_tree);	
	printf("\n");	

	insert_btree(&my_tree,7);
	print_btree(my_tree);	
	printf("\n");

	insert_btree(&my_tree,8);
	print_btree(my_tree);	
	printf("\n");

	insert_btree(&my_tree,9);
	print_btree(my_tree);	
	printf("\n");

	insert_btree(&my_tree,10);
	print_btree(my_tree);	
	printf("\n");

	insert_btree(&my_tree,11);
	print_btree(my_tree);	
	printf("\n");

	insert_btree(&my_tree,12);
	print_btree(my_tree);	
	printf("\n");

	insert_btree(&my_tree,13);
	print_btree(my_tree);	
	printf("\n");

	insert_btree(&my_tree,14);
	print_btree(my_tree);	
	printf("\n");

	insert_btree(&my_tree,15);
	print_btree(my_tree);	
	printf("\n");

	delete_btree(&my_tree,8);
	print_btree(my_tree);
	printf("\n");


	return 0;
}	
