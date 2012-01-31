#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdio.h>
#include <string.h>

#define X 200
#define Y 200
#define WIDTH 100
#define HEIGHT 100
#define WIDTH_MIN 50
#define HEIGHT_MIN 50
#define BORDER_WIDTH 5
#define TITLE "Example"
#define ICON_TITLE "Example"
#define PRG_CLASS "Example"

static void SetWindowManagerHints ( 
 Display * display, 		/*Указатель на структуру Display */
 char * PClass, 		/*Класс программы */
 char * argv[],   		/*Аргументы программы */
 int argc,    			/*Число аргументов */
 Window window,    		/*Идентификатор окна */
 int x,     			/*Координаты левого верхнего */
 int y,	   				/*угла окна */
 int win_wdt,			/*Ширина  окна */
 int win_hgt,  			/*Высота окна */
 int win_wdt_min,			/*Минимальная ширина окна */
 int win_hgt_min, 		/*Минимальная высота окна */
 char * ptrTitle,  		/*Заголовок окна */
 char * ptrITitle,	/*Заголовок пиктограммы окна */
 Pixmap pixmap 	/*Рисунок пиктограммы */
)
{
 XSizeHints size_hints; /*Рекомендации о размерах окна*/

 XWMHints wm_hints;
 XClassHint class_hint;
 XTextProperty windowname, iconname;

 if ( !XStringListToTextProperty (&ptrTitle, 1, &windowname ) ||
    !XStringListToTextProperty (&ptrITitle, 1, &iconname ) ) {
  puts ( "No memory!\n");
  exit ( 1 );
}

size_hints.flags = PPosition | PSize | PMinSize;
size_hints.min_width = win_wdt_min;
size_hints.min_height = win_hgt_min;
wm_hints.flags = StateHint | IconPixmapHint | InputHint;
wm_hints.initial_state = NormalState;
wm_hints.input = True;
wm_hints.icon_pixmap= pixmap;
class_hint.res_name = argv[0];
class_hint.res_class = PClass;

XSetWMProperties ( display, window, &windowname,
  &iconname, argv, argc, &size_hints, &wm_hints,
  &class_hint );
}

void main(int argc, char *argv[])
{
 Display * display;  /* Указатель на структуру Display */
 int screen_number;    /* Номер экрана */
 GC gc;				/* Графический контекст */
 XEvent report;
 Window window, window1;
 XWindowAttributes wa, wa1;
 int corner;

 corner = 0;

 /* Устанавливаем связь с сервером */
 if ( ( display = XOpenDisplay ( NULL ) ) == NULL ) {
  puts ("Can not connect to the X server!\n");
  exit ( 1 );
 }

 /* Получаем номер основного экрана */
 screen_number = DefaultScreen ( display );

 /* Создаем окно */
 window = XCreateSimpleWindow ( display, RootWindow ( display, screen_number ), 
		 X, Y, WIDTH, HEIGHT, BORDER_WIDTH, BlackPixel ( display, screen_number ),
		 WhitePixel ( display, screen_number ) );
 window1 = XCreateSimpleWindow ( display, RootWindow ( display, screen_number ), 
		 X + WIDTH, Y, WIDTH, HEIGHT, BORDER_WIDTH, BlackPixel ( display, screen_number ),
		 WhitePixel ( display, screen_number ) );

 /* Задаем рекомендации для менеджера окон */
 SetWindowManagerHints ( display, PRG_CLASS, argv, argc,
   window, X, Y, WIDTH, HEIGHT, WIDTH_MIN,
   HEIGHT_MIN, TITLE, ICON_TITLE, 0 );
 SetWindowManagerHints ( display, PRG_CLASS, argv, argc,
   window1, X, Y, WIDTH, HEIGHT, WIDTH_MIN,
   HEIGHT_MIN, TITLE, ICON_TITLE, 0 );

 /* Выбираем события,  которые будет обрабатывать программа */
 XSelectInput ( display, window, ExposureMask | ButtonPressMask );
 XSelectInput(display, window1, ExposureMask);

 /* Покажем окно */
 XMapWindow ( display, window );
 XMapWindow(display, window1);

 /* Создадим цикл получения и обработки ошибок */
 while ( 1 ) {
  XNextEvent ( display, &report );

  switch ( report.type ) {
    case Expose :
     /* Запрос на перерисовку */
     if ( report.xexpose.count != 0 )
      break;

     gc = XCreateGC ( display, window, 0 , NULL );

     XFreeGC ( display, gc );
     XFlush(display);
     break;

	 case ButtonPress:
	  if ( report.xbutton.button == Button3 ){
		  corner = (corner + 1)%4;
		  XGetWindowAttributes(display, window, &wa);
		  XGetWindowAttributes(display, window1, &wa1);

		  switch(corner){
			  case 0:
				  XMoveWindow(display, window1, wa.x + wa.width, wa.y - wa1.height);
				  break;
			  case 1:
				  XMoveWindow(display, window1, wa.x + wa.width, wa.y + wa.height);
				  break;
			  case 2:
				  XMoveWindow(display, window1, wa.x - wa1.width, wa.y + wa.height);
				  break;
			  case 3:
				  XMoveWindow(display, window1, wa.x - wa1.width, wa.y - wa1.height);
				  break;
		  }
	  }
	  break;
  }
 }
}
