/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 10:36:00 by npremont          #+#    #+#             */
/*   Updated: 2024/03/07 16:25:48 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(t_list **en, t_bool is_child)
{
	ft_envclear(en, free_globvar);
	rl_clear_history();
	if (is_child == false)
		write(1, "exit\n", 5);
	exit(EXIT_SUCCESS);
}
