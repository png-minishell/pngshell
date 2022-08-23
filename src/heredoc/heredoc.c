/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:09:10 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/23 14:37:27 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include "error_control_functions.h"
#include "minishell_definitions.h"
#include "libft.h"

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
	t_list			*head;
	int				fds[2];

	head = NULL;
	e_pipe(fds);
	while (1)
	{
		line = readline("heredoc> ");
		if (line == NULL || ft_strncmp(line, limiter, -1) == 0)
			break ;
		ft_lstadd_back(&head, ft_lstnew(ft_strjoin(line, "\n")));
	}
	write_list(fds[1], head);
	ft_lstclear(&head, free);
	close(fds[1]);
	return (fds[0]);
}
