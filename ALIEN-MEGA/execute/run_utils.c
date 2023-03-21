/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 21:40:07 by reben-ha          #+#    #+#             */
/*   Updated: 2023/03/21 18:57:59 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int wait_pross(pid_t pross)	
{
	int status;

	waitpid(pross, &status, 0);
	while (wait(NULL) != -1)
		;
	return (status);
}

int	find_path(char **paths)
{
	int	i;

	i = 0;
	while (paths[i] && access(paths[i], F_OK | X_OK) == FAIL)
		i++;
	if (access(paths[i], X_OK) != FAIL)
		return (i);
	return (FAIL);
}

void	ft_apply_now(char *path, char **cmd, char **env)
{
	ft_error(access(path, F_OK), 1);
	ft_error(access(path, X_OK), 1);
	ft_error(execve(path, cmd, env), 1);
}

char	**ft_path(char *cmd)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	// path = expand_env("PATH"); // waiting for Update
	path = ft_strdup("/Users/reben-ha/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Frameworks/Mono.framework/Versions/Current/Commands");
	if (!path)
		return (ft_printf(2, "Minishell : %s : No such file or directory\n"
				, cmd), exit(127), NULL);
	paths = ft_split(path, ':');
	i = -1;
	while (paths[++i] != NULL)
	{
		paths[i] = ft_strjoin_gnl(paths[i], "/");
		paths[i] = ft_strjoin_gnl(paths[i], cmd);
	}
	return (paths);
}

void	execute_x(char **cmd, char **env)
{
	char	**paths;
	char	*path;

	if (!env)
		return (ft_printf(2, "Minishell : %s : No such file or directory\n"
				, cmd[0]), exit(127));
	if (ft_strchr_check(cmd[0], '/'))
		ft_apply_now(cmd[0], cmd, env);
	paths = ft_path(cmd[0]);
	if (find_path(paths) == FAIL)
		return (ft_printf(2, "Minishell : %s : command not found\n"
				, cmd[0]), exit(127));
	path = paths[find_path(paths)];
	ft_free(paths);
	ft_error(execve(path, cmd, env), 0);
}
