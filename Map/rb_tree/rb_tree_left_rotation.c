/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_left_rotation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:33:16 by charmstr          #+#    #+#             */
/*   Updated: 2021/06/09 23:34:07 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rb_tree.h"

/*
** note:	This function operates a left rotation on a given node.
**			The root goes left and down, while the root->right child becomes
**			new_root. If the root->right had a left child, it gets swaped to
**			the other side, and becomes the right child of the new_root->left.
**
**	note:	the rotation is not performed if the root->right child is NULL.
*/

void	rb_tree_left_rotation(t_rb_node **root)
{
	t_rb_node *new_root;

	if (!root || !*root || !(*root)->right)
		return ;
	new_root = (*root)->right;
	new_root->parent = (*root)->parent;
	(*root)->parent = new_root;
	(*root)->right = new_root->left;
	if (new_root->left)
		new_root->left->parent = *root;
	new_root->left = *root;
	*root = new_root;
}
