#include <stdlib.h>
#include <stdio.h>

#include <bcl.h>

void process( int min, int max, char* ims, char imd){
  pnm source = pnm_load(ims);
  int width = pnm_get_width(source);
  int height = pnm_get_height(source);
  pnm dest = pnm_new(width, height, PnmRawPpm);

  if(num == 0){
    for(int k = 0; k < (int)height; k++){
      for (int l = 0; l < (int)width; l++){
	pnm_set_component(dest,k,l,0,pnm_get_component(source,k,l,0));
	pnm_set_component(dest,k,l,1,pnm_get_component(source,k,l,0));
	pnm_set_component(dest,k,l,2,pnm_get_component(source,k,l,0));
      }
    }
  }

  if(num == 1){
    for(int k = 0; k < (int)height; k++){
      for (int l = 0; l < (int)width; l++){
	pnm_set_component(dest,k,l,0,pnm_get_component(source,k,l,1));
	pnm_set_component(dest,k,l,1,pnm_get_component(source,k,l,1));
	pnm_set_component(dest,k,l,2,pnm_get_component(source,k,l,1));
      }
    }
  }

  if(num == 2){
    for(int k = 0; k < (int)height; k++){
      for (int l = 0; l < (int)width; l++){
	pnm_set_component(dest,k,l,0,pnm_get_component(source,k,l,2));
	pnm_set_component(dest,k,l,1,pnm_get_component(source,k,l,2));
	pnm_set_component(dest,k,l,2,pnm_get_component(source,k,l,2));
      }
    }
  }
x
  pnm_save(dest, PnmRawPpm, imd);
}

void 
usage (char *s)
{
  fprintf(stderr,"Usage: %s %s", s, "<num> <ims> <imd>\n");
  exit(EXIT_FAILURE);
}

#define PARAM 3
int 
main(int argc, char *argv[])
{
  if (argc != PARAM+1) usage(argv[0]);

  size_t num = atoi(argv[1]);
 
  char * ims = argv[2];

  char * imd = argv[3];

  
  if((int)num<0 || (int)num>2){
    printf("Les images sont considérées en RGB\n");
    return EXIT_FAILURE;
  }
 
  process(num,ims,imd);
  return EXIT_SUCCESS;
}
