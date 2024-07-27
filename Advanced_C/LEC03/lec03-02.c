#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

int main()
{
  FILE *fin;
  FILE *fout;
  int32_t character;
  wchar_t tmp;
  int8_t arr_out[100]={0};
  size_t i=0;

  fin = fopen("input_wchar.txt","rb");
  while( fread(&tmp, sizeof(wchar_t), 1, fin)==1 )
     arr_out[i++] = tmp;
  fclose(fin);
  fout = fopen("output_ascii.txt","w");
  fprintf(fout,"%s",arr_out);
  fclose(fout);
  return 0;
}
