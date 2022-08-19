/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:09:10 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/19 14:25:44 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "error_control_functions.h"
#include "minishell_definitions.h"
#include "libft.h"

#define	HERE_DOC_SIGN "heredoc> "
#define HERE_DOC_SIGN_LEN 9

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
	char			*buf;
	int				read_size;
	int				sign_flag;
	t_list			*head;
	
	buf = e_malloc(sizeof(char) * (limiter_length + 1));
	head = NULL;
	sign_flag = 1;
	while (1)
	{
		if (sign_flag)
			write(STDOUT_FILENO, HERE_DOC_SIGN, HERE_DOC_SIGN_LEN);
		read_size = read(STDIN_FILENO, buf, limiter_length);
		buf[read_size] = 0;
		if (ft_strncmp(buf, limiter, -1) == 0)
			break ;
		sign_flag = (ft_strchr(buf, '\n') != NULL);
		ft_lstadd_back(&head, ft_lstnew(ft_strdup(buf)));
	}
	write_list(fd, head);
	ft_lstclear(&head, free);
	free(buf);
}
