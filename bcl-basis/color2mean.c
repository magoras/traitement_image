#include <stdlib.h>
#include <stdio.h>

#include <bcl.h>

void process( char* ims ,char* imd){

  pnm source = pnm_load(ims);
  
  int width = pnm_get_width(source);
  int height = pnm_get_height(source);
  
  pnm dest = pnm_new(width, height, PnmRawPpm);

  for(int k = 0; k < (int)height; k++){
    for (int l = 0; l < (int)width; l++){
      int mean = (((int)pnm_get_component(source,k,l,0) + (int)pnm_get_component(source,k,l,1) + (int)pnm_get_component(source,k,l,2))/3);
      pnm_set_component(dest,k,l,0,mean);
      pnm_set_component(dest,k,l,1,mean);
      pnm_set_component(dest,k,l,2,mean);
    }
  }
 

  pnm_save(dest, PnmRawPpm, imd);
}

void 
usage (char *s)
{
  fprintf(stderr,"Usage: %s %s", s, "<ims0> <ims1> <ims2> <imd> \n");
  exit(EXIT_FAILURE);
}

#define PARAM 2
int 
main(int argc, char *argv[])
{
  if (argc != PARAM+1) usage(argv[0]);

  char* ims = argv[1];
  char* imd = argv[2];

  process(ims,imd);
  
  /* if(){ */
  /*   printf("\n"); */
  /*   return EXIT_FAILURE; */
  /* } */
 
  return EXIT_SUCCESS;
}
