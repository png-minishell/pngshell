/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_control_functions.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 14:53:07 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/19 19:50:29 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_CONTROL_FUNCTIONS_H
# define ERROR_CONTROL_FUNCTIONS_H

# include <unistd.h>
# include <stddef.h>
# include "minishell_definitions.h"

void		*e_malloc(size_t malloc_size);
t_status	e_close(const int fd);
t_status	e_dup2(const int fd1, const int fd2);
pid_t		e_fork(void);
int			e_open(const char *path, int flag, int mode);

#endif
