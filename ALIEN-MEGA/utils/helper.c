/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennamr <ebennamr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 13:46:50 by reben-ha          #+#    #+#             */
/*   Updated: 2023/03/23 18:16:40 by ebennamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_loc	ini_loc(int i, int j)
{
	t_loc	loc;

	loc.i = i;
	loc.j = j;
	return (loc);
}
