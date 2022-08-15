/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sungjpar <sungjpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:08:15 by sungjpar          #+#    #+#             */
/*   Updated: 2022/08/15 15:12:27 by sungjpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "echo.h"

t_status	run_program(int argc, char **argv)
{
	const t_option	option = get_option(argc, argv);

	return (echo_string(argv, option));
}
