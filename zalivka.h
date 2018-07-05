#include"bcm2835.h"
#define R1 RPI_GPIO_P1_11
#define R2 RPI_GPIO_P1_08

int zalivka_inicializace ( void )
{
//	usleep (1000000);
	bcm2835_gpio_fsel ( R1, BCM2835_GPIO_FSEL_OUTP );
	bcm2835_gpio_fsel ( R2, BCM2835_GPIO_FSEL_OUTP );
//	printf ("zinicializovano R1\n");
}


void R1_set ( void )
{
	bcm2835_gpio_write ( R1, LOW );
}

void R1_reset ( void )
{
	bcm2835_gpio_write ( R1, HIGH );
}

void R2_set ( void )
{
	bcm2835_gpio_write ( R2, LOW);
}

void R2_reset ( void )
{
	bcm2835_gpio_write ( R2, HIGH );
}

int get_config ( char *cesta, int * cas_hod, int * cas_min,  char *kanal, char * stav )
{
//#define POCET_PARAMETRU	3	//maximalni pocet parametru v souboru config.txt

	FILE *config_file;
	//int counter = POCET_PARAMETRU;
	config_file = fopen ( cesta, "r" );
	int i = 0;
	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	int hour =  timeinfo->tm_hour;
	int minute =  timeinfo->tm_min;
	int second =  timeinfo->tm_sec;
	printf ( "%d:%d:%d\n", hour, minute, second );
	R1_reset();
	while (  1 )
	{	
		delay(500);
		if ( fscanf ( config_file, "%d:%d%s%s", &cas_hod[i], &cas_min[i], kanal, stav ) != 4) {
			break;
		}
		printf("%d:%d %s %s",  cas_hod[i], cas_min[i], kanal, stav );
		// ZAP\0VYP
		time ( &rawtime );
		timeinfo = localtime ( &rawtime );
		if (cas_hod[i] == hour) {
			if (minute == cas_min[i]) {
				if (stav[i * 4] == 'Z') {
					printf(" - ZAPNUTO\n");
					R1_set();
					continue;
				}
			}
			printf(" - VYPNUTO\n");
			continue;
		}
		else {
			printf(" - VYPNUTO\n");
			continue;
		}

		
//		if ( strcmp ( cas , VALUE11 ) == 0 ) strcpy ( nazev_hodnoty11, kanal);
		i++;


	}

	fclose ( config_file );
	return 1;
}


int on_or_off(int * cas_hod, int * cas_min,  char *kanal, char * stav ) {
	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	int hour =  timeinfo->tm_hour;
	int minute =  timeinfo->tm_min;
	int second =  timeinfo->tm_sec;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	if (cas_hod[0] == hour) {
		if (minute == cas_min[0]) {
			if (stav[0] == 'Z') {
				printf("ZAPNUTO");
				return 1;
			}
			printf("%d == %d", cas_hod[0], hour);
			return 0;
		}
		return 0;
	}
	else {
		printf("%d != %d", cas_hod[0], hour);
		return 0;
	}
}
