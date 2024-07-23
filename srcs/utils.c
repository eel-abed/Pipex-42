/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 17:33:01 by eel-abed          #+#    #+#             */
/*   Updated: 2024/07/17 21:01:05 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return;

	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
}

static int count_words(char const *s, char c)
{
	int count = 0;
	int in_word = 0;

	while (*s)
	{
		if (*s != c && in_word == 0)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char *word_dup(const char *str, int start, int finish)
{
	char *word;
	int i;

	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char **ft_split(char const *s, char c)
{
	size_t i = 0;
	size_t j = 0;
	int index = -1;
	char **split;

	if (!s || !(split = malloc((count_words(s, c) + 1) * sizeof(char *))))
		return (0);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && index < 0)
			index = i;
		else if ((s[i] == c || i == ft_strlen(s)) && index >= 0)
		{
			split[j++] = word_dup(s, index, i);
			index = -1;
		}
		i++;
	}
	split[j] = 0;
	return (split);
}

char *find_command(char *cmd, char **env)
{
	char *path = NULL;
	char *dir;
	char *bin;
	char **paths;
	int i = 0;

	// Chercher la variable PATH dans env
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = env[i] + 5; // Sauter "PATH="
			break;
		}
		i++;
	}

	if (!path)
		return (NULL);

	paths = ft_split(path, ':');
	i = 0;
	while (paths[i])
	{
		dir = ft_strjoin(paths[i], "/");
		bin = ft_strjoin(dir, cmd);
		free(dir);
		if (access(bin, F_OK) == 0)
		{
			// Free paths before returning
			while (paths[i])
				free(paths[i++]);
			free(paths);
			return (bin);
		}
		free(bin);
		i++;
	}
	// Free paths if command not found
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return (NULL);
}

int error_handler(char *message)
{
	perror(message);
	return (1);
}
