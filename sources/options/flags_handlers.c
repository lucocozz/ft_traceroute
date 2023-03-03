/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 20:26:22 by user42            #+#    #+#             */
/*   Updated: 2023/03/03 18:40:34 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

int	handle_packetlen(t_options *data, char *argument)
{
	int	value;

	if (data->host == NULL) {
		data->host = argument;
		return (0);
	}
	if (ft_is_integer(argument) == false)
		return (-1);
	value = atoi(argument);
	if (value < 0)
		return (-2);
	if (value > 10)
		fatal(EXIT_ERROR, "no more than 10 probes per hop");
	data->packetlen = value;
	return (0);
}

int	handle_flag_help(t_options *data, char *argument)
{
	(void)(data && argument);
	printf("%s", TRACEROUTE_HELP);
	exit(EXIT_SUCCESS);
	return (0);
}

int	handle_flag_4(t_options *data, char *argument)
{
	(void)argument;
	data->family = PF_INET;
	return (0);
}

int	handle_flag_6(t_options *data, char *argument)
{
	(void)argument;
	data->family = PF_INET6;
	return (0);
}

int	handle_flag_icmp(t_options *data, char *argument)
{
	(void)argument;
	data->socktype = SOCK_RAW;
	data->port = DFT_PORT;
	return (0);
}

int	handle_flag_tcp(t_options *data, char *argument)
{
	(void)argument;
	data->socktype = SOCK_STREAM;
	data->port = DFT_TCP_PORT;
	return (0);
}

int	handle_flag_udp(t_options *data, char *argument)
{
	(void)argument;
	data->socktype = SOCK_DGRAM;
	data->port = DFT_UDP_PORT;
	return (0);
}

int	handle_flag_first(t_options *data, char *argument)
{
	uint	value;

	if (ft_is_integer(argument) == false)
		return (-1);
	value = atoi(argument);
	if (!(value >= 1 && (short)value <= data->max_ttl))
		fatal(EXIT_ERROR, "first hop out of range");
	data->first_ttl = value;
	return (0);
}

int	handle_flag_max(t_options *data, char *argument)
{
	uint	value;

	if (ft_is_integer(argument) == false)
		return (-1);
	value = atoi(argument);
	if (value <= 0)
		fatal(EXIT_ERROR, "first hop out of range");
	if (value <= __UINT8_MAX__ )
		fatal(EXIT_ERROR, "max hops cannot be more than 255");
	data->max_ttl = value;
	return (0);
}

int	handle_flag_port(t_options *data, char *argument)
{
	uint	value;

	if (ft_is_integer(argument) == false)
		return (-1);
	value = atoi(argument);
	data->port = value;
	return (0);
}

int	handle_flag_queries(t_options *data, char *argument)
{
	uint	value;

	if (ft_is_integer(argument) == false)
		return (-1);
	value = atoi(argument);
	if (!(value >= 1 && value <= 10))
		fatal(EXIT_ERROR, "no more than 10 probes per hop");
	data->queries = value;
	return (0);
}
