/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadams <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 09:31:37 by oadams            #+#    #+#             */
/*   Updated: 2021/02/20 14:49:56 by oadams           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_BONUS_H
# define LIBFT_BONUS_H

# include "libft.h"

typedef struct		s_dict
{
	char			*key;
	void			*value;
	void			(*del)(void*);
	struct s_dict	*next;
}					t_dict;

int					ft_isupper(int c);
int					ft_islower(int c);
int					ft_isspace(int c);
int					ft_isgraph(int c);
int					ft_ispunct(int c);
int					ft_strisalnum(char *str);
int					ft_strisalpha(char *str);
int					ft_strisnum(char *str);
int					ft_strfindc(char *str, char c);
int					ft_strcmp(const char *s1, const char *s2);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strncat(char *dest, const char *src, size_t n);
char				*ft_strstr(char *haystack, char *needle);
int					ft_strintab(char **tab, char *str);
void				ft_strclr(char *s);
char				*ft_strcreate(char *str);
char				*ft_strmap(char const *s, char (*f)(char));
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strrmchar(char *str, char c);
char				*ft_tabjoin(char **tab, char *sep);
char				**ft_splitset(char const *str, char *set);
char				*ft_strreplace(char *str, char *old, char *newsub);
double				ft_atof(const char *nptr);
int					ft_putchar(int c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
char				*ft_readfile(char *path, int bs);
void				*ft_realloc(void *ptr, size_t size);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				ft_freetab(char **tab);
t_dict				*ft_dictnew(char *key, void *value, size_t value_size,
		void (*del)(void*));
t_dict				**ft_dictadd(t_dict **head, t_dict *newentry);
void				*ft_dictget(t_dict **head, char *key);
size_t				ft_dictsize(t_dict **head);
void				ft_dictrm(t_dict **head, char *key);
void				*ft_dictupdate(t_dict **head, char *key, void *value,
		size_t value_size);
void				ft_dictclear(t_dict **head);
char				*ft_dictgetc(t_dict **head, char *key);
int					*ft_dictgeti(t_dict **head, char *key);

#endif
