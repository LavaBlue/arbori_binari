#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "binary_trees.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main()
{
	int i, n, val;
	int left_height, right_height;
	BOOL ret_delete;

	pNOD r = NULL;		/* vlad: the root; 
						 * At the very beginning time the tree is empty (!) 
						 * I will assume it this way.
						 */

	/* building the tree */
	fprintf(stdout, "nr. de noduri: \n"); scanf("%i", &n);
	assert(n > 0);

	for(i=1; i<=n; i++)
    {
		fprintf(stdout, "valoarea de inserat: "); scanf("%i", &val);
		ins_nod(&r, val);	/* vlad: each node is a leaf */
    }

	/* tree traversals */
	puts("");
	fprintf(stdout, "Arborele contine urmatoarele noduri (valori): (inorder)\n");
	inOrder(r);

	puts("");
	fprintf(stdout, "Arborele contine urmatoarele noduri (valori): (preorder)\n");
	preOrder(r);

	puts("");
	fprintf(stdout, "Arborele contine urmatoarele noduri (valori): (postorder)\n");
	postOrder(r);

	puts("");	/* newline, given the actual display style (I have no newline between the traversals */
	left_height = right_height = 0;
	fprintf(stdout, "The tree's height is (before deletion): %d\n", tree_height(&r, &left_height, &right_height));
	fprintf(stdout, "Left height: %i, right height: %i\n", left_height, right_height);

	/* is it a balanced tree? */
	puts("");
	fprintf(stdout, "Is balanced? %s \n", isBalanced(&r, left_height, right_height)?"Yes":"No");

	/* tree deletions (not all nodes) */
	for(i=1; i<n; i++)
	{
		puts("");
		do
		{
			fprintf(stdout, "valoarea de sters "); scanf("%i", &val);
			if( (ret_delete = del_nod(&r, val)) == FALSE ) fprintf(stdout, "Nod inexistent! Nu pot sterge...\n");
		} while( ret_delete == FALSE );
	
	 	fprintf(stdout, "Dupa stergere (inorder):\n");
		inOrder(r);

		/* vlad: compute tree's height after deletion */
		puts("");
		left_height = right_height = 0;
		fprintf(stdout, "The tree's height is (after deletion): %d\n", tree_height(&r, &left_height, &right_height));
		fprintf(stdout, "Left height: %i, right height: %i\n", left_height, right_height);
	}

#if 0
	puts("");
	do
	{
		fprintf(stdout, "valoarea de sters "); scanf("%i", &val);
		if( (ret_delete = del_nod(&r,val)) == FALSE ) fprintf(stdout, "Nod inexistent! Nu pot sterge...\n");
	} while( ret_delete == FALSE );

 	fprintf(stdout, "Dupa stergere (inorder):\n");
	inOrder(r);




	/* is it a balanced tree? */
	puts("");
	fprintf(stdout, "Is balanced? %s \n", isBalanced(&r, left_height, right_height)?"Yes":"No");
#endif

	fflush(stdin);
	return 0;
}
