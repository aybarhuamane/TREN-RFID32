/*---------------------------------------------------------
  Programa : WATCHDOG TIMER - ESP32
  Autor    : Fellipe Couto [ http://www.efeitonerd.com.br ]
  Data     : 24/08/2019
  ---------------------------------------------------------*/
#include <Arduino.h>
#include <esp_task_wdt.h> //Biblioteca do watchdog
#define BUTTON 2          //Porta de conexão do botão

void setup() {
  //Configura a porta com pull-up interno
  pinMode(BUTTON, INPUT_PULLUP);

  //Inicia a comunicação serial e exibe a mensagem
  Serial.begin(115200);
  Serial.println("WATCHDOG TIMER - ESP32");
  Serial.println("Mantenha o botao pressionado por mais de 4 segundos para o reiniciar o circuito.\n");

  //Habilita o watchdog configurando o timeout para 4 segundos
  esp_task_wdt_init(5, true);
  esp_task_wdt_add(NULL);
}

void loop() {
  //Variável para contagem de tempo
  int count = 1;
  //Serial.println(touchRead(2));
  //Fica preso no loop enquanto o botão estiver pressionado
  while ((touchRead(2)) < 8) {
    Serial.println(touchRead(2));
    Serial.print("Botao pressionado... ");
    Serial.println(count);
    count++;
    delay(1000);
  }

  //Reseta o temporizador do watchdog
  esp_task_wdt_reset();
}