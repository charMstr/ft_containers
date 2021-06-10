/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_del_range.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:33:16 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/14 00:10:30 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rb_tree.h"

/*
** note:	This function is similar to the rb_tree_del() function. But it
**			will del from the red/black tree all the nodes whose item is
**			greater or equal to item_ref_min and lower or equal to
**			item_ref_max, according to the cmp function.
**
** note:	Refer to rb_tree_delone() if you want to delete only the first met
**			node.
**			Refer to rb_tree_del() if yo want to delete only one matching
**			node.
**
** note:	the del function will free the (void*)(node->item).
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
*/

void		rb_tree_del_range(t_rb_node **root, t_rb_tree_range *range, \
		int (*cmp)(void *, void *), void (*del)(void*))
{
	t_rb_node *del_me;

	if (!cmp || !del || !range || !root || !*root)
		return ;
	while ((del_me = rb_tree_getnode_range(root, range, cmp)))
	{
		del(del_me->item);
		free(del_me);
	}
}
