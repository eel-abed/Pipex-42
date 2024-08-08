/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eel-abed <eel-abed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:43:32 by eel-abed          #+#    #+#             */
/*   Updated: 2024/08/08 15:18:44 by eel-abed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pipex_args
{
	char	*infile;
	char	*cmd1;
	char	*cmd2;
	char	*outfile;
	char	**env;
}	t_pipex_args;

void	ft_putstr_fd(char *s, int fd);
int		pipex(t_pipex_args *args);
void	execute_cmd(char *cmd, char **env);
char	**ft_split(char const *s, char c);
char	*find_command(char *cmd, char **env);
int		error_handler(char *message);
char	*get_path_variable(char **env);
char	*search_command_in_paths(char *cmd, char **paths);
char	*find_command(char *cmd, char **env);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
