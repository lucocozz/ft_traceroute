/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 15:28:15 by lucocozz          #+#    #+#             */
/*   Updated: 2023/03/28 18:29:14 by lucocozz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_traceroute.h"

void	handle_sigint(int signum)
{
	(void)signum;
}

void	set_signals_handlers(void)
{
	// signal(SIGINT, &handle_sigint);
}

