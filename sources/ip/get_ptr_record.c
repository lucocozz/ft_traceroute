/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ptr_record.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:20:57 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/07 18:38:23 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	get_ptr_record(struct sockaddr *from_addr, char *buffer)
{
	getnameinfo(from_addr, sizeof(*from_addr), buffer, PTR_RECORD_SIZE, NULL, 0, 0);
}
