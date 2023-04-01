/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traceroute_queries.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 10:48:26 by lucocozz          #+#    #+#             */
/*   Updated: 2023/04/01 17:08:57 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

t_querie	traceroute_queries(t_sockets sockets, Packet *packet, struct addrinfo *address)
{
	t_querie		querie;
	struct timeval	start, end;

	if (gettimeofday(&start, NULL) < 0)
		return ((t_querie){.error = ERR_UNDEFINED});
	if (send_packet(sockets.send, packet, address) == -1)
		return ((t_querie){.error = ERR_SEND});
	// send_packet(sockets.send, packet, address);
	querie = recv_packet(sockets.recv, address->ai_family);
	if (gettimeofday(&end, NULL) < 0)
		return ((t_querie){.error = ERR_UNDEFINED});
	querie.time = get_elapsed_time(start, end);
	return (querie);
}
