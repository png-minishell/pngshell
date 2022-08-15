/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 14:50:56 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/15 15:18:12 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ECHO_H
#define ECHO_H

typedef int	t_bool;
# define TRUE 1
# define FALSE 0

typedef enum	e_status
{
	SUCCESS = 0,
	FAILED = -1
}	t_status;

typedef enum	e_option
{
	DEFAULT = 0,
	N_MODE = 1,
}	t_option;

t_status	run_program(int argc, char *argv[]);
t_option	get_option(int argc, char *argv[]);
t_status	echo_string(char *strings[], t_option mode);

#endif
