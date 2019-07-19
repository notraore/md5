/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digest.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: notraore <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:36:15 by notraore          #+#    #+#             */
/*   Updated: 2019/05/15 15:36:17 by notraore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "md5.h"

/******************* MD5 *******************/
unsigned		f_zero(unsigned abcd[])
{
	return ((abcd[1] & abcd[2]) | (~abcd[1] & abcd[3]));
}

unsigned		f_one(unsigned abcd[])
{
	return ((abcd[3] & abcd[1]) | (~abcd[3] & abcd[2]));
}

unsigned		f_two(unsigned abcd[])
{
	return (abcd[1] ^ abcd[2] ^ abcd[3]);
}

unsigned		f_three(unsigned abcd[])
{
	return (abcd[2] ^ (abcd[1] | ~abcd[3]));
}
