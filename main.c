#include "md5.h"

unsigned f_zero(unsigned b, unsigned c, unsigned d)
{
	return ((b & c) | (~b & d));
}

unsigned f_one(unsigned b, unsigned c, unsigned d)
{
	return ((d & b) | (~d & c));
}

unsigned f_two(unsigned b, unsigned c, unsigned d)
{
	return (b ^ c ^ d);
}

unsigned f_three(unsigned b, unsigned c, unsigned d)
{
	return (c ^ (b |~d));
}

double			my_pow(double x, int y)
{
	int		i;
	double value;

	i = 0;
	value = 1;

	if (y == 0)
		return (1.0f);
	else if (x == 0)
		return (0.0f);
	while (i < ABS(y))
	{
		value *= x;
		i++;
	}
	if (y < 0)
		return (1.0f / value);
	else
		return value;
}

unsigned		*calc(unsigned *ks)
{
	int		i;
	double	s;
	double	pwr;

	i = 0;
	pwr = my_pow(2, 32);
	while (i < 64)
	{
		s = fabs(sin(1 + i));
		ks[i] = (unsigned)(s * pwr);
		i++;
	}
	return (ks);
}

unsigned		rol(unsigned v, short amt)
{
	unsigned msk = (1 << amt) -1;
	return (((v >> (32 - amt)) & msk) | ((v << amt) & ~msk));
}

unsigned		mdf(const char *msg, int msglen)
{
	typedef unsigned Digest[4];
	(void)(msg);
	(void)(msglen);

	static Digest h0 = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};
	printf("%d\n", h0[0]);
	return (1);
}

int main(void)
{
	char *line;

	get_next_line(0, &line);
	ft_putendl(line);
	mdf("e", 1);
	return 0;
}