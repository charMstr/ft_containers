/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:33:16 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/14 00:10:30 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rb_tree.h"

/*
** note:	this function will give the total number of nodes in the rb_tree.
**
** RETURN:	0 the tree is NULL
**			1 or more.
*/

static void	rb_tree_size_assist(t_rb_node *root, int *size);

int			rb_tree_size(t_rb_node *root)
{
	int size;

	size = 1;
	if (!root)
		return (0);
	rb_tree_size_assist(root->left, &size);
	rb_tree_size_assist(root->right, &size);
	return (size);
}

static void	rb_tree_size_assist(t_rb_node *root, int *size)
{
	if (!root)
		return ;
	(*size)++;
	rb_tree_size_assist(root->left, size);
	rb_tree_size_assist(root->right, size);
}
