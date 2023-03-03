/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cli.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:52:36 by lucocozz          #+#    #+#             */
/*   Updated: 2023/02/26 20:09:15 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

t_cli	get_cli(int argc, char **argv)
{
	t_cli	cli;

	if (argc == 1) {
		handle_flag_help(NULL, NULL);
		exit(EXIT_ERROR);
	}
	cli = parse_cli(argc, argv);
	if (cli.host == NULL)
		fatal(EXIT_ERROR, "Specify \"host\" missing argument.");
	return (cli);
}
