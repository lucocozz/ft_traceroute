/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 20:26:22 by user42            #+#    #+#             */
/*   Updated: 2023/03/03 20:44:58 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int	handle_packetlen(t_cli *cli, char *argument)
{
	int	value;

	if (cli->host == NULL) {
		cli->host = argument;
		return (0);
	}
	if (ft_is_integer(argument) == false)
		return (-1);
	value = atoi(argument);
	if (value < 0)
		return (-2);
	if (value > 10)
		fatal(EXIT_ERROR, "no more than 10 probes per hop");
	cli->packetlen = value;
	return (0);
}

int	handle_flag_help(t_cli *cli, char *argument)
{
	(void)(cli && argument);
	printf("%s", TRACEROUTE_HELP);
	exit(EXIT_SUCCESS);
	return (0);
}

int	handle_flag_4(t_cli *cli, char *argument)
{
	(void)argument;
	cli->family = PF_INET;
	return (0);
}

int	handle_flag_6(t_cli *cli, char *argument)
{
	(void)argument;
	cli->family = PF_INET6;
	return (0);
}

int	handle_flag_icmp(t_cli *cli, char *argument)
{
	(void)argument;
	cli->socktype = SOCK_RAW;
	cli->port = DFT_PORT;
	return (0);
}

int	handle_flag_tcp(t_cli *cli, char *argument)
{
	(void)argument;
	cli->socktype = SOCK_STREAM;
	cli->port = DFT_TCP_PORT;
	return (0);
}

int	handle_flag_udp(t_cli *cli, char *argument)
{
	(void)argument;
	cli->socktype = SOCK_DGRAM;
	cli->port = DFT_UDP_PORT;
	return (0);
}

int	handle_flag_first(t_cli *cli, char *argument)
{
	uint	value;

	if (ft_is_integer(argument) == false)
		return (-1);
	value = atoi(argument);
	if (!(value >= 1 && (short)value <= cli->max_ttl))
		fatal(EXIT_ERROR, "first hop out of range");
	cli->first_ttl = value;
	return (0);
}

int	handle_flag_max(t_cli *cli, char *argument)
{
	uint	value;

	if (ft_is_integer(argument) == false)
		return (-1);
	value = atoi(argument);
	if (value <= 0)
		fatal(EXIT_ERROR, "first hop out of range");
	if (value <= __UINT8_MAX__ )
		fatal(EXIT_ERROR, "max hops cannot be more than 255");
	cli->max_ttl = value;
	return (0);
}

int	handle_flag_port(t_cli *cli, char *argument)
{
	uint	value;

	if (ft_is_integer(argument) == false)
		return (-1);
	value = atoi(argument);
	cli->port = value;
	return (0);
}

int	handle_flag_queries(t_cli *cli, char *argument)
{
	uint	value;

	if (ft_is_integer(argument) == false)
		return (-1);
	value = atoi(argument);
	if (!(value >= 1 && value <= 10))
		fatal(EXIT_ERROR, "no more than 10 probes per hop");
	cli->queries = value;
	return (0);
}
