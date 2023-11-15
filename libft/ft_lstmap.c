
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*current;

	if (!lst || !f || !del)
		return (NULL);
	current = NULL;
	while (lst)
	{
		node = ft_lstnew(f(lst->content));
		if (!node)
		{
			ft_lstclear(&current, del);
			return (current);
		}
		ft_lstadd_back(&current, node);
		lst = lst->next;
	}
	return (current);
}
