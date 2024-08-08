/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:12:09 by eel-abed          #+#    #+#             */
/*   Updated: 2024/08/08 15:18:19 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*get_path_variable(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*search_command_in_paths(char *cmd, char **paths)
{
	char	*dir;
	char	*bin;
	int		i;

	i = 0;
	while (paths[i])
	{
		dir = ft_strjoin(paths[i], "/");
		bin = ft_strjoin(dir, cmd);
		free(dir);
		if (access(bin, F_OK) == 0)
		{
			while (paths[i])
				free(paths[i++]);
			free(paths);
			return (bin);
		}
		free(bin);
		i++;
	}
	return (NULL);
}

char	*find_command(char *cmd, char **env)
{
	char	*path;
	char	**paths;
	char	*result;
	int		i;

	path = get_path_variable(env);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	result = search_command_in_paths(cmd, paths);
	if (result)
		return (result);
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return (NULL);
}
