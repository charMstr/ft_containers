/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_apply_inorder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:33:16 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/14 00:10:30 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rb_tree.h"

/*
** note:	this function will apply a callback func to every item of a
**			rb_tree. Browsing is inorder(first is LEFT, then ROOT, then RIGHT).
**
** RETURN:	1 ok
**			something failed in the callback function.
*/

int	rb_tree_apply_inorder(t_rb_node *root, int (*applyf)(void *))
{
	if (root && !rb_tree_apply_inorder(root->left, applyf))
		return (0);
	if (root && !applyf(root->item))
		return (0);
	if (root && !rb_tree_apply_inorder(root->right, applyf))
		return (0);
	return (1);
}
