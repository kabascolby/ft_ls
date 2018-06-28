#include "libft.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

/*
**max_len : is data type size ex: sizeof(int)
**data
*/

t_dymamic_array    ft_init_dynamic_array(size_t length, size_t data_t_size)
{
    t_dymamic_array da;
    da.length = 0;
    da.item_size = data_t_size;
    da.capacity = length * data_t_size;
    da.tab = (void *)malloc(da.capacity);
    memset(da.tab, 0, da.capacity);
    return (da);
}

int ft_free_darray(t_dymamic_array *da)
{
    size_t i;

    i = -1;
    while(++i < da->capacity / da->length)
        free((uint8_t *)da->tab + i * da->item_size);
    ft_memdel(&da->tab);
    if(da->tab)
        return(0);
    return (1);
}

uint8_t			ft_darray_grow(t_dymamic_array *da)
{
	void	*ptr;
    size_t  cap;

    cap = da->capacity * 2;
	ptr = (void *)malloc(cap);
	if (!ptr)
		return (0);
	if (da->tab)
    {
      size_t i;

      i = -1;
      while(++i < (da->capacity / da->item_size))
        memcpy((((uint8_t*)ptr) + i * da->item_size), (((uint8_t*)da->tab) + i * da->item_size), da->item_size);
    }
	if(ft_free_darray(da))
    {
        da->tab = ptr;
        da->capacity = cap;
    }
    return (1);
}

void ft_add_to_darray(void *data, t_dymamic_array *da)
{
    if(da->length  ==  da->capacity / da->item_size)
        ft_darray_grow(da);
    uint8_t     i;
    memcpy(((uint8_t*)da->tab) + da->length * da->item_size, data, da->item_size);
    da->length += 1; 
}

int main(void)
{ 
    t_dymamic_array T;
    char *k = "lamine";
    char *m = "test";
    T = ft_init_dynamic_array(2, sizeof(char *));
    ft_add_to_darray(&k, &T);
    ft_add_to_darray(&m, &T);
    printf("t[0] = %s\n", ((char**)T.tab)[0]);
    printf("t[1] = %s\n", *((char**)T.tab + 1));
    ft_add_to_darray(&"Mohamed", &T);
    printf("t[0] = %s\n", ((char**)T.tab)[0]);
    printf("t[1] = %s\n", *((char**)T.tab + 1));
    printf("t[1] = %s\n", *((char**)T.tab + 2));
    
    return (0);
}