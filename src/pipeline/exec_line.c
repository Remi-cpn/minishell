/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/29 13:50:03 by rcompain          #+#    #+#             */
/*   Updated: 2026/01/31 16:34:22 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/mini_shell.h"
#include <sys/wait.h>

static void	dispatch_builtins(t_data *shell, t_ast *ast)
{
	t_ast_cmd	*cmd;

	if (ast->kind != CMD)
		return ;
	cmd = (t_ast_cmd *)ast;
	if (ft_strncmp(cmd->name, "echo", 4) == 0)
		echo_cmd(shell, cmd->args);
	else if (ft_strncmp(cmd->name, "exit", 4) == 0)
		exit_cmd(shell, cmd->args);
	else if (ft_strncmp(cmd->name, "env", 3) == 0)
		env_cmd(shell, cmd->args);
	else if (ft_strncmp(cmd->name, "pwd", 3) == 0)
		pwd_cmd(shell, cmd->args);
	else if (ft_strncmp(cmd->name, "cd", 2) == 0)
		cd_cmd(shell, cmd->args);
	else if (ft_strncmp(cmd->name, "export", 6) == 0)
		export_cmd(shell, cmd->args);
	else if (ft_strncmp(cmd->name, "unset", 5) == 0)
		unset_cmd(shell, cmd->args);
}

// void	child_process(t_data *shell, char **cmd, int i, int pipes)
// {
// 	int	find;
// 	int	j;

// 	find = find_path(shell, cmd);
// 	if (find == FAILURE)
// 	{
// 		shell->exit_status = ERROR;
// 		return ;
// 	}
// 	dup2(pipex->fds[i - 1][0], STDIN_FILENO);
// 	dup2(pipex->fds[i][1], STDOUT_FILENO);
// 	j = 0;
// 	while (j < pipex->nbr_fds)
// 	{
// 		close(pipex->fds[j][0]);
// 		close(pipex->fds[j][1]);
// 		j++;
// 	}
// 	execve(pipex->path, pipex->cmd[i], pipex->envp);
// 	exit_prog(pipex, ERROR);
// }

static void	child_process_one_cmd(t_data *shell, t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out != STDOUT_FILENO)
		dup2(cmd->fd_out, STDOUT_FILENO);
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	if (cmd->fd_out != STDOUT_FILENO)
		close(cmd->fd_out);
	execve(shell->cmd_path, cmd->args, shell->env);
	exit_prog(shell, ERR_CMD_NOT_FOUND);
}

static void	exec_one_cmd(t_data *shell, t_cmd *cmd)
{
	int	pid;
	int	find;
	int	status;

	if (cmd->is_builtin == true)
		dispatch_builtins(shell, NULL);
	else
	{
		find = find_path(shell, cmd->args);
		if (find == -1)
		{
			call_to_exit(shell, ERR_PATH, "cmd: Path not found\n");
			return ;
		}
		pid = fork();
		if (pid == 0)
			child_process_one_cmd(shell, cmd);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			shell->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			shell->exit_status = 128 + WTERMSIG(status);
	}
}
//static void	exec_pipeline(t_data *shell, t_cmd *cmds);

// i = 0;
// if (shell->nbr_cmd > 1)
//  exec_pipeline(shell, cmds);
// else
void	exec_line(t_data *shell, t_ast **ast)
{
	t_cmd	*cmds;
	int		i;

	cmds = init_cmds(shell, ast);
	i = 0;
	exec_one_cmd(shell, &cmds[i]);
}
