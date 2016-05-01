#include "binary_trees.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* vlad: insertion and deletion functions */

/* programul va primi ca parametru numarul pe care trebuie sa îl adauge.
 * vlad: Algoritmul seamana cu 'sortarea prin interclasare': gasesc pozitia (locul) potrivita
 * unde urmeaza sa fac inserarea si stochez nodul in acea pozitie.
 * Surse bibliografice:
 * - Niklaus Wirth - Algo + data structures = programs
 * - http://software.ucv.ro/~cstoica/ISP/Lucrarea%209%20-%20arbori.pdf (!)
 * - http://infoscience.3x.ro/c++/stergere_abc.htm
 * - http://staff.cs.upt.ro/~chirila/teaching/upt/id21-aa/lectures/AA-ID-Cap08-2.pdf (!)
 * - http://andrei.clubcisco.ro/cursuri/1sd/curs/curs06.pdf
 */
void ins_nod(pNOD *pPrim, int val)
{ 
	pNOD nod1, nod2, nod3;		/* vlad: reference types, since I have to use the links */
   
	/* se creaza nodul care se adauga în arbore. */
	nod1 = (pNOD)malloc(sizeof(NOD));
	assert(nod1 != NULL);

	nod1->inf = val;		/* vlad: information stored in the node */

	/* deoarece o sa se adauge ca nod frunza(!) => nu va avea nici un copil, 
	 * deci legaturile stânga si dreapta vor fi nule
	 */
	nod1->leg_st = NULL;
	nod1->leg_dr = NULL; 

	/* verificam mai intai daca exista o radacina (daca arborele a fost creat) */
	if(*pPrim == NULL)
	{ 
		/* nu am mai introdus nimic pana acum => nodul creat va deveni radacina arborelui */
  		*pPrim = nod1; 
	} else {	/* Daca exista un nod radacina, inserarea în arbore se va face conform
	 			 * algoritmului prezentat la curs.
	 			 */
			nod2 = *pPrim;	/* vlad: plec din radacina */
			/* se va cauta locul de inserare al nodului 'nod1', pornind cautarea din
			 * radacina. 
			 * Nodul 'nod3' va reprezenta nodul parinte al nodului 'nod1'
			 */
			do {
	    		if (val < nod2->inf) {	/* vlad: avansez la stanga (daca: val < val_nod) */
			    	nod3 = nod2;		/* vlad: pastrez ultima legatura inainte de NULL */
			    	nod2 = nod2->leg_st;
				} else {	/* se merge spre dreapta (daca: val_de_inserat > val_nod) */
					nod3 = nod2;
					nod2 = nod2->leg_dr; 
				}/* end else */
			} while (nod2 != NULL); /* end do-while */
	
			/* dupa gasirea nodului parinte, se creaza legatura 
			 * nod3 (nod parinte) -> nod1 (nodul inserat acum)
			 */
			if (val < nod3->inf) 	/* vlad: should NOT be nod2 here... */
				/* se asaza in stânga parintelui */
		    	nod3->leg_st = nod1;
			else
				/* se asaza în dreapta parintelui */
		    	nod3->leg_dr = nod1; 
	}/* end else */

	return;
}

/* vlad: sterge nod si pastreaza caracteristicile unui arbore binar de cautare 
 * Pentru ca arborele sa-si pastreze proprietatile, la stergere trebuie avute in vedere 3 situatii:
 * Cazul I: nodul de sters NU are fiu stanga;
 * Cazul II: nodul de sters NU are fiu dreapta;
 * Cazul III: nodul de sters are ambii fii.
 *
 * Principiul este de a inlocui nodul sters cu 'valoarea nodului celui mai din stanga, al subarborelui sau drept'. Adica nodul cel mai mic din subarborele drept.
 * Tot un arbore binar de cautare este si atunci cand inlocuiesc nodul de sters cu valoarea maxima din subarborele stang.
 */
bool del_nod(pNOD *pPrim, int nr)
{ 
	pNOD tmp, tmp1, tmp2, min; 

	/* se porneste cautarea informatiei de sters din radacina */
	assert(*pPrim != NULL);		/* vlad: nu incerc sa parcurg un arbore vid => eroare dc primesc NULL! 
								 * if I ask for deletion of an unexistent node then this is an error! 
								 */

	tmp1 = *pPrim;		/* vlad: caut valoarea de sters; incep cu radacina */
	do {
		tmp = tmp1;
		if (tmp1->inf > nr) 
			tmp1 = tmp1->leg_st;	/* vlad: avansez pe subarbore stang */
		else 
			tmp1 = tmp1->leg_dr;	/* vlad: avansez pe subarbore drept */
	} while(tmp1 && tmp1->inf != nr);
	
	if(tmp1 == NULL) return FALSE;	/* vlad: no such node in the tree! */

	/* vlad: retin in tmp parintele nodului pe care urmeaza sa-l sterg */
	if( (tmp1->leg_dr == NULL) && (tmp1->leg_st == NULL) )	/* vlad: nod frunza */
	{
		if(tmp->leg_dr == tmp1) tmp->leg_dr = NULL;
		if(tmp->leg_st == tmp1) tmp->leg_st = NULL;
		free(tmp1);
		return TRUE;
	}

	if ((tmp1->leg_dr) == NULL)		/* cazul I: nu am fiu dreapta (dar am stanga) NU se poate altfel, pt ca sunt in arbore binar (!) Asadar am cel mult 2 noduri: 1 sau 2 */
	{
  		tmp1->inf		= tmp1->leg_st->inf;		/* mutare inf din nodul din st, in nodul curent */
  		tmp1->leg_st	= tmp1->leg_st->leg_st;		/* refacere legaturi */
		fprintf(stdout, "Cazul 1: am eliberat stanga\n");
  		free(tmp->leg_st);		/* vlad: eliberarea zonei de memorie */
	} else 	if (tmp1->leg_st == NULL) 	/* cazul II: nu am fiu stânga (dar am dreapta) */
			{ 
  				/* mutare inf din nodul din st, in nodul curent */
				tmp1->inf		= tmp1->leg_dr->inf;
				tmp1->leg_dr	= tmp1->leg_dr->leg_dr;
				fprintf(stdout, "Cazul 2: am eliberat dreapta\n");
				free(tmp->leg_dr);	/* vlad: eliberarea zonei de memorie */	
			}

	if( tmp1->leg_dr && tmp1->leg_st )		/* cazul III: amandoi fiii */
	{	
		/* mergem la copilul din dreapta: subarborele drept */
		min = tmp1->leg_dr;
		tmp2 = tmp1;	/* vlad: what if I don't enter the while below?
						 * Well, this statement will be valid afterward. I can take */
		/* cautam cel mai din stânga copil (din subarborele drept)
		 * Cum ziceam mai sus, o varianta echivalenta este: maximul din subarborele stang. 
		 * Se poate alege intre oricare din cele doua variante: structura de BST se pastreaza.
		 */
		while(min->leg_st != NULL)
		{ 
			tmp2 = min;			/* vlad: retin tatal nodului celui mai din stanga */
			min = min->leg_st;	/* vlad: nodul cel mai din stanga: nu are subarbore stang, are doar drept */
		};

		assert(min != NULL);	/* vlad: min este parintele ultimului nod frunza; tmp2 este parintele lui min */

		tmp1->inf	 = min->inf;	fprintf(stdout, "Noua informatie a nodului: %i\n", tmp1->inf);
		tmp2->leg_dr = NULL;	/* vlad: this is the most important note here! 
								 * I don't alter the left subtree (which I preserve). Since I've followed the right
								 * subtree, the left one should not be touched. 
								 * I will only alter the right one - and it disappears, here.
								 */
		fprintf(stdout, "Cazul 3: am eliberat nodul cerut \n");
		free(min);		/* vlad: eliberarea zonei de memorie */
	}	/* end: cazul III */

	return TRUE;
}


/* vlad: parcurgeri */

void inOrder(pNOD pRad)
{
	/* daca nu s-a ajuns la ultimul nod */ 
	if (pRad != NULL)
	{ 
		/* se viziteaza copilul din stânga */
 		inOrder(pRad->leg_st);

		/* se viziteaza radacina (aici la mijloc) */
		fprintf(stdout, "%d -> ", pRad->inf);

		/* se viziteaza copilul din dreapta */
		inOrder(pRad->leg_dr);
	}

	return;
}


void preOrder(pNOD pRad)
{ 
	/* Daca nu am arbore vid (la intrare) si daca nu s-a ajuns la ultimul nod (in timpul rularii) */
	if (pRad != NULL) 
	{ 
		/* se viziteaza radacina (aici prima) */
		fprintf(stdout, "%d -> ", pRad->inf);

		/* se viziteaza copilul din stânga, apoi cel din dreapta */
		preOrder(pRad->leg_st);
		preOrder(pRad->leg_dr);
	}

	return;
}


void postOrder(pNOD pRad)
{
	/* daca nu s-a ajuns la ultimul nod */ 
	if (pRad != NULL)
	{ 
		/* se viziteaza copilul din stânga, apoi cel din dreapta (this is the mandatory order */
 		postOrder(pRad->leg_st);
		postOrder(pRad->leg_dr);

		/* se viziteaza radacina (aici ultima) */
		fprintf(stdout, "%d -> ", pRad->inf);
	}

	return;
}

/* vlad: compute the height of a given node (if the input node is the root => compute the tree's height
 * The height esentially depends upon >the order< the input keys are feeded into this program (!)
 */
int tree_height(pNOD *pRoot, int *pHL, int *pHR)
{
	if(*pRoot == NULL )
		return 0;

	/* vlad: use this: height = 1 + max{height(root.left), height(root.right)} */
	return 1 + ( (*pHL = tree_height( &(*pRoot)->leg_st, pHL, pHR ) > (*pHR = tree_height( &(*pRoot)->leg_dr, pHL, pHR)) ) ? *pHL : *pHR);
}
