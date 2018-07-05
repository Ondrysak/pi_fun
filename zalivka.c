#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "zalivka.h"
time_t rawtime;
struct tm * timeinfo;

int main (char argc, char *argv[])
{
//  flag = 0;
  //FILE * soubor;
  //char text[250];
  if ( ! bcm2835_init () ) return -1;

  zalivka_inicializace();

 time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    int hour =  timeinfo->tm_hour;
    int minute =  timeinfo->tm_min;
    int second =  timeinfo->tm_sec;
  printf ( "Hour:minute:second %d:%d:%d\n", hour, minute, second );
  printf("CVAKAME\n");

  //soubor = fopen(argv[1], "r");
  /*   do {
         scanf("%254s", text);
         if (!strcmp(text, "q"))
             break;
         printf("Zapisuji >> %s <<\n", text);
         fprintf(soubor, ">> %s <<\n", text);
     } while (1);
     fclose(soubor);
  /  */
  char kanal[255], stav[255];
  int  cas_hod[252], cas_min[255];


  /*
    char * varname = "HELLO";
    char * value [250];
    value = (   (char*) getenv (*varname));
    printf("%s", value);
  */
  while (-1)

  {
    get_config (argv[1], cas_hod, cas_min, kanal, stav);
    printf("n------\n");
    delay (1000);

    /*time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    int hour =  timeinfo->tm_hour;
    int minute =  timeinfo->tm_min;
    int second =  timeinfo->tm_sec;

    int turn_on = on_or_off(cas_hod, cas_min, kanal, stav);

    if (turn_on)
    {

      R1_set();
      delay (1000);
  printf ( " TURN ON %d:%d:%d\n", hour, minute, second );
    }
    else
    {
      R1_reset();
      delay (1000);
        printf ( " TURN OFF %d:%d:%d\n", hour, minute, second );
    }

*/
//        printf ( "CVAK %d:%d:%d\n", hour, minute, second );
//       R2_reset();
//       delay (1000);
//       R2_set();
//       delay (1000);\
  }
  /*
        else
        {
          printf ( "nic %d:%d:%d\n", hour, minute, second );
          delay (100);
        }
        */
}
return 1;
}
