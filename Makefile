#!/usr/bin/make -f

################################################################################
# SETTINGS                                                                     #
################################################################################

PRJ = lem-in
CC = gcc
CFLAGS += -Wall -Werror -Wextra -Wimplicit -g -fsanitize=address
PRJ_SRC_DIR = src
PRJ_OBJ_DIR = obj
PRJ_SRC = \
	load\
	main\
	room\
	room_helper\
	util
PRJ_OBJ = $(patsubst %, $(PRJ_OBJ_DIR)/%.o, $(PRJ_SRC))
PRJ_INC = -I inc
LIBFT_DIR = libft
LIBFT_SRC_DIR = $(LIBFT_DIR)/src
LIBFT_OBJ_DIR = $(LIBFT_DIR)/obj
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_SRC = \
	ft_memalloc\
	ft_memcpy\
	ft_memdel\
	ft_memmove\
	ft_memset\
	ft_strchr\
	ft_strcmp\
	ft_stpcpy\
	ft_strdup\
	ft_strlen\
	ft_strsub\
	get_next_line
LIBFT_OBJ = $(patsubst %, $(LIBFT_OBJ_DIR)/%.o, $(LIBFT_SRC))
LIBFT_INC = -I $(LIBFT_DIR)/inc

################################################################################
# DISPLAY                                                                      #
################################################################################

COLSIZE = 50
NC = \033[0m
GREEN = \033[1;32m
RED = \033[1;31m
YELLOW = \033[1;33m

################################################################################
# RULES                                                                        #
################################################################################

all: $(PRJ)

$(PRJ): $(LIBFT) $(PRJ_OBJ)
	@printf "$(YELLOW)%-$(COLSIZE)s$(NC)" "Building $@... "
	@$(CC) $(CFLAGS) $(LIBFT) $(PRJ_OBJ) -o $@
	@echo "$(GREEN)DONE$(NC)"

$(PRJ_OBJ_DIR)/%.o: $(PRJ_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo " > Compiling $<..."
	@$(CC) $(CFLAGS) $(PRJ_INC) $(LIBFT_INC) -c $< -o $@

$(LIBFT): $(LIBFT_OBJ)
	@ar -rcs $@ $(LIBFT_OBJ)
	@echo "$(GREEN)DONE$(NC)"

$(LIBFT_OBJ_DIR)/%.o: $(LIBFT).lock $(LIBFT_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(LIBFT_INC) -c $(lastword $^) -o $@

$(LIBFT).lock:
	@printf "$(YELLOW)%-$(COLSIZE)s$(NC)" "Building $(LIBFT)... "
	@touch $(LIBFT).lock

clean:
	@rm -rf $(PRJ_OBJ_DIR)
	@rm -rf $(LIBFT_OBJ_DIR)
	@rm -f $(LIBFT)
	@rm -f $(LIBFT).lock
	@echo "$(RED)Object files removed$(NC)"

fclean: clean
	@rm -f $(PRJ)
	@echo "$(RED)$(PRJ) removed"

re: fclean all
