/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convers_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jherrald <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 22:58:23 by jherrald          #+#    #+#             */
/*   Updated: 2020/02/27 15:04:01 by jherrald         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	apply_zero(t_f *f, t_put *put, t_llu nb, int x)
{
	while (put->width--)
		ft_write('0', put);
	ft_hexa_min(nb, put, x);
}

static void	apply_minus(t_f *f, t_put *put, t_llu nb, int x)
{
	if (f->precision > 0)
		while (put->precision--)
			ft_write('0', put);
	ft_hexa_min(nb, put, x);
	while (put->width--)
		ft_write(' ', put);
}

static void	apply_width(t_f *f, t_put *put, t_llu nb, int x)
{
	while (put->width--)
		ft_write(' ', put);
	while (put->precision--)
		ft_write('0', put);
	ft_hexa_min(nb, put, x);
}

static void	apply_precision(t_f *f, t_put *put, t_llu nb, int x)
{
	while (put->precision--)
		ft_write('0', put);
	ft_hexa_min(nb, put, x);

}

static void	apply_precision_param_zero(t_f *f, t_put *put, t_llu nb, int x)
{
	if (f->precision == 0 && nb == 0)
		while (f->width--)
			ft_write(' ', put);
	if (nb != 0)
		ft_hexa_min(nb, put, x);
}

void		convers_x(va_list arg, t_f *f, t_put *put, int x)
{
	t_llu		nb;

	nb = va_arg(arg, t_llu);
	put->len = ft_lenght_hex(nb);
	init_put(put);
	fill_put(f, put);
	if (nb == 0 && !f->width && f->precision == -1)
		ft_hexa_min(nb, put, x);
	if ((f->precision == 0 && nb == 0) || (!put->precision && !put->width
		&& !f->zero && !f->minus))
	{
		apply_precision_param_zero(f, put, nb, x);
		return ;
	}
	if (f->zero && f->width && !f->minus)
		apply_zero(f, put, nb, x);
	else if (f->minus && f->width && !f->zero)
		apply_minus(f, put, nb, x);
	else if (!f->minus && !f->zero && put->width)
		apply_width(f, put, nb, x);
	if (put->precision && !put->width && !f->zero && !f->minus)
		apply_precision(f, put, nb, x);
}