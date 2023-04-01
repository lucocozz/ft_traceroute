/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_packet_header.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:22:21 by lucocozz          #+#    #+#             */
/*   Updated: 2023/04/01 14:22:51 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

static void	__set_icmp_header(Packet *packet)
{
	IcmpPacket	*icmp = (IcmpPacket*)packet;

	icmp->set_type_code(packet, ICMP_ECHO, 0);
	icmp->set_un_echo(packet, getpid(), 0);
}

static void	__set_udp_header(Packet *packet, t_cli cli)
{
	UdpPacket		*udp = (UdpPacket*)packet;
	const u_short	ident = (getpid() & 0xffff) | 0x8000;

	udp->set_uh_ulen(packet, cli.packetlen);
	udp->set_ports(packet, ident, cli.port);
}

static void	__set_tcp_header(Packet *packet, t_cli cli)
{
	TcpPacket		*tcp = (TcpPacket*)packet;
	const u_short	ident = (getpid() & 0xffff) | 0x8000;

	tcp->set_flags(packet, TH_SYN);
	tcp->set_ports(packet, ident, cli.port);
	tcp->set_seq(packet, 0);
}

void	set_packet_header(Packet *packet, t_cli cli)
{
	switch (packet->type)
	{
	case IPPROTO_ICMP:
		__set_icmp_header(packet);
		break;
	case IPPROTO_UDP:
		__set_udp_header(packet, cli);
		break;
	case IPPROTO_TCP:
		__set_tcp_header(packet, cli);
		break;
	default:
		break;
	}
}
