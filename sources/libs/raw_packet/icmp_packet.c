/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp_packet.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:43:50 by lucocozz          #+#    #+#             */
/*   Updated: 2023/04/01 19:18:00 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "icmp_packet.h"

static t_psize	__set_sizes(size_t size);
static void	*__memcpy(void *dest, void const *src, size_t n);
static void	__bzero(void *s, size_t n);



/*  public  */

uint16_t	icmp_get_port(Packet *packet)
{
	(void)packet;

	return (HTONS(0));
}

void	icmp_packet_checksum(Packet *packet)
{
	IcmpPacket	*icmp = (IcmpPacket*)packet;

	icmp->header->checksum = checksum(packet->raw, packet->size.total);
}

void	icmp_packet_destroy(Packet *packet)
{
	IcmpPacket	*icmp = (IcmpPacket*)packet;

	free(packet->raw);
	free(icmp);
}

Packet	*icmp_packet_create(size_t size)
{
	static const PacketInterface	vtable = {
		.destroy = icmp_packet_destroy,
		.checksum = icmp_packet_checksum,
		.get_port = icmp_get_port
	};
	static Packet	base = {
		.vtable = &vtable,
		.type = IPPROTO_ICMP,
	};

	IcmpPacket *packet = malloc(sizeof(IcmpPacket));
	if (packet == NULL)
		return (NULL);
    __memcpy(&packet->base, &base, sizeof(Packet));
	packet->base.size = __set_sizes(size);

    /* IcmpPacket specific members */
	packet->set_type_code = ___set_icmp_type_code;
	packet->set_un_echo = ___set_icmp_un_echo;
	packet->set_echo_seq = ___set_icmp_echo_seq;

	packet->base.raw = malloc(sizeof(struct icmphdr) + size);
	if (packet->base.raw == NULL) {
		free(packet);
		return (NULL);
	}
	__bzero(packet->base.raw, sizeof(struct icmphdr) + size);

	packet->header = packet->base.raw;
	packet->base.payload = packet->base.raw + sizeof(struct icmphdr);

    return ((Packet*)(&packet->base));
}




/*  private  */

void	___set_icmp_un_echo(Packet *packet, uint16_t id, uint16_t seq)
{
	IcmpPacket	*icmp = (IcmpPacket*)packet;

	icmp->header->un.echo.id = id;
	icmp->header->un.echo.sequence = seq;
}

void	___set_icmp_echo_seq(Packet *packet, uint16_t seq)
{
	IcmpPacket	*icmp = (IcmpPacket*)packet;

	icmp->header->un.echo.sequence = seq;
}

void	___set_icmp_type_code(Packet *packet, uint8_t type, uint8_t code)
{
	IcmpPacket	*icmp = (IcmpPacket*)packet;

	icmp->header->type = type;
	icmp->header->code = code;

}

static t_psize	__set_sizes(size_t size)
{
	t_psize	psize;

	psize.header = sizeof(struct icmphdr);
	psize.payload = size;
	psize.total = sizeof(struct icmphdr) + size;
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
