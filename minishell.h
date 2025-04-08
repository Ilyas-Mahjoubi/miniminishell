/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:09:42 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/04/08 18:59:21 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define RED     "\033[0;31m"
#define BOLD    "\033[1m"
#define RESET   "\033[0m"

# include "./libft/libft.h"
# include "./libprintf/ft_printf.h"
# include "./get_next_line/get_next_line.h"

# include <stdlib.h>
#include <sys/wait.h>
# include <errno.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

//extern int error = 0; // thilina part
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

// start thilina strct
typedef struct s_env {
	char	*name;
	char	*content;
	struct s_env	*next;
}t_env;

typedef struct s_info {
	char	**env;
	char	**tmp;
	int		size;
} t_info;
// finish the part of thilina

typedef struct s_token {
	char *content;         // The actual text
	t_token_type type;     // Type of token
	struct s_token *next;  // Pointer to next token
} t_token;

typedef struct s_command {
	char **args;			// Array of command arguments (first is the command itself)
	struct s_redirection *redirections;	// Linked list of redirections for this command
	struct s_command *next;		// Next command in pipeline (for pipe operations)
} t_command;



t_token *free_tokens(t_token *head);
t_token *creat_token(char *content, t_token_type type);
t_token	*get_last_token(t_token *head);
t_token *handle_env_variable(char *input, int *i, t_token *head, t_token *current);
t_token *handle_single_quotes(char *input, int *i, t_token *head, t_token *current);
t_token *add_double_quote_text(char *input, int start, int end, t_token *head, t_token *current);
t_token *process_double_quotes(char *input, int *i, t_token *head, t_token *current);
t_token *handle_quotes(char *input, int *i, t_token *head, t_token *current);
/////
int	ft_cd(char **args, t_info *info);
void	ft_echo(char **args);
void	ft_env(t_info *info);
void	ft_export(t_info *info, char **args);
char	*ft_pwd(int	i);
void	ft_unset(t_info *info, char **args);
void	form_env(char **env, t_info	*info);
char	*ft_pwd(int	i);
void	free_mat(char **matrix);
int		exisit(char **matrix, char *arg);
void	matrix_tmp(t_info *info);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_export(t_info *info, char **args);
int		verify_equal(char *str);
///
void free_commands(t_command *head);
char **collect_command_args(t_token **token_ptr);
t_command *tokens_to_commands(t_token *tokens);
void execute_commands(t_command *commands, t_info *info);


#endif
