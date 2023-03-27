/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 23:53:56 by reben-ha          #+#    #+#             */
/*   Updated: 2023/03/27 02:44:29 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../01.Main/minishell.h"

static char	*generator_tmp(void)
{
	char		*gen_tmp;
	int			*num;
	int			status;

	num = malloc(10);
	status = read(open("/dev/urandom", O_RDONLY), num, 10);
	if (status == -1)
		return (free(num), ft_strdup("tmp-"));
	gen_tmp = ft_strjoin("/tmp/tmp-", ft_itoa(*num));
	return (free(num), gen_tmp);
}

static void	ft_read_tmp(char *tmp_file, char *limiter)
{
	char	*str;
	int		fd_tmp;

	fd_tmp = open(tmp_file, O_RDWR | O_TRUNC | O_CREAT, 0600);
	ft_error(fd_tmp, 1);
	limiter = ft_strjoin(limiter, "\n");
	while (1)
	{
		ft_printf(2, "pipe heredoc> ");
		str = get_next_line(0);
		// str = readline("pipe heredoc> ");
		if (!str || ft_strncmp(str, limiter, ft_strlen(limiter)) == 0)
			break ;
		ft_printf(fd_tmp, "%s", str);
		free(str);
	}
	free(limiter);
	close(fd_tmp);
}

char	*here_doc(char *delimiter)
{
	char *tmp_file;

	tmp_file = generator_tmp();
	ft_read_tmp(tmp_file, delimiter);
	return (tmp_file);
}