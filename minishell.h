/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:09:42 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/04/05 18:01:51 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./Libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

// i need to put the args for thilina
typedef enum {
	TOKEN_WORD,       // Regular words/commands
	TOKEN_PIPE,       // |
	TOKEN_REDIR_IN,   // <
	TOKEN_REDIR_OUT,  // >
	TOKEN_REDIR_APPEND, // >>
	TOKEN_SQUOTE, // single quosted string (no expansion)
	TOKEN_DQUOTE, // double quoted string (allow expansion)
	TOKEN_HEREDOC,    // <<
	TOKEN_VAR,
	TOKEN_SPACE       // Space characters (optional)
} t_token_type;

typedef struct s_token {
	char *content;         // The actual text
	t_token_type type;     // Type of token
	struct s_token *next;  // Pointer to next token
} t_token;

typedef struct s_env {
	char *key;
	char *value;
	struct s_env *next;
} t_env;

t_token *free_tokens(t_token *head);
t_token *creat_token(char *content, t_token_type type);
void *free_env(t_env *env);
int	ft_strcmp(const char *s1, const char *s2);
t_token	*get_last_token(t_token *head);
t_token *handle_env_variable(char *input, int *i, t_token *head, t_token *current);
t_token *handle_single_quotes(char *input, int *i, t_token *head, t_token *current);
t_token *add_double_quote_text(char *input, int start, int end, t_token *head, t_token *current);
t_token *process_double_quotes(char *input, int *i, t_token *head, t_token *current);
t_token *handle_quotes(char *input, int *i, t_token *head, t_token *current);

#endif