#include <stdlib.h>
#include <stdio.h>
#include <pnm.h>

void setpix(int i, int j,int dx, int dy, pnm source,int can,pnm dest,int rows,int cols) {
  if((i>0) && (j>0) && ((i-dy>0) || (j-dy>0)) && (i<rows) && (j<cols))
      pnm_set_component(dest,i,j,can,pnm_get_component(source,i-dy,j-dx,can));
}

void
process(int dx, int dy, char* ims_name, char* imd_name)
{
  /*(void)dx;
  (void)dy;
  (void)ims_name;
  (void)imd_name;*/

  pnm source = pnm_load(ims_name);
  size_t cols = pnm_get_width(source);
  size_t rows = pnm_get_height(source);
  pnm dest = pnm_new(cols, rows, PnmRawPpm);

  for (int i = dy ; i < (int)rows + dy ; i++){
    for (int j = dx ; j < (int)cols + dx ; j++){
        for (int can = 0 ; can < 3 ; can ++){
            setpix(i,j,dx,dy,source,can,dest,(int)rows,(int)cols);
      }
    }
  }


pnm_save(dest, PnmRawPpm, imd_name);
}

void
usage(char* s)
{
  fprintf(stderr,"%s <dx> <dy> <ims> <imd>\n",s);
  exit(EXIT_FAILURE);
}

#define PARAM 4
int
main(int argc, char* argv[])
{
  if(argc != PARAM+1)
    usage(argv[0]);
  int dx = atoi(argv[1]);
  int dy = atoi(argv[2]);
  char* ims = argv[3];
  char* imd = argv[4];
  process(dx, dy, ims, imd);

  return EXIT_SUCCESS;
}
