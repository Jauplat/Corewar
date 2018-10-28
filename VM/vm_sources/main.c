/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malek <malek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 18:16:02 by dhuber            #+#    #+#             */
/*   Updated: 2018/10/03 13:18:48 by jauplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"
/*
static void	print_arena(t_vm *vm)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (!((i + 1) % 64) && i)
		{
			if (vm->arena[i] >= 0x0 && vm->arena[i] <= 0xf)
				ft_printf("0%x\n", vm->arena[i++]);
			else if (vm->arena[i] < 0)
				ft_printf("%x\n", (unsigned char)vm->arena[i++]);
			else
				ft_printf("%x\n", vm->arena[i++]);
		}
		else
		{
			if (vm->arena[i] >= 0x0 && vm->arena[i] <= 0xf)
				ft_printf("0%x ", vm->arena[i++]);
			else if (vm->arena[i] < 0)
				ft_printf("%x ", (unsigned char)vm->arena[i++]);
			else
				ft_printf("%x ", vm->arena[i++]);
		}
	}
}
*/
static void	print_vm(t_vm *vm)
{
	int	i;

	i = 0;
	while (i < vm->nbr_players)
	{
		ft_printf("player %d = [%d]\n", i + 1, vm->player[i].number);
		ft_printf("address[i] = [%d]\n", vm->a[i]);
		ft_printf("player address = [%d]\n\n", vm->player[i].address);
		ft_printf("player r1 = [%d]\n\n", vm->player[i].reg[0]);
		ft_printf("vm name = [%s]\n", vm->player[i].name);
		ft_printf("{name length = [%i]}\n", ft_strlen(vm->player[i].name));
		ft_printf("vm comment = [%s]\n", vm->player[i].comment);
		ft_printf("{comment length = [%i}]\n", ft_strlen(vm->player[i].comment));
		ft_printf("vm prog_size = [%d]\n\n", vm->player[i].program_size);
		ft_printf("vm code = [%s]\n\n", vm->player[i].code);
		ft_printf("\n\t\t-----------------------------\n\n");
		i++;
	}
}

int			main(int ac, char **av)
{
	t_vm		vm;

	if (ac == 1)
		return (-1);
	init(&vm, ac, av);
	parse_flag(&vm);
	parse_champ(&vm);
	print_vm(&vm);
	load_arena(&vm);
//	print_arena(&vm);
	return (0);
}
