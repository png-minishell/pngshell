/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:09:10 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/21 20:20:09 by sungjpar         ###   ########.fr       */
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

void	heredoc(const char *limiter)
{
	char			*line;
	t_list			*head;
	int				fd;

	head = NULL;
	fd = e_open(HEREDOC_FILE_NAME, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	while (1)
	{
		line = readline("heredoc> ");
		if (ft_strncmp(line, limiter, -1) == 0 || line[0] == 0)
			break ;
		ft_lstadd_back(&head, ft_lstnew(ft_strjoin(line, "\n")));
	}
	write_list(fd, head);
	ft_lstclear(&head, free);
	close(fd);
}
