/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_apply_range.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:33:16 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/14 00:10:30 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rb_tree.h"

/*
** note:	this functionn will apply a callback func to every item of a
**			red/black tree node that is superior or equal to item_ref_min, and
**			inferior or equal to item_ref_max, according to cmp func.
**			browsing is preorder(first is root, then left, then right).
**
** note:	if the rb_tree_apply_preorder returns zero (fail), it means allong
**			the way it stoped applying the function onto the node->items of the
**			red/black tree. all the nodes extracted into the subtree are still
**			reinserted into the root tree and it is the responsability of the
**			the user to exit/free the root tree.
**
** note:	Cumstom function cmp has a similar behavior to ft_strcmp().
**			It is the exact same cmp function used with rb_tree_del,
**			rb_tree_getnode(), rb_tree_add() and rb_tree_find().
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
**
** note:	In our case setting item_ref_max to NULL will include the nodes
**			from item_ref_min up to NULL items as well.
**			setting item_ref_min to NULL will include only nodes containing
**			NULL->items.
**
** RETURN:	1 if ok
**			0 if failure in callback function. or NULL function pointer.
*/

int			rb_tree_apply_range(t_rb_node **root, t_rb_tree_range *range, \
		int (*cmp)(void *, void *), int (*applyf)(void *))
{
	t_rb_node *subtree;
	t_rb_node *extracted;
	int res;

	if (!range || !cmp || !applyf)
		return (0);
	subtree = NULL;
	while ((extracted = rb_tree_getnode_range(root, range, cmp)))
		rb_tree_add(&subtree, extracted, cmp);
	if (!subtree)
		return (1);
	res = rb_tree_apply_preorder(subtree, applyf);
	while (subtree && (extracted = rb_tree_getnode(&subtree, \
			subtree->item, cmp)))
	{
		rb_tree_add(root, extracted, cmp);
	}
	return (res);
}
