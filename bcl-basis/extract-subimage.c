#include <stdlib.h>
#include <stdio.h>

#include <bcl.h>

void process( size_t i , size_t j, size_t rows, size_t cols, char* ims, char* imd){
  pnm source = pnm_load(ims);
  pnm dest = pnm_new(cols, rows, PnmRawPpm);
  for(size_t k = 0; k < rows; k++){
    for (size_t l = 0; l < cols; l++){
      pnm_set_component(dest,k,l,0,pnm_get_component(source,i+k,j+l,0));
      pnm_set_component(dest,k,l,1,pnm_get_component(source,i+k,j+l,1));
      pnm_set_component(dest,k,l,2,pnm_get_component(source,i+k,j+l,2));
    }
  }
  pnm_save(dest, PnmRawPpm, imd);
}

void 
usage (char *s)
{
  fprintf(stderr,"Usage: %s %s", s, "<i> <j> <rows> <cols> <ims> <imd>\n");
  exit(EXIT_FAILURE);
}

#define PARAM 6
int 
main(int argc, char *argv[])
{
  if (argc != PARAM+1) usage(argv[0]);
  size_t i = atoi(argv[1]);
  size_t j = atoi(argv[2]);


  size_t rows = atoi(argv[3]);
  size_t cols = atoi(argv[4]);

  char * ims = argv[5];
  char * imd = argv[6];

  pnm source = pnm_load(ims);
  int width = pnm_get_width(source);
  int height = pnm_get_height(source);
  
  if( (int)i < 0 || (int)i > height || (int)j < 0 || (int)j > width ){
    printf(" Les coordonnées de début doivent être dans l'image (si négatif c'est évident sinon trop grandes) \n");
    return EXIT_FAILURE;
  }
  if ((int)i-height > (int)rows){
    printf("Destination trop large\n");
    return EXIT_FAILURE;
  }
  if ((int)j-width > (int)cols) {
    printf("Destination trop haute\n");
    return EXIT_FAILURE;
  }
  if ((int)cols < 0 || (int)rows < 0){ 
    printf(" On ne peut créer une image avec des dimensions négatives\n");
    return EXIT_FAILURE;
  }
  
  process(i,j,rows,cols,ims,imd);
  return EXIT_SUCCESS;
}
