#include <stddef.h> // for size_t
#include <stdio.h>
#include "alloc_function.h"
#include <sys/mman.h>
#include <stdbool.h>
#include <string.h>

//#define magic_number(sizeof(chunk_size)/sizeof(page_pool_size)) _Generic((x), 
//)(x)


typedef struct BlockHeader{
  size_t size;
  //void* forw_pointer;
  // NOW this part is interesting -- you can use struct pointer somth and it work out the same way.
  // something like this will work and would be easier to chenge the pointers address later on;
  //
  //
  //struct BlockHeader* next; --> causing problems in calling it in for // pointer to the next free space  
  bool is_free;
  //void* next_pointer; //- | they are  not part of the header bruh :P
  void* prev_pointer; //- | anyway header is simply nothing but a assumption of where the line separating them is;
}BlockHeader;

typedef struct pointer_data{
  // struct Node*, you tell the computer: "This pointer points to a complete Node package
  // that contains both a number (x) AND another pointer (next)."
  struct pointer_data* prev;
  struct pointer_data* next;
}pointer_data;

//
//
// idk why but it assumes that the void(){} will return int -> wtf? --> include "" called this function above this page !! kind of printed ig?
//how do i pass that ? T_T --  change this and .h file one as well 
//
//
void midalloc(void* chunk_size, int* clear_mapping, // same problem how to typecast it bruh?
                     void* permissions,void* flags, void *type, void* file_des, void* offset){
  //
  //
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
  //so this mmp should technically call the chunk that is random
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
  // the page of the os must only be of one neibhourhood only - i can't have like stack and heap segments on this one page 
  // so i would have to get another page for the heap/stack --  x no its fine the os does that itself -- also at one time there would
  // be multiple pages open at the same tme - stack/heap or compiled file or global variables. 0_0.
  //
  //why not just call a large page and break it into smaller sub pages for independent stuff? 
  // mprotect() --> the above thing is done using this shit i guess?
  //
  //
  //
  //
  char* data_allocate = "I hate my life";
  void* chunk = mmap(NULL,
                     *(size_t*)chunk_size, // somehow worked lol :),
                     *(int*)permissions,*(int*)flags,*(int*)file_des,*(int*)offset); // is changing this stuff better option ? idk :P

  size_t data_of_user_combined; // why not int?
  //
  //
  //global_header_pointer simply keeps the note of where the first free block is (the anchor).
  void* global_header_pointer = NULL;
  //wtf is this (BlockHeader*)raw_pool
  //
  // 
  // int or size_t which one? i am confused -- well automatically make it int so that it won't make an error even if the user typed wrong;
  //
  // Block splitting time yay T-T  --- x
  // kind of trying to break the main chunk into pages for use in heap and stack and stuff
  // but then i would have to find a way to check which page the data goes to ig 0_0.
  //
  //BlockHeaderk* new_page_chunk = (BlockHeader*)&chunk + no_of_mem_segments;
  //
  //
  //
  // leaving the idea of splitting the mmap aside for now. -- can do some page header stuff and all but it would be pain ig :(
  //
  //
  //
  //
  //
  //
  //chunk tha came from the mmap is void* -> so i will convert to blockheader type DAMN :)
  //and the i can't write to it because its void and i don't know its width is unknown
  //
  //
  // THE ASSIGNMENTS of pointers is in the registers of the cpu -- rax or rbx ????? WTF????
  // thread stack? wtf\
  //
  //okay so basically there's rax and other registers in the bloody system - like rax rbp are low on size and less no.
  //of them so cpu can use AVX-512 ( 32 of them ) giving 2kb of raw storage.
  // --> these are designed for SIMD (single instruction,multiple data)
  //
  // SCRATCH-PAD memory - i don't know someone made what i thought :(
  //
  //now there's something called the register spilling and loop tiling -  If you are writing an algorithm (like matrix multiplication),
  //the compiler will pull a 2KB sub-matrix directly into these vector registers - skipping the l1 cache and keep using data from this pipeline.
  //
  //now for the fact that there should be constant memory in that register for the cpu to use and not access the ram everytime for it.
  //this thing is called  Immediate Value Encoding and Register Pinning. -- ig :P
  //
  //The compiler now maps your struct's offsets relative to the base address 0x7fff0000:
  BlockHeader* firstHeader = (BlockHeader*)chunk;
  //to manipulate this stuff i would have to use double pointers :) so bsically BlockHeader* is datatype and
  //BlockHeader** is that type pointer pointing to that address; 
  //to change the thing the pointer points to.
  //
  //
  //
  //wtf i have to change  this or the pointer arith will fail right?
  // this will be changed so another pointer to it is taken so manipulation becomes ez :)
  //
  //what should be the optimal type of pointer ?
  BlockHeader* header_pointer = (BlockHeader*)firstHeader; // -- damn its just pointing to the end of the header !!
  // Wtf ? ---->>> any math or dereferencing done through header_space will corrupt the struct's fields (size, is_free).
  global_header_pointer = &header_pointer;
  //
  // so basically this double pointer things means that there is a header_space is a pointer to a pointer of type blockheader
  // while thhis head_pointer is its normal generic one.
  // TWIST ig: at the end of all both of these pointers are pointing to the same address
  // header_pointer assums that to be a struct while header_space assumes it a pointer to another pointer
  // header_pointer + 1 jumps ahead by sizeof(BlockHeader) (e.g., 16 or 32 bytes).
  // header_space + 1 jumps ahead by only sizeof(BlockHeader*) (typically 8 bytes on a 64-bit system).
  //
  //
  //3remove blockheader pointer type -- can also use something called uintptr_t
  char* header_space = (char*)(BlockHeader**)header_pointer;
  //
  // --- TASK: know the refrencing of the virutal addresses correctly. -- that is storage wise check;
  //suppossing the base address is 0x7fff000
  firstHeader->is_free = 1;// ->x7fff000
  //
  //pointer arithmetic is the next line -- yk this shit -- +N = N(size_t)
  // x7fff00x something relative to this -- i forgot lol T_T
  firstHeader->size = data_of_user_combined - sizeof(BlockHeader);
  //
  // this is not a good place to put pointer but i still wll;
  //pointer_data* prev = NULL;
  //pointer_data* next;
  //can't bring them to loop - beginner stuff - would make it a local variable - deleted every iteration
  //
  //
  //
  // header_pointer is fine but i need to make use of firstHeader or somtheing equivalent that allows me to manipulate the struct as well
  //
  //
  // right now it simply goes through every one instance of it T-T. 
  if(header_pointer->is_free == 1){
    // what if there is no space -- remove some stuff - but which one or is there some better way;



    // SHOULD I USE HEADER_SPACE ?? - LIKE I FEEL SOMETHING WILL GO WRONG
    // header_space is nothing but a thing assuming tha address containing another address of a pointer.
    // header_pointer reads the entire size of struct as its a pointer to that struct
    // but header_space reads only 8 bytes which is the size of that memory address
    // for manipulating the memory address i will use the header_space
    // Advances by sizeof(BlockHeader*) (8 bytes on 64-bit). If you try to jump to user space using this, you will corrupt your own struct fields.
    // WTF -- WHY WILL IT GET CORRUPTED T_T if i use BlockHeader** ?? wtf is the problem ?
    //
    //header_space for layout and header_pointer for manipulating the actual payload space;
    header_pointer->is_free = 0;
    header_pointer -> size = strlen(data_allocate) * sizeof(int);
    //
    //
    // ****ROUND THE DATA UPTO MULTIPLE OF 8 !!
    // cpu architecture -- will reads in chunks no matter what (bit wise (8 byte chunks)) --> MEMORY WORD :(
    // cpu can grab memory only at clean multiples of 8 -- like 0x00 and 0x08 and stuff like that.
    // so basically allocation can happen anywhere but the calling by cpu only happens on those spots !!!
    //
    // Physical Memory Chunks (Words): -- normal
    //Word 0: [ 00 ][ 01 ][ 02 ][ 03 ][ 04 ][ 05 ][ 06 ][ 07 ]  (Address 0x00)
    //Word 1: [ 08 ][ 09 ][ 10 ][ 11 ][ 12 ][ 13 ][ 14 ][ 15 ]  (Address 0x08)
    //
    //Your 4-byte integer goes over the boundary!
    //Word 0: [    ][    ][    ][    ][    ][ X0 ][ X1 ][ X2 ]  
    //Word 1: [ X3 ][    ][    ][    ][    ][    ][    ][    ]  
    //
    //now to read this single 4byte integer have to first fetch word 0 and then fetch word 1 
    //and then "Mask out" the irrelevant bytes using "Bitwise Shifts" -- my cpu cycles !! T-T
    //and bring all 4 of them into a register !! - my register T-T.
    //doubles the cache pressure :P and memory bus traffic - wtf. on ARM this causes an unaligned access fault.
    data_allocate = header_space; // is this fine ? i am scared it will break something. 
    //
    // how tf i will get the next_pointer if i don't which is free without going through every single one?
    header_pointer->prev_pointer = (void*)&header_space;
    //well heaader is basically what i define it to be so i can just let it go inside the header and assume its outside of the header :)
    //
    pointer_data pointers;
    pointers.prev = (void*)&header_pointer; // should store it but isn't it a local varible  -- how tf do i make it remember it and make it a permanent variable;
    //
    //stuck how to do that every single header ? - so basically how would i make a linked list 
    //
    
    header_space += (sizeof(char)*strlen(data_allocate) + header_pointer->size)/sizeof(BlockHeader);
    header_pointer = (BlockHeader*)&header_space; // wtf am i doing? --> kind of fine

    //
    //

    // now how tf do i make the linked list; 
    // and how do i make it go through and update the header pointers?
    // supposedly the pointer i made suppose prev is simply there in the register which would be removed later but i would write the next address directly into the 
    // permanent mmap memory page itself and now how the fuck do i do that ???
    //
    //  CODEVAULT: int i = 0  ---- Node* curr = &root;
    //             i < n --------- curr!= NULL;
    //             i ++ ------ curr = curr->next;
    // 
    // root.next = malloc() --- T-T 
    // root.next->next; -- 2nd pointer 
    // root.next->next->x; its value
    // root.next->next->next; -- that's how it will go i guess
    // but how to make it automated and won't the list be like 150 elements or more long T-T;
    //
    // iterating over a linked list is same as iterating over an array - almost same; -- yay i may be able to change
    // for(Node* curr = &root ;curr!=NULL; curr = curr->next){
    //      curr -> next = some_stuff; -- that should work nicely
    // }
    //
    //
  }

  else{
    
  }

  // now i guess i can change things like firstHeader --> something like size or is_free.
  //wtf is pointer typecasting?
  //
  //there's BlockHeader* pointer or something like that -- also pointer + 1 points to the user data 

  // probably something like pointer == (thing) that will allocate the space to it - so basically call the algo for the pointers but what pointer
  // if i can't take in what type of data it is - how would i make function out of it?
  // -->  void is the answer simply while giving call something like int* sdsd = function();   // Return the payload as a generic void*
  if(clear_mapping){
    munmap(chunk,strlen(data_allocate)*sizeof(char));
  }

  
}
//
//
//weird stuff - leave for now;
void register_call(void){
  // warming up the cache with prefetching wtf did i just hear???
}
