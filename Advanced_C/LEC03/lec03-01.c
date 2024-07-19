#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
int main()
{
        FILE *fin;
        wchar_t s[]=L"Hello";
        fin = fopen("input_wchar.txt","w");
        for(size_t i=0; s[i]; i++)
           fwrite(&s[i],sizeof(wchar_t),1,fin);
        fclose(fin);
        return 0;
        
}
