/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reben-ha <reben-ha@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 21:40:07 by reben-ha          #+#    #+#             */
/*   Updated: 2023/03/28 20:19:43 by reben-ha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../01.Main/minishell.h"

int run_builtin(char **cmd, int fd_in, int fd_out)
{
	int		i;

	i = -1;
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (dup_fd(fd_in, fd_out), echo_cmd(cmd), SUCCESS);
	else if (ft_strcmp(cmd[0], "cd") == 0)
		return (dup_fd(fd_in, fd_out), cd_cmd(cmd[1]), SUCCESS);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		return (dup_fd(fd_in, fd_out), exit_cmd(cmd), SUCCESS);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		return (dup_fd(fd_in, fd_out), pwd_cmd(), SUCCESS);
	else if (ft_strcmp(cmd[0], "export") == 0)
		return (dup_fd(fd_in, fd_out), export_cmd(cmd), SUCCESS);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		return (dup_fd(fd_in, fd_out), unset_cmd(&cmd[1]), SUCCESS);
	else if (ft_strcmp(cmd[0], "env") == 0)
		return (dup_fd(fd_in, fd_out), env_cmd(), SUCCESS);
	else
		return (FAIL);
}

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
	path = expand_env("PATH");
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

	if (run_builtin(cmd, -1, -1) == SUCCESS)
		exit(g_pub.exit_status);
	if (!env) // change to expend_env();
		return (ft_printf(2, "Minishell : %s : No such file or directory\n"
				, cmd[0]), exit(127));
	if (ft_strchr_check(cmd[0], '/'))
		ft_apply_now(cmd[0], cmd, env);
	paths = ft_path(cmd[0]);
	if (find_path(paths) == FAIL)
		return (ft_printf(2, "Minishell : %s : command not found\n"
				, cmd[0]), exit(127));
	path = ft_strdup(paths[find_path(paths)]);
	ft_free(paths);
	ft_error(execve(path, cmd, env), 0);
}
