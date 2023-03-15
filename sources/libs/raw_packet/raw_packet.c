/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_packet.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:13:00 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/15 00:27:17 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raw_packet.h"

void	packet_destroy(Packet* packet)
{
	packet->vtable->destroy(packet);
}

Packet	*packet_create(int type, size_t size)
{
	switch (type)
	{
	case IPPROTO_ICMP:
		return (icmp_packet_create(size));
	case IPPROTO_UDP:
		return (udp_packet_create(size));
	case IPPROTO_TCP:
		return (tcp_packet_create(size));
	default:
		return (NULL);
	}
}

void	packet_checksum(Packet *packet)
{
	packet->vtable->checksum(packet);
}
