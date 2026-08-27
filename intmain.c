#include "libft.h"
#include <stdio.h>

void print_content(void *content)
{
    printf("\n%s\n", (char *)content);
}

#include "libft.h"

void *to_upper_content(void *content)
{
    int     i;
    char    *str;

    if (!content)
        return (NULL);

    str = ft_strdup((char *)content);
    if (!str)
        return (NULL);

    i = 0;
    while (str[i])
    {
       
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] = str[i] - 32;
        }
        i++;
    }

    return ((void *)str);
}

int main()
{
    t_list *head;

    head = NULL;

    t_list *node1;
    t_list *node2;
    t_list *node3;
    
    node1 = ft_lstnew("ahmet");
    node2 = ft_lstnew("mehmet");
    node3 = ft_lstnew("nunu");
    

    ft_lstadd_front(&head, node1);
    ft_lstadd_front(&head, node2);
    ft_lstadd_front(&head, node3);

    t_list *temp = head;
    
    while(temp)
    {
        printf("%s\n", (char *)temp->content);
        temp = temp->next;
    }

    ft_lstiter(head, print_content);
 

    t_list *newlist;

    newlist = ft_lstmap(head, to_upper_content, free);

    ft_lstiter(newlist, print_content);

    ft_lstclear(&node1, NULL);
    
}