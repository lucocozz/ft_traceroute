/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   udp_packet.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:43:50 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/15 15:43:47 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "udp_packet.h"

void			__set_udp_uh_ulen(Packet *packet, size_t size);
static t_psize	__set_sizes(size_t size);
static void	*__memcpy(void *dest, void const *src, size_t n);
static void	__bzero(void *s, size_t n);



/*  public  */



void	udp_packet_checksum(Packet *packet)
{
	UdpPacket	*udp = (UdpPacket*)packet;

	udp->header->uh_sum = checksum(packet->raw, packet->size.total);
}

void	udp_packet_destroy(Packet *packet)
{
	UdpPacket	*udp = (UdpPacket*)packet;

	free(packet->raw);
	free(udp);
}

Packet	*udp_packet_create(size_t size)
{
	static const PacketInterface	vtable = {
		.destroy = udp_packet_destroy,
		.checksum = udp_packet_checksum
	};
	static Packet	base = {
		.vtable = &vtable,
		.type = IPPROTO_UDP,
	};

	UdpPacket *packet = malloc(sizeof(UdpPacket));
	if (packet == NULL)
		return (NULL);
    __memcpy(&packet->base, &base, sizeof(Packet));
	packet->base->size = __set_sizes(size);

    /* UdpPacket specific members */
	packet->set_uh_ulen = ___set_udp_uh_ulen;
	packet->set_ports = ___set_udp_ports;
	packet->set_uh_dport = ___set_udp_uh_dport;

	packet->base->raw = malloc(sizeof(struct udphdr) + size);
	if (packet->base->raw == NULL) {
		free(packet);
		return (NULL);
	}
	__bzero(packet->base->raw, sizeof(struct udphdr) + size);

	packet->header = packet->base->raw;
	packet->base->payload = packet->base->raw + sizeof(struct udphdr);

    return ((Packet*)(&packet->base));
}




/*  private  */

void	___set_udp_ports(Packet *packet, uint16_t source, uint16_t dest)
{
	UdpPacket	*udp = (UdpPacket*)packet;
	
	udp->header->uh_sport = HTONS(source);
	udp->header->uh_dport = HTONS(dest);
}

void	___set_udp_uh_ulen(Packet *packet, size_t size)
{
	UdpPacket	*udp = (UdpPacket*)packet;

	udp->header->uh_ulen = HTONS(sizeof(struct udphdr) + size);
}

void	___set_udp_uh_dport(Packet *packet, uint16_t dest)
{
	UdpPacket	*udp = (UdpPacket*)packet;

	udp->header->uh_dport = HTONS(dest);
}

static t_psize	__set_sizes(size_t size)
{
	t_psize	psize;

	psize.header = sizeof(struct udphdr);
	psize.payload = size;
	psize.total = sizeof(struct udphdr) + size;
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
