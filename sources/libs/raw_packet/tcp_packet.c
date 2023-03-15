/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp_packet.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:43:50 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/15 15:44:04 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tcp_packet.h"

static t_psize	__set_sizes(size_t size);
static void	*__memcpy(void *dest, void const *src, size_t n);
static void	__bzero(void *s, size_t n);



/*  public  */

void	tcp_packet_checksum(Packet *packet)
{
	TcpPacket	*tcp = (TcpPacket*)packet;

	tcp->header->check = checksum(packet->raw, packet->size.total);
}

void	tcp_packet_destroy(Packet *packet)
{
	TcpPacket	*tcp = (TcpPacket*)packet;

	free(packet->raw);
	free(tcp);
}

Packet	*tcp_packet_create(size_t size)
{
	static const PacketInterface	vtable = {
		.destroy = tcp_packet_destroy,
		.checksum = tcp_packet_checksum
	};
	static Packet	base = {
		.vtable= &vtable,
		.type = IPPROTO_TCP,
	};

	TcpPacket *packet = malloc(sizeof(TcpPacket));
	if (packet == NULL)
		return (NULL);
    __memcpy(&packet->base, &base, sizeof(Packet));
	packet->base->size = __set_sizes(size);

    /* TcpPacket specific members */
	packet->set_ports = ___set_tcp_ports;
	packet->set_flags = ___set_tcp_flags;
	packet->set_seq = ___set_tcp_seq;
	packet->set_th_dport = ___set_tcp_th_dport;

	packet->base->raw = malloc(sizeof(struct tcphdr) + size);
	if (packet->base->raw == NULL) {
		free(packet);
		return (NULL);
	}
	__bzero(packet->base->raw, sizeof(struct tcphdr) + size);

	packet->header = packet->base->raw;
	packet->base->payload = packet->base->raw + sizeof(struct tcphdr);

    return ((Packet*)(&packet->base));
}




/*  private  */

void	___set_tcp_flags(Packet *packet, int flags)
{
	TcpPacket	*tcp = (TcpPacket*)packet;

	tcp->header->th_flags = flags;
}

void	___set_tcp_ports(Packet *packet, uint16_t source, uint16_t dest)
{
	TcpPacket	*tcp = (TcpPacket*)packet;

	tcp->header->th_sport = HTONS(source);
	tcp->header->th_dport = HTONS(dest);
}

void	___set_tcp_th_dport(Packet *packet, uint16_t dest)
{
	TcpPacket	*tcp = (TcpPacket*)packet;

	tcp->header->th_dport = HTONS(dest);
}

void	___set_tcp_seq(Packet *packet, int seq)
{
	TcpPacket	*tcp = (TcpPacket*)packet;

	tcp->header->th_seq = seq;
}

static t_psize	__set_sizes(size_t size)
{
	t_psize	psize;

	psize.header = sizeof(struct tcphdr);
	psize.payload = size;
	psize.total = sizeof(struct tcphdr) + size;
	return (psize);
}





/*  utils  */

static void	*__memcpy(void *dest, void const *src, size_t n)
{
	char		*d = dest;
	const char	*s = src;

	while (n--)
		*d++ = *s++;
	return (dest);
}

static void	__bzero(void *s, size_t n)
{
	unsigned char	*ptr = s;

	for (unsigned int i = 0; i < n; ++i)
		ptr[i] = 0;
}
