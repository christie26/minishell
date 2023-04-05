

int ft_is_space(char c)
{
    if (c == ' ')
        return (1);
    return (0);
}

int ft_is_word(char c)
{
    if (c == ' ')
        return (0);
    else if (c == '<')
        return (0);
    else if (c == '>')
        return (0);
    else if (c == '|')
        return (0);
    else if (c == '&')
        return (0);
    return (1);
}