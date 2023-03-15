/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   icmp_packet.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:35:16 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/15 15:32:08 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICMP_PACKET_H
# define ICMP_PACKET_H

# include "raw_packet.h"

typedef struct IcmpPacket {
	Packet			base;
	struct icmphdr	*header;

	void	(*set_type_code)(Packet *packet, uint8_t type, uint8_t code);
	void	(*set_un_echo)(Packet *packet, uint16_t id, uint16_t seq);
	void	(*set_echo_seq)(Packet *packet, uint16_t seq);
} IcmpPacket;

Packet	*icmp_packet_create(size_t size);
void	___set_icmp_un_echo(Packet *packet, uint16_t id, uint16_t seq);
void	___set_icmp_type_code(Packet *packet, uint8_t type, uint8_t code);
void	___set_icmp_echo_seq(Packet *packet, uint16_t seq);


#endif
