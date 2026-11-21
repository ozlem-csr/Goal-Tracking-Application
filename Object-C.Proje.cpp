//Hedef ve istek Listesi Otomasyonu:
//Kullanicinin hedeflerini veya yapmak istediklerini kaydedip duzenleyebilecegi bir takip sistemi. 

//hedefi yazip ekleyince durumu devam yani 0 oluyor. hedefi tamamlamak icin metin kutusuna hedefin ID numarasini yazip butona tiklayin, 
//boylece dosyada da durumu 1 oluyor.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<graphics.h>
#include<dos.h>
#include<conio.h>
#include<windows.h>

struct Hedef {       
    int id;
    char baslik[60];
    char kategori[40]; 
    int durum;  
};

class HedefListesi {
public:
    struct Hedef hedefler[200];
    int hedefSayisi;

    HedefListesi() {
        hedefSayisi = 0;   
    }

  void dosyadanOku(){       
	FILE *d;
	d=fopen("hedefler.txt","r");
	if(d==NULL)
	{
		printf("Dosya bulunamadi.\n");
		return;
	}
	
	hedefSayisi = 0;
	
	while(fscanf(d,"%d %s %s %d\n",&hedefler[hedefSayisi].id,
	      hedefler[hedefSayisi].baslik,
		  hedefler[hedefSayisi].kategori,
		  &hedefler[hedefSayisi].durum) != EOF) {
		  	
	    hedefSayisi++;	  	
	}
	
	fclose(d);
  }
  
  void dosyayaYaz(){     
  	FILE *d;
  	d=fopen("hedefler.txt","w");
  	
  	if(d == NULL){
  		printf("Dosya bulunamadi.\n");
  		return;
	}
	
	for(int i=0; i<hedefSayisi; i++){
		fprintf(d, "%d %s %s %d\n", hedefler[i].id, 
                hedefler[i].baslik, 
                hedefler[i].kategori, 
                hedefler[i].durum);
	}
	fclose(d);
  }
  
  void hedefEkle(){
  	if(hedefSayisi >= 200){
  		printf("Kapasite dolu, yeni hedef ekleyemezsiniz!");
  		return;
	}
	
	hedefler[hedefSayisi].id = hedefSayisi + 1;  
	
	printf("Yeni hedefin adini giriniz: ");
    scanf("%s", hedefler[hedefSayisi].baslik);
    
    printf("Kategoriyi giriniz: ");
    scanf("%s", hedefler[hedefSayisi].kategori);
    
    hedefler[hedefSayisi].durum = 0;  
    
    hedefSayisi = hedefSayisi + 1;  
    
    printf("Tebrikler! Hedef basariyla eklendi.\n");
    dosyayaYaz();
   }
   
   void hedefleriListele(){
   	 if (hedefSayisi == 0){
   	 	printf("Kayitli hedef bulunamadi!\n");
   	 	return;
	 }
	 
   	 for(int i=0; i<hedefSayisi; i++){
   	 	if(hedefler[i].durum == 0){
   	 	   printf("ID: %d, Baslik: %s, Kategori: %s, Durum: %d Devam ediyor\n",
			      hedefler[i].id, hedefler[i].baslik, hedefler[i].kategori, hedefler[i].durum);
		}
		
		else if(hedefler[i].durum == 1){
   	 	   printf("ID: %d, Baslik: %s, Kategori: %s, Durum: %d Tamamlandi\n",
			      hedefler[i].id, hedefler[i].baslik, hedefler[i].kategori, hedefler[i].durum);
		}
     }
    }
    
    void hedefTamamla(){    //guncelle
    
    	if (hedefSayisi == 0){
   	 	printf("Kayitli hedef bulunamadi!\n");
   	 	return;
	    }
	    
		hedefleriListele();
		
		int secilenID;
		printf("Tamamladiginiz hedefin ID'sini girin:\n");
		scanf("%d",&secilenID);
		
		for(int i=0; i<hedefSayisi; i++)
    	{
    		if(hedefler[i].id == secilenID){
    			hedefler[i].durum=1;
    			printf("Hedef tamamlandi!\n");
			}
		}
		
		dosyayaYaz();
	}
};




void listeCiz(HedefListesi liste){
    int i;
    char satir[100]; 
    
    setcolor(YELLOW);
    rectangle(40, 60, 220, 350); 
    setcolor(WHITE);
    outtextxy(70, 40, "HEDEFLER");
    
    for(i = 0;i<liste.hedefSayisi;i++){
        if(liste.hedefler[i].durum==0){
            sprintf(satir, "%d. %s [Devam]", liste.hedefler[i].id, liste.hedefler[i].baslik);
        } else{
            sprintf(satir, "%d. %s [Bitti]", liste.hedefler[i].id, liste.hedefler[i].baslik);
        }
        outtextxy(50, 75+(i*20), satir);
    }
}

void metinKutusu(char *yazi){
    setcolor(BLUE);
    rectangle(250, 100, 450, 140); 
    setfillstyle(SOLID_FILL, BLACK);
    floodfill(251, 101, BLUE);
    setcolor(WHITE);
    outtextxy(260, 115, yazi);
}

void ekleButon(){
    setcolor(RED);
    rectangle(250, 170, 450, 220);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    floodfill(251, 171, RED);
    setcolor(WHITE);
    outtextxy(310, 188, "Ekle");
}

void tamamlaButon(){
    setcolor(GREEN);
    rectangle(250, 250, 450, 300);
    setfillstyle(SOLID_FILL, LIGHTGREEN);
    floodfill(251, 251, GREEN);
    setcolor(BLACK);
    setbkcolor(LIGHTGREEN);
    outtextxy(300, 268, "Tamamla");
    setbkcolor(BLACK);
}

void ciz(HedefListesi liste, char *yazi){
    cleardevice();
    listeCiz(liste);
    metinKutusu(yazi);
    ekleButon();
    tamamlaButon();
}



int main() {
    HedefListesi liste;
    liste.dosyadanOku(); 
    
    int gd=DETECT,gm;
    int x,y; 
    char yazi[30]=""; 
    char ch;
    
    initgraph(&gd,&gm,""); 
    ciz(liste, yazi); 
    
    while(1){
        if(kbhit()){
            ch = getch();
            if(ch == 27){ 
                break;
            }
            if(ch == 8 && strlen(yazi) > 0){ 
                yazi[strlen(yazi)-1]='\0';
            }
            else if(ch != 8 && ch != 13 && strlen(yazi) < 29){ 
                yazi[strlen(yazi)+1]='\0';
                yazi[strlen(yazi)]=ch;
            }
            ciz(liste,yazi); 
        }
        
        if(ismouseclick(WM_LBUTTONDOWN)){
            getmouseclick(WM_LBUTTONDOWN,x,y);
            
            if(x >= 250 && x <= 450 && y >= 170 && y <= 220){
                if(strlen(yazi) > 0 && liste.hedefSayisi<200){
                    
                    Beep(800,100); 
                    
                    liste.hedefler[liste.hedefSayisi].id=liste.hedefSayisi+1;
                    strcpy(liste.hedefler[liste.hedefSayisi].baslik,yazi); 
                    strcpy(liste.hedefler[liste.hedefSayisi].kategori,"Genel"); 
                    liste.hedefler[liste.hedefSayisi].durum=0; 
                    
                    liste.hedefSayisi++;
                    liste.dosyayaYaz(); 
                    
                    yazi[0]='\0'; 
                    ciz(liste, yazi); 
                    delay(300); 
                }
            }
            
            if(x >= 250 && x <= 450 && y >= 250 && y <= 300){
                if(strlen(yazi)>0){ 
                    
                    Beep(800,100); 
                    int girilenID=atoi(yazi); 
                    
                    for(int i = 0; i < liste.hedefSayisi; i++){
                        if(liste.hedefler[i].id==girilenID){
                            liste.hedefler[i].durum=1;
                        }
                    }
                    liste.dosyayaYaz(); 
                    
                    yazi[0]='\0'; 
                    ciz(liste,yazi); 
                    delay(300);
                }
            }
        }
        delay(10); 
    }
    closegraph(); 
    return 0;
}

