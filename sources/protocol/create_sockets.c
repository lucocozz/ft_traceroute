/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_sockets.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 12:33:49 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/16 18:22:45 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static int	__set_options(int socket)
{
	struct timeval	timeout = {.tv_sec = 0, .tv_usec = DFT_TIMEOUT_US};
	if (setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0)
		return (-1);
	return (0);
}

int	create_sockets(struct addrinfo *address, t_sockets *sockets)
{
	sockets->send = socket(address->ai_family, address->ai_socktype, address->ai_protocol);
	if (sockets->send == -1)
		return (-1);
	sockets->recv = socket(address->ai_family, SOCK_RAW, GET_VPROTO(address->ai_family));
	if (sockets->recv == -1) {
		close(sockets->send);
		return (-1);
	}
	if (__set_options(sockets->recv) == -1)
		return (-1);
	return (0);
}
