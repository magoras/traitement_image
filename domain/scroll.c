#include <stdlib.h>
#include <stdio.h>
#include <pnm.h>

void setpix(int i, int j,int dx, int dy, pnm source,int can,pnm dest,int rows,int cols) {
  if((i>0) && (j>0) && (i-dy>0) && (j-dy>0) && (i<rows) && (j<cols))
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
  int col  = (int)cols;
  int row = (int)rows;
  pnm dest = pnm_new(cols, rows, PnmRawPpm);


  if(dx>=0 && dy>=0){
    for (int i = 0 ; i < dy ; i++){
      for (int j = 0 ; j < dx ; j++){
          for (int can = 0 ; can < 3 ; can ++){
            //pnm_set_component(dest,i,j,can,pnm_get_component(source,rows-dy+i,cols-dx+j,can));
            setpix(i,j,-col+dx,-row+dy,source,can,dest,row,col);
          }
        }
      }
      for (int i = dy ; i < row + dy ; i++){
        for (int j = dx ; j < col + dx ; j++){
            for (int can = 0 ; can < 3 ; can ++){
              setpix(i,j,dx,dy,source,can,dest,row,col);
            }
          }
        }

        for (int i = dy ; i < row ; i++){
          for (int j = 0 ; j < dx ; j++){
              for (int can = 0 ; can < 3 ; can ++){
                setpix(i,j,-col+dx,0,source,can,dest,row,col);

              }
            }
          }

          for (int i = 0 ; i < dy ; i++){
            for (int j = dx ; j < col  ; j++){
                for (int can = 0 ; can < 3 ; can ++){
                  setpix(i,j,0,-row+dy,source,can,dest,row,col);
                }
              }
            }

            


pnm_save(dest, PnmRawPpm, imd_name);
pnm_free(source);
pnm_free(dest);
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
