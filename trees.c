#include "ft_ls.h"

t_tree  *create_node(char *s)
{
    t_tree *node;
    if(!(node = (t_tree *)malloc(sizeof(t_tree))))
        return(0);
    node->name = strdup(s);
    node->cpt = 0;
    node->left = NULL;
    node->right= NULL;

}

void build_tree(t_ls *ls, char *s)
{

}