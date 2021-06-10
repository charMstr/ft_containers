/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_dup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 18:33:16 by charmstr          #+#    #+#             */
/*   Updated: 2019/11/14 00:10:30 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rb_tree.h"

static int			rb_tree_dup_left(t_rb_node *old, t_rb_node *parent,
		void *(*dup_item)(void *), void (*del)(void *));
static int			rb_tree_dup_right(t_rb_node *old, t_rb_node *parent,
		void *(*dup_item)(void *), void (*del)(void *));
static t_rb_node	*rb_tree_dup_node(t_rb_node *ref, t_rb_node *parent,
		void *(*dup_item)(void *), void (*del)(void *));

/*
** note:	This function will make a perfect duplicate of the red/black tree.
**			the node->item are dynamically duplicated, and inserted in the
**			exact same position within newly created nodes.
**
** note:	this functionn will apply a callback func to every node->item in
**			order to duplicate it. Browsing is infix first so that we can
**			free the copy_tree in case of failure along way.
**
** RETURN:	new_tree root ptr.
**			NULL failure memory allocation, or wrong inputs
*/

t_rb_node			*rb_tree_dup(t_rb_node *root, void *(*dup_item)(void *), \
		void (*del)(void *))
{
	t_rb_node	*new_tree;
	int			res;

	res = 1;
	if (!root || !del ||  !dup_item)
		return (NULL);
	if (!(new_tree = rb_tree_dup_node(root, NULL, dup_item, del)))
		return (NULL);
	if ((res = rb_tree_dup_left(root->left, new_tree, dup_item, del)))
		res = rb_tree_dup_right(root->right, new_tree, dup_item, del);
	if (!res)
		rb_tree_clear(&new_tree, del);
	return (new_tree);
}

/*
** note:	this function will creat the new node, it will duplicate the
**			current_node->item. place intro new_node: the item, the color, the
**			parent.
**
** note:	if the ref_node contains a null item. we carry on as our red/black
**			tree supports nodes containing NULL items. but they will need to
**			be cleaned with the rb_tree_del eventually.
**
** RETURN:	new_node
**			NULL if failure, or NULL ref_node
*/

static t_rb_node	*rb_tree_dup_node(t_rb_node *ref, t_rb_node *parent,
		void *(*dup_item)(void *), void (*del)(void *))
{
	t_rb_node	*new_node;
	void		*new_item;

	if (!ref)
		return (NULL);
	if (!ref->item)
		new_item = NULL;
	else if (!(new_item = dup_item(ref->item)))
		return (NULL);
	if (!(new_node = rb_tree_new(new_item)))
	{
		del(new_item);
		return (NULL);
	}
	new_node->parent = parent;
	new_node->color = ref->color;
	return (new_node);
}

/*
** note:	This function is called when we go to to left of the current node
**			in the old tree. We browse the existing node level in an infix
**			order, allowing us to malloc a new duplicated node when necessary,
**			while still be able to abort and free the new tree in case of
**			failure.
**
** RETURN:	1 ok
**			failure need to del the created duplicat.
*/

static int			rb_tree_dup_left(t_rb_node *old, t_rb_node *parent,
		void *(*dup_item)(void *), void (*del)(void *))
{
	int			res;
	t_rb_node	*new_node;

	if (!old)
		return (1);
	if (!(new_node = rb_tree_dup_node(old, parent, dup_item, del)))
		return (0);
	parent->left = new_node;
	new_node->parent = parent;
	if ((res = rb_tree_dup_left(old->left, new_node, dup_item, del)))
		res = rb_tree_dup_right(old->right, new_node, dup_item, del);
	return (res);
}

/*
** note:	as above  but going to the right.
**
** RETURN:	1 ok
**			failure need to del the created duplicat.
*/

static int			rb_tree_dup_right(t_rb_node *old, t_rb_node *parent,
		void *(*dup_item)(void *), void (*del)(void *))
{
	int			res;
	t_rb_node	*new_node;

	if (!old)
		return (1);
	if (!(new_node = rb_tree_dup_node(old, parent, dup_item, del)))
		return (0);
	parent->right = new_node;
	new_node->parent = parent;
	if ((res = rb_tree_dup_left(old->left, new_node, dup_item, del)))
		res = rb_tree_dup_right(old->right, new_node, dup_item, del);
	return (res);
}
