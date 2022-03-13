#include <stdio.h>

#ifdef debug 
void print_node(char * s,struct btnode *node) {
	printf("%s:\n",s);
        
	printf("key is: <");
        for (int i = 0; i < node->keynum; i++) {
                printf(" %d ",node->key[i]);
        }
        printf(">\n");

        printf("child is: ");
        for (int i = 0; i < node->keynum + 1; i++) {
                printf("%p ",node->child[i]);
        }
        printf("\n\n");
}

#endif

