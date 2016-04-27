#ifndef __BINARY_TREES_
#define __BINARY_TREES_

/* vlad: data types */
typedef enum {FALSE, TRUE} bool;

typedef struct Nod	
{
	int inf;		/* vlad: informatia */
	struct Nod *leg_st, *leg_dr;	/* vlad: referinte descendente */
} NOD;
typedef NOD *pNOD;		/* vlad: very similar with linked-lists */

/* vlad: functions' prototypes */
void ins_nod(pNOD*, int );
bool del_nod(pNOD*, int );

void inOrder(pNOD);
void preOrder(pNOD);
void postOrder(pNOD);

#endif
