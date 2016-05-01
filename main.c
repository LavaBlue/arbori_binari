#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "binary_trees.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main()
{
	int i, n, val;
	int left_height, right_height;
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

	/* tree deletions (not all nodes) */
	fprintf(stdout, "valoarea de sters "); scanf("%i", &val);
	del_nod(&r,val);

	fprintf(stdout, "valoarea de sters "); scanf("%i", &val);
	del_nod(&r,val);

 	fprintf(stdout, "Dupa stergere am urmatoarele noduri (valori): (inorder)\n");
	inOrder(r);

	/* vlad: compute tree's height after deletion */
	puts("");
	left_height = right_height = 0;
	fprintf(stdout, "The tree's height is (after deletion): %d\n", tree_height(&r, &left_height, &right_height));
	fprintf(stdout, "Left height: %i, right height: %i\n", left_height, right_height);

	fflush(stdin);
	return 0;
}
