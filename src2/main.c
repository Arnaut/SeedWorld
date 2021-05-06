#include "Perlin.h"
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <math.h>
#include <time.h>

unsigned countBits(unsigned int number)
{
  return (int)log2(number)+1;
}

int main(int argc, char** argv) {
  if(argc != 6)errx(0,"Syntax : ./SeedWorld [height] [width] [octaves] [biais] [seed]");

  int height = strtoul(argv[1], NULL, 10);
  int width = strtoul(argv[2], NULL, 10);
  int octaves = strtoul(argv[3], NULL, 10);
  float biais = atof(argv[4]);
  unsigned int Seed = strtoul(argv[5], NULL, 10);

  if(Seed==0)Seed = (unsigned int) (time(NULL));
  srand(Seed);
  printf("Seed:%i\n",Seed);

  int minsize;
  if(height<width)minsize=height;
  else minsize=width;
  minsize = countBits(minsize);
  if(octaves>minsize)errx(1,"octaves is to big: must be %i max for this picture size",minsize);

  PerlinNoise(height,width,octaves,biais);

  return 0;
}
