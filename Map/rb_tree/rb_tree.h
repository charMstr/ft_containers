/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:37:31 by charmstr          #+#    #+#             */
/*   Updated: 2020/01/30 15:57:52 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_H
# define RB_TREE_H

# include <unistd.h>
# include <stdlib.h>

#define SIZE_LEAF_DEBUG 6

/*
** note:	this structure is used for the functions that work on ranges.
*/

typedef struct	s_rb_tree_range
{
	void		*item_ref_min;
	void		*item_ref_max;
}				t_rb_tree_range;

/*
** note:	this next structure is using the enum and implements a red/black
**			tree using the same functions as above (except for new, add, del,
**			get..) through polymorphism.
*/

typedef enum	e_rb_color
{
				RB_BLACK,
				RB_RED
}				t_rb_color;

typedef struct 	s_rb_node t_rb_node;
struct			s_rb_node
{
	t_rb_node	*parent;
	t_rb_node	*left;
	t_rb_node	*right;
	void		*item;
	t_rb_color	color;
};

/*
** debug functions
*/

void			rb_tree_putchar_fd(char c, int fd);
void			rb_tree_putstr_fd(char *s, int fd);
void			rb_tree_debug(t_rb_node *root, void (*display)());
int				rb_tree_black_height(t_rb_node *root);
int				rb_tree_depth(t_rb_node *root);

/*
** balancing functions.
*/

void			rb_tree_left_rotation(t_rb_node **root);
void			rb_tree_right_rotation(t_rb_node **root);
void			rb_tree_get_balance(t_rb_node **root, t_rb_node *current,\
			int first_time);

/*
** size of the btree
*/

int				rb_tree_size(t_rb_node *root);

/*
** adding nodes/creat tree.
*/

t_rb_node		*rb_tree_new(void *item);
void			rb_tree_add(t_rb_node **root, t_rb_node *node, \
			int (*cmp)(void *, void *));
t_rb_node		*rb_tree_dup(t_rb_node *root, void *(*dup_item)(void *), \
			void (*del)(void *));

/*
** deleting functions
*/

void			rb_tree_clear(t_rb_node **root, void (*del)(void*));
void			rb_tree_delone(t_rb_node **root, void *item_ref, \
			int (*cmp)(void *, void *), void (*del)(void*));
void			rb_tree_del(t_rb_node **root, void *item_ref, \
			int (*cmp)(void *, void *), void (*del)(void*));
void			rb_tree_del_range(t_rb_node **root, t_rb_tree_range *range, \
			int (*cmp)(void *, void *), void (*del)(void*));
void			rb_tree_make_item_uniq(t_rb_node **root, void *item_ref, \
			int (*cmp)(void *, void *), void (*del)(void*));
void			rb_tree_make_nodes_uniq(t_rb_node **root, \
			int (*cmp)(void *, void *), void (*del)(void *));

/*
** search / extract node(s).
*/

void			*rb_tree_find(t_rb_node *root, void *item_ref, \
			int (*cmp)(void *, void *));
t_rb_node		*rb_tree_getnode(t_rb_node **root, void *item_ref, \
			int (*cmp)(void *, void *));
t_rb_node		*rb_tree_getnode_range(t_rb_node **root, \
			t_rb_tree_range *range, int (*cmp)(void *, void *));

/*
** apply functions
*/

int				rb_tree_apply_inorder(t_rb_node *root, int (*applyf)(void *));
int				rb_tree_apply_preorder(t_rb_node *root, int (*applyf)(void *));
int				rb_tree_apply_range(t_rb_node **root, t_rb_tree_range *range, \
			int (*cmp)(void *, void *), int (*applyf)(void *));

#endif
