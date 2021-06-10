/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_black_height.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:33:16 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/14 00:10:30 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rb_tree.h"

/*
** note:	this function will check that the black_height is even across the
**			red/black rb_tree.
** note:	while counting the black height from a given root node, the given
**			node is not included in the count.
**
** RETURN:	1 OK
**			0 KO
*/

static int	rb_tree_black_height_assist(t_rb_node *root, int ref, int count);

int			rb_tree_black_height(t_rb_node *root)
{
	int			left_height;
	t_rb_node	*root_copy;

	root_copy = root;
	if (!root)
		return (1);
	left_height = 0;
	while (root)
	{
		root = root->left;
		if (!root || root->color == RB_BLACK)
			left_height++;
	}
	if (!rb_tree_black_height_assist(root_copy->left, left_height, 0))
		return (0);
	return (rb_tree_black_height_assist(root_copy->right, left_height, 0));
}

static int	rb_tree_black_height_assist(t_rb_node *root, int ref, int count)
{
	if (!root)
	{
		count++;
		if (count == ref)
			return (1);
		return (0);
	}
	if (root->color == RB_BLACK)
		count++;
	if (!rb_tree_black_height_assist(root->left, ref, count))
		return (0);
	return (rb_tree_black_height_assist(root->right, ref, count));
}
