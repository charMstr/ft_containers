/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_right_rotation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:33:16 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/14 00:10:30 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rb_tree.h"

/*
** note:	This function operates a right rotation on a given node.
**			The root goes right and down, while the root->left child becomes
**			new_root. If the root->left had a right child, it gets swaped to
**			the other side, and becomes the left child of the new_root->right.
**
**	note:	the rotation is not performed if the root->right child is NULL.
*/

void	rb_tree_right_rotation(t_rb_node **root)
{
	t_rb_node *new_root;

	if (!root || !*root || !(*root)->left)
		return ;
	new_root = (*root)->left;
	new_root->parent = (*root)->parent;
	(*root)->parent = new_root;
	(*root)->left = new_root->right;
	if (new_root->right)
		new_root->right->parent = *root;
	new_root->right = *root;
	*root = new_root;
}
