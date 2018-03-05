int NEGATIVOIRSALA = 5; //D1
int NEGATIVOIRESCADA = 4 ; //D2
int NEGATIVOIRCRIANCAS = 2; //D4
int NEGATIVOIRMEIO = 14; //D5
int NEGATIVOIRPRINCIPAL = 13; //D7

//Sala --> S
//Escada --> E
//Crianças --> K
//Escritorio --> M
//Casal --> C
//Externas -->  F

//generico
void sendIr(String strRepeticao, String strLocal, String strValue)
{   
  int intRepeticao = strRepeticao.toInt();
  
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, HIGH); }
  if(strLocal != "E"){digitalWrite(NEGATIVOIRESCADA, HIGH); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCRIANCAS, HIGH); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMEIO, HIGH); }
  if(strLocal != "P"){digitalWrite(NEGATIVOIRPRINCIPAL, HIGH); }
    
    for (int i = 0; i < intRepeticao; i++) {
      unsigned long code = strValue.toInt() ;
      irsend.sendNEC(code, 32);
      delay(40);
    }
    
  if(strLocal != "S"){digitalWrite(NEGATIVOIRSALA, LOW); }
  if(strLocal != "E"){digitalWrite(NEGATIVOIRESCADA, LOW); }
  if(strLocal != "C"){digitalWrite(NEGATIVOIRCRIANCAS, LOW); }
  if(strLocal != "M"){digitalWrite(NEGATIVOIRMEIO, LOW); } 
  if(strLocal != "P"){digitalWrite(NEGATIVOIRPRINCIPAL, LOW); } 

  
  

  Serial.print("ir generico: ");
  Serial.println(strValue);
  Serial.print("Local: ");
  Serial.println(strLocal);
  Serial.print("Repeticao: ");
  Serial.println(intRepeticao);
  
  irrecv.enableIRIn(); // Re-enable receiver
}




