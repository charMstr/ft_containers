/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_make_item_uniq.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:33:16 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/14 00:10:30 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rb_tree.h"

/*
** note:	this function makes sure there is no more that one node
**			containing an item macthing item_ref in the tree, according
**			to cmp function. If there is more than one. del will remove
**			node->item. and node will be freed.
**
**	note:	refer to rb_tree_uniq() if you want to do the same operation
**			in a normal binary search tree (non red/black).
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

void	rb_tree_make_item_uniq(t_rb_node **root, void *item_ref, \
		int (*cmp)(void *, void *), void (*del)(void*))
{
	t_rb_node *uniq;

	if (!cmp || !del || !root || !*root)
		return ;
	uniq = rb_tree_getnode(root, item_ref, cmp);
	if (!uniq)
		return ;
	rb_tree_del(root, item_ref, cmp, del);
	rb_tree_add(root, uniq, cmp);
}
