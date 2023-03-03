/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 19:06:55 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/03 19:44:08 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	missing_arg_error(char *flag, int argc, char *help)
{
	printf("Option `-%s' (argc %d) requires an argument: `%s'\n", flag, argc, help);
	exit(EXIT_ERROR);
}

void	arg_error(char *flag, char *argument, int argc)
{
	printf("Cannot handle `-%s' option with arg `%s' (argc %d)", flag, argument, argc);
	exit(EXIT_ERROR);
}

void	bad_option(char *flag, int argc)
{
	printf("Bad option `-%s' (argc %d)\n", flag, argc);
	exit(EXIT_ERROR);
}

void	packetlen_error(char *argument, int argc)
{
	printf("Cannot handle \"packetlen\" cmdline arg `%s' on position %d (argc %d)\n", argument, argc, argc);
	exit(EXIT_ERROR);	
}

void	extra_arg_error(char *argument, int argc)
{
	printf("Extra arg `%s' (position %d, argc %d)\n", argument, argc, argc);
	exit(EXIT_ERROR);	
}
