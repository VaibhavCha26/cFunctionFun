#include <stddef.h> // for size_t
#include <stdio.h>
#include "alloc_function.h"
#include <sys/mman.h>

void midalloc(void){
  // sbrk() -- expand the boundary by that much bytes -- bad idea - slow;
  //one continous block of memory -- if i want to grow it i would 
  //have to grow the top boundary higher -- can shrink it ig? 
  //but what's the point -- like i can call any memory right ? why does it matter 
  //if the stuff below it is empty?
  //
  //
  //chunk pre fetching or smth? -- basically take a large page and fill that first and then
  //call the os back when the page is full;
  // 1.so basically the point of prefetching is that i will make sure the memory i will write to it later won't be interrupted 
  //some other sys process that may get between them so - calling first gave me a free highway where there is nothing but my stuff :)
  // 2.Reduce System Call Overhead (Context Switching) -- asking multiple times. -- but what about writing to those virutal addresses?? - cpu my love will do the writing :)
  // 3.*the allocator will know its boundaries i guess ? -- wtf ?
  //           
  //modern allocators use mmap for almost anything >128kb :P
  //so this mmap should technically call the chunk that is random
  //call from anywhere it has space in the page.
  //
  //
  //
  //every grid will be a combination of header and the actual memory -- the header contains the size and status -- can it also contain the pointer
  //to the next free space - so i can go though it and keep manipulating the header then :?
  //
  //
  //new problem what if i don't know what type the pointer is?
  //
  //so this call is a chunk but how do i manipulate it now? -- algo's like block header strategy occur on it :P
  //there's something called the explicit pointer way (the pro way ig) instead make a global pointer and inside the mem block it get rewritten to something else 
  //instead of manipulating the header you can store the thing in the memory block itself and probably clear when that block is used.
  //
  //
  //
  //WHEN BUSY:
/*+-------------------+---------------------------------------+

| HEADER            | USER'S DATA SPACE                     |
| size: 100         |                                       |
| is_free: 0        | (User is writing photos/strings here) |
+-------------------+---------------------------------------+ */ 
//
//
  /* WHEN FREE:
+-------------------+--------------------+------------------+

| HEADER            | NEXT_FREE POINTER  | PREV_FREE POINTER|
| size: 100         |                    |                  |
| is_free: 1        | (Points to Block 4)| (Points to NULL) |
+-------------------+--------------------+------------------+
                    \_______________________________________/
                      This was the user's old data space! **/ 


  // this stuff of pointers and stuff gets removed when we use it for assignment by the user -- it will take the place of the pointers itself;
  // who the fuck cares -- at the end of the day its all handshakes between os and allocator and sometimes between cpu and allocator or os
  //
  //
  //
  void* chunk = mmap(NULL,
                     100*sizeof(size_t),
                     permissions,flags,type);
  //wtf is this (BlockHeader*)raw_pool
  //
  //
  BlockHeader* firstHeader = (BlockHeader*)raw_pool

  // now i guess i can change things like firstHeader --> something like size or is_free.
  //wtf is pointer typecasting?
  //
  //there's BlockHeader* pointer or something like that -- also pointer + 1 points to the user data 

  // probably something like pointer == (thing) that will allocate the space to it - so basically call the algo for the pointers but what pointer
  // if i can't take in what type of data it is - how would i make function out of it?
  if(clear_mapping){
    munmap(chunk,len);
  }
  
}
