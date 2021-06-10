/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:33:16 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/14 00:10:30 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rb_tree.h"

/*
** note:	this function will creat a new node. and place item in it. the node
**			is of type red_black. its color is RB_RED.
**
** return:	NULL if malloc failed
**			new node ptr
*/

t_rb_node	*rb_tree_new(void *item)
{
	t_rb_node	*new;

	if (!(new = (t_rb_node*)malloc(sizeof(t_rb_node))))
		return NULL;
	new->parent = NULL;
	new->left = NULL;
	new->right = NULL;
	new->item = item;
	new->color = RB_RED;
	return (new);
}
