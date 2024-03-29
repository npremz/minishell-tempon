/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_parenthesis.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 20:45:03 by lethomas          #+#    #+#             */
/*   Updated: 2024/03/07 14:13:17 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_lstinsert_back_redirection(t_list *elem_receiver,
	t_list *elem_to_insert)
{
	elem_to_insert->prev->next = elem_to_insert->next;
	if (elem_to_insert->next != NULL)
		elem_to_insert->next->prev = elem_to_insert->prev;
	elem_receiver->prev->next = elem_to_insert;
	elem_to_insert->prev = elem_receiver->prev;
	elem_receiver->prev = elem_to_insert;
	elem_to_insert->next = elem_receiver;
}

static void	ft_set_receiver_out(t_list *token_list, t_list **elem_to_insert,
	t_list **elem_receiver_out)
{
	int		counter_parenthesis;
	t_token	*token_to_insert;

	counter_parenthesis = 1;
	*elem_to_insert = token_list->next;
	while (counter_parenthesis != 0)
	{
		token_to_insert = (t_token *)(*elem_to_insert)->content;
		if (token_to_insert->type == left_parenthesis)
			counter_parenthesis++;
		if (token_to_insert->type == right_parenthesis)
			counter_parenthesis--;
		if (ft_token_is_cmd_op(token_to_insert))
		{
			*elem_receiver_out = (*elem_to_insert)->next;
			while (((t_token *)(*elem_receiver_out)->content)->type
				== left_parenthesis)
				*elem_receiver_out = (*elem_receiver_out)->next;
		}
		*elem_to_insert = (*elem_to_insert)->next;
	}
}

static int	ft_move_redirection(t_list *elem_to_insert,
	t_list	*elem_receiver_in, t_list *elem_receiver_out)
{
	t_list	*elem_temp;
	t_list	*elem_receiver;

	while (elem_to_insert != NULL
		&& !ft_token_is_cmd_op((t_token *)elem_to_insert->content)
		&& ((t_token *)elem_to_insert->content)->type != right_parenthesis)
	{
		elem_temp = elem_to_insert->next;
		if (((t_token *)elem_to_insert->content)->type == redirection_in
			|| ((t_token *)elem_to_insert->content)->type
			== redirection_here_doc)
			elem_receiver = elem_receiver_in;
		else if (((t_token *)elem_to_insert->content)->type == redirection_out
			|| ((t_token *)elem_to_insert->content)->type == redirection_append)
			elem_receiver = elem_receiver_out;
		else
			return (EXIT_FAILURE);
		ft_lstinsert_back_redirection(elem_receiver, elem_to_insert);
		elem_to_insert = elem_temp;
		elem_temp = elem_to_insert->next;
		ft_lstinsert_back_redirection(elem_receiver, elem_to_insert);
		elem_to_insert = elem_temp;
	}
	return (EXIT_SUCCESS);
}

static void	ft_set_receiver_in(t_list **token_list, t_list **elem_receiver_in)
{
	int	counter_parenthesis;

	counter_parenthesis = 1;
	*token_list = (*token_list)->prev;
	while (counter_parenthesis != 0)
	{
		if (((t_token *)(*token_list)->content)->type == left_parenthesis)
			counter_parenthesis--;
		if (((t_token *)(*token_list)->content)->type == right_parenthesis)
			counter_parenthesis++;
		if (counter_parenthesis != 0)
			*token_list = (*token_list)->prev;
	}
	*elem_receiver_in = *token_list;
	while (((t_token *)(*elem_receiver_in)->content)->type == left_parenthesis)
		*elem_receiver_in = (*elem_receiver_in)->next;
}

int	ft_token_parenthesis(t_list *token_list)
{
	t_list	*elem_receiver_in;
	t_list	*elem_receiver_out;
	t_list	*elem_to_insert;
	t_list	*token_list_temp;

	while (token_list != NULL)
	{
		if (((t_token *)token_list->content)->type == right_parenthesis)
		{
			token_list_temp = token_list;
			ft_set_receiver_in(&token_list_temp, &elem_receiver_in);
			elem_receiver_out = elem_receiver_in;
			ft_set_receiver_out(token_list_temp, &elem_to_insert,
				&elem_receiver_out);
			if (ft_move_redirection(elem_to_insert, elem_receiver_in,
					elem_receiver_out))
				return (EXIT_FAILURE);
		}
		token_list = token_list->next;
	}
	return (EXIT_SUCCESS);
}
