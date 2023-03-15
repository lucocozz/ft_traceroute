/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_traceroute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 18:01:43 by user42            #+#    #+#             */
/*   Updated: 2023/01/27 16:46:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

/*
https://www.gnu.org/software/libc/manual/html_node/Feature-Test-Macros.html
https://man7.org/linux/man-pages/man7/feature_test_macros.7.html
*/
# define _GNU_SOURCE

# include <netdb.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/time.h>
# include <arpa/inet.h>
# include <signal.h>
# include <stdint.h>
# include <stdbool.h>
# include <string.h>
# include <errno.h>
# include <ifaddrs.h>
# include <linux/if_ether.h>
# include <linux/filter.h>
# include "raw_packet.h"
# include "libft.h"

# define GET_LEVEL(family) (family == PF_INET ? IPPROTO_IP : IPPROTO_IPV6)
# define GET_ADDRLEN(family) (family == PF_INET ? INET_ADDRSTRLEN : INET6_ADDRSTRLEN)
# define HTONS(n) (((((unsigned short)(n) & 0xFF)) << 8) | (((unsigned short)(n) & 0xFF00) >> 8))

# define EXIT_ERROR 2
# define MSG_BUFFER_SIZE 2048
# define PTR_RECORD_SIZE 255
# define MAX_ADDR_LEN 48

# define DFT_INTERVAL 0
# define DFT_FIRST_TTL 1
# define DFT_MAX_TTL 30
# define DFT_FAMILY PF_INET
# define DFT_QUERIES 3
# define DFT_TCP_PORT 80
# define DFT_UDP_PORT 53
# define DFT_ICMP_PORT 33434
# define DFT_PORT DFT_UDP_PORT
# define DFT_HOST NULL
# define DFT_SOCKTYPE SOCK_DGRAM
# define DFT_PROTOTYPE IPPROTO_UDP
# define DFT_PACKETLEN 40
# define DFT_TIMEOUT 5

# define NOERROR 0
# define INTERRUPTED -2
# define ERR_UNDEFINED -1
# define ERR_TTL_EXCEEPTED 1
# define ERR_TIMEOUT 2
# define ERR_NET_UNREACHABLE 3
# define ERR_WRONG_ID 4
# define ERR_SEND 5

# define TRACEROUTE_HELP											\
"Usage\n"															\
"  ft_traceroute [-46ITn] [ -f first_ttl ] [ -m max_ttl ] [ -N squeries ] [ -p port ] host [ packetlen ]\n\n"	\
"Options:\n"														\
"  -4\t\t\t\tUse IPv4\n"													\
"  -6\t\t\t\tUse IPv6\n"													\
"  -f first_ttl  --first=first_ttl\n\t\t\t\tStart from the first_ttl hop (instead from 1)\n"			\
"  -I  --icmp\t\t\tUse ICMP ECHO for tracerouting\n"						\
"  -T  --tcp\t\t\tUse TCP SYN for tracerouting (default port is 80)\n"	\
"  -m max_ttl  --max-hops=max_ttl\n\t\t\t\tSet the max number of hops (max TTL to be\n\t\t\t\treached). Default is 30\n" \
"  -p port  --port=port\t\tSet the destination port to use. It is either\n\t\t\t\tinitial udp port value for \"default\" method\n\t\t\t\t(incremented by each probe, default is 33434), or\n\t\t\t\tinitial seq for \"icmp\" (incremented as well,\n\t\t\t\tdefault from 1), or some constant destination\n\t\t\t\tport for other methods (with default of 80 for\n\t\t\t\t\"tcp\", 53 for \"udp\", etc.)\n" \
"  -q queries  --queries=nqueries\n\t\t\t\tSet the number of probes per each hop. Default is\n\t\t\t\t3\n" \
"  --help\t\t\tRead this help and exit\n" \
"\nArguments:\n"													\
"+    host\t\tThe Host to traceroute to\n"							\
"     packetlen\t\tThe full packet lenght (default is the lenght of an IP\n\t\t\theader plus 40). Can be ignored or increased to a minimal\n\t\t\tallowed value\n"

typedef struct s_cli
{
	char			*host;
	int				interval;
	int				family;
	short			first_ttl;
	short			max_ttl;
	short			queries;
	uint			port;
	uint			socktype;
	uint			prototype;
	uint			packetlen;
}	t_cli;

typedef struct s_options
{
	char	*flag;
	bool	has_argument;
	char	*help;
	int		(*handler)(t_cli *, char *);
}	t_options;

typedef struct s_querie
{
	int		bytes;
	char	ptr_record[PTR_RECORD_SIZE];
	char	address[MAX_ADDR_LEN];
	float	time;
	short	error;
}	t_querie;

/* system */
void	warn(const char *msg);
void	fatal(short status, const char *msg);
void	cleanup(int socket, struct addrinfo *address);
void	set_signals_handlers(void);

/* protocol */
int			create_socket(struct addrinfo *address);
int			send_packet(int socket, Packet *packet, struct addrinfo *address);
t_querie	recv_packet(int socket, int family);
void		set_packet_header(Packet *packet, t_cli cli);
void		update_packet_header(Packet *packet, t_cli cli, int seq);

/* ip */
char			*get_ip_address(struct addrinfo *address);
struct addrinfo	*resolve_service(t_cli cli);
bool			is_ip_format(int family, char *ip);
void			get_ptr_record(struct sockaddr *from_addr, char *buffer);
int				set_ttl(int socket, int level, short ttl);

/* utils */
float	get_elapsed_time(struct timeval start, struct timeval end);

/* traceroute */
int			traceroute(t_cli cli, struct addrinfo *address, int socket);
t_querie	traceroute_queries(int socket, Packet *packet, struct addrinfo *address);

/* display */
void	print_header(t_cli cli, char *ip, Packet *packet);
void	print_querie(t_querie querie);

/* cli */
t_cli	get_cli(int argc, char **argv);
t_cli	parse_cli(int argc, char **argv);

void	missing_arg_error(char *flag, int argc, char *help);
void	arg_error(char *flag, char *argument, int argc);
void	bad_option(char *flag, int argc);
void	packetlen_error(char *argument, int argc);
void	extra_arg_error(char *argument, int argc);
int		handle_packetlen(t_cli *cli, char *argument);
int		handle_flag_help(t_cli *cli, char *argument);
int		handle_flag_4(t_cli *cli, char *argument);
int		handle_flag_6(t_cli *cli, char *argument);
int		handle_flag_icmp(t_cli *cli, char *argument);
int		handle_flag_tcp(t_cli *cli, char *argument);
int		handle_flag_udp(t_cli *cli, char *argument);
int		handle_flag_first(t_cli *cli, char *argument);
int		handle_flag_max(t_cli *cli, char *argument);
int		handle_flag_port(t_cli *cli, char *argument);
int		handle_flag_queries(t_cli *cli, char *argument);

#endif
