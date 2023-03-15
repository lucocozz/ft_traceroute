/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checksum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 23:54:23 by lucocozz          #+#    #+#             */
/*   Updated: 2023/02/21 16:10:06 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

uint16_t checksum(uint16_t *addr, size_t len)
{
    int			sum = 0;
    int			nleft = len;
    uint16_t	*tmp = addr;
    uint16_t	answer = 0;

    while (nleft > 1) {
        sum += *tmp++;
        nleft -= 2;
    }
    if (nleft == 1) {
        *(u_char *)(&answer) = *(u_char *)tmp;
        sum += answer;
    }
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    answer = ~sum;
    return (answer);
}
