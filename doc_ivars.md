# Les variables internes
## La structure t_db
```C
typedef struct	s_db
{
	char		*key;
	char		*value;
	u_int8_t	type;
	u_int32_t	hit;
}		t_db;
```
**key** est le nom de la variable et **value** la valeur.
**type** sert a differencier les variables [d'environnement](#denvironnement), [internes](#internes) et [speciales](#speciales).
```C
# define EXPORT_VAR	0x001
# define INTERNAL_VAR	0x002
# define SPECIAL_VAR	0x004
```
On ne peut pas exporter ou creer une variable dont le nom commence par un chiffre ou qui contient un caractere non alphanumerique.
## Les types de variables
### D'environnement
On y accede avec la commande **`env`**

On y retrouve des variables comme **PATH**, **PWD**, **SHLVL** etc.

Elles sont representees par `type = EXPORT_VAR`

On peut les creer avec la commande `export NAME NAME=VALUE`
### Internes
On y accede avec la commande **`set`**

On y retrouve des variables comme **IFS** et **LINES**

Elles sont representees par `type = INTERNAL_VAR`

On peut les creer comme ça : `$> NAME=VALUE`, si une commande suit cette expression (ex : `$> HOME=/tmp cd`),
la variable est cree pour cette commande puis supprimee
### Speciales
On ne peut ni les lister, ni les creer directement, mais on les affiche commme des variables normales avec le symbole $

On y retrouve des variables comme **$?**, **$#** et **$$**
([liste complete](https://www.gnu.org/software/bash/manual/html_node/Special-Parameters.html))
## Creer des variables (Methode directe et non recommandee)
```C
ft_lstappend(&(shell->env),ft_lstnew(fetch_db(&(shell->db), str, type), sizeof(t_db)));
```

avec `(char*)str: key=value` ou juste `str: key` (pour creer la variable sans lui affecter de value)
et `(int)type: EXPORT_VAR, INTERNAL_VAR ou SPECIAL_VAR`. Il vaut mieux preferer la fonction `get_or_create_db`
pour creer une variable interne (voir la partie suivante).
## Mettre a jour ou creer une variable (Methode recommandee)
```C
char *value;

value = ft_strdup("VALUE");
if (edit_var(shell, "NAME", value, VAR_TYPE) != SUCCESS)
	//GERER LE PROBLEME
```
Il faut que value soit allouee dynamiquement, pas besoin de strdel `char *value` en cas de SUCCESS, `db->value` pointe vers elle, en cas de FAILURE non plus.
La variable NAME devra etre free apres l'execution, peu importe le retour de la fonction.
## Detruire une variable
```C
del_db(shell, "NAME")
```
returnera `SUCCESS` ou `FAILURE` si la variable n'existe pas et/ou si `shell->env == NULL`
