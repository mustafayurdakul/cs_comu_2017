#include <stdio.h>
#include <stdlib.h>

struct hucre {
        int icerik;
        struct hucre *sonraki;
};

struct hucre* hucre_olustur(int icerik){
        struct hucre *a;
        a=(struct hucre*)malloc(sizeof(struct hucre));
        if(a==NULL) {
                printf("Heap alaninda yer ayrilamadi ...\n");
                exit(1);
        }
        a->icerik=icerik;
        a->sonraki=NULL;
        return a;
}

void liste_basina_ekle(int icerik,struct hucre **liste_basi){
        struct hucre* a=hucre_olustur(icerik);
        a->sonraki=*liste_basi;
        *liste_basi=a;
}

void liste_sonuna_ekle(int icerik,struct hucre **liste_basi){
        struct hucre* a=hucre_olustur(icerik);
        if(*liste_basi==NULL) {
                a->sonraki=*liste_basi;
                *liste_basi=a;
        }
        else {
                struct hucre *x=*liste_basi;
                while(x->sonraki!=NULL) {
                        x=x->sonraki;
                }
                x->sonraki=a;
        }
}

void liste_yaz(struct hucre *liste_basi){
        while(liste_basi!=NULL) {
                printf("%4d ",liste_basi->icerik);
                liste_basi=liste_basi->sonraki;
        }
        printf("\n");
}

void liste_yaz_recursive(struct hucre *liste_basi){
        if(liste_basi!=NULL) {
                printf("%4d ",liste_basi->icerik);
                liste_yaz_recursive(liste_basi->sonraki);
        }
        else{
                printf("\n");
        }
}
void tersten_liste_yaz_recursive(struct hucre *liste_basi){

        if(liste_basi!=NULL) {
                tersten_liste_yaz_recursive(liste_basi->sonraki);
                printf("%4d ",liste_basi->icerik);
        }

}
void liste_yok_et(struct hucre **liste_basi){
        struct hucre *simdiki;
        while(*liste_basi!=NULL) {
                //  simdiki=(*liste_basi);
                //  *liste_basi=(*liste_basi)->sonraki;
                //  free(simdiki);
                free(*liste_basi);
                *liste_basi=(*liste_basi)->sonraki;
        }
}

void liste_sirali_ekle(int icerik, struct hucre **liste_basi){
        struct hucre *a, *b, *eklenen;
        b=*liste_basi;
        while(b!=NULL && b->icerik <= icerik) {
                if(b->icerik==icerik) return;
                a = b;
                b= b->sonraki;
        }
        eklenen=hucre_olustur(icerik);
        if(b==*liste_basi) {
                eklenen->sonraki=*liste_basi;
                *liste_basi=eklenen;
        }
        else {
                a->sonraki=eklenen;
                eklenen->sonraki=b;

        }
}

void liste_eleman_sil(int silinen, struct hucre **liste_basi){
        struct hucre *temp=*liste_basi;
        struct hucre *once;

        while(temp!=NULL && temp->icerik!=silinen) {
                once = temp;
                temp=temp->sonraki;
        }
        if(temp==NULL) return;
        else {
                if(temp==*liste_basi) *liste_basi=(*liste_basi)->sonraki;
                else once->sonraki=temp->sonraki;
                free(temp);
        }

}
void liste_sirala(struct hucre **liste_basi){
        struct hucre *a,*b,*c,*d;

        if(*liste_basi == NULL || (*liste_basi)->sonraki==NULL) return;

        d=(*liste_basi)->sonraki;
        (*liste_basi)->sonraki=NULL;

        while(d!=NULL) {
                c=d;
                d=d->sonraki;
                b=*liste_basi;
                while(b!=NULL && b->icerik < c->icerik) {
                        a=b;
                        b=b->sonraki;
                }
                if(b==*liste_basi) {
                        c->sonraki=*liste_basi;
                        *liste_basi=c;
                }
                else {
                        a->sonraki = c;
                        c->sonraki = b;
                }
        }
}

void liste_ters_cevir(struct hucre **liste_basi){

        struct hucre *a,*b;

        a=NULL;
        while(*liste_basi!=NULL) {
                b=*liste_basi;
                *liste_basi=(*liste_basi)->sonraki;
                b->sonraki=a;
                a=b;
        }
        *liste_basi=a;
}





int main(int argc, char** argv) {

        struct hucre *liste1=NULL;

        liste_basina_ekle(20,&liste1);
        liste_basina_ekle(30,&liste1);
        liste_basina_ekle(200,&liste1);
        liste_basina_ekle(40,&liste1);
        liste_basina_ekle(80,&liste1);
        liste_yaz(liste1);


        printf("\n");

        liste_ters_cevir(&liste1);
        liste_yaz(liste1);
        printf("\n");

        tersten_liste_yaz_recursive(liste1);
        printf("\n");




        return (EXIT_SUCCESS);
}
