/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:43:48 by eel-abed          #+#    #+#             */
/*   Updated: 2024/07/18 19:06:18 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void child_process(int pipefd[2], char *infile, char *cmd, char **env)
{
	int fd_in;

	fd_in = open(infile, O_RDONLY);
	if (fd_in == -1)
		exit(error_handler("Error opening input file"));

	if (dup2(fd_in, STDIN_FILENO) == -1)
		exit(error_handler("Dup2 failed"));
	if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		exit(error_handler("Dup2 failed"));

	close(fd_in);
	close(pipefd[0]);
	close(pipefd[1]);

	execute_cmd(cmd, env);
}

static void parent_process(int pipefd[2], char *outfile, char *cmd, char **env)
{
	int fd_out;

	fd_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
		exit(error_handler("Error opening output file"));

	if (dup2(pipefd[0], STDIN_FILENO) == -1)
		exit(error_handler("Dup2 failed"));
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		exit(error_handler("Dup2 failed"));

	close(fd_out);
	close(pipefd[0]);
	close(pipefd[1]);

	execute_cmd(cmd, env);
}

int pipex(char *infile, char *cmd1, char *cmd2, char *outfile, char **env)
{
	int pipefd[2];
	pid_t pid1, pid2;
	int status;

	if (pipe(pipefd) == -1)
		return (error_handler("Pipe failed"));

	pid1 = fork();
	if (pid1 < 0)
		return (error_handler("Fork failed"));
	if (pid1 == 0)
		child_process(pipefd, infile, cmd1, env);

	pid2 = fork();
	if (pid2 < 0)
		return (error_handler("Fork failed"));
	if (pid2 == 0)
		parent_process(pipefd, outfile, cmd2, env);

	close(pipefd[0]);
	close(pipefd[1]);

	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);

	return (WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **env)
{
	char	*infile = argv[1];
	char *cmd1 = argv[2];
	char *cmd2 = argv[3];
	char *outfile = argv[4];
	if (argc != 5)
	{
		ft_putstr_fd("Error: Invalid number of arguments\n", 2);
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}
	if (access(infile, R_OK) == -1)
	{
		perror("Error");
		return (1);
	}
	int result = pipex(infile, cmd1, cmd2, outfile, env);
	if (result != 0)
	{
		ft_putstr_fd("Error: Pipex failed\n", 2);
		return (1);
	}
	return (0);
}
