/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:21:04 by hbreeze           #+#    #+#             */
/*   Updated: 2024/10/01 19:13:06 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>

# include "get_next_line.h"

// Mandatory

// Character checks

// Returns: a non 0 int if the char represented by c is alphabetical.
int				ft_isalpha(int c);

// Returns: a non 0 int if the char represented by c is a number
int				ft_isdigit(int c);

// Returns: a non 0 int if the char represented by c is alphabetical or a number
int				ft_isalnum(int c);

// Returns: a non 0 int if the char represented by c is part of the ASCII table
int				ft_isascii(int c);

// Returns: a non 0 int if the char represented by c is printable
int				ft_isprint(int c);

// Returns: c if c is not a lowercase letter OR the uppercase variant of c 
int				ft_toupper(int c);

// Returns: c if c is not a uppercase letter OR the uppercase variant of c
int				ft_tolower(int c);

// Str functions

// Returns: the length of the string passed as str, 0 for a null pointer
size_t			ft_strlen(const char *str);

// Returns: the length of the source, 0 for an null src
size_t			ft_strlcpy(char *dest, const char *src, size_t size);

// Returns: src_len + dest_len, 0 for null dest or src,
// 	or source_len + size if dest is greater or equal than size 
size_t			ft_strlcat(char *dest, const char *src, size_t size);

// Returns: the index of the leftmost occurance of character c in str,
// 	or 0 if c is not in string or 0 if str is null
char			*ft_strchr(const char *str, int c);

// Returns: the index of the rightmost occurance of character c in str,
// 	or 0 if c is not in string or 0 if str is null
char			*ft_strrchr(const char *str, int c);

//	Returns: 0 if the substring [0,n] of s1 and s2 match,
// 	or a non 0 int if they dont match
int				ft_strncmp(const char *s1, const char *s2, size_t n);

// Returns: the index of the first occurance of the string little
// 	in the first len bytes of  big, or 0 if either string parameters are null,
// 	or 0 if len is less than the length of little
// or 0 if the length of the little string is greater than the length of big
char			*ft_strnstr(const char *big,
					const char *little, size_t len);

// Returns: a malloc'd duplicate of the string src
// 	or 0 if malloc fails.
char			*ft_strdup(const char *src);

// Returns: a malloc'd copy of the substring between start and
// 	min(start+len, length of s - start)in str
// 	or 0 if malloc fails
char			*ft_substr(const char *str, size_t start, size_t len);

// Returns: a malloc'd string that concatenates s1 and s2,
// 	or 0 if malloc fails,
// 	or 0 if either s1 or s2 are null
char			*ft_strjoin(const char *s1, const char *s2);

// Returns: s1 with any character in set stripped from the start and end,
// 	or 0 if malloc fails,
// 	or 0 if s1 if null,
// Note: null set will duplicate s1
char			*ft_strtrim(const char*s1, const char *set);

// Returns: a list of the substrings in the string, using c as the separator
// 	Note: c is not included in the substrings
// 	Note: start and end of string count as seperators
char			**ft_split(const char *str, char c);

// Memory functions

// Returns: Nothing XD
void			*ft_memset(void *str, int c, size_t n);

// Returns: Nothing XD
void			ft_bzero(void *s, size_t n);

// Returns: void pointer to dest, 0 if src AND dest are null
// 	Note: This will CRASH if dest is null!!!
void			*ft_memcpy(void *dest, const void *src, size_t n);

// Returns: void pointer to dest, 0 if src is null
// 	Note: This will CRASH if dest is null!!!
void			*ft_memmove(void *dest, const void *src, size_t n);

// Returns: index of c in the first n bytes of s,
// 	0 if s is null
// 	0 if c is not in s
void			*ft_memchr(const void *s, int c, size_t n);

// Returns: 0 if the first n bytes of s1 and s2 match,
// 	or a non 0 int if they dont match
int				ft_memcmp(const void *s1, const void *s2, size_t n);

// Returns: a malloc'd void pointer of nmemb * size bytes
// 	or 0 if malloc failed or overflow occurs when nmemb * size
void			*ft_calloc(size_t nmemb, size_t size);

// Ascii <-> Int functions

// Returns: int represented by the ascii string nptr
int				ft_atoi(const char *nptr);

// Returns: malloc'd string reprentation of integer n
// 	or 0 if malloc fails.
char			*ft_itoa(int n);

// Iteration

// Returns: a malloc'd copy of string s with function f applied to each charcter
// 	0 if malloc fails or s is null or f is null
char			*ft_strmapi(const char *s, char (*f)(unsigned int, char));

// Returns: Nothing (Applies f to charcters of s IN PLACE)
void			ft_striteri(char *s, void (*f)(unsigned int, char*));

// IO

// Returns: Nothing XD
void			ft_putchar_fd(char c, int fd);

// Returns: Nothing XD
void			ft_putstr_fd(char *s, int fd);

// Returns: Nothing XD
void			ft_putendl_fd(char *s, int fd);

// Returns: Nothing XD
void			ft_putnbr_fd(int n, int fd);

// BONUS

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

// Creation

// Returns: A new malloc'd list item containing content with next set to null,
// 	0 if malloc fails
t_list			*ft_lstnew(void *content);

// Returns: Nothing XD
void			ft_lstadd_front(t_list **lst, t_list *new);

// Returns: Nothing XD
void			ft_lstadd_back(t_list **lst, t_list *new);

// Naviation

// Returns: the number of list items in lst
int				ft_lstsize(t_list *lst);

// Returns: pointer to last item in lst
t_list			*ft_lstlast(t_list *lst);

// Deletion

// Returns: nothing LOL
void			ft_lstdelone(t_list *lst, void (*del)(void*));

// Returns: nothing LOL
void			ft_lstclear(t_list **lst, void (*del)(void*));

// Iteration

// Returns: nothing (applies function f to
// 	content of all list items IN PLACE)
void			ft_lstiter(t_list *lst, void (*f)(void *));

// Returns: A new list containing the result of f applied
// 	to the content of each list item in lst
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
					void (*del)(void *)
					);

// Returns: the list item at index in lst
t_list			*ft_lstget(t_list *lst, size_t index);

/**
 * @brief Function to iterate over a list with a parameter
 * @param lst Pointer to the list
 * @param f Function to apply to the content of each list item
 * @param param Parameter to pass to the function
 */
void			ft_lstiter_param_bonus(t_list *lst,
					void (*f)(t_list *, void *),
					void *param);

#endif