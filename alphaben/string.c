/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennamr <ebennamr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 16:53:30 by ebennamr          #+#    #+#             */
/*   Updated: 2023/03/01 18:15:46 by ebennamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	indexofchar(char *line, char c)
{
	int i;

	i = 0;
	if (line == 0)
		return (-1);
	while (line[i])
	{
		if (line[i] == c)
			return (i);
		i++;
	}

	return (-1);
}

ft_strlen2(char **arr)
{
	int len;

	len = 0;
	if (arr == 0)
	return (0);
	while (*arr[len])
		len++;
	return (0);
}
