/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:43:48 by eel-abed          #+#    #+#             */
/*   Updated: 2024/07/17 17:48:36 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int pipex(char *infile, char *cmd1, char *cmd2, char *outfile)
{
	int pipefd[2];
	pid_t pid;

	if (pipe(pipefd) == -1)
	{
		perror("Pipe failed");
		return (1);
	}

	pid = fork();
	if (pid == -1)
	{
		perror("Fork failed");
		return (1);
	}
	else if (pid == 0)
	{
		// Processus enfant
		close(pipefd[0]); // Ferme l'extrémité de lecture du pipe
		// TODO: Rediriger l'entrée standard vers infile
		// TODO: Rediriger la sortie standard vers pipefd[1]
		// TODO: Exécuter cmd1
	}
	else
	{
		// Processus parent
		close(pipefd[1]); // Ferme l'extrémité d'écriture du pipe
		// TODO: Rediriger l'entrée standard vers pipefd[0]
		// TODO: Rediriger la sortie standard vers outfile
		// TODO: Exécuter cmd2
	}

	// TODO: Attendre la fin des processus enfants
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc != 5)
	{
		ft_putstr_fd("Error: Invalid number of arguments\n", 2);
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 2);
		return (1);
	}

	char *infile = argv[1];
	char *cmd1 = argv[2];
	char *cmd2 = argv[3];
	char *outfile = argv[4];

	if (access(infile, R_OK) == -1)
	{
		perror("Error");
		return (1);
	}

	// Appelez votre fonction pipex principale (à implémenter plus tard)
	// int result = pipex(infile, cmd1, cmd2, outfile);

	return (0);
}
