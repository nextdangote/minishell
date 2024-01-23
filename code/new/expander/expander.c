#include "../includes/lumumbash.h"
#include <ctype.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*t;
	unsigned char	*u;

	t = (unsigned char *)s1;
	u = (unsigned char *)s2;
	i = 0;
	while (n--)
	{
		if (t[i] != u[i] || t[i] == 0 || u[i] == 0)
			return (t[i] - u[i]);
		i++;
	}
	return (0);
}

int ft_strlen(char *str)
{
	int i;

	i = 0;

	while(*str)
	{
		str++;
		i++;
	}
	return(i);
}

int	ft_check_expand(char *str, int i, char **env)
{
	char *potential_env_var = calloc(255, sizeof(char));
	int j = 0;
	if (str[i - 1] != '\'')
	{
		while(str[i] != 0 || !(isspace(str[i])) || str[i] != '\"')
		{
			potential_env_var[j] = str[i];
			j++;
			i++;
		}
		potential_env_var[j] = '\0';
	}
	int k = 0;
	while(env[k] != NULL)
		k++;
	int temp = k;
	k = 0;
	int l = 0;
	//int flag = 0;
	while (k < temp)
	{
		if (ft_strncmp(str, env[k], ft_strlen(env[k])) == 0)
		{
			//flag == 1;
			return(k);
		}
		k++;
	}
	return(0);
	//faire le cas ou le mot est mauvais return (-1)
	//et si -1 on ne rajoute rien dans new_str
}

char	*ft_find_env_var_part2(char *str)
{
	int i;
	int j;
	int k;
	int tmp;
	char *new_str;

	i = 0;
	j = 0;
	k = 0;
	tmp = 0;
	while(str[i] != '=')
		i++;
	i++;
	tmp = i;
	while(str[i] != '\0')
	{
		j++;
		i++;
	}
	new_str = malloc(sizeof(char) * (j + 1));
	while(str[tmp] != 0)
		new_str[k++] = str[tmp++];// if fails just put the incrementation (++) on the next line
	new_str[k] = 0;
	return (new_str);
}

char    *expander(char *str, char **env)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = calloc(999,sizeof(char));
	while(i <= ft_strlen(str))
	{
		if (str[i] == '\'' && str[i + 1] == '$')
		{
			i++;
			while(str[i] != '\'')
				i++;
			new_str[j] = '\'';
			new_str[j++] = '?';
			new_str[j++] = '?';
		}
		else if(str[i] == '$' && (ft_check_expand(str, i, env) >= 0) && str[i + 1] != '\0')
		{
			char *env_var;
			int k = 0;
			int m = 0;
			int o = ft_check_expand(str, i, env);
			//k = ft_length_env_var(str, i, env); //to do and check the length of what to add in the str
			//k = ft_find_env_var(str, i, env);
			env_var = ft_find_env_var_part2(env[o]); //the env var to expand and put inside the new str 🔴🔴🔴🔴🔴 here Inside I should check for the start after the equal and then give back the rest of the string
			while (env_var[m] != 0)
			{
				new_str[j] = env_var[m];
				m++;
				j++;
			}
		}
		else if(str[i] != '$' && str[i] != '\0')
			new_str[j] = str[i];
		i++;
		j++;
	}
	return (new_str);
}

/*int main(int argc, char **argv, char **env)
{
	char *str;
	// maybe duplicate env ? // but why tho ?
	// -> duplicate env et la split pour avoir une liste des mots avant le egal et une liste des mots apres le egal
	// faire un compteur lorsque je check la liste de la premiere partie et renvoyer l'indexxxxxx
	// dans la partie qui copie juste choisir le mot avec index 
	// dans ft_check_expand pour diviser la liste je peux faire une ft_split avec tous les \n, ensuite j'ai une liste avec la var et la valeur de la var, ensuite j'itere dans chaque mot en checkant si ça correspond et si oui et que le next char est egal alors je peux expand.
	// au moment de recup le mot je peux call une fonction similaire a la fonction precedente juste que quand je trouve je retiens l'index du mot dans la liste et l'index de la lettre ou commence le (en vrai je peux juste avant au lieu de retourner 1 retourner l'index du mot dans la double char array et -1 si il n'y est pas) 
	// ensuite j'i
	if (argc != 2)
	{
		printf("give program name and a command to expand\n");
		return(0);
	}
	str = expander(argv[1], env);
	printf("this is the string expanded : %s\n", str);
}*/



// il reste :
// supprimer les double quotes -> ne pas les imprimer
// faire en sorte que quand il y a des singles quotes ça ne print pas ou plutot que ça print \??
// 