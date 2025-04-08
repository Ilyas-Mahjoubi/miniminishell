/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tokenz.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:55:47 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/04/08 16:38:53 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void execute_commands(t_command *commands, t_info *info)
{
	t_command *cmd = commands;

	while (cmd) {
		if (cmd->args && cmd->args[0]) {
			// Check for built-in commands
			if (ft_strcmp(cmd->args[0], "cd") == 0)
				ft_cd(cmd->args + 1, info);
			else if (ft_strcmp(cmd->args[0], "pwd") == 0)
				ft_pwd(1);
			else if (ft_strcmp(cmd->args[0], "echo") == 0)
				ft_echo(cmd->args + 1);
			else if (ft_strcmp(cmd->args[0], "export") == 0)
				ft_export(info, cmd->args + 1);
			else if (ft_strcmp(cmd->args[0], "unset") == 0)
				ft_unset(info, cmd->args + 1);
			else if (ft_strcmp(cmd->args[0], "env") == 0)
				ft_env(info);
			//else if (ft_strcmp(cmd->args[0], "exit") == 0)
			//	handle_exit(cmd->args + 1);
			//else
			//	execute_external_command(cmd->args, info);
		}
		cmd = cmd->next;
	}
}

/* t_command *tokens_to_commands(t_token *tokens)
{
	t_command *head = NULL;
	t_command *current = NULL;
	t_token *token = tokens;

	// Iterate through all tokens
	while (token) {
		// Start a new command at the beginning or after a pipe
		if (!head || token->type == TOKEN_PIPE) {
			t_command *new_cmd = malloc(sizeof(t_command));
			if (!new_cmd)
				return NULL; // Memory allocation error

			new_cmd->args = NULL;
			new_cmd->redirections = NULL;
			new_cmd->next = NULL;

			if (!head)
				head = new_cmd;
			else
				current->next = new_cmd;

			current = new_cmd;

			if (token->type == TOKEN_PIPE) {
				token = token->next; // Skip the pipe token
				continue;
			}
		}

		// Process tokens for the current command
		// (We'll implement this part next)

		token = token->next;
	}

	return head;
} */ //this is the old one ok

t_command *tokens_to_commands(t_token *tokens)
{
	t_command *head = NULL;
	t_command *current = NULL;
	t_token *token = tokens;
	// Iterate through all tokens
	while (token) {
		// Start a new command at the beginning or after a pipe
		if (!head || token->type == TOKEN_PIPE) {
			t_command *new_cmd = malloc(sizeof(t_command));
			if (!new_cmd)
				return NULL; // Memory allocation error
			new_cmd->args = NULL;
			new_cmd->redirections = NULL;
			new_cmd->next = NULL;
			if (!head)
				head = new_cmd;
			else
				current->next = new_cmd;
			current = new_cmd;
			if (token->type == TOKEN_PIPE) {
				token = token->next; // Skip the pipe token
				continue;
			}
		}
		// Collect command arguments
		current->args = collect_command_args(&token);
		if (!current->args) {
			// Handle error - cleanup and return NULL
			free_commands(head);
			return NULL;
		}
		// Continue with the next token (if any)
		if (token)
			token = token->next;
	}
	return head;
}

/* char **collect_command_args(t_token **token_ptr)
{
	t_token *token = *token_ptr;
	int arg_count = 0;
	t_token *tmp = token;

	// Count arguments (tokens until pipe or redirection)
	while (tmp && tmp->type != TOKEN_PIPE &&
		   tmp->type != TOKEN_REDIR_IN && tmp->type != TOKEN_REDIR_OUT &&
		   tmp->type != TOKEN_REDIR_APPEND && tmp->type != TOKEN_HEREDOC) {
		arg_count++;
		tmp = tmp->next;
	}

	// Allocate memory for arguments array
	char **args = malloc((arg_count + 1) * sizeof(char *));
	if (!args)
		return NULL;

	// Fill the arguments array
	int i = 0;
	while (i < arg_count) {
		if (token->type == TOKEN_WORD || token->type == TOKEN_SQUOTE ||
			token->type == TOKEN_DQUOTE || token->type == TOKEN_VAR) {
			args[i] = ft_strdup(token->content);
			if (!args[i]) {
				// Free allocated memory on error
				while (--i >= 0)
					free(args[i]);
				free(args);
				return NULL;
			}
			i++;
		}
		token = token->next;
	}
	args[i] = NULL; // Null-terminate the arguments array

	*token_ptr = token; // Update token pointer to continue parsing
	return args;
} */

char **collect_command_args(t_token **token_ptr)
{
	t_token *token = *token_ptr;
	int arg_count = 0;
	t_token *tmp = token;
	// Count arguments (tokens until pipe or redirection)
	while (tmp && tmp->type != TOKEN_PIPE &&
		   tmp->type != TOKEN_REDIR_IN && tmp->type != TOKEN_REDIR_OUT &&
		   tmp->type != TOKEN_REDIR_APPEND && tmp->type != TOKEN_HEREDOC) {
		arg_count++;
		tmp = tmp->next;
	}
	if (arg_count == 0)
		return NULL;
	// Allocate memory for arguments array
	char **args = malloc((arg_count + 1) * sizeof(char *));
	if (!args)
		return NULL;
	// Fill the arguments array
	int i = 0;
	while (i < arg_count) {
		if (token->type == TOKEN_WORD || token->type == TOKEN_SQUOTE ||
			token->type == TOKEN_DQUOTE || token->type == TOKEN_VAR) {
			args[i] = ft_strdup(token->content);
			if (!args[i]) {
				// Free allocated memory on error
				while (--i >= 0)
					free(args[i]);
				free(args);
				return NULL;
			}
		} else {
			args[i] = NULL;
		}
		i++;
		token = token->next;
	}
	args[i] = NULL; // Null-terminate the arguments array
	*token_ptr = tmp; // Update token pointer to continue parsing
	return args;
}



