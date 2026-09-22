#pragma once 
// basically the new malloc should be able 
// to the the entire work of malloc - the allocator
// and should also take arguments for sending the
// data through cache if needed or send it to stack as wwell
void midalloc(void* chunk_size, int* clear_mapping,
                     void* permissions,void* flags, void *type,void* file_des,void* offset);
