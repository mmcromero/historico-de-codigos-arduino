// zoomkat 8-6-10 serial I/O string test
// type a string in serial monitor. then send or enter
// for IDE 0019 and later

String readString;

void setup() {
  Serial.begin(9600);
  //Serial.println("serial test 0021"); // so I can keep track of what is loaded
}

void loop() {

  while (Serial.available()) {
    delay(10);  
    if (Serial.available() >0) {
      char c = Serial.read();
      readString += c;
    }
  }
        
  if (readString.length() >0) { 
        if(readString == "oi"){Serial.println("Ola");}
        if(readString == "tudo bem" || readString == "tudo bem?" || readString == "tudo bem ?"){Serial.println("Tudo e vc ?");}
        
        /*
        if(readString == "1"){luzHall();}
        if(readString == "2"){luzJantar();}
        if(readString == "3"){luzSala();}
        if(readString == "4"){luzMesaSala();}
        if(readString == "5"){luzQuartinho();}
        if(readString == "6"){luzCozinha();}
        if(readString == "7"){luzArea();}
        if(readString == "8"){luzCorredor1();}
        if(readString == "9"){luzCorredor2();}
        if(readString == "10"){luzQuartoArthur1();}
        if(readString == "11"){luzQuartoArthur2();}
        if(readString == "12"){luzQuartoSuite1();}
        if(readString == "13"){luzQuartoSuite2();}
        if(readString == "14"){luzBanheiroSocial1();}
        if(readString == "15"){luzBanheiroSocial2();}
        if(readString == "16"){luzBanheiroSuite1();}
        if(readString == "17"){luzBanheiroSuite2();}
        */
        
        //Serial.println(readString);
        readString="";
  }
}
