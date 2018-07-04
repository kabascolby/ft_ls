#include "ft_ls.h"

t_tree	*create_node(char *s)
{
	t_tree	*node;

	if (!(node = (t_tree *)malloc(sizeof(t_tree))))
		return(0);
	node->data = strdup(s);
	node->cpt = 0;
	node->left = NULL;
	node->right= NULL;
	return (node);
}

void	insert_tree(t_tree *r, char *s)
{
	if (r == NULL)
		r = create_node(s);
	else if (ft_strcmp(r->data, s) <= 0)
		insert_tree(r->left, s);
	else
		insert_tree(r->right, s);
}

void traverse_dir(void (*flags[])(char *s)
{
	printf("i'm here");
}

void inorder_print(t_tree *r)
{
	if	(!r)
		return;
	inorder_print(r->left);
	printf("%s\n",r->data);
	inorder_print(r->right);
}