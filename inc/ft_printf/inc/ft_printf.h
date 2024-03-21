/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:56:49 by iostancu          #+#    #+#             */
/*   Updated: 2024/03/13 23:14:42 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <stdlib.h>
# include <limits.h>
# include <stdarg.h>
# include <unistd.h>
# define TRUE 1
# define FALSE 0
# define HEX "0123456789abcdef"
# define UPHEX "0123456789ABCDEF"

int				ft_printf(const char *frmt, ...);
int				ft_putchar(va_list ap);
int				ft_putnbr(va_list ap);
int				ft_putstr(va_list ap);
int				ft_putnbrbase(va_list ap);
unsigned int	ft_unsignednbr(va_list ap);
unsigned int	ft_nbrbase_lu(va_list ap, int isup);

#endif
