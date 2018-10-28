/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malek <malek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 18:03:16 by dhuber            #+#    #+#             */
/*   Updated: 2018/10/03 13:18:46 by jauplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

void		init_champ(t_vm *vm, t_player *player, int i)
{
	ft_memset(player->name, 0, PROG_NAME_LENGTH + 1);
	ft_bzero(player->comment, COMMENT_LENGTH + 1);
	ft_memset(player->code, 0, CHAMP_MAX_SIZE + 1);
	player->number = vm->n[i];
	if (vm->n[i] == -1)
		player->number = i + 1;
	player->address = vm->a[i];
	player->reg[0] = player->number;
	player->lives = 0;
	player->carry = 0;
	player->pc = 0;
}

void		init(t_vm *vm, int ac, char **av)
{
	vm->av = av;
	vm->ac = ac;
	vm->v = 0;
	vm->cursors = 0;
	vm->dump = -1;
	vm->cycle = 0;
	vm->nbr_players = 0;
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->check = 0;
	vm->nbr_live = 0;
	vm->last_live = 0;
	ft_memset(vm->n, -1, sizeof(vm->n) + 1);
	ft_memset(vm->a, -1, sizeof(vm->a) + 1);
	ft_memset(vm->arena, 0, MEM_SIZE + 1);
}
