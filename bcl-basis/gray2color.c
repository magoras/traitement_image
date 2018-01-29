#include <stdlib.h>
#include <stdio.h>

#include <bcl.h>

void process( char* ims0, char* ims1, char*ims2, char* imd){
  pnm sourcer = pnm_load(ims0);
  pnm sourceg = pnm_load(ims1);
  pnm sourceb = pnm_load(ims2);
  
  
  int widthr = pnm_get_width(sourcer);
  int heightr = pnm_get_height(sourcer);

  int widthg = pnm_get_width(sourceg);
  int heightg = pnm_get_height(sourceg);

  int widthb = pnm_get_width(sourceb);
  int heightb = pnm_get_height(sourceb);
  
  if (widthr != widthg && widthr != widthb) printf("images sources de format différents\n");

  if (heightr != heightg && heightr != heightb) printf("images sources de format différents\n");
  size_t height = heightr;
  size_t width = widthr;
  pnm dest = pnm_new(width, height, PnmRawPpm);

  for(int k = 0; k < (int)height; k++){
    for (int l = 0; l < (int)width; l++){
      pnm_set_component(dest,k,l,0,pnm_get_component(sourcer,k,l,0));
      pnm_set_component(dest,k,l,1,pnm_get_component(sourceg,k,l,1));
      pnm_set_component(dest,k,l,2,pnm_get_component(sourceb,k,l,2));
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

#define PARAM 4
int 
main(int argc, char *argv[])
{
  if (argc != PARAM+1) usage(argv[0]);

  char* ims0 = argv[1];
  char* ims1 = argv[2];
  char* ims2 = argv[3];
  char* imd = argv[4];

  process(ims0,ims1,ims2,imd);
  
  /* if(){ */
  /*   printf("\n"); */
  /*   return EXIT_FAILURE; */
  /* } */
 
  return EXIT_SUCCESS;
}
