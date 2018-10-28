/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malek <malek@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 12:55:59 by dhuber            #+#    #+#             */
/*   Updated: 2018/07/29 17:03:20 by dhuber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../vm_includes/virtual_machine.h"

static void		check_null_octet(t_vm *vm, int fd, int k)
{
	int		i;
	char	octet[4];

	read(fd, octet, 4);
	i = 0;
	while (i < 4)
	{
		if (octet[i] != 0 && !k)
			vm_error(vm, "Champ name too long.", "", 1);
		else if (octet[i] != 0 && k)
			vm_error(vm, "Champ comment too long.", "", 1);
		i++;
	}
}

static void		parse_name(t_vm *vm, int nbr, int fd)
{
	ssize_t			ret;
	char			*cpy;
	unsigned char	magic_nbr[8];
	char			name[PROG_NAME_LENGTH + 1];

	cpy = vm->player[nbr].name;
	ft_bzero(magic_nbr, 9);
	ft_bzero(name, PROG_NAME_LENGTH + 1);
	read(fd, magic_nbr, 4);
	convert_memory(magic_nbr, 8);
	if (ft_strncmp((char*)magic_nbr, "00ea83f3", 8))
		vm_error(vm, "Wrong Exec_Magic.", (char*)magic_nbr, 1);
	if ((ret = read(fd, name, PROG_NAME_LENGTH)) == -1)
		vm_error(vm, "Can't read file.", "", 1);
	ft_memmove(cpy, name, PROG_NAME_LENGTH + 1);
}

static void		parse_comment(t_vm *vm, int nbr, int fd)
{
	ssize_t				ret;
	char				*cpy;
	unsigned char		octet[8];
	char				comment[COMMENT_LENGTH + 1];

	cpy = vm->player[nbr].comment;
	ft_bzero(octet, 9);
	ft_bzero(comment, COMMENT_LENGTH);
	read(fd, octet, 4);
	convert_memory(octet, 8);
	vm->player[nbr].program_size = ft_atoi_base((const char*)&octet[0], 16);
	if (vm->player[nbr].program_size > CHAMP_MAX_SIZE)
		vm_error(vm, "Champ too big.", "", 1);
	if ((ret = read(fd, comment, COMMENT_LENGTH)) == -1)
		vm_error(vm, "Can't read file.", "", 1);
	ft_memmove(cpy, comment, COMMENT_LENGTH + 1);
}

static void		parse_code(t_vm *vm, int nbr, int fd)
{
	ssize_t				ret;
	unsigned char		*cpy;
	unsigned char		code[CHAMP_MAX_SIZE + 1];

	cpy = vm->player[nbr].code;
	ft_bzero(code, CHAMP_MAX_SIZE + 1);
	if ((ret = read(fd, code, CHAMP_MAX_SIZE)) == -1)
		vm_error(vm, "Can't read file.", "", 1);
	ft_memmove(cpy, code, CHAMP_MAX_SIZE + 1);
}

void			parse_champ(t_vm *vm)
{
	int		nbr;
	int		fd;
	char	**tmp;

	tmp = (vm->av + 1);
	nbr = 0;
	while (*tmp)
	{
		if (ft_strstr(*tmp, ".cor"))
		{
			if ((fd = open(*tmp, O_RDONLY)) < 0)
				vm_error(vm, "Fail to read champ : ", *tmp, 1);
			init_champ(vm, &vm->player[nbr], nbr);
			parse_name(vm, nbr, fd);
			check_null_octet(vm, fd, 0);
			parse_comment(vm, nbr, fd);
			check_null_octet(vm, fd, 1);
			parse_code(vm, nbr++, fd);
			if (close(fd) == -1)
				vm_error(vm, "Can't close file.", "", 1);
		}
		tmp += 1;
	}
	ft_place_champ(vm);
}
