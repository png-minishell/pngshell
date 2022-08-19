/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:09:10 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/19 15:31:02 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
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

void	heredoc(const int fd, const char *limiter)
{
	const size_t	limiter_length = ft_strlen(limiter);
	char			*line;
	int				sign_flag;
	t_list			*head;
	
	head = NULL;
	sign_flag = 1;
	while (1)
	{
		line = readline("heredoc> ");
		if (ft_strncmp(line, limiter, -1) == 0)
			break ;
		ft_lstadd_back(&head, ft_lstnew(line));
	}
	write_list(fd, head);
	ft_lstclear(&head, free);
}
