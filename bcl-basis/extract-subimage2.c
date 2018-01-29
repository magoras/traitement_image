#include <stdlib.h>
#include <stdio.h>

#include <bcl.h>

void process(int i, int j, int rows, int cols, char *ims, char *imd){
  if( rows<0 || cols < 0 || i > rows || j > cols){        // On gère une éventuelle erreur sur les paramètres
    perror("**************** erreur sur les arguments****************\n");
    exit(EXIT_FAILURE);
  }

  pnm base = pnm_load(ims);
  pnm new  = pnm_new(cols, rows, PnmRawPpm);

  for(int k=0 ; k<rows; k++){
    for(int l=0; l<cols; l++){
    pnm_set_component(new, k, l, 0, pnm_get_component(base, i+k, j+l, 0));
    pnm_set_component(new, k, l, 1, pnm_get_component(base, i+k, j+l, 1));
    pnm_set_component(new, k, l, 2, pnm_get_component(base, i+k, j+l, 2));
    }
  }
  pnm_save(new, PnmRawPpm, imd);
  pnm_free(base);
  pnm_free(new);
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
  char *ims = argv[5];
  char *imd = argv[6];

  process(i, j, rows, cols, ims, imd);
  return EXIT_SUCCESS;
}
