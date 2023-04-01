/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_packet.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:06:00 by lucocozz          #+#    #+#             */
/*   Updated: 2023/04/01 19:10:53 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAW_PACKET_H
# define RAW_PACKET_H

# ifndef __USE_MISC
#  define __USE_MISC
# endif

# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <netinet/udp.h>
# include <netinet/tcp.h>
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>

# define HTONS(n) (((((unsigned short)(n) & 0xFF)) << 8) | (((unsigned short)(n) & 0xFF00) >> 8))

typedef struct s_psize {
	size_t	header;
	size_t	payload;
	size_t	total;
} t_psize;

typedef struct Packet {
	const struct PacketInterface* const vtable;
	int		type;
	void	*raw;
	char	*payload;
	t_psize	size;
} Packet;

typedef struct PacketInterface {
	void		(*destroy)(Packet*);
	void		(*checksum)(Packet*);
	uint16_t	(*get_port)(Packet*);
} PacketInterface;

Packet		*packet_create(int type, size_t size);
void		packet_destroy(Packet *packet);
void		packet_checksum(Packet *packet);
uint16_t	checksum(uint16_t *addr, size_t len);
uint16_t	get_port(Packet *packet);

# include "icmp_packet.h"
# include "udp_packet.h"
# include "tcp_packet.h"

#endif
