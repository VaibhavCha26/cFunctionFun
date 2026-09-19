#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include <SDL3/SDL.h>
#include <wchar.h>

int main(int argc, char* argv[]){
  // must check for testFile if it exists or not -- :P who cares.
  FILE *testFile = fopen(
    "/home/script_kiddie/Downloads/testing_image.png"
    ,"rb");
  
  png_structp wtfisgoingon = // this is my png_pointer !!! -- memory is here in this -- well rhetoricallya
  /*  
   What it does: Allocates and initializes the primary png_struct tracking state on the heap
   The Mechanics: It takes the version string flag (PNG_LIBPNG_VER_STRING) to verify that the 
   header files you compiled with exactly match the binary .so/.dll library files running on your OS. 
   The three NULL arguments are optional slots 
   where you could pass custom memory allocation or error-handling callback functions if you didn't want to use standard malloc and stderr.
   System View: Carves out a dedicated, private working memory space for the zlib decompression tables and state records.
   */
    png_create_read_struct(
    PNG_LIBPNG_VER_STRING,NULL,
                         NULL,NULL); 
  // -->2nd bench probably for storing the keeping data like
  // bank ledger where libpng will write the image's metadata.
  //
  //
  //
  //
  png_infop info = png_create_info_struct(
    wtfisgoingon);
  //
  png_init_io( wtfisgoingon,testFile);
  //
  //
  //this is the first true reading of the data -- T-T 
  //everything before it was just playing around with page;
  png_read_info(wtfisgoingon,info);
  //
  //
  fclose(testFile);
  //
  png_destroy_read_struct(&wtfisgoingon,
                          &info,
                          NULL);
  //why not use png_destroy_info_struct;
  //supposdely the destroying the parent read struct destroys everything in itself
  //even if i called it will be a double memory corruption crash.
  return 0;
}
