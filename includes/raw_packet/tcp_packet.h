/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tcp_packet.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 15:35:16 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/15 15:56:24 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TCP_PACKET_H
# define TCP_PACKET_H

# include "raw_packet.h"

typedef struct TcpPacket {
	Packet			base;
	struct tcphdr	*header;

	void	(*set_ports)(Packet *packet, uint16_t source, uint16_t dest);
	void	(*set_flags)(Packet *packet, int flags);
	void	(*set_seq)(Packet *packet, int seq);
	void	(*set_th_dport)(Packet *packet, uint16_t dest);
} TcpPacket;

Packet	*tcp_packet_create(size_t size);
void	___set_tcp_ports(Packet *packet, uint16_t source, uint16_t dest);
void	___set_tcp_flags(Packet *packet, int flags);
void	___set_tcp_seq(Packet *packet, int seq);
void	___set_tcp_th_dport(Packet *packet, uint16_t dest);

#endif
