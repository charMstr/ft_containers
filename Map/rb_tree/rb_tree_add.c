/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:33:16 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/14 00:10:30 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rb_tree.h"

static void	rb_tree_add_assist(t_rb_node **root, t_rb_node **current, \
		t_rb_node *node, int (*cmp)(void *, void *));
static void	rb_tree_add_balance(t_rb_node **root, t_rb_node **current);
static void	rb_tree_add_balance_parent_is_left_child(t_rb_node **root, \
		t_rb_node **current, t_rb_node **grandpa);
static void	rb_tree_add_balance_parent_is_right_child(t_rb_node **root, \
		t_rb_node **current, t_rb_node **grandpa);

/*
** note:	this function will insert a new rb_node in the red/black tree.
**			The insertion's position is decided with the cmp function. For each
**			node, if cmp returns a negative value go left, if >= 0 go right.
**
** note:	node is a new node previously malloced w/ tb_tree_new().
**
** note:	Cumstom function cmp has a similar behavior to ft_strcmp().
**			It is the exact same cmp function used with rb_tree_del,
**			rb_tree_get(), rb_tree_add() and rb_tree_find().
**			It has to handle te case of NULL input, returning 0 if both inputs
**			are NULL. or > 0  if the new_item , and < 0 if the current
**			tree_item is NULL so that we keep null at the far right.
**
**			Therefore cmp's start should always look like this:
**			int	cmp_func(void *new_item, void *tree_item)
**			{
**				if (!new_item && !tree_item)
**					return (0);
**				if (!new_item)
**					return (1);
**				if (!tree_item)
**					return (-1);
**				...
*/

void		rb_tree_add(t_rb_node **root, t_rb_node *node, \
		int (*cmp)(void *, void *))
{
	if (!root || !cmp || !node)
		return;
	if (!*root)
	{
		*root = node;
		(*root)->color = RB_BLACK;
		return;
	}
	node->parent = *root;
	if (cmp(node->item, (*root)->item) < 0)
		rb_tree_add_assist(root, &(*root)->left, node , cmp);
	else
		rb_tree_add_assist(root, &(*root)->right, node , cmp);
}

static void	rb_tree_add_assist(t_rb_node **root, t_rb_node **current, \
		t_rb_node *node, int (*cmp)(void *, void *))
{
	if (!*current)
	{
		*current = node;
		rb_tree_add_balance(root, current);
		return;
	}
	node->parent = *current;
	if (cmp(node->item, (*current)->item) < 0)
		rb_tree_add_assist(root, &(*current)->left, node , cmp);
	else
		rb_tree_add_assist(root, &(*current)->right, node , cmp);

}


/*
** note:	this red/black tree function is called the first time we insert a
**			node that is not the very root node.
**
** note:	this function dispatches the work between the case where the parent
**			is a left child of the grandparent, or is a right child of the
**			grandparent. There is no need to go further if there is no parent
**			or grandparent.
**
** note:	root is the root's real address and is always passed on through
**			recursion.
*/

static void	rb_tree_add_balance(t_rb_node **root, t_rb_node **current)
{
	t_rb_node **grandpa;

	if (!(*current)->parent)
	{
		(*current)->color = RB_BLACK;
		return ;
	}
	if (!(((*current)->parent->color) == RB_RED) || !(*current)->parent->parent)
		return ;
	if (!(*current)->parent->parent->parent)
		grandpa = root;
	else if ((*current)->parent->parent->parent->left == \
			(*current)->parent->parent)
		grandpa = &(*current)->parent->parent->parent->left;
	else
		grandpa = &(*current)->parent->parent->parent->right;
	if ((*grandpa)->left == (*current)->parent)
		rb_tree_add_balance_parent_is_left_child(root, current, grandpa);
	else
		rb_tree_add_balance_parent_is_right_child(root, current, grandpa);
}

/*
** note:	this function is called when the current node is red, and its
**			parent is red as well, AND, the parent is the left child of the
**			existing grand parent.
**
** note:	First condition means the uncle is RED. We swap colors of parent,
**			uncle, grand-Parent and we reset the current root to grand-Parent.
*/

static void	rb_tree_add_balance_parent_is_left_child(t_rb_node **root, \
		t_rb_node **current, t_rb_node **grandpa)
{
	if ((*grandpa)->right && (*grandpa)->right->color == RB_RED)
	{
		(*current)->parent->color = RB_BLACK;
		(*grandpa)->right->color = RB_BLACK;
		(*grandpa)->color = RB_RED;
		rb_tree_add_balance(root, grandpa);
		return ;
	}
	if ((*current) == (*current)->parent->right)
	{
		rb_tree_left_rotation(&(*grandpa)->left);
		current = &(*grandpa)->left->left;
	}
	(*current)->parent->color = RB_BLACK;
	(*grandpa)->color = RB_RED;
	rb_tree_right_rotation(grandpa);
}

/*
** note:	this function is called when the current node is red, and its
**			parent is red as well, AND, the parent is the right child of the
**			existing grand parent.
**
** note:	First condition means the uncle is RED. we swap colors of parent,
**			uncle, grand-Parent and we reset the current root to grand-Parent.
*/

static void	rb_tree_add_balance_parent_is_right_child(t_rb_node **root, \
		t_rb_node **current, t_rb_node **grandpa)
{
	if ((*grandpa)->left && (*grandpa)->left->color == RB_RED)
	{
		(*current)->parent->color = RB_BLACK;
		(*grandpa)->left->color = RB_BLACK;
		(*grandpa)->color = RB_RED;
		rb_tree_add_balance(root, grandpa);
		return ;
	}
	if ((*current) == (*current)->parent->left)
	{
		rb_tree_right_rotation(&(*grandpa)->right);
		current = &(*grandpa)->right->right;
	}
	(*current)->parent->color = RB_BLACK;
	(*grandpa)->color = RB_RED;
	rb_tree_left_rotation(grandpa);
}
