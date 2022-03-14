#include <stdio.h>

#ifdef debug 
void print_node(char * s,struct btnode *node) {
	printf("%s:\n",s);
        
	printf("key is: <");
        for (int i = 0; i < node->keynum; i++) {
                printf(" %d ",node->key[i]);
        }
        printf(">\n");

        if (node->child[0] != NULL) {
		printf("child is: ");
        	
		for (int i = 0; i < node->keynum + 1; i++) {
                	//printf("%p ",node->child[i]);
				printf("<");
        		
				for (int j = 0; j < node->child[i]->keynum; j++) {
                			printf(" %d ",node->child[i]->key[j]);
        			}

        			printf("> ");
		}
        printf("\n\n");
	} else {
		
	}

}

#endif

