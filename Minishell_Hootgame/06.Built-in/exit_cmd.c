/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennamr <ebennamr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:16:55 by reben-ha          #+#    #+#             */
/*   Updated: 2023/04/06 21:22:26 by ebennamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../01.Main/minishell.h"

static long result(const char *str, int i, int sg)
{
	long nb;

	nb = 0;
	while (str[i])
	{
		nb = nb * 10 + (((int)str[i]) - 48);
		if (ft_isdigit(str[i]) != TRUE || nb < 0)
		{
			ft_printf(2, "minishell : exit: numeric argument required");
			exit(255);
		}
			i++;
	}
	if (nb > 9223372036854775807 && sg == 1)
		return (-1);
	else if (nb > 9223372036854775807 && sg == -1)
		return (0);
	return (nb * sg);
}

static long long getexit_number(const char *str)
{
	long i;
	int sg;

	sg = 1;
	i = 0;
	while (indexofchar("\t\v\f\r\n\n ", str[i]) != -1)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sg = -1;
		i++;
	}
	return (result(str, i, sg));
}

void	exit_cmd(char **cmd)
{
	if (cmd == NULL || cmd[0] == NULL)
	{
		ft_printf(2, "exit\n"),
		exit(g_pub.exit_status);
	}
	else if (cmd[1] != NULL)
	{
		ft_printf(2,"exit\nMinishell : exit: too many arguments\n");
		exit(255);
	}
	ft_printf(2, "exit\n");
	exit(getexit_number(cmd[0]));
}
