/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jauplat <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 17:57:55 by jauplat           #+#    #+#             */
/*   Updated: 2018/10/07 15:48:44 by jauplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../asm_includes/asm.h"

/*
**	copy the string to the name and check this size
*/

void	name_copy(char *s, t_header *head)
{
	int		i;
	int		j;

	j = 0;
	i = ft_strlen(head->name);
	while (s[j] && s[j] != '"' && i < PROG_NAME_LENGTH)
	{
		head->name[i] = s[j];
		j++;
		i++;
	}
	if (s[j] == '\0')
	{
		head->name[i] = '\n';
		i += 1;
	}
	if (i == PROG_NAME_LENGTH)
		error(-4);
	if (s[j] == '"')
	{
		if (s[j + 1])
			error(-4);
	}
}

/*
**	get the first double quote (limit of name)
**	and continue while the second is missing
*/

void	name(t_header *head, int fd, char **str, int j)
{
	int		i;
	int		r;

	i = 0;
	if (!str || !str[0] || !str[0][0])
		((r = get_next_line(fd, &str[0]) <= 0)) ? error(-2) : NULL;
	if (j == 0)
		i = index_quote(str[0]);
	j += check_quote(str[0]);
	if (j > 2)
		error(-4);
	if (j > 0)
		name_copy(str[0] + i, head);
	if (j < 2)
	{
		ft_strdel(&str[0]);
		name(head, fd, &str[0], j);
	}
}

/*
**	principaly function to the treatment of label
*/

void	label(t_champ *begin, char **str)
{
	t_champ	*list;

	list = begin;
	while (list->next)
		list = list->next;
	if (list->label[0] != '\0')
	{
		list->next = init_champ();
		list = list->next;
	}
	add_label(list, &str[0][0]);
	if (begin->next)
		check_label(begin, list);
	memset(&str[0][0], ' ', ft_strlen(list->label) + 1);
	list->adr = begin->prog_size;
}

/*
**	check if we haven't same label
*/

void	check_label(t_champ *begin, t_champ *list)
{
	t_champ	*tmp;

	tmp = begin;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->label, list->label) == 0)
			error(-7);
		tmp = tmp->next;
	}
}

/*
**	add new label and check if is it valid
*/

void	add_label(t_champ *list, char *str)
{
	int		i;
	char	*tmp;

	tmp = LABEL_CHARS;
	i = 1;
	if (ft_strchr(tmp, str[0]))
	{
		while (str[i] != LABEL_CHAR)
		{
			if (ft_strchr(tmp, str[i]))
				i++;
			else if (!ft_strchr(tmp, str[i]))
				error(-6);
		}
		ft_strncpy(list->label, (char*)str, (size_t)i);
	}
	else
		error(-6);
}
