#include "array.h"

#include <malloc.h>
#include <memory.h>

void m_start_array(m_array* array, u32 size_of_type, u32 count){
    array->array = (void**)malloc(size_of_type * count); // Initialize the array
    array->index = 0; // The index to add to the array
    array->size_of_type = size_of_type; // Size of each item(stride)
    array->size = size_of_type * count; // Total(Initial) size of the array
    array->current_count = 0;
}

void m_push_array(m_array* array, void* item){
    array->current_count++;
    if(array->size < array->size_of_type * (array->current_count)){
        array->array = realloc(array->array, array->size + (array->size_of_type));
        array->size = array->size + array->size_of_type;
    }
    array->array[array->index] = item;
    array->index++;
}

void m_pop_array(m_array* array){
    if(array->size <= 0){
        return;
    }
    array->index--;
}

void m_remove_item(m_array* array, void* item){
    b8 found = FALSE;
    u32 index_to_remove = 0;

    for(u32 i = 0; i < array->current_count; i++){
        if(array->array[i] == item){
            found = TRUE;
            index_to_remove = i;
        }
    }

    array->current_count--;
    
    for(u32 i = index_to_remove; i < array->current_count; i++){
        array->array[i] = array->array[i+1];
    }

    array->index--;
}

void m_remove_item_at_index(m_array* array, u32 index){
    array->current_count--;
    
    for(u32 i = index; i < array->current_count; i++){
        array->array[i] = array->array[i+1];
    }

    array->index--;
}