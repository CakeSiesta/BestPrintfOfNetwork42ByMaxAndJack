/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jherrald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 08:48:06 by jherrald          #+#    #+#             */
/*   Updated: 2020/02/28 10:57:45 by jherrald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		fill_put_c(t_f *f, t_put *put)
{
	init_put(put);
	if (f->width > 1)
		put->width = f->width - 1;
}

void			convers_c(va_list arg, t_f *f, t_put *put, int i)
{
	char c;

	fill_put_c(f, put);
	if (i)
		c = '%';
	if (i && f->zero)
	{
		while (put->width > 0)
		{
			ft_write('0', put);
			put->width--;
		}
		ft_write(c, put);
		return ;
	}
	if (!i)
		c = va_arg(arg, int);
	if (put->width && f->minus)
	{
		ft_write(c, put);
		while (put->width--)
			ft_write(' ', put);
	}
	else if (put->width && !f->minus)
	{
		while (put->width--)
			ft_write(' ', put);
		ft_write(c, put);
	}
	if (!put->width)
		ft_write(c, put);
}
