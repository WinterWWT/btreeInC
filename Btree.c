#include "Btree.h"

int main()
{
	btree my_tree;
	init_btree(&my_tree);

	struct btnode child1;
	memset(&child1,0,sizeof(child1));

	struct btnode child2 = {
                .keynum = 2,
                .key[0] = 4,
                .key[1] = 5,
                .parent = &my_tree
        };

	my_tree.keynum = 1;
	my_tree.key[0] = 3;
	my_tree.child[0] = &child1;
	my_tree.child[1] = &child2;

	child1.keynum = 2;
	child1.key[0] = 1;
	child1.key[1] = 2;
	child1.parent = &my_tree;

//	struct btnode child2 = {
//		.keynum = 2,
//		.key[0] = 4,
//		.key[1] = 5,
//		.parent = &my_tree
//	};

	struct result * my_result = search_btree(&my_tree,6);

	printf("my_tree->keynum is %d.\n",my_tree.keynum);

	printf("res is %p.\nfound_tag is %d.\nkeynum is %d.\n",my_result,my_result->found_tag,my_result->node->keynum);

	printf("result is: %s.\n",(my_result->found_tag == 0)?"not found":"found");

	for (int i = 0; i < my_result->node->keynum; i++) {
		printf("%d ",my_result->node->key[i]);
	}

	printf("\n");
	return 0;
}
