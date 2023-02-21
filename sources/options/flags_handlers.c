/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 20:26:22 by user42            #+#    #+#             */
/*   Updated: 2023/02/21 18:32:18 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	handle_flag_help(t_options *data, char *argument)
{
	(void)(data && argument);
	printf("%s", TRACEROUTE_HELP);
	exit(EXIT_SUCCESS);
}

void	handle_flag_4(t_options *data, char *argument)
{
	(void)argument;
	data->family = PF_INET;
}

void	handle_flag_6(t_options *data, char *argument)
{
	(void)argument;
	data->family = PF_INET6;
}

void	handle_flag_icmp(t_options *data, char *argument)
{
	(void)argument;
	data->socktype = SOCK_RAW;
	data->port = DFT_PORT;
}

void	handle_flag_tcp(t_options *data, char *argument)
{
	(void)argument;
	data->socktype = SOCK_STREAM;
	data->port = DFT_TCP_PORT;
}

void	handle_flag_udp(t_options *data, char *argument)
{
	(void)argument;
	data->socktype = SOCK_DGRAM;
	data->port = DFT_UDP_PORT;
}

void	handle_flag_first(t_options *data, char *argument)
{
	long	value;
	char	msg[256] = {0};

	if (ft_is_integer(argument) == false) {
		sprintf(msg, "%s '%s'", MSG_INVALID_ARG, argument);
		fatal(EXIT_FAILURE, msg);
	}
	value = ft_atoi(argument);
	if (!(value >= 1 && value <= __LONG_MAX__)) {
		sprintf(msg, "%s '%s': out of range: %d <= value <= %ld", MSG_INVALID_ARG, argument, 1, __LONG_MAX__);
		fatal(EXIT_FAILURE, msg);
	}
	data->first_ttl = value;
}

void	handle_flag_max(t_options *data, char *argument);
void	handle_flag_port(t_options *data, char *argument);
void	handle_flag_queries(t_options *data, char *argument);
