/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:52:36 by lucocozz          #+#    #+#             */
/*   Updated: 2023/02/26 20:09:15 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

t_options	get_options(int argc, char **argv)
{
	t_options	options;

	if (argc == 1) {
		handle_flag_help(NULL, NULL);
		exit(EXIT_ERROR);
	}
	options = parse_options(argc, argv);
	if (options.host == NULL)
		fatal(EXIT_ERROR, "Specify \"host\" missing argument.");
	return (options);
}
