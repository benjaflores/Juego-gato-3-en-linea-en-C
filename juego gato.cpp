/*
    Universidad de La Frontera
    Ingenieria Civil Electronica

    ICC-202 PROGRAMACION DE COMPUTADORES

    Autor: Benjamin Flores Lopez (b.flores02@ufromail.cl)

    Fecha: 11 de enero de 2019

    Descripcion general del programa: programa que permite jugar el popular juego "gato" (o "3 en linea") en 2 modalidades de juego:
    
    1.- Modo un jugador vs el sistema, donde el sistema tiene precargadas varias jugadas y el movimiento más apto para cada jugada del jugador.
    2.- Modo de 2 jugadores, donde 2 jugadores deben ingresar sus jugadas por turnos intercalados.

   **Las jugadas deben ser ingresadas exclusivamente de la forma "A,B" donde A representa la coordenada de la fila (horizontal) seleccionada y B representa la coordenada de la columna (vertical) seleccionada. A y B solo aceptan valores enteros entre 1 y 3, además no se permite jugar en cuadros en los que ya se haya jugado.

*/

//SE INCLUYE LA LIBRERIA ESTANDAR DE ENTRADA/SALIDA
#include <stdio.h>

//SE DEFINE EL PROTOTIPO DE LAS FUNCIONES
void impresionTablero();
void pedirJugadaX();
void pedirJugadaO();
void comprobarGanador();
void imprimirGanadorX();
void imprimirGanadorO();
void imprimirGanadorPC();
void imprimirGanadorJugador();
void pantallaInicio();
void imprimirEmpate();
void jugarPC();

//VARIABLES GLOBALES
int modalidad = 0;     //Almacena la modalidad de juego (1 jugador o 2 jugadores)
char tableroGato[3][3] = {{'-','-','-'},{'-','-','-'},{'-','-','-'}};  //Matriz que almacena los caracteres del tablero (inicializada con guiones) 
int ganador = 0;       //Variable que permanece en 0 mientras no haya un ganador en el juego
int ganadorX = 0;      //Variable que indica que el ganador es X
int ganadorO = 0;      //Variable que indica que el ganador es O
int fila = 0;          //Variable que almacena la fila seleccionada
int columna = 0;       //Variable que almacena la columna seleccionada
int numeroJugadas = 0; //Variable que almacena el numero de jugadas ingresadas en el juego actual

//FUNCION MAIN
int main(){
//Inicializacion del juego y pantalla de bienvenida con seleccion de modalidad
pantallaInicio();

//Acciones para el modo "jugador vs PC"
if(modalidad == 1){
impresionTablero();      //Imprime el tablero inicial
while(ganador != 1){     //Acciones mientras no haya ganador
pedirJugadaX();          //Solicita la jugada a X (jugador)
comprobarGanador();      //Comprueba la existencia de algun ganador
if(ganador == 1){        //Acciones si X provoca una jugada ganadora
impresionTablero();      //Imprime el tablero actual
break;                   //Break para salir del bucle while
}
if(numeroJugadas == 9 && ganador == 0){      //Acciones cuando no hay ganador y no quedan jugadas disponibles
impresionTablero();      //Imprime el tablero actual
imprimirEmpate();        //Imprime mensaje avisando al jugador del empate
break;                   //Break para salir del bucle while
}
jugarPC();               //Sistema hace su jugada
impresionTablero();      //Imprime el tablero actual
comprobarGanador();      //Comprueba la existencia de algun ganador
if(ganador == 1){        //Acciones si el sistema hace una jugada ganadora
break;                   //Break para salir del bucle while
}
}
if(ganador == 1){        //Acciones si existe un ganador
if(ganadorX == 1){       //Acciones si el ganador es el jugador
imprimirGanadorJugador();//Imprime mensaje notificando al jugador de su victoria
}
if(ganadorO == 1){       //Acciones si el ganador es el sistema
imprimirGanadorPC();     //Imprime mensaje notificando al jugador de la victoria del sistema
}
}
}
//Acciones para el modo "multijugador"
if(modalidad == 2){
impresionTablero();      //Imprime el tablero inicial
while(ganador != 1){     //Acciones mientras no haya ganador
pedirJugadaX();          //Solicita la jugada a jugador X
impresionTablero();      //Imprime el tablero actual
comprobarGanador();      //Comprueba la existencia de algun ganador
if(ganador == 1){        //Acciones si X provoca una jugada ganadora
break;                   //Break para salir del bucle while
}
if(numeroJugadas == 9 && ganador == 0){
impresionTablero();      //Imprime el tablero actual
imprimirEmpate();        //Imprime mensaje avisando del empate a los jugadores
break;                   //Break para salir del bucle while
}
pedirJugadaO();          //Solicita la jugada a jugador O
impresionTablero();      //Imprime el tablero actual
comprobarGanador();      //Comprueba la existencia de algun ganador
if(ganador == 1){        //Acciones si existe un ganador
break;                   //Break para salir del bucle while
}
}
if(ganador == 1){        //Acciones si existe un ganador
if(ganadorX == 1){       //Acciones si el ganador es el jugador X
imprimirGanadorX();      //Imprime mensaje notificando al jugador X de su victoria
}
if(ganadorO == 1){       //Acciones si el ganador es el jugador O
imprimirGanadorO();      //Imprime mensaje notificando al jugador O de su victoria
}
}
}
}                        //Cierre de funcion main

//FUNCIONES
void pantallaInicio(){
printf("     #########                                                 ##           ##                             ##\n     #########                                                 ##           ##                          ########\n        ###             ####      #####      ####              ##   ####    ##         #####     #####     ##        ####\n        ###  ##    ##  ##  ##    ##   ##    #    #        #######  ##  ##   ##        ##   ##        ##    ##       #    #\n  ###   ###  ##    ##  ######   ##     ##  ##    ##      ##    ##  ######   ##       ##     ##   ######    ##      ##    ##\n   ### ###   ##    ##   ##       ##   ###   #    #       ##    ##   ##      ##        ##   ###  ##   ##    ##  ##   #    #\n     ###      ######     #####    ##### ##   ####         ##### ##   #####  ##         ##### ##  ##### ##   ####     ####\n                                        ##                                                   ##\n                                  ##   ##                                              ##   ##\n                                   #####                                                #####\n\n\n\n\n\n\n                                         ###       ###\n                                     X   ###   O   ###   X\n                                         ###       ###\n                                  ###########################\n                                  ###########################\n                                         ###       ###\n                                     O   ###   X   ###   O\n                                         ###       ###\n                                  ###########################\n                                  ###########################\n                                         ###       ###\n                                     X   ###   O   ###   X\n                                         ###       ###\n\n\n\n");
printf("Seleccione la modalidad de juego:\n\n1.- Un jugador contra el PC\n2.- Dos jugadores\n\n");
scanf("%d",&modalidad);
//Mensaje de error en seleccion
while(modalidad != 1 && modalidad !=2){
printf("\nOpcion invalida, por favor ingrese nuevamente:\n\n");
scanf("%d",&modalidad);
}
}

void impresionTablero(){
printf("\n\n\n    1   2   3\n");
printf("  _____________\n");
printf("  |   |   |   |\n");
printf("1 | %c | %c | %c |\n",tableroGato[0][0],tableroGato[0][1],tableroGato[0][2]);
printf("  |___|___|___|\n");
printf("  |   |   |   |\n");
printf("2 | %c | %c | %c |\n",tableroGato[1][0],tableroGato[1][1],tableroGato[1][2]);
printf("  |___|___|___|\n");
printf("  |   |   |   |\n");
printf("3 | %c | %c | %c |\n",tableroGato[2][0],tableroGato[2][1],tableroGato[2][2]);
printf("  |___|___|___|\n\n\n");
}

void pedirJugadaX(){
printf("TURNO DEL JUGADOR X >> Ingrese su jugada de la forma 'fila,columna'\n\n");
scanf("%d,%d",&fila,&columna);
while (tableroGato[fila-1][columna-1] != '-' || ((fila != 1 && fila != 2 && fila != 3) || (columna != 1 && columna != 2 && columna != 3))){
printf("\nJUGADA INVALIDA, INGRESE NUEVAMENTE:\n\n");
scanf("%d,%d",&fila,&columna);
}
if(tableroGato[fila-1][columna-1] == '-'){
tableroGato[fila-1][columna-1] = 'X';
numeroJugadas++;
}
}

void pedirJugadaO(){
printf("TURNO DEL JUGADOR O >> Ingrese su jugada de la forma 'fila,columna'\n\n");
scanf("%d,%d",&fila,&columna);
while (tableroGato[fila-1][columna-1] != '-' || ((fila != 1 && fila != 2 && fila != 3) || (columna != 1 && columna != 2 && columna != 3))){
printf("JUGADA INVALIDA, INGRESE NUEVAMENTE:\n");
scanf("%d,%d",&fila,&columna);
}
if(tableroGato[fila-1][columna-1] == '-'){
tableroGato[fila-1][columna-1] = 'O';
numeroJugadas++;
}
}

void comprobarGanador(){

for (int i = 0 ; i < 3 ; i++){
if(tableroGato[i][0] == tableroGato[i][1] && tableroGato[i][0] == tableroGato[i][2] && tableroGato[i][0] == 'X'){
ganadorX = 1;
ganador = 1;
}
if(tableroGato[0][i] == tableroGato[1][i] && tableroGato[0][i] == tableroGato[2][i] && tableroGato[0][i] == 'X'){
ganadorX = 1;
ganador = 1;
}
}
if(tableroGato[0][0] == tableroGato[1][1] && tableroGato[0][0] == tableroGato[2][2] && tableroGato[0][0] == 'X'){
ganadorX = 1;
ganador = 1;
}
if(tableroGato[0][2] == tableroGato[1][1] && tableroGato[0][2] == tableroGato[2][0] && tableroGato[0][2] == 'X'){
ganadorX = 1;
ganador = 1;
}
for (int j = 0 ; j < 3 ; j++){
if(tableroGato[j][0] == tableroGato[j][1] && tableroGato[j][0] == tableroGato[j][2] && tableroGato[j][0] == 'O'){
ganadorO = 1;
ganador = 1;
}
if(tableroGato[0][j] == tableroGato[1][j] && tableroGato[0][j] == tableroGato[2][j] && tableroGato[0][j] == 'O'){
ganadorO = 1;
ganador = 1;
}
}
if(tableroGato[0][0] == tableroGato[1][1] && tableroGato[0][0] == tableroGato[2][2] && tableroGato[0][0] == 'O'){
ganadorO = 1;
ganador = 1;
}
if(tableroGato[0][2] == tableroGato[1][1] && tableroGato[0][2] == tableroGato[2][0] && tableroGato[0][2] == 'O'){
ganadorO = 1;
ganador = 1;
}
}

void imprimirGanadorX(){
printf("\n\n¡¡FELICIDADES!! El jugador X ha hecho 3 en linea y es el ganador del juego\n\n");
}

void imprimirGanadorO(){
printf("\n\n¡¡FELICIDADES!! El jugador O ha hecho 3 en linea y es el ganador del juego\n\n");
}

void imprimirEmpate(){
printf("\n\nEl juego ha finalizado en un empate, no quedan jugadas disponibles\n\n");
}

void imprimirGanadorJugador(){
printf("\n\n¡¡FELICIDADES!! Has completado 3 en linea y has vencido al PC ¡eres el ganador del juego!\n\n");
}

void imprimirGanadorPC(){
printf("\n\n¡¡LO SIENTO, EL JUEGO HA TERMINADO!! El sistema ha hecho 3 en linea y es el ganador del juego. Suerte para la proxima :)\n\n");
}

void jugarPC(){

//PRIMERA JUGADA
if (tableroGato[1][1] == '-'){
tableroGato[1][1] = 'O';
numeroJugadas++;
}

if (tableroGato[1][1] == 'X' && tableroGato[0][0] == '-'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}

//SEGUNDA JUGADA
//Si X jugó en el (1,1):
if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,2):

if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,3):

if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,1):

if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,2), X tiene solo 7 opciones:

if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,3):

if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (3,1):

if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}

//Si X jugó en el (3,2):

if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (3,3), ya están considerados todos los casos en los if anteriores.

//TERCERA JUGADA

//Si X jugó en el (1,1), luego en (1,2):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,1), luego en (1,3):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,1), luego en (2,1):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,1), luego en (2,3):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,1), luego en (3,1):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,1), luego en (3,2):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,1), luego en (3,3):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,2), luego en (1,3):

if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,2), luego en (2,1):

if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,2), luego en (2,3):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,2), luego en (3,1):

if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,2), luego en (3,2):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,2), luego en (3,3):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,3), luego en (2,1):

if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,3), luego en (2,3):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'O'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'O'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'O'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'O'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,3), luego en (3,1):

if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,3), luego en (3,2):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,3), luego en (3,3):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'O' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'O' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'O' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'O' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,1), luego en (2,3):

if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,1), luego en (3,1):

if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,1), luego en (3,2):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,1), luego en (3,3):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,2), luego en (1,2):

if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'O' && tableroGato[2][2] == '-'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'O' && tableroGato[2][2] == '-'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'O' && tableroGato[2][2] == '-'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == '-'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,2), luego en (1,3):

if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,2), luego en (2,1):

if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,2), luego en (2,3):

if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,2), luego en (3,1):

if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'X' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,2), luego en (3,2):

if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,2), luego en (3,3):

if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,3), luego en (3,1):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'O'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'O'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'O'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'O'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,3), luego en (3,2):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,3), luego en (3,3):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (3,1), luego en (3,2):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (3,1), luego en (3,3):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}

//Si X jugó en el (3,2), luego en (3,3):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}

//CUARTA JUGADA SI ES QUE NO HAY GANADOR AÚN
//Si X jugó en el (1,1), luego en (1,2), luego en (3,1):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,1), luego en (1,3), luego en (3,2):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,1), luego en (2,1), luego en (1,3):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,1), luego en (2,3), luego en (3,1):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,1), luego en (3,1), luego en (2,3):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,1), luego en (3,2), luego en (1,3):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,1), luego en (3,3), luego en (1,3):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,2), luego en (1,3):

if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'O' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'O' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,2), luego en (2,1), luego en (3,3):

if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,2), luego en (2,3), luego en (3,1):

if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,2), luego en (3,1), luego en (3,3):

if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,2), luego en (3,2), luego en (2,3):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,2), luego en (3,3), luego en (3,1):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,3), luego en (2,1), luego en (3,3):

if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'O' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'O' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}


//Si X jugó en el (1,3), luego en (2,3), luego en (1,1):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'O'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'O'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,3), luego en (3,1), luego en (3,3):

if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,3), luego en (3,2), luego en (1,1):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (1,3), luego en (3,3), luego en (2,1):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'O' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'O' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,1), luego en (2,3), luego en (3,3):

if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,1), luego en (3,1), luego en (3,3):

if (tableroGato[0][0] == 'O' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'O' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,1), luego en (3,2), luego en (1,3):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,1), luego en (3,3), luego (1,3):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,2), luego en (1,2), luego en (1,3):

if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'O' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'O' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'O' && tableroGato[2][2] == '-'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,2), luego en (1,2), luego en (2,1):

if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'O' && tableroGato[2][2] == '-'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == '-'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,2), luego en (1,2), luego en (2,3):

if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'O' && tableroGato[2][2] == '-'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == '-'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,2), luego en (1,2), luego en (3,1):

if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'X' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == '-'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == '-'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,2), luego en (1,2), luego en (3,3):

if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][2] == 'O' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,2), luego en (1,3), luego en (2,1):

if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,2), luego en (2,1), luego en (1,2):

if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'O' && tableroGato[2][2] == '-'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == '-'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,2), luego en (2,1), luego en (1,3):

if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,2), luego en (2,1), luego en (3,1):

if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][2] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,2), luego en (2,1), luego en (3,2):

if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,2), luego en (2,1), luego en (3,3):

if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == '-' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][0] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == '-' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,2), luego en (2,3), luego en (3,1):

if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == '-'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,2), luego en (3,1):

if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'X' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == '-'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == '-'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,2), luego en (1,3):

if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == '-'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'O' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,2), luego en (3,3), luego en (2,1):

if (tableroGato[1][1] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[2][1] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'O' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'X'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[1][1] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,3), luego en (3,1), luego en (1,1):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'O'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == '-' && tableroGato[2][2] == 'O'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,3), luego en (3,2), luego en (1,1):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (2,3), luego en (3,3), luego en (3,1):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'O' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'O' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}

//Si X jugó en el (3,1), luego en (3,2), luego en (1,1):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == '-' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[1][2] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'O' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'X' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'O'){
tableroGato[0][2] = 'O';
numeroJugadas++;
}

//Si X jugó en el (3,1), luego en (3,3), luego en (1,2):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == '-' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'X' && tableroGato[2][1] == 'O' && tableroGato[2][2] == 'X'){
tableroGato[0][0] = 'O';
numeroJugadas++;
}

//Si X jugó en el (3,2), luego en (3,3), luego en (1,3):

if (tableroGato[0][0] == 'X' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == 'X' && tableroGato[0][2] == 'X' && tableroGato[1][0] == '-' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[0][1] = 'O';
numeroJugadas++;
}if (tableroGato[0][0] == '-' && tableroGato[0][1] == '-' && tableroGato[0][2] == 'X' && tableroGato[1][0] == 'X' && tableroGato[1][1] == 'O' && tableroGato[1][2] == 'O' && tableroGato[2][0] == 'O' && tableroGato[2][1] == 'X' && tableroGato[2][2] == 'X'){
tableroGato[1][0] = 'O';
numeroJugadas++;
}
}
