/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_gel_balance.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:33:16 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/14 00:10:30 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rb_tree.h"

typedef struct	s_balance
{
	t_rb_node	*parent;
	t_rb_node	*sibling;
	t_rb_node	**rotation_address;
	int			is_left_child;
}				t_balance;

static void	rb_tree_get_balance_case2(t_rb_node **root, t_balance *balance);
static void	rb_tree_get_balance_case3_4(t_rb_node **root, t_balance *balance);
static void	rb_tree_get_balance_case5(t_balance *balance);
static void	rb_tree_get_balance_case6(t_balance *balance);

/*
** note:	this function is called when assisting with extraction of a node
**			and should stay a private function. It will balance the trees in
**			the situation when the extraction leads to the appearance of a
**			"double black" node. It will try the six possible sequential
**			scenarios.
*/

void rb_tree_get_balance(t_rb_node **root, t_rb_node *current, int first_time)
{
	t_balance	balance;

	balance.is_left_child = 0;
	if (current == *root)
		return ;
	balance.sibling = current->parent->left;
	if (current->parent->left == current)
	{
		balance.is_left_child = 1;
		balance.sibling = current->parent->right;
	}
	if (first_time && balance.is_left_child)
		current->parent->left = NULL;
	else if (first_time)
		current->parent->right = NULL;
	balance.parent = current->parent;
	if (current->parent == *root)
		balance.rotation_address = root;
	else if (current->parent->parent->right == current->parent)
		balance.rotation_address = &current->parent->parent->right;
	else
		balance.rotation_address = &current->parent->parent->left;
	rb_tree_get_balance_case2(root, &balance);
}

/*
** note:	After checking that the current node was not the root node. We know
**			from this point that the node has a parent and a sibling.
**
** note:	We first treat the case when the sibling is red (case 2):
**				we swap the color between parent and sibling. and rotate parent
**				in the opposite direction of sibling (sibling goes up).
**
** note:	Then we check the scenarios when parent, sibling and sibling's
**			children are all black. If yes, we swap colors between parent, and
**			we move the problem up onto parent, recursing from the case1.
**			Else we move onto case 4.
*/

static void	rb_tree_get_balance_case2(t_rb_node **root, t_balance *balance)
{
	if (balance->sibling->color == RB_RED)
	{
		balance->parent->color = RB_RED;
		balance->sibling->color = RB_BLACK;
		if (balance->is_left_child)
		{
			balance->sibling = balance->sibling->left;
			rb_tree_left_rotation(balance->rotation_address);
			balance->rotation_address = &balance->parent->parent->left;
		}
		else
		{
			balance->sibling = balance->sibling->right;
			rb_tree_right_rotation(balance->rotation_address);
			balance->rotation_address = &balance->parent->parent->right;
		}
		if (balance->parent == *root)
			*root = balance->sibling;
	}
	rb_tree_get_balance_case3_4(root, balance);
}

/*
** note:	this function takes care of the case when the parent is red, the
**			sibling and its children are all black. If its the case, we swap
**			colors between parent and sibling and then it is over with
**			balancing. Otherwise, we move on to case 5.
*/

static void	rb_tree_get_balance_case3_4(t_rb_node **root, t_balance *balance)
{
	if (balance->parent->color == RB_BLACK \
			&& balance->sibling->color == RB_BLACK
			&& (!balance->sibling->right \
				|| balance->sibling->right->color == RB_BLACK)\
			&& (!balance->sibling->left \
				|| balance->sibling->left->color == RB_BLACK))
	{
		balance->sibling->color = RB_RED;
		return (rb_tree_get_balance(root, balance->parent, 0));
	}
	if ((!balance->sibling->right \
		|| balance->sibling->right->color == RB_BLACK) \
		&& (!balance->sibling->left \
		|| balance->sibling->left->color == RB_BLACK) \
		&& balance->parent->color == RB_RED)
	{
		balance->parent->color = RB_BLACK;
		balance->sibling->color = RB_RED;
		return ;
	}
	rb_tree_get_balance_case5(balance);
}

/*
** note:	this function tries the scenario when sibling is black and closest
**			nephew is red, whereas furthest nephew is black. And parent doesnt
**			not matter.
**			If this is the case, we swap color between closest sibling(becomes
**			black) and sibling (becomes red). and then do a rotation on sibling
**			that moves up closest sibling.
**			Then move on to case 6 anyway.
*/

static void	rb_tree_get_balance_case5(t_balance *balance)
{
	if (balance->is_left_child && balance->sibling->color == RB_BLACK &&
		(!balance->sibling->right \
		|| balance->sibling->right->color == RB_BLACK) \
		&& balance->sibling->left && balance->sibling->left->color == RB_RED)
	{
		balance->sibling->color = RB_RED;
		balance->sibling->left->color = RB_BLACK;
		balance->sibling = balance->sibling->left;
		rb_tree_right_rotation(&balance->parent->right);
	}
	else if (!balance->is_left_child \
		&& balance->sibling->color == RB_BLACK && (!balance->sibling->left \
		|| balance->sibling->left->color == RB_BLACK) \
		&& balance->sibling->right && balance->sibling->right->color == RB_RED)
	{
		balance->sibling->color = RB_RED;
		balance->sibling->right->color = RB_BLACK;
		balance->sibling = balance->sibling->right;
		rb_tree_left_rotation(&balance->parent->left);
	}
	rb_tree_get_balance_case6(balance);
}

/*
** note:	this is the final case of rebalancing tree while extracting a node.
**			It occurs when sibling is black. and furthest nephew is red.
**			This case is terminating.
**			Furthest nephew becomes red. Whatever parent's color, it is swapped
**			with sibling's color. then a rotation is done on parent so that
**			sibling goes up.
*/

static void	rb_tree_get_balance_case6(t_balance *balance)
{
	if (balance->sibling->color == RB_BLACK && \
			((!balance->is_left_child && balance->sibling->left \
			&& balance->sibling->left->color == RB_RED)\
		|| (balance->is_left_child && balance->sibling->right \
			&& balance->sibling->right->color == RB_RED)))
	{
		balance->parent->color ^= balance->sibling->color;
		balance->sibling->color ^= balance->parent->color;
		balance->parent->color ^= balance->sibling->color;
		if (balance->is_left_child)
		{
			balance->sibling->right->color = RB_BLACK;
			rb_tree_left_rotation(balance->rotation_address);
		}
		else
		{
			balance->sibling->left->color = RB_BLACK;
			rb_tree_right_rotation(balance->rotation_address);
		}
	}
}
