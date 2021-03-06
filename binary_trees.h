#ifndef __BINARY_TREES_
#define __BINARY_TREES_

/* vlad: data types */
typedef enum {FALSE, TRUE} BOOL;

typedef struct Nod	
{
	int inf;		/* vlad: informatia */
	struct Nod *leg_st, *leg_dr;	/* vlad: referinte descendente */
} NOD;
typedef NOD *pNOD;		/* vlad: very similar with linked-lists */

/* vlad: functions' prototypes */
void ins_nod(pNOD*, int);
BOOL del_nod(pNOD*, int);
int tree_height( pNOD*, int*, int*);
BOOL isBalanced( pNOD*, int, int);

void inOrder(pNOD);
void preOrder(pNOD);
void postOrder(pNOD);

#endif
