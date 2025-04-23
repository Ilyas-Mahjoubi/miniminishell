/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellnorm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:22:23 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/04/23 19:39:53 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../minishell.h"

// static t_token	*handle_pipe(int *i, t_token *head, t_token *current)
// {
// 	t_token	*new_token;

// 	new_token = creat_token("|", TOKEN_PIPE);
// 	if (!new_token)
// 		return (free_tokens(head));
// 	if (!head)
// 		head = new_token;
// 	else
// 		current->next = new_token;
// 	(*i)++;
// 	return (head);
// }

// static t_token	*handle_redirection(char *input, int *i, t_token *head, t_token *current)
// {
// 	t_token	*new_token;

// 	new_token = NULL;
// 	if (input[*i] == '<')
// 	{
// 		if (input[*i + 1] == '<')
// 		{
// 			new_token = creat_token("<<", TOKEN_HEREDOC);
// 			*i += 2;
// 		}
// 		else
// 		{
// 			new_token = creat_token("<", TOKEN_REDIR_IN);
// 			(*i)++;
// 		}
// 	}
// 	else if (input[*i] == '>')
// 	{
// 		if (input[*i + 1] == '>')
// 		{
// 			new_token = creat_token(">>", TOKEN_REDIR_APPEND);
// 			*i += 2;
// 		}
// 		else
// 		{
// 			new_token = creat_token(">", TOKEN_REDIR_OUT);
// 			(*i)++;
// 		}
// 	}
// 	if (!new_token)
// 		return (free_tokens(head));
// 	if (!head)
// 		head = new_token;
// 	else
// 		current->next = new_token;
// 	return (head);
// }

// static t_token *handle_word(char *input, int *i, t_token *head, t_token *current)
// {
// 	int		start;
// 	char	*word;
// 	t_token	*new_token;

// 	start = *i;
// 	while (input[*i] && !ft_strchr(" \t|><\'\"$", input[*i]))  // Now "$" is also treated as a boundary
// 		(*i)++;  // Move the index forward until we hit a boundary

// 	if (*i > start)
// 	{
// 		word = ft_substr(input, start, *i - start);  // Extract the word
// 		if (!word)
// 			return (free_tokens(head));

// 		new_token = creat_token(word, TOKEN_WORD);  // Create a regular word token
// 		free(word);
// 		if (!new_token)
// 			return (free_tokens(head));

// 		if (!head)
// 			head = new_token;
// 		else
// 			current->next = new_token;
// 	}
// 	return (head);
// }

// static t_token *handle_dollar_quotes(char *input, int *i, t_token *head, t_token *current)
// {
// 	char	quote_char;
// 	int		start;
// 	char	*word;
// 	t_token	*new_token;

// 	(*i)++; // Skip the $
// 	quote_char = input[*i];
// 	(*i)++; // Skip the opening quote
// 	start = *i; // Start of content inside quotes
// 	// Find the closing quote
// 	while (input[*i] && input[*i] != quote_char)
// 		(*i)++;
// 	if (!input[*i]) // No closing quote found
// 		return (printf("error\n"), free_tokens(head)); // Error: unclosed quote
// 	word = ft_substr(input, start, *i - start);
// 	if (!word)
// 		return (free_tokens(head));
// 	// Create a token with the content as a regular word (no variable expansion)
// 	new_token = creat_token(word, TOKEN_WORD);
// 	free(word);
// 	if (!new_token)
// 		return (free_tokens(head));
// 	if (!head)
// 		head = new_token;
// 	else
// 		current->next = new_token;
// 	(*i)++; // Skip the closing quote
// 	return (head);
// }

// t_token *tokenize_input(char *input)
// {
// 	t_token	*head = NULL;
// 	t_token	*current = NULL;
// 	int		i = 0;

// 	while (input[i])
// 	{
// 		if (input[i] == ' ' || input[i] == '\t') // Skip spaces
// 			i++;
// 		else if (input[i] == '|') // Handle pipe
// 			head = handle_pipe(&i, head, current);
// 		else if (input[i] == '<' || input[i] == '>') // Handle redirection
// 			head = handle_redirection(input, &i, head, current);
// 		else if (input[i] == '\'' || input[i] == '"') // Handle quotes
// 			head = handle_quotes(input, &i, head, current);
// 		else if (input[i] == '$') // Handle variables
// 		{
// 			if (input[i + 1] == '"' || input[i + 1] == '\'')  // Case for $"string" or $'string'
// 			{
// 				head = handle_dollar_quotes(input, &i, head, current);
// 			}
// 			else
// 			{
// 				head = handle_env_variable(input, &i, head, current); // Handle $HOME
// 			}
// 		}
// 		else
// 			head = handle_word(input, &i, head, current); // Handle regular words

// 		if (!head)
// 			return (NULL);  // If error occurred, return NULL

// 		current = get_last_token(head);  // Update current token
// 	}

// 	return (head);  // Return the list of tokens
// }

// int main(void)
// {
// 	char *line;
// 	t_token *tokens;
// 	t_token *current;
// 	t_info info;

// 	ft_printf(RED BOLD);
// 	ft_printf(" __  __ _____ _   _ _____ _____ _   _ _____ _      _     \n");
// 	ft_printf("|  \\/  |_   _| \\ | |_   _|/ ____| | | | ____| |    | |    \n");
// 	ft_printf("| \\  / | | | |  \\| | | | | (___ | |_| |  _| | |    | |    \n");
// 	ft_printf("| |\\/| | | | | . ` | | |  \\___ \\|  _  | |___| |    | |    \n");
// 	ft_printf("| |  | |_| |_| |\\  |_| |_ ____) | | | |_____|_|____|_|____\n");
// 	ft_printf("|_|  |_|_____|_| \\_|_____|_____/|_| |_|______|______|______|\n");
// 	ft_printf(RESET);
// 	ft_printf("\n     MINISHELL by Ilyas & Thilina - Core Dumpers 💥\n\n");
// 	// Initialize environment
// 	form_env(__environ, &info);
// 	using_history();
// 	while (1)
// 	{
// 		line = readline("\001\033[1;32m\002minishell$ \001\033[0m\002");
// 		if (!line)
// 			break;
// 		if (line[0] != '\0')
// 		{
// 			add_history(line);
// 			tokens = tokenize_input(line);
// 			// Debug: Print tokens
// 			current = tokens;
// 			printf("Tokens:\n");
// 			while (current)
// 			{
// 				printf("Token: %s, Type: %d\n", current->content, current->type);
// 				current = current->next;
// 			}
// 			if (tokens) {
// 				t_command *commands = tokens_to_commands(tokens);
// 				// Debug: Print commands
// 				t_command *cmd_debug = commands;
// 				printf("Commands:\n");
// 				while (cmd_debug) {
// 					printf("Command: ");
// 					if (cmd_debug->args) {
// 						for (int i = 0; cmd_debug->args[i]; i++) {
// 							printf("%s ", cmd_debug->args[i]);
// 						}
// 					} else {
// 						printf("(no args)");
// 					}
// 					printf("\n");
// 					cmd_debug = cmd_debug->next;
// 				}
// 				execute_commands(commands, &info);
// 				free_commands(commands);
// 				free_tokens(tokens);
// 			}
// 		}
// 		free(line);
// 	}
// 	clear_history();
// 	// Clean up environment
// 	free_mat(info.env);
// 	return 0;
// }

#include "../minishell.h"

static t_token	*handle_pipe(int *i, t_token *head, t_token *current)
{
	t_token	*new_token;

	new_token = creat_token("|", TOKEN_PIPE);
	if (!new_token)
		return (free_tokens(head));
	if (!head)
		head = new_token;
	else
		current->next = new_token;
	(*i)++;
	return (head);
}

static t_token	*handle_redirection(char *input, int *i, t_token *head, t_token *current)
{
	t_token	*new_token;

	new_token = NULL;
	if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			new_token = creat_token("<<", TOKEN_HEREDOC);
			*i += 2;
		}
		else
		{
			new_token = creat_token("<", TOKEN_REDIR_IN);
			(*i)++;
		}
	}
	else if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			new_token = creat_token(">>", TOKEN_REDIR_APPEND);
			*i += 2;
		}
		else
		{
			new_token = creat_token(">", TOKEN_REDIR_OUT);
			(*i)++;
		}
	}
	if (!new_token)
		return (free_tokens(head));
	if (!head)
		head = new_token;
	else
		current->next = new_token;
	return (head);
}

// New function to join adjacent segments into one word
static t_token *join_word_segment(char *segment, t_token *head, t_token **current_word_token)
{
	char *new_content;
	t_token *new_token;

	if (!segment)
		return (free_tokens(head));

	if (*current_word_token == NULL)
	{
		// No current word being built, create a new token
		new_token = creat_token(segment, TOKEN_WORD);
		free(segment);
		if (!new_token)
			return (free_tokens(head));
		
		if (!head)
			head = new_token;
		else
			get_last_token(head)->next = new_token;
		
		*current_word_token = new_token;
	}
	else
	{
		// Append to existing word token
		new_content = ft_strjoin((*current_word_token)->content, segment);
		free(segment);
		if (!new_content)
			return (free_tokens(head));
		
		free((*current_word_token)->content);
		(*current_word_token)->content = new_content;
	}
	
	return (head);
}

// Modified handle_word to extract word segment
static char *extract_word_segment(char *input, int *i)
{
	int start;
	//char *word;

	start = *i;
	while (input[*i] && !ft_strchr(" \t|><\'\"$", input[*i]))
		(*i)++;
	
	if (*i > start)
		return ft_substr(input, start, *i - start);
	return NULL;
}

// Modified handle_single_quotes to return string content
static char *extract_single_quote_content(char *input, int *i)
{
	int content_start = *i + 1; // Skip the opening quote
	char quote_char = input[*i];
	char *content;

	(*i)++; // Skip the opening quote

	// Find the closing quote
	while (input[*i] && input[*i] != quote_char)
		(*i)++;

	if (!input[*i]) // No closing quote found
	{
		printf("error: unclosed quote\n");
		return NULL;
	}

	content = ft_substr(input, content_start, *i - content_start);
	(*i)++; // Skip the closing quote
	return content;
}

// Modified handle_double_quotes to return string content
static char *extract_double_quote_content(char *input, int *i)
{
	int content_start = *i + 1; // Skip the opening quote
	char quote_char = input[*i];
	char *content;

	(*i)++; // Skip the opening quote
	// Find the closing quote
	while (input[*i] && input[*i] != quote_char)
		(*i)++;
	if (!input[*i]) // No closing quote found
	{
		printf("error: unclosed quote\n");
		return NULL;
	}
	content = ft_substr(input, content_start, *i - content_start);
	(*i)++; // Skip the closing quote
	return content;
}

// Modified tokenize_input to handle adjacent quoted segments
t_token *tokenize_input(char *input)
{
	t_token	*head = NULL;
	t_token	*current_word_token = NULL;
	int		i = 0;
	char	*segment = NULL;

	while (input[i])
	{
		if (input[i] == ' ' || input[i] == '\t') // Space - end of current word
		{
			current_word_token = NULL; // Reset current word
			i++;
		}
		else if (input[i] == '|') // Pipe - end of current word and command
		{
			current_word_token = NULL; // Reset current word
			head = handle_pipe(&i, head, get_last_token(head));
		}
		else if (input[i] == '<' || input[i] == '>') // Redirection - end of current word
		{
			current_word_token = NULL; // Reset current word
			head = handle_redirection(input, &i, head, get_last_token(head));
		}
		else if (input[i] == '\'') // Single quotes
		{
			segment = extract_single_quote_content(input, &i);
			if (!segment)
				return (free_tokens(head));
			head = join_word_segment(segment, head, &current_word_token);
		}
		else if (input[i] == '"') // Double quotes
		{
			segment = extract_double_quote_content(input, &i);
			if (!segment)
				return (free_tokens(head));
			head = join_word_segment(segment, head, &current_word_token);
		}
		else if (input[i] == '$') // Variable
		{
			// For now, handle variables as separators (we'll need to modify this later)
			current_word_token = NULL;
			head = handle_env_variable(input, &i, head, get_last_token(head));
		}
		else // Regular word character
		{
			segment = extract_word_segment(input, &i);
			if (segment) // Only process if we got something
				head = join_word_segment(segment, head, &current_word_token);
		}
		if (!head)
			return (NULL);  // If error occurred, return NULL
	}
	return (head);  // Return the list of tokens
}

// The rest of minishellnorm.c remains unchanged
int main(void)
{
	char *line;
	t_token *tokens;
	t_token *current;
	t_info info;

	ft_printf(RED BOLD);
	ft_printf(" __  __ _____ _   _ _____ _____ _   _ _____ _      _     \n");
	ft_printf("|  \\/  |_   _| \\ | |_   _|/ ____| | | | ____| |    | |    \n");
	ft_printf("| \\  / | | | |  \\| | | | | (___ | |_| |  _| | |    | |    \n");
	ft_printf("| |\\/| | | | | . ` | | |  \\___ \\|  _  | |___| |    | |    \n");
	ft_printf("| |  | |_| |_| |\\  |_| |_ ____) | | | |_____|_|____|_|____\n");
	ft_printf("|_|  |_|_____|_| \\_|_____|_____/|_| |_|______|______|______|\n");
	ft_printf(RESET);
	ft_printf("\n     MINISHELL by Ilyas & Thilina - Core Dumpers 💥\n\n");
	// Initialize environment
	form_env(__environ, &info);
	using_history();
	while (1)
	{
		line = readline("\001\033[1;32m\002minishell$ \001\033[0m\002");
		if (!line)
			break;
		if (line[0] != '\0')
		{
			add_history(line);
			tokens = tokenize_input(line);
			// Debug: Print tokens
			current = tokens;
			printf("Tokens:\n");
			while (current)
			{
				printf("Token: %s, Type: %d\n", current->content, current->type);
				current = current->next;
			}
			if (tokens) {
				t_command *commands = tokens_to_commands(tokens);
				// Debug: Print commands
				t_command *cmd_debug = commands;
				printf("Commands:\n");
				while (cmd_debug) {
					printf("Command: ");
					if (cmd_debug->args) {
						for (int i = 0; cmd_debug->args[i]; i++) {
							printf("%s ", cmd_debug->args[i]);
						}
					} else {
						printf("(no args)");
					}
					printf("\n");
					cmd_debug = cmd_debug->next;
				}
				execute_commands(commands, &info);
				free_commands(commands);
				free_tokens(tokens);
			}
		}
		free(line);
	}
	clear_history();
	// Clean up environment
	free_mat(info.env);
	return 0;
}