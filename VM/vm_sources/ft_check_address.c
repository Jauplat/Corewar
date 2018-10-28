/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_address.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamel <mkamel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 16:01:14 by mkamel            #+#    #+#             */
/*   Updated: 2018/07/25 17:31:44 by mkamel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"
#define MAX_3 ((address[0] > address[1]) ? address[0] : address[1])
#define MIN_3 ((address[0] < address[1]) ? address[0] : address[1])
#define MID_3 (MAX_3 - MIN_3)
#define MAD_3 ((MAX_3 + ((MEM_SIZE - MAX_3 + MIN_3) / 2)) % MEM_SIZE)

void		ft_fill_vma(t_vm *vm, int *address, int x, int j)
{
	int		i;

	i = 0;
	while (i < x)
	{
		vm->a[i] == -1 ? vm->a[i] = address[j++] : 0;
		i++;
	}
}

void		ft_three(t_vm *vm, int j, int x, int i)
{
	int		address[x];
	int		nb;

	nb = 0;
	while (nb != x)
	{
		if (vm->a[nb] != -1)
		{
			address[i] = vm->a[nb];
			i++;
		}
		nb++;
	}
	if (j == 1)
	{
		address[1] = ((address[0] + (MEM_SIZE / 3)) % MEM_SIZE);
		address[2] = ((address[1] + (MEM_SIZE / 3)) % MEM_SIZE);
		ft_fill_vma(vm, address, x, 1);
	}
	else if (j == 2)
	{
		address[2] = (MID_3 >= (MEM_SIZE / 2)) ? (MAX_3 - (MID_3 / 2)) : MAD_3;
		ft_fill_vma(vm, address, x, 2);
	}
}

void		ft_check_ad(t_vm *vm, int x, int j)
{
	int		ad;
	int		i;

	ad = 0;
	if (x == 2 && j != 2)
	{
		i = (vm->a[0] == -1) ? 1 : 0;
		ad = ((vm->a[i] + (MEM_SIZE / 2)) % MEM_SIZE);
		i = (vm->a[0] == -1) ? 0 : 1;
		vm->a[i] = ad;
	}
	else if (x == 3 && j != 3)
		ft_three(vm, j, x, 0);
	else if (x == 4 && j != 4)
		ft_four(vm, j, x, 0);
}
