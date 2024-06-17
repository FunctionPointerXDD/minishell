/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanse_wild_card_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansjeo <chansjeo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:42:54 by sihong            #+#    #+#             */
/*   Updated: 2024/02/27 13:05:12 by chansjeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_expansed_s_case_key_start(t_wild_key_lst **kl, char *d_name, int *i)
{
	if ((*kl)->wild == 0)
	{
		if (ft_strncmp((*kl)->key, d_name, ft_strlen((*kl)->key)) == 0)
		{
			*i += ft_strlen((*kl)->key);
			(*kl) = (*kl)->next;
		}
		else
			return (0);
	}
	return (1);
}

int	get_expansed_s_check_key(char *d_name, int *i, t_wild_key_lst *kl)
{
	while (d_name[*i])
	{
		if (ft_strncmp(kl->next->key, &d_name[*i], \
			ft_strlen(kl->next->key)) == 0)
		{
			if (d_name[*i + ft_strlen(kl->next->key)] != 0)
			{
				if (kl->next->next == 0)
				{
					*i += ft_strlen(kl->next->key);
					continue ;
				}
				else
					break ;
			}
			else
				break ;
		}
		*i += 1;
	}
	if (d_name[*i] == 0)
		return (0);
	else
		*i += ft_strlen(kl->next->key);
	return (1);
}

void	get_expansed_s_append_s(int i, char *d_name, char **expansed_s)
{
	char	*tmp;

	if (i == (int)ft_strlen(d_name))
	{
		if (*expansed_s == 0)
			*expansed_s = ft_strdup_adv(d_name);
		else
		{
			tmp = *expansed_s;
			*expansed_s = ft_strjoin_adv(*expansed_s, " ");
			free(tmp);
			tmp = *expansed_s;
			*expansed_s = ft_strjoin_adv(*expansed_s, d_name);
			free(tmp);
		}
	}
}

void	get_expansed_s(t_wild_key_lst *kl, char *d_name, char **expansed_s)
{
	int		i;

	i = 0;
	while (kl)
	{
		if (get_expansed_s_case_key_start(&kl, d_name, &i) == 0)
			return ;
		if (kl->wild != 0)
		{
			if (kl->next == 0)
			{
				i = ft_strlen(d_name);
				break ;
			}
			else
			{
				if (get_expansed_s_check_key(d_name, &i, kl) == 0)
					return ;
				kl = kl->next->next;
			}
		}
	}
	get_expansed_s_append_s(i, d_name, expansed_s);
}
