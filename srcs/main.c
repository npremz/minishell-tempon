/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lethomas <lethomas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 04:56:11 by lethomas          #+#    #+#             */
/*   Updated: 2023/12/16 23:28:44 by lethomas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing_exec.h"

int	main(int argc, char **argv)
{
	char	*arg;

	errno = 0;
	if (argc != 2)
		return (EXIT_FAILURE);
	arg = ft_strdup(argv[1]);
	if (ft_exec_cmd_line(arg))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
//heredoc controlD
//getenv fils de fils
//parenthese vide
//homepath si . ou ./ ->voir pour les cas bizarres

// int	main(int argc, char **argv)
// {
// 	if (main2(argc, argv))
// 		return (EXIT_FAILURE);
// 	system("leaks parsing");
// 	return (EXIT_SUCCESS);
// }
