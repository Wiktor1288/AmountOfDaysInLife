int Thisdate[3]={8,2,2021}, date[8], ver1=48, number, day, month, year, AmountOfdaysInLife=0;
uint16_t j=0, AmountOfdaysInMonth[12]={31,28,31,30,31,30,31,31,30,31,30,31}, AmountOfdaysInYear=365;
String txt1="Zyjesz juz tyle dni: ", txt2="Jeszcze nie masz 18 lat musisz poczekac tyle dni:", pom1;
char buffor[10];
bool message=false;
void setup() {
  Serial.begin(9600);
  Serial.println("Witaj Sprawdzam czy jestes pelnoletni");
}

void loop() {
  message=false;
  Serial.println("Prosze podaj date urodzenia w formacie dd.mm.yyyy");
  while(!message){
    if(Serial.available() > 0) {
      number=Serial.readBytesUntil('\n',buffor,10);
      Serial.println("podana data");
      j=0;
      for(uint8_t i=0; i<8; i++){
        
        if(j==2 || j==5){
          j++;
          Serial.print('.');
        }
        date[i]=(int)buffor[j]-48;
        Serial.print(date[i]);
        j++;
        
        
      }
      Serial.print('\n');
      message=true;
    }
     delay(1000);
  }
  day=date[0]*10+date[1];
  month=date[2]*10+date[3];
  year=date[4]*1000+date[5]*100+date[6]*10+date[7];
  if( year < Thisdate[2]){                                                         
    AmountOfdaysInLife=AmountOfdaysInMonth[month-1]-day;

    for(uint8_t i=month; i < 12; i++){
      AmountOfdaysInLife+=AmountOfdaysInMonth[month];
    }

    AmountOfdaysInLife+=AmountOfdaysInYear*(Thisdate[2]-year-1)+39;
  
  }
  else if( year==Thisdate[2] && month < Thisdate[1]){
    AmountOfdaysInLife=AmountOfdaysInMonth[month-1]-day+Thisdate[0];
  }
  else if(year==Thisdate[2] && month == Thisdate[1] && day <= Thisdate[0]){
    AmountOfdaysInLife=Thisdate[0]-day;
  }
  else{
    Serial.print("Oszukujesz!");
    Serial.print('\n');
  }


  if(AmountOfdaysInLife >= 18*AmountOfdaysInYear){
    pom1=String(AmountOfdaysInLife,DEC);
    Serial.print("Jestes juz pelnoletni.");
    Serial.print('\n');
    Serial.println(txt1 + pom1);
  }
  if(AmountOfdaysInLife < 18*AmountOfdaysInYear){
  number=18*AmountOfdaysInYear-AmountOfdaysInLife;
  Serial.println(txt2);
  pom1=String(number,DEC);
  Serial.println(pom1);
  }
  


  
}
