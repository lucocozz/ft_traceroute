/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   udp_packet.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:35:16 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/15 15:56:28 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UDP_PACKET_H
# define UDP_PACKET_H

# include "raw_packet.h"

typedef struct UdpPacket {
	Packet			base;
	struct udphdr	*header;

	void	(*set_uh_ulen)(Packet *packet, size_t size);
	void	(*set_ports)(Packet *packet, uint16_t source, uint16_t dest);
	void	(*set_uh_dport)(Packet *packet, uint16_t dest);

} UdpPacket;

Packet	*udp_packet_create(size_t size);
void	___set_udp_uh_ulen(Packet *packet, size_t size);
void	___set_udp_ports(Packet *packet, uint16_t source, uint16_t dest);
void	___set_udp_uh_dport(Packet *packet, uint16_t dest);

#endif
