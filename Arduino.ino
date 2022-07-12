#include <SoftwareSerial.h>

SoftwareSerial esp(2, 3);

int nilai=0, hasilmax=0, hasilmin=0, hasil;
float arus=0.0, tegangan=0.0;
float daya=0.0;
bool ganti=true;
long sekarang=0, sebelum=0;
String kirim="";

void cekArus(){
  nilai=analogRead(A1);
  hasilmax=nilai;
  hasilmin=nilai;
  for(int i = 0; i<1000; i++){
    nilai=analogRead(A1);
    if(nilai>hasilmax){
      hasilmax=nilai;
    }
    if(nilai<hasilmin){
      hasilmin=nilai;
    }
  }
  hasil = hasilmax-hasilmin;
  arus = 0.006706*hasil - 0.06847;
  arus=abs(arus);
  hasilmax=0;
  hasilmin=0;
}

void cekTegangan(){
  nilai=analogRead(A2);
  hasilmax=nilai;
  hasilmin=nilai;
  for(int i = 0; i<1000; i++){
    nilai=analogRead(A2);
    if(nilai>hasilmax){
      hasilmax=nilai;
    }
    if(nilai<hasilmin){
      hasilmin=nilai;
    }
  }
  hasil = hasilmax-hasilmin;
  tegangan = 0.4213*hasil - 0.8427;
  tegangan=abs(tegangan);
  hasilmax=0;
  hasilmin=0;
}

void setup(){
  Serial.begin(115200);
  esp.begin(115200);
}

void loop(){
  sekarang=millis();
  if(sekarang-sebelum>=5000){
    sebelum= sekarang;
    cekArus();
    cekTegangan();
    daya=arus*tegangan;
    kirim="Arus : "+String(arus)+"; Tegangan : "+String(tegangan)+"; Daya : "+String(daya);
    Serial.println(kirim);
    esp.println(kirim);
    ganti=!ganti;
    kirim="";
  }
}
