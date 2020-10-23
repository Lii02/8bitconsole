#ifndef BIT_MEMORY_H
#define BIT_MEMORY_H

void initialize_memory(void);
size_t get_memory_allocated();

void* li_malloc(unsigned int size);
void* li_realloc(void* block, unsigned int new_size);
void li_free(void* block);

#endif