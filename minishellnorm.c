/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishellnorm.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilmahjou <ilmahjou@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 16:22:23 by ilmahjou          #+#    #+#             */
/*   Updated: 2025/04/07 21:04:07 by ilmahjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static t_token *handle_word(char *input, int *i, t_token *head, t_token *current)
{
    int     start;
    char    *word;
    t_token *new_token;

    start = *i;
    while (input[*i] && !ft_strchr(" \t|><\'\"$", input[*i]))  // Now "$" is also treated as a boundary
        (*i)++;  // Move the index forward until we hit a boundary

    if (*i > start)
    {
        word = ft_substr(input, start, *i - start);  // Extract the word
        if (!word)
            return (free_tokens(head));

        new_token = creat_token(word, TOKEN_WORD);  // Create a regular word token
        free(word);
        if (!new_token)
            return (free_tokens(head));

        if (!head)
            head = new_token;
        else
            current->next = new_token;
    }
    return (head);
}

static t_token *handle_dollar_quotes(char *input, int *i, t_token *head, t_token *current)
{
    char    quote_char;
    int     start;
    char    *word;
    t_token *new_token;

    (*i)++; // Skip the $
    quote_char = input[*i];
    (*i)++; // Skip the opening quote
    
    start = *i; // Start of content inside quotes
    
    // Find the closing quote
    while (input[*i] && input[*i] != quote_char)
        (*i)++;
    
    if (!input[*i]) // No closing quote found
        return (printf("error\n"), free_tokens(head)); // Error: unclosed quote
        
    word = ft_substr(input, start, *i - start);
    if (!word)
        return (free_tokens(head));
        
    // Create a token with the content as a regular word (no variable expansion)
    new_token = creat_token(word, TOKEN_WORD);
    free(word);
    
    if (!new_token)
        return (free_tokens(head));
        
    if (!head)
        head = new_token;
    else
        current->next = new_token;
        
    (*i)++; // Skip the closing quote
    
    return (head);
}

t_token *tokenize_input(char *input)
{
    t_token *head = NULL;
    t_token *current = NULL;
    int     i = 0;

    while (input[i])
    {
        if (input[i] == ' ' || input[i] == '\t') // Skip spaces
            i++;
        else if (input[i] == '|') // Handle pipe
            head = handle_pipe(&i, head, current);
        else if (input[i] == '<' || input[i] == '>') // Handle redirection
            head = handle_redirection(input, &i, head, current);
        else if (input[i] == '\'' || input[i] == '"') // Handle quotes
            head = handle_quotes(input, &i, head, current);
        else if (input[i] == '$') // Handle variables
        {
            if (input[i + 1] == '"' || input[i + 1] == '\'')  // Case for $"string" or $'string'
            {
                head = handle_dollar_quotes(input, &i, head, current);
            }
            else
            {
                head = handle_env_variable(input, &i, head, current); // Handle $HOME
            }
        }
        else
            head = handle_word(input, &i, head, current); // Handle regular words

        if (!head)
            return (NULL);  // If error occurred, return NULL

        current = get_last_token(head);  // Update current token
    }

    return (head);  // Return the list of tokens
}

int	main(void)
{
	char		*line;
	t_token		*tokens;
	t_token		*current;

	using_history();
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		if (line[0] != '\0')
		{
			add_history(line);
			tokens = tokenize_input(line);
			current = tokens;
			while (current)
			{
				printf("Token: %s, Type: %d\n", current->content, current->type);
				current = current->next;
			}
			free_tokens(tokens);
		}
		free(line);
	}
	clear_history();
	return (0);
}