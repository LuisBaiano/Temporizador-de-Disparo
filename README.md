# Temporizador-de-Disparo

## Índice

1. Objetivos
2. Descrição
3. Funcionalidades
4. Requisitos do Projeto
5. Como Executar o Programa
6. Estrutura do Código
7. Referências
8. Demonstrativo em Vídeo

---

## 1. Objetivos

O projeto tem como objetivo a implementação de um sistema de controle de LEDs utilizando um botão na Raspberry Pi Pico (RP2040). O sistema implementa um debounce via software e uma sequência de transição de LEDs, garantindo um comportamento controlado após o acionamento do botão.

## 2. Descrição

Este projeto utiliza a placa Raspberry Pi Pico para controlar um conjunto de LEDs RGB através de um botão. A cada acionamento, uma sequência de estados é iniciada, desligando os LEDs um a um com um intervalo de 3 segundos. O código emprega interrupções para detecção do botão e timers para controle de tempo.

## 3. Funcionalidades

* Interrupção para detecção de acionamento do botão.
* Implementação de debounce via software.
* Controle de LEDs com transição temporizada.
* Uso de timers para gerenciamento das mudanças de estado.

## 4. Requisitos do Projeto

* Placa Raspberry Pi Pico (RP2040)
* Ambiente de desenvolvimento configurado (SDK do RP2040, compilador C/C++)
* LEDs RGB conectados aos pinos 11, 12 e 13
* Botão conectado ao pino 5

## 5. Estrutura do Código

### 1. Configuração do Ambiente

* Instale o SDK do Raspberry Pi Pico seguindo a documentação oficial.
* Configure a ferramenta de build `CMake` e o compilador ARM.

### 2. Compilação do Código

* Clone o repositório ou copie o código para um diretório local.
* No terminal, navegue até o diretório do projeto e execute:
  ```sh
  mkdir build && cd build
  cmake ..
  make
  ```

### 3. Upload para a Raspberry Pi Pico W

* Conecte a Raspberry Pi Pico ao computador enquanto segura o botão `BOOTSEL`.
* Copie o arquivo `.uf2` gerado para a unidade que aparecerá no sistema.
* A Pico será reiniciada automaticamente e executará o código.

* **Definição de pinos** : Configuração dos GPIOs para LEDs e botão.
* **Callback do alarme** : Função que controla a sequência de LEDs.
* **Interrupção do botão** : Implementa debounce e inicia a sequência.
* **Main** : Inicializa os periféricos e configura as interrupções.

## 6. Referências

* [Documentação da Raspberry Pi Pico](https://www.raspberrypi.com/documentation/microcontrollers/)
* [RP2040 Datasheet](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)

## 7. Demonstrativo em Vídeo

[Link para o vídeo demonstrativo](#) *(substituir pelo link do YouTube)*
