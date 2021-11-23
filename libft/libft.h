/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaliste <agaliste@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:12:25 by agaliste          #+#    #+#             */
/*   Updated: 2021/11/07 17:28:44 by agaliste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# define BUFFER_SIZE 1

/*
** Libc Functions (Part 1)
*/

int					ft_tolower(int c);
int					ft_toupper(int c);
int					ft_isascii(int c);
int					ft_isalnum(int c);
int					ft_isprint(int c);
void				ft_bzero(void *sr, size_t n);
char				*ft_strchr(const char *s, int n);
char				*ft_strrchr(const char *s, int n);
int					ft_isalnum(int c);
int					ft_isdigit(int c);
int					ft_isalpha(int c);
char				*ft_strdup(const char *s1);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
size_t				ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t				ft_strlen(const char *str);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *hstck, const char *ndl, size_t len);
int					ft_atoi(const char *str);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_memcpy(void *dst, const void *src, size_t n);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
void				*ft_memmove(void *dst, const void *src, size_t len);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_calloc(size_t count, size_t size);

/*
** Added Functions (Part 2)
*/

char				*ft_strjoin(const char *s1, const char *s2);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_itoa(int n);
char				**ft_split(char const *s, char c);

/*
** Bonus Functions
*/

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void*));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));

t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

/*
** Extra functions
*/
void				ft_lstdel_last(t_list *lista);
long				ft_atoli(const char *s);
char				*get_next_line(int fd);
void				ft_freestr(char **str);
void				*ft_realloc(void *ptr, size_t size);

#endif
