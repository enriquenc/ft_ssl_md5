/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_vector.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmaslyan <tmaslyan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:37:28 by tmaslyan          #+#    #+#             */
/*   Updated: 2020/03/07 15:19:22 by tmaslyan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <md5.h>

t_md5_result_vector	md5_vector_init_default(void)
{
	t_md5_result_vector dest;

	dest.a = A_INIT_VALUE;
	dest.b = B_INIT_VALUE;
	dest.c = C_INIT_VALUE;
	dest.d = D_INIT_VALUE;
	return (dest);
}

t_md5_result_vector	md5_vector_copy(t_md5_result_vector dest,
										t_md5_result_vector src)
{
	dest.a = src.a;
	dest.b = src.b;
	dest.c = src.c;
	dest.d = src.d;
	return (dest);
}

t_md5_result_vector	md5_vector_add(t_md5_result_vector dest,
										t_md5_result_vector src)
{
	dest.a += src.a;
	dest.b += src.b;
	dest.c += src.c;
	dest.d += src.d;
	return (dest);
}

void				md5_rounds(t_md5_cycle_variables *var,
								t_md5_result_vector calc_vector)
{
	if (var->i < 16)
	{
		var->f = F(calc_vector.b, calc_vector.c, calc_vector.d);
		var->g = var->i;
	}
	else if (var->i < 32)
	{
		var->f = G(calc_vector.b, calc_vector.c, calc_vector.d);
		var->g = (5 * var->i + 1) % 16;
	}
	else if (var->i < 48)
	{
		var->f = H(calc_vector.b, calc_vector.c, calc_vector.d);
		var->g = (3 * var->i + 5) % 16;
	}
	else if (var->i < 64)
	{
		var->f = I(calc_vector.b, calc_vector.c, calc_vector.d);
		var->g = (7 * var->i) % 16;
	}
}
