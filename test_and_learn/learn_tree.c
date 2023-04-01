# include <stdio.h>
# include <stdlib.h>

typedef struct s_treenode {
    int                 value;
    struct s_treenode   *left;
    struct s_treenode   *right;
}   t_treenode;

t_treenode  *ft_create_node(int value)
{
    t_treenode *result;

    result = malloc(sizeof(t_treenode));
    if (!result)
        return (0);
    else
    {
        result->left = NULL;
        result->right = NULL;
        result->value = value;
    }
    return (result);
}

void    ft_print_tabs(int number)
{
    for (int i = 0;i < number; i++)
        printf("\t");
}

void    ft_print_tree_rec(t_treenode *root, int level)
{
    if (root == NULL)
    {
        ft_print_tabs(level);
        printf("----<empty>---\n");
        return ;
    }    
    ft_print_tabs(level);
    printf("value = %d\n", root->value);
    
    ft_print_tabs(level);
    printf("left\n");
    
    ft_print_tree_rec(root->left, level + 1);

    ft_print_tabs(level);
    printf("right\n");

    ft_print_tree_rec(root->right, level + 1);

    ft_print_tabs(level);
    printf("done\n");
}

void    ft_print_tree(t_treenode *root)
{
    ft_print_tree_rec(root, 0);
}

int main(void)
{
    t_treenode *n1 = ft_create_node(10);
    t_treenode *n2 = ft_create_node(20);
    t_treenode *n3 = ft_create_node(30);
    t_treenode *n4 = ft_create_node(40);
    t_treenode *n5 = ft_create_node(50);

    n1->left = n2;
    n1->right = n3;
    n3->left = n4;
    n3->right = n5;

    ft_print_tree(n1);

    free(n1);
    free(n2);
    free(n3);
    free(n4);
    free(n5);
}