/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malek <malek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/27 16:33:02 by malek             #+#    #+#             */
/*   Updated: 2018/07/29 16:13:28 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

static void		load(t_vm *vm, t_player *player, int adr)
{
	int i;

	i = 0;
	while (i < CHAMP_MAX_SIZE)
	{
		if (adr + i >= MEM_SIZE)
			ft_memmove(&vm->arena[(adr + i) - MEM_SIZE], &player->code[i], 1);
		else
			ft_memmove(&vm->arena[adr + i], &player->code[i], 1);
		i++;
	}
}

void			load_arena(t_vm *vm)
{
	int i;

	i = 0;
	while (i < vm->nbr_players)
	{
		load(vm, &vm->player[i], vm->player[i].address);
		i++;
	}
}
