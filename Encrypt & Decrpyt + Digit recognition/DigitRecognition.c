#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


// In this part i'll take an image , i will encrpyt that image with the algorithm above and then i'll the decrypt it back
// as it was in the first time.
struct pixel
{
    unsigned char r,g,b;
};
struct detectie{
    int x,y,buna,cifra;
    double valCorelatie;
};
uint32_t xorshift32(uint32_t state)
{
    uint32_t x = state;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    state = x;
    return x;
}
void GetHandW(FILE*file, int *H, int *W)
{
    unsigned char *imageData=(unsigned char *)malloc(54*sizeof(unsigned char));
    const int hByte=22;
    const int wByte=18;
    fread(imageData,sizeof(unsigned char),54,file);
    *W = *(int*)&imageData[wByte];
    *H = *(int*)&imageData[hByte];
    free(imageData);
}
struct pixel pixelXorInt(struct pixel pixel, unsigned int a)
{
    struct pixel result;
    result.b= pixel.b ^ (a & 255);
    a =a >> 8;
    result.g= pixel.g ^ (a & 255);
    a =a >> 8;
    result.r= pixel.r ^ (a & 255);
    return result;
}
struct pixel pixelXorPixel(struct pixel pixel_1, struct pixel pixel_2)
{
    struct pixel result;
    result.r=pixel_1.r^pixel_2.r;
    result.g=pixel_1.g^pixel_2.g;
    result.b=pixel_1.b^pixel_2.b;
    return result;
}
void BMP_to_vector(char * nume_fisier,int *H,int *W, struct pixel **m)
{
    int i,j;
    FILE *file=fopen(nume_fisier, "rb");
    if(file==NULL)
        printf("Could not open the file.\n");
    GetHandW(file,H,W);
    fseek(file,54,SEEK_SET);
    (*m)=( struct pixel*)malloc((*W)*(*H)*sizeof( struct pixel));
    unsigned char *x=(unsigned char*)malloc(3*sizeof(unsigned char));
    for(i=(*H)-1;i>=0;i--)
    {
        for(j=0;j<(*W);j++)
        {
            fread(&(*m)[i*(*W)+j].b,1,1,file);
            fread(&(*m)[i*(*W)+j].g,1,1,file);
            fread(&(*m)[i*(*W)+j].r,1,1,file);
        }
    }
    free(x);
    free(m);
    fclose(file);
}
void GenRandom(unsigned int **r, int length, unsigned int seed)
{
    unsigned int i,copie;
    *r=(unsigned int*)malloc(length*sizeof(unsigned int));
    (*r)[0]=seed;
    for(i=1;i<length;i++)
        (*r)[i]=xorshift32((*r)[i-1]);
    free(r);
}
void swap(int *x, int *y)
{
    int aux=*x;
    *x=*y;
    *y=aux;
}
void RandomPerm(unsigned int **p, int length, unsigned int *r)
{
    int i,j;
    *p=(unsigned int*)calloc(length,sizeof(unsigned int));
    for(i=0;i<length;i++)
        (*p)[i]=i;
    for(i=length-1;i>0;i--)
    {
        j=r[length-i]%(i+1);
        swap(&((*p)[j]),&((*p)[i]));
    }
}
void Encrypt(struct pixel**m, int H, int W,struct pixel **c, char *secret_key)
{
    int length=H*W,i,j;
    FILE *key=fopen(secret_key,"r");
    if(key==NULL)
        printf("Could not open the file.\n");
    unsigned int seed,*r,*p;
    fscanf(key,"%d",&seed);
    const unsigned int sv;
    fscanf(key,"%d",&sv);
    GenRandom(&r, 2*length, seed);
    (*c)=(struct pixel*)malloc(length*sizeof(struct pixel));
    if(c==NULL)
        printf("Could not allocate memory\n");
     struct pixel *q=(struct pixel*)malloc(length*sizeof(struct pixel));
    if(q==NULL)
        printf("Could not allocate memory\n");
    RandomPerm(&p,length,r);

    for(i=0;i<length;i++)
        q[p[i]]=(*m)[i];
    afisare_vector("permutare.bmp","peppers.bmp",&q,H,W);
    struct pixel temp=pixelXorInt(q[0],sv);
    (*c)[0]=pixelXorInt(temp,r[W*H]);
    for(i=1;i<length;i++)
    {
        temp=pixelXorPixel((*c)[i-1],q[i]);
        (*c)[i]=pixelXorInt(temp,r[W*H+i]);
    }
    for(i=0;i<length;i++)
        (*m)[i]=(*c)[i];
    free(q);

    fclose(key);
}
void Decrypt(struct pixel **m, int H, int W,struct pixel **c, char *secret_key)
{
    int i,length=H*W;
    FILE *key=fopen(secret_key,"r");
    if(key==NULL)
        printf("Could not open the file.\n");
    unsigned int seed,*r,*p;
    fscanf(key,"%d",&seed);
    const unsigned int sv;
    fscanf(key,"%d",&sv);
    GenRandom(&r, 2*length,seed);
    RandomPerm(&p,length,r);
    struct pixel *D=(struct pixel *)malloc(length*sizeof(struct pixel));
    struct pixel temp=pixelXorInt((*c)[0],sv);
    (*c)[0]=pixelXorInt(temp,r[W*H]);
    for(i=1;i<length;i++)
    {
        temp=pixelXorPixel((*c)[i-1],(*c)[i]);
        D[i]=pixelXorInt(temp,r[W*H+i]);
    }
    unsigned int *invers=(unsigned int *)malloc(H*W*sizeof(unsigned int));
    for(i=0;i<H*W;i++)
        invers[p[i]]=i;
    for(i=0;i<H*W;i++)
        (*m)[invers[i]]=D[i];
    free(c);
    free(D);
    fclose(key);
}
void afisare_vector(char *nume_destinatie,char *nume_sursa,struct  pixel **m, int H, int W)
{
    FILE *bin=fopen(nume_destinatie,"wb");
    if(bin==NULL)
        printf("Could not open the file.\n");
    FILE *file=fopen(nume_sursa,"rb");
    if(file==NULL)
        printf("Could not open the file.\n");
    int i,j;
    unsigned int *imagedata=(unsigned int *)malloc(54*sizeof(unsigned int));
    if(imagedata==NULL)
        printf("Could not allocate memory\n");
    fread(imagedata,sizeof(char),54,file);
    fwrite(imagedata,sizeof(char),54,bin);
    for(i=H-1;i>=0;i--)
    {
        for(j=0;j<W;j++)
        {
            fwrite(&(*m)[i*W+j].b,sizeof(unsigned char),1,bin);
            fwrite(&(*m)[i*W+j].g,sizeof(unsigned char),1,bin);
            fwrite(&(*m)[i*W+j].r,sizeof(unsigned char),1,bin);
        }
    }
    free(imagedata);
    fclose(bin);
    fclose(file);
}
void afisare_matrice(char *nume_destinatie,char *nume_sursa,struct  pixel ***m, int H, int W)
{
    FILE *bin=fopen(nume_destinatie,"wb");
    FILE *file=fopen(nume_sursa,"rb");
    int i,j,padding=0;
    int *imagedata=(int *)malloc(54*sizeof(int));
    fread(imagedata,sizeof(char),54,file);
    fwrite(imagedata,sizeof(char),54,bin);
    if(W%4!=0)
        padding=4-3*(W%4);
    for(i=H-1;i>=0;i--)
    {
        for(j=0;j<W;j++)
        {
            fwrite(&(*m)[i][j].r,sizeof(unsigned char),1,bin);
            fwrite(&(*m)[i][j].g,sizeof(unsigned char),1,bin);
            fwrite(&(*m)[i][j].b,sizeof(unsigned char),1,bin);
        }
        int copy_padding=padding;
        if(copy_padding!=0)
        {
            fwrite(&(*m)[i][j].r,sizeof(unsigned char),1,bin);
            copy_padding--;
        }
        if(copy_padding!=0)
        {
            fwrite(&(*m)[i][j].g,sizeof(unsigned char),1,bin);
            copy_padding--;
        }
        if(copy_padding!=0)
        {
            fwrite(&(*m)[i][j].b,sizeof(unsigned char),1,bin);
            copy_padding--;
        }
    }
}
void chipatrat(struct pixel **m, int H, int W)
{
    int i,length=H*W;
    double Xr=0,Xg=0,Xb=0,f=(1.0)*H/256*W;
    int *frecvR=(int *)calloc(256,sizeof(int));
    int *frecvG=(int *)calloc(256,sizeof(int));
    int *frecvB=(int *)calloc(256,sizeof(int));
    for(i=0;i<length;i++)
    {
        int a;
        a=(*m)[i].r;
        frecvR[a]++;
        a=(*m)[i].g;
        frecvG[a]++;
        a=(*m)[i].b;
        frecvB[a]++;
    }
    for(i=0;i<256;i++)
    {
        Xr=Xr+(frecvR[i]-f)/f*(frecvR[i]-f);
        Xg=Xg+(frecvG[i]-f)/f*(frecvG[i]-f);
        Xb=Xb+(frecvB[i]-f)/f*(frecvB[i]-f);
    }
    printf("%0.2lf %0.2lf %0.2lf \n",Xr, Xg, Xb);

}

//Digit recognition part (Template Matching algorithm)


void BMP_to_matrix(char *nume_fisier,int *H,int *W,struct pixel ***n)
{
    FILE *file=fopen(nume_fisier, "rb");
    if(file==NULL)
        printf("Could not open the file .");
    GetHandW(file,H,W);
    int padding=0,i,j;
    if((3*(*W))%4!=0)
        padding=4-((3*(*W))%4);
    (*n)=(struct pixel**)malloc((*H)*sizeof(struct pixel*));
    if(n==NULL)
        printf("Could not allocate memory");
    for(i=0;i<(*H);i++)
    {
        (*n)[i]=(struct pixel*)malloc(((*W)+1)*sizeof(struct pixel));
        if((*n)[i]==NULL)
        {
            printf("Could not allocate memory");
            break;
        }

    }
    unsigned char *x=(unsigned char*)malloc(3*sizeof(unsigned char));
    if(x==NULL)
        printf("Could not allocate memory");
    j=0;
    i=0;
    for(i=(*H)-1;i>=0;i--)
    {
        for(j=0;j<(*W);j++)
        {
            fread(x,sizeof(unsigned char),3,file);
            (*n)[i][j].r=x[0];
            (*n)[i][j].g=x[1];
            (*n)[i][j].b=x[2];
        }
        int copy_padding=padding;
        if(copy_padding!=0)
        {
            fread(x,sizeof(unsigned char),1,file);
            (*n)[i][j].r=x[0];

            copy_padding--;
        }
        if(copy_padding!=0)
        {
            fread(x,sizeof(unsigned char),1,file);
            (*n)[i][j].g=x[0];
            copy_padding--;
        }
        if(copy_padding!=0)
        {
            fread(x,sizeof(unsigned char),1,file);
            (*n)[i][j].b=x[0];
            copy_padding--;
        }
    }
    fclose(file);
    free(x);
    free(n);
}

void grayscale( struct pixel ***m, int H, int W)
{
    int i,j,length=W*H;
    for(i = 0; i < H; i++)
        for(j=0; j < W; j++)
        {
            (*m)[i][j].r = (0.299)*(*m)[i][j].b + (0.587)*(*m)[i][j].g + (0.114)*(*m)[i][j].r;
            (*m)[i][j].g = (0.299)*(*m)[i][j].b + (0.587)*(*m)[i][j].g + (0.114)*(*m)[i][j].r;
            (*m)[i][j].b = (0.299)*(*m)[i][j].b + (0.587)*(*m)[i][j].g + (0.114)*(*m)[i][j].r;
        }
}
double corelatie( struct pixel **fi,  struct pixel **sablon)
{
    int i,j,inaltime=15,latime=11,n=inaltime*latime;
    double smedie=0,fmedie=0,os=0,of=0,corelation=0;
    for(i=0;i<inaltime;i++)
        for(j=0;j<latime;j++)
            smedie=smedie+sablon[i][j].r;
    smedie=smedie/n;
    for(i=0;i<inaltime;i++)
        for(j=0;j<latime;j++)
            os=os+(sablon[i][j].r-smedie)*(sablon[i][j].r-smedie);
    os=os/n;
    os=sqrt(os);
    for(i=0;i<inaltime;i++)
        for(j=0;j<latime;j++)
            fmedie=fmedie+fi[i][j].r;
    fmedie=fmedie/n;
    for(i=0;i<inaltime;i++)
        for(j=0;j<latime;j++)
            of=of+(fi[i][j].r-fmedie)*(fi[i][j].r-fmedie);
    of=of/n;
    of=sqrt(of);
    for(i=0;i<inaltime;i++)
        for(j=0;j<latime;j++)
            corelation=corelation+(fi[i][j].r-fmedie)*(sablon[i][j].r-smedie);
    corelation=corelation/os/of/n;
    return corelation;
}
void templatematching(struct pixel **imagine,struct detectie ***matrice, int *indCorelatie, char * nume_sablon,int H, int W)
{
    int i,j,k,l,inaltime_sablon,latime_sablon;
    long cifra;
    double valCorelatie=0;
    struct pixel **sablon;
    char *p=nume_sablon;
    double prag=0.5;

    //We extract the digit that's in the image from the image name

    while(*p)
    {
        if(isdigit(*p))
        {
            cifra = strtol(p, &p, 10);
            break;
        }
        else
            p++;
    }
    BMP_to_matrix(nume_sablon,&inaltime_sablon,&latime_sablon,&sablon);
    struct pixel **subImagine=( struct pixel **)malloc(inaltime_sablon*sizeof( struct pixel*));
    if(subImagine==NULL)
        printf("Could not allocate memory");
    for(i=0;i<inaltime_sablon;i++)
    {
        subImagine[i]=( struct pixel *)malloc(latime_sablon*sizeof( struct pixel));
        if(subImagine[i]==NULL)
        {
            printf("Could not allocate memory");
            break;
        }
    }
    //Plecam din coltul stanga sus al imaginii , pixel cu pixel
    for(i=0 ; i<H-inaltime_sablon; i++)
    {
        for(j=0; j<W-latime_sablon; j++)
        {
            //Here we set a window the same size with the image of the digits.

            for(k=i;k<i+inaltime_sablon;k++)
            {
                for(l=j;l<j+latime_sablon;l++)
                {
                    subImagine[k-i][l-j].r=imagine[k][l].r;
                    subImagine[k-i][l-j].g=imagine[k][l].g;
                    subImagine[k-i][l-j].b=imagine[k][l].b;
                }
            }
            //Calculam corealtie dintre fereastra si sablon
            valCorelatie=corelatie(subImagine,sablon);
            if(valCorelatie>prag)
            {

                // If the corelation value is bigger than the flag 'prag' we save this one.
                (*matrice)[cifra][indCorelatie[cifra]].x=i;
                (*matrice)[cifra][indCorelatie[cifra]].y=j;
                (*matrice)[cifra][indCorelatie[cifra]].valCorelatie=valCorelatie;
                (*matrice)[cifra][indCorelatie[cifra]].buna=1;
                (*matrice)[cifra][indCorelatie[cifra]].cifra=cifra;
                indCorelatie[cifra]++;
            }
        }
    }
    free(subImagine);
}
void Color(struct pixel ***imagine,int lungime,struct detectie **A)
{
    int i,j,coder,codeg,codeb;
    for(i=0;i<lungime;i++)
    {
        if((*A)[i].buna==0)
            continue;
        switch((*A)[i].cifra)
        {
            case 0:
            {
                coder=255;
                codeg=0;
                codeb=0;
                break;
            }
            case 1:
            {
                coder=255;
                codeg=255;
                codeb=0;
                break;
            }
            case 2:
            {
                coder=0;
                codeg=255;
                codeb=0;
                break;
            }
            case 3:
            {
                coder=0;
                codeg=255;
                codeb=255;
                break;
            }
            case 4:
            {
                coder=255;
                codeg=0;
                codeb=255;
                break;
            }
            case 5:
            {
                coder=0;
                codeg=0;
                codeb=255;
                break;
            }
            case 6:
            {
                coder=192;
                codeg=192;
                codeb=192;
                break;
            }
            case 7:
            {
                coder=255;
                codeg=140;
                codeb=0;
                break;
            }
            case 8:
            {
                coder=128;
                codeg=0;
                codeb=128;
                break;
            }
            case 9:
            {
                coder=128;
                codeg=0;
                codeb=0;
                break;
            }
        }
        //We color the image with a color specifically to each digit.
        for(j=(*A)[i].x;j<(*A)[i].x+15;j++)
        {
            (*imagine)[j][(*A)[i].y].r=(*imagine)[j][(*A)[i].y+10].r=codeb;
            (*imagine)[j][(*A)[i].y].g=(*imagine)[j][(*A)[i].y+10].g=codeg;
            (*imagine)[j][(*A)[i].y].b=(*imagine)[j][(*A)[i].y+10].b=coder;
        }
        for(j=(*A)[i].y; j<(*A)[i].y+11; j++)
        {
            (*imagine)[(*A)[i].x][j].r=(*imagine)[(*A)[i].x+15-1][j].r=codeb;
            (*imagine)[(*A)[i].x][j].g=(*imagine)[(*A)[i].x+15-1][j].g=codeg;
            (*imagine)[(*A)[i].x][j].b=(*imagine)[(*A)[i].x+15-1][j].b=coder;
        }
    }
}
int intersect(struct detectie a, struct detectie b)
{

    //Here we take care of the problem that 2 detections can intersect
    const int inaltime=15,latime=11;
    //First we make sure that the second image is starting at the right of the first one.
    if(a.x>b.x || (a.x==b.x && a.y>b.y))
    {
        struct detectie aux;
        aux=a;
        a=b;
        b=aux;
    }
    // We test if there are any intersections.
    if((b.x<=(a.x+inaltime) && b.y<=(a.y+latime) && b.x>=a.x && b.y>=a.y) || (b.y<=a.y && b.x>=a.x && b.x<=(a.x+inaltime) && (b.y+latime)>=a.y))
    {
        int lungime=a.x+inaltime-b.x;
        int latime= a.y+latime-b.y;
        double arieIntersectie=lungime*latime,arieA=inaltime*latime,arieB=arieA,arieReuniune=arieA+arieB-arieIntersectie;
        double raport=(1.0)*arieReuniune/arieIntersectie;
        if(raport>0.2)
            return 1;
    }
    return 0;
}
int comparator(const struct detectie *x , const struct detectie *y)
{
    if((*x).valCorelatie==(*y).valCorelatie)
        return 0;
    if((*x).valCorelatie>(*y).valCorelatie)
        return -1;
    return 1;
}
void eliminareDetectie(int n, struct detectie *A,struct detectie **B)
{
    qsort(A,n,sizeof(struct detectie),comparator);
    int i=0,j;
    for(i=0;i<n;i++)
        for(j=i+1;j<n;j++)
            if(intersect(A[i],A[j]))
            {
                A[i].buna=0;
                break;
            }
    for(i=0;i<n;i++)
        (*B)[i]=A[i];
}
int vector_detectii(struct detectie ***matrice,struct detectie **A, int *indCorelatie)
{
    int i,j,k=0;
    int lungimemax=0;
    for(i=0;i<10;i++)
        lungimemax=lungimemax+indCorelatie[i];
    *A=(struct detectie *)calloc(lungimemax,sizeof(struct detectie));
    for(i=0;i<10;i++)
        for(j=0;j<indCorelatie[i];j++)
        {
            (*A)[k]=(*matrice)[i][j];
            k++;
        }
    return lungimemax;
}
void copieGray( struct pixel ***imagine,  struct pixel ***imagineGray, int H, int W)
{
    int i,j;
    *imagineGray=( struct pixel**)malloc(H*sizeof( struct pixel*));
    if(imagineGray==NULL)
        printf("Could not allocate memory");
    for(i=0;i<H;i++)
    {
        (*imagineGray)[i]=( struct pixel*)malloc(W*sizeof( struct pixel));
        if((*imagineGray)[i]==NULL)
        {
            printf("Could not allocate memory");
            break;
        }
    }
    for(i=0;i<H;i++)
        for(j=0;j<W;j++)
            (*imagineGray)[i][j]=(*imagine)[i][j];
    free(imagineGray);
}
int main()
{
    int H,W,Hp,Wp,inaltime_sablon,latime_sablon,i,j,lungime;
    struct pixel *m,*reversem,*c,**imagine,**imagineGray;
    //Presupunem ca imaginile au maxim 20 de caractere in nume.
    char *nume_imagine=(char*)malloc(20*sizeof(char));
    char *nume_imagine_criptata=(char*)malloc(20*sizeof(char));
    char *nume_imagine_decriptata=(char*)malloc(20*sizeof(char));
    char *nume_imagine_2=(char*)malloc(20*sizeof(char));
    char *nume_imagine_finala=(char*)malloc(20*sizeof(char));
    char *secret_key=(char*)malloc(20*sizeof(char));
    if(nume_imagine==NULL || nume_imagine_2==NULL || nume_imagine_criptata==NULL || nume_imagine_decriptata==NULL || nume_imagine_finala==NULL || secret_key==NULL)
        printf("Could not allocate memory " );
    struct detectie *A;


    int *indCorelatie=(int *)calloc(10,sizeof(int));
    if(indCorelatie==NULL)
    {
        printf("Could not allocate memory");
        return -1;
    }
    //First Part

    //We upload the image in the program and trasform the pixels in a vector.
    printf("Type the name of the image: ");
    scanf("%s", nume_imagine);
    BMP_to_vector(nume_imagine,&Hp,&Wp,&m);


    //Encrypt the image using the secret key
    printf("Type the name of the document that has the encryption key: ");
    scanf("%s", secret_key);
    printf("Type the name of the new crypted image: ");
    scanf("%s", nume_imagine_criptata);
    Encrypt(&m,Hp,Wp,&c,secret_key);
    afisare_vector(nume_imagine_criptata,nume_imagine,&m,Hp,Wp);

    //DDecrypt the image using the same key
    Decrypt(&m,Hp,Wp,&c,secret_key);
    printf("Type the name of the decrypted image: ");
    scanf("%s", nume_imagine_decriptata);
    afisare_vector(nume_imagine_decriptata,nume_imagine_criptata,&m,Hp,Wp);

    printf("First part complete");

    //Second part

    //Upload the image in the program and trasnform it into a matrix.
    printf("Type the name of the image you want to apply digit recoginition: ");
    scanf("%s", nume_imagine_2);
    BMP_to_matrix(nume_imagine_2,&H,&W,&imagine);
    struct detectie **matrice=(struct detectie**)malloc(10*sizeof(struct detectie*));
    if(matrice==NULL)
    {
        printf("Could not allocate memory ");
        return -1;
    }
    for(i=0;i<10;i++)
    {
        matrice[i]=(struct detectie*)malloc(H*W*sizeof(struct detectie));
        if(matrice[i]==NULL)
        {
            printf("Could not allocate memory " );
            return -1;
        }
    }

    //We apply grayscale to the image in order to be easier to make detections.
    copieGray(&imagine, &imagineGray,H,W);
    grayscale(&imagineGray,H,W);

    //We make templatematching algorythm with every digit on the matrix
    templatematching(imagineGray,&matrice,indCorelatie,"cifra0.bmp",H,W);
    templatematching(imagineGray,&matrice,indCorelatie,"cifra1.bmp",H,W);
    templatematching(imagineGray,&matrice,indCorelatie,"cifra2.bmp",H,W);
    templatematching(imagineGray,&matrice,indCorelatie,"cifra3.bmp",H,W);
    templatematching(imagineGray,&matrice,indCorelatie,"cifra4.bmp",H,W);
    templatematching(imagineGray,&matrice,indCorelatie,"cifra5.bmp",H,W);
    templatematching(imagineGray,&matrice,indCorelatie,"cifra6.bmp",H,W);
    templatematching(imagineGray,&matrice,indCorelatie,"cifra7.bmp",H,W);
    templatematching(imagineGray,&matrice,indCorelatie,"cifra8.bmp",H,W);
    templatematching(imagineGray,&matrice,indCorelatie,"cifra9.bmp",H,W);

    //We choose only those detection who have a bigger score
    lungime=vector_detectii(&matrice,&A,indCorelatie);

    struct detectie *B=(struct detectie *)calloc(lungime,sizeof(struct detectie));
    if(B==NULL)
    {
        printf("Could not allocate memory ");
        return -1;
    }
    eliminareDetectie(lungime,A,&B);
    //Color the digits from the initial image
    Color(&imagine,lungime,&B);

    //Export the new image
    printf("Type the name of the new image: ");
    scanf("%s", nume_imagine_finala);
    afisare_matrice(nume_imagine_finala,nume_imagine_2,&imagine,H,W);

    //Free the alocated memory.
    free(nume_imagine);
    free(nume_imagine_2);
    free(nume_imagine_criptata);
    free(nume_imagine_decriptata);
    free(nume_imagine_finala);
    free(secret_key);
    free(A);
    free(B);

    return 0;
}
