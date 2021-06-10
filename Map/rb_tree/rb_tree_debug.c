/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_debug.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:37:31 by charmstr          #+#    #+#             */
/*   Updated: 2020/01/30 15:57:52 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rb_tree.h"

/*
** note:	This debugging function will display the red/black tree in a tree
**			fashion. it is similar in all case to the rb_tree_debug() func.
**			RED nodes are displayed in red.
**
** note:	The custom display func takes care of displaying the item of a node
**			represented as a string of SIZE_LEAF_DEBUG characters maximum,
**			padded with whitespaces if necessary. If item is null: the leaf is
**			represented as "[null]"...
**
** note:	the define SIZE_LEAF_DEBUG shoud be used by the display func.
**			SIZE_LEAF_DEBUG should be an even number.
**
** note:	Every node is represented by:
**			- either whitespaces if NULL
**			- or between squarred brackets a string representing the item.
*/

/*
**	int	max;		//max depth of the rb_tree
**	int	current;	//current depth while recursing
**	int	bottom;		//current is trying to reach bottom while doing a bfs.
*/

typedef struct	s_depth
{
	int			max;
	int			current;
	int			bottom;
}				t_depth;

static	void	rb_tree_deb2(t_rb_node *node, t_depth depth, void (*display)())
{
	int	size_line;
	int	i;

	i = 0;
	size_line = (1 << (depth.max - ++depth.current)) * SIZE_LEAF_DEBUG;
	if (!node)
	{
		while (i++ < size_line)
			rb_tree_putchar_fd(' ', 1);
		return ;
	}
	if (depth.current == depth.bottom)
	{
		while (i++ < (size_line - SIZE_LEAF_DEBUG) / 2)
			rb_tree_putchar_fd(' ', 1);
		if (node->color == RB_RED)
			rb_tree_putstr_fd("\033[31m", 1);
		display(node->item);
		rb_tree_putstr_fd("\033[0m", 1);
		while (i++ <= (size_line - SIZE_LEAF_DEBUG))
			rb_tree_putchar_fd(' ', 1);
		return ;
	}
	rb_tree_deb2(node->left, depth, display);
	rb_tree_deb2(node->right, depth, display);
}

void	rb_tree_debug(t_rb_node *root, void (*display)())
{
	t_depth	depths;

	rb_tree_putstr_fd("\n===================================================="\
			"===========================\n====================== BTREE DEBUG "\
			"START ======================================\n", 1);
	if (root && display)
	{
		depths.max = rb_tree_depth((t_rb_node*)root);
		depths.current = 0;
		depths.bottom = 0;
		while (++depths.bottom <= depths.max)
		{
			rb_tree_deb2(root, depths, display);
			rb_tree_putchar_fd('\n', 1);
		}
	}
	else
		rb_tree_putstr_fd("NULL ROOT, or NULL display func\n", 1);
	rb_tree_putstr_fd("\n============================== DEBUG END ==========="\
			"===========================\n==================================="\
			"============================================\n\n\n", 1);
}
