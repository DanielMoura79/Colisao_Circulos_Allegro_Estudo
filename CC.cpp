#include <math.h>
#include <allegro.h>

// DECLARACOES INICIAIS //
int sair=0; void sair_allegro() {sair=1;}; 
int timer=0; void tempo() {timer++;};
int Ctrl_FPS=60; float delay=0;

// INICIALIZACAO ALLEGRO //
int main()
{
  allegro_init();
  install_timer();
  install_keyboard();
  install_mouse(); 
  set_color_depth(32);
  set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
  install_int_ex(tempo, BPS_TO_TIMER(60)); //60fps
  set_window_title("ALLEGRO MINIMAL");
  set_close_button_callback( sair_allegro );
  install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
  BITMAP *buffer = create_bitmap(640,480);
  int ball1_x=100;
	int ball1_y=100;
	int ball1_raio=40;
	int ball2_x=320;
	int ball2_y=240;
  int ball2_raio=70;
  
  // LOOP DE JOGO //
  while (sair==0)
  {
  delay=timer; 
	if (key[KEY_ESC]) {sair=1;}; 
	clear_to_color(buffer,makecol(255,255,255));
	
	/* < SEU CODIGO AQUI! > */

	//ajusta posicao da linha
  if (mouse_b & 1) { ball1_x=mouse_x; ball1_y=mouse_y; };
  if (mouse_b & 2) { ball2_x=mouse_x; ball2_y=mouse_y; };
  
  //calcula a colisao
  int colisao=0;
  int distancia=0;
  int cateto1=ball2_x-ball1_x;
  int cateto2=ball2_y-ball1_y;
  int hipotenusa= sqrt( (cateto1*cateto1)+(cateto2*cateto2) );
  distancia = hipotenusa; //somente para fins didaticos: (distancia=hipotebusa) entenderam alunos?
  
  if (distancia <= ball1_raio+ball2_raio) { colisao=1; }
  
  //mouse
	line(buffer, mouse_x-20, mouse_y, mouse_x+20, mouse_y, makecol(000, 000, 000));
	line(buffer, mouse_x, mouse_y-20, mouse_x, mouse_y+20, makecol(000, 000, 000));
	
	//desenha na tela
  circle(buffer, ball1_x, ball1_y, ball1_raio, makecol(255,0,0));
  circle(buffer, ball2_x, ball2_y, ball2_raio, makecol(0,0,255));
  line(buffer, ball1_x, ball1_y, ball2_x, ball2_y, makecol(000,000,000));
	textprintf_ex(buffer, font, 5,  5, makecol(000,000,000), -1, "Use o botao esquerdo e direito para mover as esferas");
	textprintf_ex(buffer, font, 5, 25, makecol(000,000,000), -1, "Distancia: %d", distancia);
	textprintf_ex(buffer, font, 5, 45, makecol(000,000,000), -1, 
	  "C1x: %d, C1y: %d, C1r: %d, C2x: %d, C2y: %d, C2r: %d, C1r+C2r: %d",
	  ball1_x, ball1_y, ball1_raio, ball2_x, ball2_y, ball2_raio, ball1_raio+ball2_raio);
	if (colisao==1) { textprintf_ex(buffer, font, mouse_x-30, mouse_y-30, makecol(000,000,000), -1, "colisao!!!"); };
	draw_sprite(screen, buffer, 0, 0);
		
  // FINALIZACOES //
	while(timer==delay){};	
	clear(buffer);
  }; 
  destroy_bitmap(buffer);
  return 0;
};
END_OF_MAIN();
