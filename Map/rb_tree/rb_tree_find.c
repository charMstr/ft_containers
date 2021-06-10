/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_find.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:33:16 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/14 00:10:30 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rb_tree.h"

/*
** note:	this function will return the adress of the first item within a
**			node that we  meet while browsing in a dfs infix manner.
**
** note:	we return straight away if we are looking for node->item == NULL,
**			because there is no point.
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

 void	*rb_tree_find(t_rb_node *root, void *item_ref, int (*cmp)(void *, void *))
{
	void	*res;

	if (!root || !cmp || !item_ref)
		return (NULL);
	if (!cmp(item_ref, root->item))
		return (root->item);
	if (!(res = rb_tree_find(root->left, item_ref, cmp)))
		res = rb_tree_find(root->right, item_ref, cmp);
	return (res);
}
