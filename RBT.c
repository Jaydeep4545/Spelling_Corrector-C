#include "dic.h"

node initilize(node p, valueType v)
{

	node tree = (node)malloc(sizeof(struct Node));
	tree->left = tree->right = NULL;
	tree->parent = p;
	tree->value = v;
	tree->color = RED;
	return tree;
}
node grandparent(node n)
{
	if (n == NULL || n->parent == NULL)
		return NULL;
	return n->parent->parent;
}
node uncle(node n)
{
	node g = grandparent(n);
	if (n == NULL || g == NULL)
		return NULL;
	if (n->parent == g->left)
		return g->right;
	else
		return g->left;
}
node sibling(node n)
{
	if (n == n->parent->left)
		return n->parent->right;
	else
		return n->parent->left;
}
int colorOf(node n)
{
	return n == NULL ? BLACK : n->color;
}
void insertNode(tree root, valueType v)
{

	node y = NULL, z, x;				/*y will be the parent to "adopt" z*/
										/*z is the new node with the key v*/
	x=(*root);									/*x is the root*/

	while(x!=NULL)
		{		
		y = x;
		if(v < x->value)
			x = x->left;
		else
			x = x ->right;
		}
		z = initilize(y, v);
		
	if (y == NULL)
		(*root) = z;
		else
			{
			if(z->value < y->value)
				y->left = z;
			else y->right = z;
			}
			
	insertUtil(root,z);					/*RB-Insert Fix-Up*/
	
		while(z->parent != NULL)			/*updating the root*/
			z= z->parent;
		(*root) = z;

}/*end of insert*/

void insertUtil(tree root,node n)
{
	node u = uncle(n), g = grandparent(n), p = n->parent;
	if (n->parent == NULL)			/*root*/
		{
		n->color = BLACK;
		return;
		}
	else
	{
	while (n->parent->color == RED)		/*we will act only if parent is red**/
	{
	u = uncle(n), g = grandparent(n), p = n->parent;
	if(p==g->left)
   	   {
	    if(u != NULL && u->color == RED) 	/*CASE 1: if uncle is red*/
		{
			p->color = BLACK;
			u->color = BLACK;
			g->color = RED;
	
			n = g;				/*and up to fix grandfather*/
		}
		else
			{
			 if (n == p->right)			/*CASE 2 - and right uncle*/
				{
					n = p;
					leftRotate(root,n);	
				}
			g = grandparent(n);					/*CASE 2+3*/
			p = n->parent;

			p->color = BLACK;
			g->color = RED;
			rightRotate(root,g);
			}
	}
	else if (p == g->right)
	{
	 if(u != NULL && u->color == RED) 	/*CASE 1: if uncle is red*/
		{
			p->color = BLACK;
			u->color = BLACK;
			g->color = RED;
	
			insertUtil(root,g);				/*and up to fix grandfather*/
		}
		else
			{
			 if (n == p->left)			/*CASE 2 - and left uncle*/
				{
					n = p;
					rightRotate(root,n);
				}
			g = grandparent(n);					/*CASE 2+3*/
			p = n->parent;

			p->color = BLACK;
			g->color = RED;
			leftRotate(root, g);
			}
	  }
	 }
	}	

	(*root)->color=BLACK;				/*coloring the root as black*/
		
	
}
void replaceNode(tree t, node o, node n)
{
	if (o->parent == NULL)
		*t = n;
	else
	{
		if (o == o->parent->left)
			o->parent->left = n;
		else
			o->parent->right = n;
	}

	if (n != NULL)
		n->parent = o->parent;
}
void removeNode(tree root, valueType v)
{
	node z = treeSearch((*root), v);

	node y = NULL, x = NULL;

	if (z == NULL)
		return;
	if (z->left == NULL || z->right == NULL)
		y = z;
	else y = treeSeccessor(z);

	if(y->left !=NULL)
		x = y->left;
		else x = y->right;

if(x!=NULL)
		x->parent = y->parent;

	if (y->parent == NULL)
		(*root) = x;
		else {
				if(y == y->parent->left)
				y->parent->left = x;
				else y->parent->right =x;
			 }

	if(y!=z)
		z->value = y->value;

	if(y->color == BLACK && x !=NULL)
		removeUtil(root,x);

		
	free(y);
}
void removeUtil(tree root, node x)
{
	
	node w = NULL;
	
	while( x != (*root) && x->color == BLACK)
	{
		if( x == x->parent->left)
			{
			w = x->parent->right;
			if(w->color == RED)						/*CASE 1*/
				{
				w->color = BLACK;			
				x->parent->color = RED;
				leftRotate(root,x->parent);
				w = x->parent->right;
				}

			if( (w->left ==NULL && w->right==NULL) || (w->left->color == BLACK && w->right->color == BLACK) )   /*CASE 2*/
				{
				w->color = RED;
				x = x->parent;
				}
			else
				{
				 if(w->right->color == BLACK)		/*CASE 3*/
					{
					w->left->color = BLACK;
					w->color = RED;
					rightRotate(root,w);
					w = x->parent->right;
					}
				w->color = x->parent->color;		/*CASE 4*/
				x->parent->color = BLACK;
				w->right->color = BLACK;
				leftRotate(root,x->parent);
				x = (*root);
				}
			}
			else			/*same with "right" and "left" exchanged*/
				{
				w= x->parent->left;
				if(w->color == RED)						/*CASE 1*/
					{
					w->color = BLACK;			
					x->parent->color = RED;
					rightRotate(root,x->parent);
					w = x->parent->left;
					}
				if( (w->left ==NULL && w->right==NULL) || (w->left->color == BLACK && w->right->color == BLACK) )   /*CASE 2*/	
					{
					w->color = RED;
					x = x->parent;
					}
				else
					{
					 if(w->left->color == BLACK)		/*CASE 3*/
						{
						w->right->color = BLACK;
						w->color = RED;
						leftRotate(root,w);
						w = x->parent->left;
						}
					w->color = x->parent->color;		/*CASE 4*/
					x->parent->color = BLACK;
					w->left->color = BLACK;
					rightRotate(root,x->parent);
					x = (*root);
					}
				}
			
		}
	x->color = BLACK;
}/*end of removeutil*/

void rightRotate(tree root, node x)
{
	node y = x->left;		/*set y*/

	x->left = y->right;		/*turn y's right subtree into x's right subtree*/
	
	if (y->right != NULL)
		y->right->parent = x;
	
	y->parent = x->parent;		/*link x parent to y*/

	if (x->parent == NULL)
		(*root) = y;
	else
		{
		if (x->parent->right == x)
			x->parent->right = y;
		else
			x->parent->left = y;
		}
		
	y->right = x;				/*put x on y's right*/
	x->parent = y;
	
	printf(" (Rotation right) ");
}
void leftRotate(tree root,node x)
{
	node y = x->right;		/*set y*/

	x->right = y->left;		/*turn y's left subtree into x's right subtree*/
	
	if (y->left != NULL)
		y->left->parent = x;
	
	y->parent = x->parent;		/*link x parent to y*/

	if (x->parent == NULL)
		(*root) = y;
	else
		{
		if (x->parent->left == x)
			x->parent->left = y;
		else
			x->parent->right = y;
		}
		
	y->left = x;				/*put x on y's left*/
	x->parent = y;
	
	printf(" (Rotation left) ");
}

node treeSearch(node x, valueType k)
{

	if( x==NULL || k == x->value)
		return x;
	if( k < x->value && x->left!=NULL)
		return treeSearch(x->left,k);
	else if( k >= x->value && x->right!=NULL)
		 return treeSearch(x->right,k);
	else return NULL;
}

node treeSeccessor(node x)
{
 
 node y=NULL;

 if(x->right!=NULL)
	 return treeMinimum(x->right);
 y = x->parent;
 while(y!=NULL && x==y->right)
 	{
 	x=y;
 	y=y->parent;
 	}
 return y;
}

node treeMinimum(node x)
{
 while(x->left!=NULL)
 	x= x->left;
 	
 return x;
}

void printNode(node n)
{
	char str[WORD_LENGTH];
	value2string26base(n->value,str);
	printf("%s\n",str);
	printf("%.0f(%s)\n\n", n->value, (n->color == BLACK ? "b" : "r"));
	
}
void inorderIterator(node n, void(*func)(node))
{
	if (n == NULL)
		return;
	inorderIterator(n->left, func);
	func(n);
	inorderIterator(n->right, func);
}

void preorderIterator(node n, void(*func)(node))
{
	if (n == NULL)
		return;
	func(n);
	preorderIterator(n->left, func);
	preorderIterator(n->right, func);
}
void inorderPrint(tree t)
{
	inorderIterator(*t, printNode);
	printf("\n");
}


void preorderPrint(tree t)
{
	preorderIterator(*t, printNode);
	printf("\n");
}


void destroy(node tree)
{
	if (tree == NULL)
		return;
	destroy(tree->left);
	destroy(tree->right);
	free(tree);
}


