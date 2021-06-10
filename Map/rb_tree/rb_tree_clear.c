/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_clear.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:33:16 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/14 00:10:30 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rb_tree.h"

/*
** note:	this function will free the complete rb_tree from the given root
**			node.
**
** note:	the del func will have to free the node->item.
*/

void	 rb_tree_clear(t_rb_node **root, void (*del)(void*))
{
	if (!root || !*root || !del)
		return ;
	rb_tree_clear(&(*root)->left, del);
	rb_tree_clear(&(*root)->right, del);
	del((*root)->item);
	free(*root);
	*root = NULL;
}
