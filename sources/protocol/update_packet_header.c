/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_packet_header.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 15:32:48 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/16 18:44:19 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	update_packet_header(Packet *packet, t_cli cli, int socket, int seq)
{
	switch (packet->type)
	{
	case IPPROTO_ICMP:
		// ((IcmpPacket*)packet)->set_echo_seq(packet, seq);
		break;
	case IPPROTO_UDP:
		((UdpPacket*)packet)->set_uh_dport(packet, cli.port + seq - 1);
		break;
	case IPPROTO_TCP:
		((TcpPacket*)packet)->set_seq(packet, seq);
	default:
		break;
	}
	set_ttl(socket, GET_LEVEL(cli.family), seq);
}
