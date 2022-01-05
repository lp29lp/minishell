
/* /1* look for $ *1/ */
/* void	check_dollar(t_struct *mode) */
/* { */
/* 	int	i; */

/* 	i = 0; */
/* 	while (mode->split_input[i] != NULL) */
/* 	{ */
/* 		if (mode->split_input[i][0] == '$') */
/* 		{ */
/* 			convert_input(i, mode); */
/* 			continue ; */
/* 		} */
/* 		i++; */

/* 	} */
/* } */

/* void	convert_input(int i, t_struct *mode) */
/* { */
/* 	int			x; */
/* 	char		*name; */
/* 	t_list_env	*temp; */

/* 	x = 0; */
/* 	name = ft_strtrim(mode->split_input[i], "$"); */
/* 	free(mode->split_input[i]); */
/* 	mode->split_input[i] = NULL; */
/* 	temp = mode->env; */
/* 	while (temp != NULL) */
/* 	{ */
/* 		if (cmp(temp->key, name) == 0) */
/* 		{ */
/* 			mode->split_input[i] = ft_strdup(temp->value); */
/* 			free(name); */
/* 			break; */
/* 		} */
/* 		temp = temp->next; */
/* 	} */
/* } */

