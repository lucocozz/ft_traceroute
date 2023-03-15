# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lucocozz <lucocozz@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/30 15:23:20 by lucocozz          #+#    #+#              #
#    Updated: 2023/03/15 15:33:57 by lucocozz         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_traceroute

SRCS =	main.c				\
		$(_PROTOCOL)		\
		$(_IP)				\
		$(_CLI)				\
		$(_LIBS)			\
		$(_SYSTEM)			\
		$(_TRACEROUTE)		\
		$(_DISPLAY)			\
		$(_UTILS)

_TRACEROUTE =				\
	traceroute.c			\
	traceroute_queries.c

_DISPLAY = 					\
	print_header.c			\
	print_querie.c			\

_PROTOCOL =					\
	create_socket.c			\
	send_packet.c			\
	recv_packet.c			\
	set_packet_header.c		\
	update_packet_header.c

_IP =						\
	get_ip_address.c		\
	is_ip_format.c			\
	resolve_service.c		\
	get_ptr_record.c		\
	set_ttl.c

_CLI =						\
	flags_handlers.c		\
	get_cli.c				\
	parse_cli.c				\
	cli_errors.c

_SYSTEM =					\
	cleanup.c				\
	logs.c					\
	signals.c

_UTILS =					\
	get_elapsed_time.c

_LIBS =						\
	$(_RAW_PACKET)			\
	libft.c

_RAW_PACKET =				\
	raw_packet.c			\
	icmp_packet.c			\
	udp_packet.c			\
	tcp_packet.c			\
	checksum.c

OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)
DEPENDENCIES = $(OBJS:%.o=%.d)

SRCS_DIR = sources
OBJS_DIR = .objs
INCLUDES_DIR = includes includes/raw_packet $(LIBS:%=lib%/includes) $(LIBS:%=lib%)

LIBS =

MAKE = make
CC = clang
RM = rm -f
MKDIR = mkdir -p
DEBUG = off

CFLAGS = -MMD -Wall -Wextra -Werror
CXXFLAGS = $(INCLUDES_DIR:%=-I %)
ifeq ($(DEBUG), on)
	CXXFLAGS += -g3
endif
LDFLAGS = $(LIBS:%=-L lib%) $(LIBS:%=-l%)

vpath %.c	$(addprefix $(SRCS_DIR), /. $(addprefix /libs, /. /raw_packet) /protocol /cli /ip /system /utils /traceroute /display)

all:
	$(foreach LIB, ${LIBS}, ${MAKE} -C lib${LIB} ;)
	$(MAKE) $(NAME)

scan:
	scan-build $(MAKE)

$(NAME): $(OBJS) | $(LIBS:%=lib%.a)
	$(CC) $(CXXFLAGS) $^ -o $(NAME) $(LDFLAGS)

-include $(DEPENDENCIES)
$(OBJS_DIR)/%.o: %.c $(OBJS_DIR)/debug$(DEBUG) | $(OBJS_DIR) 
	$(CC) $(CFLAGS) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@ 

$(OBJS_DIR):
	$(MKDIR) $(OBJS_DIR)

lib%.a:
	$(MAKE) -C $(@:%.a=%)

$(OBJS_DIR)/debug$(DEBUG): | $(OBJS_DIR)
	$(RM) $(OBJS_DIR)/debug*
	touch $@

clean:
	$(foreach LIB, $(LIBS), $(MAKE) $@ -C lib$(LIB);)
	$(RM) -r $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME) $(foreach LIB, $(LIBS), lib$(LIB)/lib$(LIB).a)

re: fclean all

.PHONY: all clean fclean re scan
