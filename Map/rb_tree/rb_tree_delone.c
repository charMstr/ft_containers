/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_delone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:33:16 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/14 00:10:30 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rb_tree.h"

/*
** note:	this function will delete first met node in the red/black tree,
**			whose item is matching the item_ref, according to the cmp function.
**			Refer to rb_tree_del() if you want to delete all the matching
**			nodes at once.
**
** note:	if item_ref is NULL, then the first NULL node->item should be
**			deleted.
**
** note:	the del function will free the (void*)(node->item).
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

void		rb_tree_delone(t_rb_node **root, void *item_ref, \
		int (*cmp)(void *, void *), void (*del)(void*))
{
	t_rb_node *del_me;

	del_me = rb_tree_getnode(root, item_ref, cmp);
	if (!del_me)
		return ;
	del(del_me->item);
	free(del_me);
}
