#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 30

typedef struct {
    uint16_t year;
    uint8_t month;
    uint8_t day;
    int8_t t;
} sensor;

struct data
{
    uint32_t number;
    sensor info[SIZE];
} d;

void cgangeIJ(sensor info[],int i, int j)
{
    sensor temp;
    temp=info[i];
    info[i]=info[j];
    info[j]=temp;
}
//упорядочивающую его по неубыванию температуры
void SortByT(sensor info[],int n)
{
    for(int i=0; i<n; ++i)
        for(int j=i; j<n; ++j)
            if(info[i].t>=info[j].t)
                cgangeIJ(info,i,j);
}

unsigned int DateToInt(sensor* info)
{
    return info->year << 16 | info[0].month << 8 | (*info).day;
    //|| - логическая ИЛИ = 0,1
    //|  - побитовая ИЛИ
}

int Compare(const void* av,const void* bv)
{
    sensor* a = (sensor*)av;
    sensor* b = (sensor*)bv;
    if(a->year!=b->year)
        return a->year - b->year;
    else if(a->month!=b->month)
        return a->month - b->month;
    else if(a->day!=b->day)
        return a->month - b->month;
    else
        return 0;
}

//упорядочивающую его по дате
void SortByDate(sensor info[],int n)
{
    for(int i=0; i<n; ++i)
        for(int j=i; j<n; ++j)
            //~ if(DateToInt(info+i)>=DateToInt(info+j))
            if(Compare(info+i,info+j)>0)
                cgangeIJ(info,i,j);
}

//typedef unsigned char U8;
void AddRecord(sensor info[],int number,uint16_t year,uint8_t month,uint8_t day1,int8_t t)
{
    info[number].year = year;
    info[number].day = day1;
    info[number].month = month;
    info[number].t = t;
}

int AddInfo(sensor info[])
{
    int counter=0;
    AddRecord(info,counter++,2021,9,16,9);
    AddRecord(info,counter++,2022,9,2,-9);
    AddRecord(info,counter++,2021,1,7,8);
    AddRecord(info,counter++,2021,9,5,1);
    return counter;
}

void print(sensor info[],int number) {
    printf("===================================\n");
    for(int i=0; i<number; i++)
        printf("%04d-%02d-%02d t=%3d\n",
               info[i].year,
               info[i].month,
               info[i].day,
               info[i].t
              );
}

void load_bin(sensor info[],int number)
{
    FILE* f = fopen("sensor.bin","rb");
//Проверка на открытие файла
    fread(info,number*sizeof(sensor),1,f);
    fclose(f);
}

void save_bin(sensor info[],int number)
{
    FILE* f = fopen("sensor.bin","wb");
//Проверка на открытие файла
    fwrite(info,number*sizeof(sensor),1,f);
    fclose(f);
}

void load_bin_d(struct data* d)
{
//Проверка на открытие файла
    FILE* f = fopen("sensor1.bin","rb");
//Проверка на считанные данные
    fread(&d->number,sizeof(d->number),1,f);
    fread(d->info,d->number*sizeof(sensor),1,f);
    fclose(f);
}

void save_bin_d(struct data* d)
{
    FILE* f = fopen("sensor1.bin","wb");
    fwrite(&d->number,sizeof(d->number),1,f);
    fwrite(d->info,d->number*sizeof(sensor),1,f);
    fclose(f);
}


void print_size(void)
{
    struct str1 {
        uint32_t u;
        uint8_t c1;
        int32_t i;
        uint8_t c2;
    } s1;
    struct str2 {
        uint32_t u;
        int32_t i;
        uint8_t c1;
        uint8_t c2;
    } s2;
    printf("Sizeof s1 = %llu\n", sizeof(s1));
    printf("Sizeof s2 = %llu\n", sizeof(s2));
}

int main(void)
{

    print_size();
    sensor info[SIZE];
    int number=AddInfo(info);
    load_bin(info,number);
    print(info,number);
    printf("\nSort by t\n");
    SortByT(info,number);
    print(info,number);
    save_bin(info,number);
    printf("\nSort by date\n");
    //SortByDate(info,number);
    qsort(info,number,sizeof(sensor),Compare);
    print(info,number);

    return 0;
}

