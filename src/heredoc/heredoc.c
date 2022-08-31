/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:09:10 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/30 18:53:40 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include "error_control_functions.h"
#include "minishell_definitions.h"
#include "libft.h"
#include "replacer.h"

static void	write_list(const int fd, t_list *head)
{
	while (head)
	{
		write(fd, head->content, ft_strlen(head->content));
		head = head->next;
	}
}

int	heredoc(const char *limiter)
{
	char			*line;
	char			*replaced_line;
	t_list			*head;
	int				fds[2];

	head = NULL;
	e_pipe(fds);
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL || ft_strncmp(line, limiter, -1) == 0)
			break ;
		replaced_line = replacer(line);
		free(line);
		ft_lstadd_back(&head, ft_lstnew(ft_strjoin(replaced_line, "\n")));
		free(replaced_line);
	}
	write_list(fds[1], head);
	ft_lstclear(&head, free);
	close(fds[1]);
	return (fds[0]);
}
