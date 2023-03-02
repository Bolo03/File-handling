#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct angajat
{
    char nume[20];
    int varsta;
    struct firma
    {
        char nume_frm[20];
        int nr_ang;
        char loc[20];
    }FRM;
}ANGJ;

void reactualizare_evid(FILE *f, ANGJ **a, int *n)
{
    if((f = fopen("evidenta.dat", "rb")) == NULL)
    {
        printf("Teapa!");
        exit(1);
    }
    fread(n, sizeof(int), 1, f);

    *a = (ANGJ*)malloc((*n) * sizeof(ANGJ));

    fread(*a, sizeof(ANGJ), *n, f);
    fclose(f);
}

void creare_evidenta(FILE *f, ANGJ **a, int *n)
{
    printf("Cati angajati doriti sa introduceti: ");
    scanf("%d", n);
    getchar();

    *a = (ANGJ*)malloc((*n) * sizeof(ANGJ));
    if(a == NULL)
    {
        printf("Teapa!");
        exit(1);
    }

    for(int i = 0; i < *n; i++)
    {
        printf("Dati numele angajatului %d: ", i+1);
        gets((*a+i)->nume);
        printf("Dati varsta angajatului: ");
        scanf("%d", &(*a+i)->varsta);
        getchar();
        printf("Dati numele firmei: ");
        gets((*a+i)->FRM.nume_frm);
        printf("Dati numarul de angajati ai firmei: ");
        scanf("%d", &(*a+i)->FRM.nr_ang);
        getchar();
        printf("Dati localitatea firmei: ");
        gets((*a+i)->FRM.loc);
        printf("\n");

    }

    if((f = fopen("evidenta.dat", "wb")) == NULL)
    {
        printf("Teapa!");
        exit(1);
    }
    fwrite(n, sizeof(int), 1, f);
    fwrite(*a, sizeof(ANGJ), *n, f);

    printf("fisierul evidenta a fost creat!\n");

    fclose(f);
}

void adauga_pers(FILE *f, ANGJ **a, int *n)
{
    int m;
    printf("Cati angajati doriti sa adaugati: ");
    scanf("%d", &m);
    getchar();

    *a = (ANGJ*)realloc(*a, (*n + m) * sizeof(ANGJ));

    for(int i = *n; i < *n + m; i++)
    {
        printf("Dati numele angajatului %d: ", i+1);
        gets((*a+i)->nume);
        printf("Dati varsta angajatului: ");
        scanf("%d", &(*a+i)->varsta);
        getchar();
        printf("Dati numele firmei: ");
        gets((*a+i)->FRM.nume_frm);
        printf("Dati numarul de angajati ai firmei: ");
        scanf("%d", &(*a+i)->FRM.nr_ang);
        getchar();
        printf("Dati localitatea firmei: ");
        gets((*a+i)->FRM.loc);
        printf("\n");
    }

    *n += m;

    if((f = fopen("evidenta.dat", "wb")) == NULL)
    {
        printf("Teapa!");
        exit(1);
    }
    fwrite(n, sizeof(int), 1, f);
    fwrite(*a, sizeof(ANGJ), *n, f);

    printf("fisierul evidenta a fost actualizat!\n");

    fclose(f);
}


void creare_fis_loc(FILE *g, ANGJ *a, int n)
{
    for(int i = 0; i < n; i++)
    {
        char filename[25];
        strcpy(filename, a[i].FRM.loc);
        strcat(filename, ".txt");

        if((g = fopen(filename, "wt")) == NULL)
        {
            printf("Teapa!");
            exit(1);
        }
        for(int j = 0; j < n; j++)
        {
            if(strcmp(a[i].FRM.loc, a[j].FRM.loc) == 0)
            {
                fprintf(g, "%s, %s\n", a[j].nume, a[j].FRM.nume_frm);
            }
        }
        fclose(g);

        printf("Fisierele au fost create\n");
    }
}

void ord_frm(FILE *h, ANGJ *a, int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(strcmp(a[i].FRM.nume_frm, a[j].FRM.nume_frm) == 0)
            {
                for(int k = j; k < n; k++)
                {
                    strcpy(a[k].nume, a[k+1].nume);
                    a[k].varsta = a[k+1].varsta;
                    strcpy(a[k].FRM.nume_frm, a[k+1].FRM.nume_frm);
                    a[k].FRM.nr_ang = a[k+1].FRM.nr_ang;
                    strcpy(a[k].FRM.loc, a[k+1].FRM.loc);
                }
                n--;
            }
        }
    }

    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(a[j].FRM.nr_ang > a[j + 1].FRM.nr_ang)
            {
                int auxi;
                char auxc[25];
                strcpy(auxc, a[j].FRM.nume_frm);
                strcpy(a[j].FRM.nume_frm, a[j+1].FRM.nume_frm);
                strcpy(a[j+1].FRM.nume_frm, auxc);

                strcpy(auxc, a[j].FRM.loc);
                strcpy(a[j].FRM.loc, a[j+1].FRM.loc);
                strcpy(a[j+1].FRM.loc, auxc);

                auxi = a[j].FRM.nr_ang;
                a[j].FRM.nr_ang = a[j+1].FRM.nr_ang;
                a[j+1].FRM.nr_ang = auxi;
            }
        }
    }

    if((h = fopen("ordonate.txt", "wt")) == NULL)
    {
        printf("Teapa!");
        exit(1);
    }

    for(int i = 0; i < n; i++)
    {
        fprintf(h, "%s, %d, %s\n", a[i].FRM.nume_frm, a[i].FRM.nr_ang, a[i].FRM.loc);
    }
    fclose(h);

    printf("Fisierul ordonate.txt a fost creat\n");
}

void identf_frm(ANGJ *a, int n)
{
    int max = 0;

    for(int i = 0; i < n; i++)
    {
        if(max < a[i].FRM.nr_ang)
        {
            max = a[i].FRM.nr_ang;
        }
    }
    printf("Firmele cu cel mai mare numar de angajati sunt:\n");
    for(int i = 0; i < n; i++)
    {
        if(a[i].FRM.nr_ang == max)
        {
            printf("%s\n", a[i].FRM.nume_frm);
        }
    }
}

void varsta_mica(FILE *l, ANGJ *a, int n)
{
    float media;
    for(int i = 0; i < n; i++)
    {
        media += a[i].varsta;
    }
    media /= n;


     if((l = fopen("varsta.txt", "wt")) == NULL)
    {
        printf("Teapa!");
        exit(1);
    }

    for(int i = 0; i < n; i++)
    {
        if(a[i].varsta < media)
        {
            fprintf(l, "%s, %d, %s, %d, %s\n", a[i].nume, a[i].varsta, a[i].FRM.nume_frm, a[i].FRM.nr_ang, a[i].FRM.loc);
        }
    }
    fclose(l);

    printf("Fisierul varsta.txt a fost creat\n");



}
int main()
{
    FILE *f, *g, *h, *l;
    ANGJ *a;
    int n, opt;
    char c = 'D';

    while(c == 'D')
    {
        printf("Ce operatiune doriti sa efectuati?\n");
        printf("1 - Crearea fisierului cu evidenta angajatilor\n");
        printf("2 - Adaugarea in fisier a unor angajati noi\n");
        printf("3 - Gasirea angajatilor care lucreaza la firme aflate in aceeasi localitate\n");
        printf("4 - Ordonarea crescatoare a firmelor in functie de numarul de angajati\n");
        printf("5 - Identificarea angajatilor care au varsta mai mica decat media de varsta a tuturor angajatilor\n");
        printf("6 - Identificarea firmei/firmelor cu cel mai mare numar de angajati\n");
        scanf("%d", &opt);
        getchar();

        switch(opt)
        {
            case 1: creare_evidenta(f, &a, &n);
                    break;
            case 2: reactualizare_evid(f, &a, &n);
                    adauga_pers(f, &a, &n);
                    break;
            case 3: reactualizare_evid(f, &a, &n);
                    creare_fis_loc(g, a, n);
                    break;
            case 4: reactualizare_evid(f, &a, &n);
                    ord_frm(h, a, n);
                    break;
            case 5: reactualizare_evid(f, &a, &n);
                    varsta_mica(l, a, n);
                    break;
            case 6: reactualizare_evid(f, &a, &n);
                    identf_frm(a, n);
                    break;
        }

        printf("\nDoriti sa efectuati alta operatiune (D/N): ");
        scanf("%c", &c);
        getchar();
    }
    return 0;
}
