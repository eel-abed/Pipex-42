/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 20:45:50 by eel-abed          #+#    #+#             */
/*   Updated: 2024/07/17 21:03:01 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void free_array(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void execute_cmd(char *cmd, char **env)
{
	char **args;
	char *path;

	args = ft_split(cmd, ' ');
	if (!args)
		exit(error_handler("Error splitting command"));

	path = find_command(args[0], env);
	if (!path)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd("\n", 2);
		free_array(args);
		exit(1);
	}

	execve(path, args, env);
	free(path);
	free_array(args);
	exit(error_handler("Error executing command"));
}
