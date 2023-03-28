/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recv_packet.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 11:07:12 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/07 19:20:40 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

struct msghdr	__init_msg(struct sockaddr_in *src_addr, struct iovec *iov)
{
	struct msghdr	msg = {0};
	int				ctrl_buffer[CMSG_SPACE(sizeof(int))];
	
	msg.msg_name = src_addr;
	msg.msg_namelen = sizeof(*src_addr);
	msg.msg_iov = iov;
	msg.msg_iovlen = 1;
	msg.msg_control = ctrl_buffer;
	msg.msg_controllen = CMSG_SPACE(sizeof(ctrl_buffer));
	return (msg);
}

static short	__get_error(int bytes)
{
	if (bytes == -1)
	{
		if (errno == EINTR)
			return (INTERRUPTED);
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return (ERR_TIMEOUT);
		return (ERR_UNDEFINED);
	}
	return (NOERROR);
}

t_querie	recv_packet(int socket, int family)
{
	struct iovec		iov;
	struct msghdr		msg;
	struct sockaddr_in	from_addr;
	char				buffer[MSG_BUFFER_SIZE];
	t_querie			data = {0};

	iov.iov_base = buffer;
	iov.iov_len = MSG_BUFFER_SIZE;
	msg = __init_msg(&from_addr, &iov);
	data.bytes = recvmsg(socket, &msg, 0);
	data.error = __get_error(data.bytes);
	if (data.error == NOERROR) {
		inet_ntop(family, &from_addr.sin_addr, data.address, GET_ADDRLEN(family));
		get_ptr_record((struct sockaddr *)&from_addr, data.ptr_record);
		if (*data.ptr_record == '\0')
			ft_strcpy(data.ptr_record, data.address);
	}
	return (data);
}
