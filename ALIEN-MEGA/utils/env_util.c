/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebennamr <ebennamr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 18:20:26 by ebennamr          #+#    #+#             */
/*   Updated: 2023/03/04 17:37:08 by ebennamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

void	add_to_env(char *content)
{
	int		env_len;
	char	**tmp;
	int		i;

	tmp = g_pub.env;
	env_len = (int)ft_matlen(g_pub.env);
	g_pub.env = malloc(sizeof(char *) * (env_len + 2));
	ft_error_str(g_pub.env, 1);
	while (i < env_len)
	{
		g_pub.env[i] = tmp[i];
		i++;
	}
	g_pub.env[i] = content;
	g_pub.env[i + 1] = NULL;
	free(tmp);
}
void	set_shlvl()
{
	char	*old_value;
	char	*new_value;
	int		value;

	old_value = expand_env("SHLVL");
	printf("%s\n",old_value);
	new_value = 0;
	if (ft_strlen(old_value) == 0)
		export_to_env("SHLVL","1", OPT_CREAT);
	else
	{
		value = ft_atoi(old_value);
		if (value >= 999 || value <= 0)
			export_to_env("SHLVL", "1", OPT_CREAT);
		else
		{

			new_value = ft_itoa(value + 1);
			printf("udpdting %s ----> %s\n\n",old_value, new_value);
				ft_error_str(new_value, 1);

			export_to_env("SHLVL", new_value, OPT_CREAT);
		}
	}
	free(old_value);
	free(new_value);
}
