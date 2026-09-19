#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>

int main(int argc, char* argv[]){
  char *admin_rights = mmap(NULL, 
                      20*sizeof(size_t), //why not size_t or something like that;
                      PROT_WRITE
                      , MAP_ANONYMOUS | MAP_PRIVATE,-1,0);

  if(admin_rights == MAP_FAILED){
    perror("mmap failed");
  }
  
  snprintf(admin_rights, // it will check PROT_WRITE permission ig ;<
           20*sizeof(size_t), 
           "why doesn't it do something4");  /// writes to buffer basically :>
  ///
  printf("%s", *(&admin_rights)); // both *(& and &(*) work somehow 
  //
  //
  munmap(admin_rights,20*sizeof(size_t)); // what if i didn't clear how much i took?
  
  return 0;
}
