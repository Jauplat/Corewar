/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   virtual_machine.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhuber <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 16:31:40 by dhuber            #+#    #+#             */
/*   Updated: 2018/07/29 16:31:44 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIRTUAL_MACHINE_H
# define VIRTUAL_MACHINE_H
# include "op.h"
# include "../ft_printf/includes/ft_printf.h"

typedef struct		s_op
{
	char			*name;
}					t_op;

typedef struct		s_cursor
{
	int				adr;
}					t_cursor;

typedef struct		s_player
{
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	unsigned char	code[CHAMP_MAX_SIZE + 1];
	int				program_size;
	int				number;
	int				address;
	int				lives;
	int				*start;
	int				carry;
	int				fork;
	int				color;
	int				pc;
	int				reg[REG_NUMBER];
	struct s_player	*next;
}					t_player;

typedef struct		s_vm
{
	char			**av;
	int				ac;
	int				v;
	int				cursors;
	int				dump;
	int				nbr_players;
	int				n[MAX_PLAYERS];
	int				a[MAX_PLAYERS];
	int				cycle;
	int				cycles_to_die;
	int				check;
	int				nbr_live;
	int				last_live;
	char			winner_name[PROG_NAME_LENGTH + 1];
	char			arena[MEM_SIZE + 1];
	t_player		player[MAX_PLAYERS + 1];
	t_cursor		*head;
	t_op			op_tab[17];
}					t_vm;

void				virtual_machine(t_vm *vm);
void				init(t_vm *vm, int ac, char **av);
void				parse_flag(t_vm *vm);
void				unknown_instruction(t_vm *vm, char *av, char *next);
void				valid_extension(t_vm *vm, char *av);
void				vm_error(t_vm *vm, char *msg, char *type, int n);
int					vm_isdigit(const char *s);
long long			vm_atoll(const char *s, t_vm *vm);

void				parse_champ(t_vm *vm);
void				init_champ(t_vm *vm, t_player *player, int i);
void				ft_place_champ(t_vm *vm);
void				ft_check_ad(t_vm *vm, int x, int j);
void				ft_four(t_vm *vm, int j, int x, int i);
void				ft_fill_vma(t_vm *vm, int *address, int x, int j);

void				load_arena(t_vm *vm);

#endif
