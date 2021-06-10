/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_getnode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:33:16 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/14 00:10:30 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rb_tree.h"

static t_rb_node	*rb_tree_getnode_assist(t_rb_node **root, \
		t_rb_node *current, void *item_ref, int (*cmp)(void *, void *));
static void	rb_tree_getnode_either_is_red(t_rb_node **root, \
		t_rb_node *current);
static t_rb_node *rb_tree_getnode_two_child(t_rb_node **root, \
		t_rb_node *current);

/*
** note:	this function will extract any node in the red/black tree whose
**			item is matching the item_ref, according to the cmp function.
**
** note:	the nodes->color is reset to red. and all its relatives to NULL.
**
** note:	if item_ref is NULL, then the first node w/ a node->item NULL will
**			be extracted/returned.
**
** note:	Cumstom function cmp has a similar behavior to ft_strcmp().
**			It is the exact same cmp function used with rb_tree_del,
**			rb_tree_getnode(), rb_btree_add() and rb_tree_find().
**			versions. It has to handle te case of NULL input, returning 0 if
**			both inputs are NULL. or > 0  if the new_item , and < 0 if the
**			current tree_item is NULL so that we keep null at the far right.
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

t_rb_node			*rb_tree_getnode(t_rb_node **root, void *item_ref, \
		int (*cmp)(void *, void *))
{
	t_rb_node *extracted;

	if (!root || !*root || !cmp)
		return (NULL);
	extracted = rb_tree_getnode_assist(root, *root, item_ref, cmp);
	if (extracted)
	{
		extracted->color = RB_RED;
		extracted->parent = NULL;
		extracted->left = NULL;
		extracted->right = NULL;
	}
	return (extracted);
}

/*
** note:	this function is there so that we can recurse without never
**			modifying the address of root
*/

static t_rb_node	*rb_tree_getnode_assist(t_rb_node **root, \
		t_rb_node *current, void *item_ref, int (*cmp)(void *, void *))
{
	t_rb_node	*res;

	if (!*root || !current)
		return (NULL);
	if (!cmp(item_ref , current->item))
	{
		res = current;
		if (current->left && current->right)
			res = rb_tree_getnode_two_child(root, current);
		else if (current->color == RB_RED || current->right || current->left)
			rb_tree_getnode_either_is_red(root, current);
		else if (!current->parent)
			*root = NULL;
		else
			rb_tree_get_balance(root, current, 1);
		return (res);
	}
	if (!(res = rb_tree_getnode_assist(root, current->left, item_ref, cmp)))
		res = rb_tree_getnode_assist(root, current->right, item_ref, cmp);
	return (res);
}

/*
** note:	this function is called in the case: either the node to be
**			extracted is red, or its children is red.
*/

static void	rb_tree_getnode_either_is_red(t_rb_node **root, \
		t_rb_node *current)
{
	t_rb_node *red_child;

	red_child = current->left;
	if (!red_child)
		red_child = current->right;
	if (current == *root)
		*root = red_child;
	if (current->parent && current->parent->right == current)
		current->parent->right = red_child;
	else if (current->parent && current->parent->left == current)
		current->parent->left = red_child;
	if (red_child)
	{
		red_child->parent = current->parent;
		red_child->color = RB_BLACK;
	}
}

/*
** note:	this function is called when we need to get a node that has two
**			children. That node is not extracted effectively, its item is first
**			swapped with another item. The new item is found in the
**		 	left-most node from the right branch. That node is then extracted
**			effectively (now containing the item we wanted to delete).
*/

static t_rb_node *rb_tree_getnode_two_child(t_rb_node **root, \
		t_rb_node *current)
{
	void		*get_me_item;
	t_rb_node	*get_me_node;

	get_me_node = current;
	get_me_item = current->item;
	get_me_node = get_me_node->right;
	while (get_me_node->left)
		get_me_node = get_me_node->left;
	current->item = get_me_node->item;
	get_me_node->item = get_me_item;
	if (get_me_node->color == RB_RED || get_me_node->right \
			|| get_me_node->left)
		rb_tree_getnode_either_is_red(root, get_me_node);
	else
		rb_tree_get_balance(root, get_me_node, 1);
	return (get_me_node);
}
