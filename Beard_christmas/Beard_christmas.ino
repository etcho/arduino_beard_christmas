int gate_pin = 1;
int button_pin = 0;
int sinal_gate = 0;
boolean subindo = true;
boolean ligado = true;
int modo = 0;
int tempo = 0;
int tempo_botao = 0;

void setup() {
  pinMode(gate_pin, OUTPUT);
  pinMode(button_pin, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(button_pin) == LOW){
    if (tempo_botao == 0){
      modo++;
      if (modo > 3){
        modo = 0;
      }
    }
    tempo_botao++;
  } else {
    tempo_botao = 0;
  }
  
  if (modo == 0 || modo == 1){
    while (sinal_gate < 0 || sinal_gate > 1023){
      continue;
    }
    if (subindo){
      sinal_gate++;
    } else {
      sinal_gate--;
    }
    if (sinal_gate == 0){
      sinal_gate = 1;
      subindo = true;
    }
    if (sinal_gate == 255){
      sinal_gate = 254;
      subindo = false;
    }
    analogWrite(gate_pin, sinal_gate);
    delay(modo == 0 ? 8 : 4);
  } else if (modo == 2){
    if (ligado){
      if (tempo > 1000){
        ligado = false;
        analogWrite(gate_pin, 0);
        tempo = 0;
      } else {
        tempo++;
      }
    } else {
      if (tempo > 2000){
        ligado = true;
        analogWrite(gate_pin, 254);
        tempo = 0;
      } else {
        tempo++;
      }
    }
    delay(1);
  } else if (modo == 3){
    analogWrite(gate_pin, 254);
    delay(1);
  }
}
