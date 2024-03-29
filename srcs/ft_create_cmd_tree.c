/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_cmd_tree.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 00:20:21 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/09 17:02:25 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_set_new_list_size(t_list **cmd_list, int *size_cmd_list,
	t_bool *is_parenthesis)
{
	int		counter_parenthesis;
	t_list	*cmd_list_new_begin;

	counter_parenthesis = 1;
	*cmd_list = (*cmd_list)->prev;
	cmd_list_new_begin = *cmd_list;
	*size_cmd_list = 0;
	*is_parenthesis = true;
	while (counter_parenthesis != 0)
	{
		if (((t_cmd *)(*cmd_list)->content)->type == right_parenthesis_cmd)
			counter_parenthesis++;
		if (((t_cmd *)(*cmd_list)->content)->type == left_parenthesis_cmd)
			counter_parenthesis--;
		(*cmd_list) = (*cmd_list)->prev;
		if (counter_parenthesis != 0)
			(*size_cmd_list)++;
	}
	(*cmd_list) = cmd_list_new_begin;
}

static int	ft_cmd_list_end(int *new_size_cmd_list, int size_cmd_list,
	t_btree **cmd_tree, t_bool is_parenthesis)
{
	t_btree	*tree_temp;

	if (size_cmd_list == *new_size_cmd_list
		+ 2 * (is_parenthesis == true))
	{
		tree_temp = (*cmd_tree)->right;
		free(*cmd_tree);
		*cmd_tree = tree_temp;
		return (true);
	}
	*new_size_cmd_list += (is_parenthesis == true);
	return (false);
}

static void	ft_set_op_cmd_tree(t_list **cmd_list, int size_cmd_list,
	int *new_size_cmd_list, t_btree **cmd_tree)
{
	*cmd_list = ft_lstshift(*cmd_list, -*new_size_cmd_list);
	(*cmd_tree)->item = (*cmd_list)->content;
	*new_size_cmd_list = size_cmd_list - *new_size_cmd_list - 1;
	(*cmd_list) = (*cmd_list)->prev;
}

static int	ft_create_cmd_node(t_list *cmd_list, int size_cmd_list,
	t_btree **cmd_tree)
{
	int		new_size_cmd_list;
	t_bool	is_parenthesis;

	new_size_cmd_list = 1;
	is_parenthesis = false;
	*cmd_tree = ft_btree_create_node(NULL);
	if (*cmd_tree == NULL)
		return (EXIT_FAILURE);
	if (size_cmd_list == 1)
	{
		(*cmd_tree)->item = cmd_list->content;
		return (EXIT_SUCCESS);
	}
	if (((t_cmd *)cmd_list->content)->type == right_parenthesis_cmd)
		ft_set_new_list_size(&cmd_list, &new_size_cmd_list, &is_parenthesis);
	if (ft_create_cmd_node(cmd_list, new_size_cmd_list, &(*cmd_tree)->right))
		return (EXIT_FAILURE);
	if (ft_cmd_list_end(&new_size_cmd_list, size_cmd_list, cmd_tree,
			is_parenthesis))
		return (EXIT_SUCCESS);
	ft_set_op_cmd_tree(&cmd_list, size_cmd_list - (is_parenthesis == true),
		&new_size_cmd_list, cmd_tree);
	if (ft_create_cmd_node(cmd_list, new_size_cmd_list, &(*cmd_tree)->left))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	ft_create_cmd_tree(t_list *cmd_list, t_btree **cmd_tree)
{
	if (ft_create_cmd_node(ft_lstlast(cmd_list), ft_lstsize(cmd_list),
			cmd_tree))
		return (EXIT_FAILURE);
	ft_free_cmd_list(cmd_list);
	return (EXIT_SUCCESS);
}
