#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdint.h>
# include <wchar.h>
# include "ft_memmgr.h"
# include "libft.h"

# define F(x)		(arg->flags & (x))
# define BASE_KEY	"0123456789abcdef"

enum			e_pfflags
{
	F_H = 1,
	F_HH = 1 << 1,
	F_L = 1 << 2,
	F_LD = 1 << 3,
	F_LL = 1 << 4,
	F_J = 1 << 5,
	F_Z = 1 << 6,
	F_PRECISE = 1 << 7,
	F_MINUS = 1 << 8,
	F_PLUS = 1 << 9,
	F_SPACE = 1 << 10,
	F_ZERO = 1 << 11,
	F_HASH = 1 << 12,
	F_ESCAPE = 1 << 13
};

typedef struct	s_arg
{
	char		*esc;
	int			flags;
	int			width;
	int			precision;
	char		conv;
}				t_arg;

typedef struct	s_buff
{
	t_mchain	*mchain;
	va_list		ap;
	size_t		len;
}				t_buff;

typedef struct	s_conv
{
	char		specifier;
	int		(*handle)(t_buff *, t_arg *);
}				t_conv;

/*
** conv_char.c
*/

int			conv_char(t_buff *buff, t_arg *arg);
int			conv_str(t_buff *buff, t_arg *arg);

/*
** conv_float.c
*/

int			conv_float(t_buff *buf, t_arg *arg);

/*
** conv_int.c
*/

int			conv_d(t_buff *buff, t_arg *arg);
int			conv_o(t_buff *buff, t_arg *arg);
int			conv_p(t_buff *buff, t_arg *arg);
int			conv_u(t_buff *buff, t_arg *arg);
int			conv_x(t_buff *buff, t_arg *arg);

/*
** conv_int_deprecated.c
*/

int			conv_ld_deprecated(t_buff *buff, t_arg *arg);
int			conv_lo_deprecated(t_buff *buff, t_arg *arg);
int			conv_lu_deprecated(t_buff *buff, t_arg *arg);

/*
** conv_misc.c
*/

void			conv_n(t_buff *buff, t_arg *arg);
int			conv_percent(t_buff *buff, t_arg *arg);

/*
** conv_wchar.c
*/

int			conv_wchar(t_buff *buff, t_arg *arg);
int			conv_wstr(t_buff *buff, t_arg *arg);

/*
** ft_printf.c
*/

int				ft_asprintf(char **ret, const char *fmt, ...);
int				ft_dprintf(int fd, const char *fmt, ...);
int				ft_printf(const char *fmt, ...);
int				ft_snprintf(char *str, size_t size, const char *fmt, ...);
int				ft_sprintf(char *str, const char *fmt, ...);

/*
** parser.c
*/

int			build_arg(t_buff *buff, t_arg *arg);
int			parse_conv(t_buff *buff, const char **fmt);

/*
** process.c
*/

int				process(char **ret, size_t size, const char *fmt, va_list ap);

/*
** util.c
*/

int			add_num(t_buff *buff, t_arg *arg, int base, int is_signed);
int			add_str(t_buff *buff, t_arg *arg, char *str, int len);

/*
** util_int.c
*/

char			*format_num(t_arg *arg, char *prefix, char *num);
char			*get_prefix(t_arg *arg, char *num, int base);
intmax_t		get_int(t_buff *buff, t_arg *arg);
uintmax_t		get_uint(t_buff *buff, t_arg *arg);
char			*uitoa(uintmax_t un, int base, int negative);

extern const t_conv	g_disp[];
extern const int	g_disp_count;
#endif