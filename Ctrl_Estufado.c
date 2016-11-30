#include "Ctrl_Estufado.h"

#int_TIMER0
void tiempo(void) {
//    int t1;
   set_timer0(10);

    f_seg++;
   if (f_seg >= 127){ f_seg = 0; segundo++; tm1++;}               //correcto
   if(tm1 > 19) {tm1=0;}
   if (segundo > 59) {segundo=0; minuto++;}
   if (minuto > 59) {minuto=0; hora++;}
   if (hora >= 24) {hora=0;}
   //if (f_seg == 0) {output_toggle(rel04);}
   clear_interrupt(INT_TIMER0);
}

#int_rda
void serial_rx_isr() {
	char c_temp;
	
	c_temp = fgetc(MODEM);
	
	if(c_temp>=0 || c_temp<=127) {
	
		if(!Rx_Buffer_Overflow) { Rx_Buffer[Rx_Wr_Index] = c_temp;  }  ;
		
		if(++Rx_Wr_Index > Rx_BUFFER_SIZE) Rx_Wr_Index = 0;
		if(++Rx_Counter > Rx_BUFFER_SIZE) { Rx_Counter = Rx_BUFFER_SIZE; Rx_Buffer_Overflow = 1; }
	}
	clear_interrupt(int_rda);
	
	
//	Rx_Buffer[Rx_Wr_Index] = fgetc(MODEM);
//	if(++Rx_Wr_Index > Rx_BUFFER_SIZE) Rx_Wr_Index = 0;
//	if(++Rx_Counter > Rx_BUFFER_SIZE) { Rx_Counter = Rx_BUFFER_SIZE; Rx_Buffer_Overflow = 1; }
	    	
}

#int_tbe
void serial_tx_isr() {
	if(Tx_Counter !=0) {
		fputc(Tx_Buffer[Tx_Rd_Index], MODEM);
		if(++Tx_Rd_Index > Tx_BUFFER_SIZE) Tx_Rd_Index = 0;
		Tx_Counter--;
		if(Tx_Counter == 0) disable_interrupts(int_tbe);
	}
}


#int_EXT
void EXT_isr( void )
{
	if ((read_ext_eeprom(0) == 0x99) || (read_ext_eeprom(0)==0xFF))
	{	write_ext_eeprom(0,0);	puerto_D = read_ext_eeprom(0);	}
	else if ((read_ext_eeprom(0) & 0x0F ) < 0x09)
	{	write_ext_eeprom(0,(read_ext_eeprom(0)) + 1);	puerto_D = read_ext_eeprom(0);	}	
	else if ((read_ext_eeprom(0) & 0x0F) >= 0x09)
	{	write_ext_eeprom(0,(read_ext_eeprom(0)) + 7);	puerto_D = read_ext_eeprom(0);	}	
}


void main(){
	
	int comando=255;
	config_inicial();
	PantallaInicio();
	
	while(TRUE) {
		scankey();
		comando = akey;
		
            if(tm1 == 0) { temphum(); temperatura(); comando=8; }
            
            if(Rx_Wr_Index >= 3){
	            Prende_On();
	            Apaga_Off();
	            output_bit(rel04,valor);
	            output_bit(rel03,valor2);
            }
		
		
		switch (comando){
		
			case 0: proceso_0(); 	limpia_tecla();		break;
			case 1: proceso_1(); 	limpia_tecla();		break;
			case 2: proceso_2(); 	limpia_tecla();		break;
			case 3: proceso_3(); 	limpia_tecla();		break;
			case 4: proceso_4(); 	limpia_tecla();		break;
			case 5: proceso_5(); 	limpia_tecla();		break;
			case 6: proceso_6(); 	limpia_tecla();		break;
			case 7: proceso_7(); 	limpia_tecla();		break;
			case 8: proceso_8(); 	limpia_tecla();		break;
			case 9: proceso_9(); 	limpia_tecla();		break;
			case 10: proceso_10(); 	limpia_tecla();		break;
			case 11: proceso_11(); 	limpia_tecla();		break;
			case 12: proceso_12(); 	limpia_tecla();		break;
			case 13: proceso_13(); 	limpia_tecla();		break;
			case 21: proceso_21(); 	limpia_tecla();		break;
			case 22: proceso_22(); 	limpia_tecla();		break;

			default:	limpia_tecla();		break;
		}
	
		//salidas();
		pantallas(100);
	}
}


//_____PROCESO RUTINAS_____________
void config_inicial(void) {
    lcd_init();
    init_ext_eeprom();
    set_tris_a(0x7f);							//a0,a1,a2,aa3,a4,a5,a6 entradas
    set_tris_b(0x00);
    set_tris_c( 0xb6 );		//  1011 0110
//    set_tris_c(0x00);
    set_tris_e(0b0000);                           //e3, e2, e1, e0 salidas
    sht_init(); 

    setup_timer_0(RTCC_INTERNAL|RTCC_DIV_128|RTCC_8_bit);      //819 us overflow
    //setup_timer_1 ( T1_DISABLED );
    //setup_timer_2 ( T2_DISABLED,0,1 );
    //setup_timer_3(T3_DISABLED | T3_DIV_BY_1);
    setup_comparator(NC_NC_NC_NC);

    enable_interrupts(INT_TIMER0);
    enable_interrupts(int_rda);
//    enable_interrupts(int_EXT);
    enable_interrupts(GLOBAL);

    setup_adc(ADC_CLOCK_INTERNAL);
    setup_adc_ports(AN0_TO_AN3);
    //set_adc_channel(0);
    borrar_Rx_Buffer();
    //output_e(0);
    delay_ms(500);

}
/*
char bgetc(void) {
	char c;
	while(Rx_Counter == 0) ;
	c = Rx_Buffer[Rx_Rd_Index];
	if(++Rx_Rd_Index > Rx_BUFFER_SIZE) Rx_Rd_Index = 0;
	if(Rx_Counter) Rx_Counter--;
	return c;
}
*/
void borrar_Rx_Buffer(void) {
    char ch;
    for (ch=0; ch<=Rx_BUFFER_SIZE; ch++) { Rx_Buffer[ch] ='\0'; }
    Rx_Wr_Index = 0; Rx_Counter = 0;
}
/*
void bputc(char c) {
	char restart = 0;
	while(Tx_Counter > (!Tx_BUFFER_SIZE - 1)) ;
	if (Tx_Counter == 0) restart = 1;
	Tx_Buffer[Tx_Wr_Index++] = c;
	if(Tx_Wr_Index > Tx_BUFFER_SIZE) Tx_Wr_Index = 0;
	Tx_Counter++;
	if(restart == 1) enable_interrupts(int_tbe);
}
*/
void salidas(void) {
		output_toggle(rel04);
		delay_ms(500);
}

//--------PANTALLAS------------------------------------------------

void PantallaInicio(void){
	printf(lcd_putc,"\fSISTEMA CONTROL");
	printf(lcd_putc,"\n");
	printf(lcd_putc,"\nServElect");
	printf(lcd_putc,"\nMx 443 1983830");
	delay_ms(4000);
}	

void pantallas(int screen) {
    long espera=2000;
    int j, i=0;
	if (screen==100) {
        printf(lcd_putc,"\fCtrl Estufado"); 
        printf(lcd_putc,"\nMadera %x", input_c());
        printf(lcd_putc,"\n segundo=%d", segundo);
        printf(lcd_putc,"\nServElect %x",Rx_Wr_Index); delay_ms(200);	// Rx_Wr_Index,  Rx_Counter
	}       //	}

	else if (screen == 0) {printf(lcd_putc,"\fProceso 0");  screen = 100; delay_ms(espera);}   //

    else if (screen == 1) {printf(lcd_putc,"\f Temp=%f\n Hum=%f",temp, hum); 
    						printf(lcd_putc,"\nAN=%s",valor_ad);
    						screen = 100; delay_ms(espera);}

    else if (screen == 2) {printf(lcd_putc,"\fProceso 2");  screen = 100; delay_ms(espera);}

    else if (screen == 3) {
    printf(lcd_putc,"\fProceso 3");
    printf(lcd_putc,"\nT0 = %x, %x", time, segundo); delay_ms(espera); screen = 100;
}

    else if (screen == 4) {printf(lcd_putc,"\fProceso 4");  
        for (i==0;i<=2;++i) {
        	printf(lcd_putc,"\nAN%c = %f , ",i,valor_ad[i]);
        }	
        screen = 100; delay_ms(espera);}

    else if (screen == 5) {printf(lcd_putc,"\fActiva Relays");  screen = 100; delay_ms(espera);}

    else if (screen == 6) {
	    j=0;
       
      printf(lcd_putc,"\fLeer Buffer c\r\n");
    	printf(lcd_putc,"%s\n", Rx_Buffer);  delay_ms(espera);
    	
    	//borrar_Rx_Buffer();
    	screen = 100; 
    }

    else if (screen == 7) {printf(lcd_putc,"\fBorrar Buffer");
      printf(lcd_putc,"\nRx_Buffer");
      printf(lcd_putc,"\n%s",Rx_Buffer);
      screen = 100; delay_ms(espera);
    }

    else if (screen == 8) {printf(lcd_putc,"\fProceso 8");  screen = 100; delay_ms(espera);}

    else if (screen == 9) {printf(lcd_putc,"\fProceso 9");  screen = 100; delay_ms(espera);}

    else if (screen == 10) {printf(lcd_putc,"\fProceso 10");  screen = 100; delay_ms(espera);}

    else if (screen == 11) {printf(lcd_putc,"\fProceso 11");  screen = 100; delay_ms(espera);}

    else if (screen == 12) {printf(lcd_putc,"\fProceso 12");  screen = 100; delay_ms(espera);}

    else if (screen == 13) {printf(lcd_putc,"\fProceso 13");  screen = 100; delay_ms(espera);}

    else if (screen == 21) {printf(lcd_putc,"\fProceso 21");  screen = 100; delay_ms(espera);}

    else if (screen == 22) {printf(lcd_putc,"\fProceso 22");  screen = 100; delay_ms(espera);}

    else screen = 100;
}

//Rutina de teclado manejado desde el puerto D
void scankey(void) {
   short listo=0; 
   int caracter;
   while (akey!=255) akey=255;
   if (!listo){
   output_bit(col1,0); output_bit(col2,1); output_bit(col3,1); output_bit(col4,1);
   switch (caracter=input_D()){
      case 0xEE: akey=1; delay_ms(50); listo=1; break;
      case 0xED: akey=2; delay_ms(50); listo=1; break;
      case 0xEB: akey=3; delay_ms(50); listo=1; break;
      case 0xE7: akey=10; delay_ms(50); listo=1; break;
      default: listo=0; akey=0xff; break;
   }
   }
   if (!listo){
   output_bit(col1,1); output_bit(col2,0); output_bit(col3,1); output_bit(col4,1);
   switch (caracter=input_D()){
      case 0xDE: akey=4; delay_ms(50); listo=1; break;
      case 0xDD: akey=5; delay_ms(50); listo=1; break;
      case 0xDB: akey=6; delay_ms(50); listo=1; break;
      case 0xD7: akey=11; delay_ms(50); listo=1; break;
      default: listo=0; akey=0xff; break;
   }
   }
   if (!listo){
   output_bit(col1,1); output_bit(col2,1); output_bit(col3,0); output_bit(col4,1);
   switch (caracter=input_D()){
      case 0xBE: akey=7; delay_ms(50); listo=1; break;
      case 0xBD: akey=8; delay_ms(50); listo=1; break;
      case 0xBB: akey=9; delay_ms(50); listo=1; break;
      case 0xB7: akey=12; delay_ms(50); listo=1; break;
      default: listo=0; akey=0xff; break;
   }
   }
   if (!listo){
   output_bit(col1,1); output_bit(col2,1); output_bit(col3,1); output_bit(col4,0);
   switch (caracter=input_D()){
      case 0x7E: akey=21; delay_ms(50); listo=1; break;
      case 0x7D: akey=0; delay_ms(50); listo=1; break;
      case 0x7B: akey=22; delay_ms(50); listo=1; break;
      case 0x77: akey=13; delay_ms(50); listo=1; break;
      default: listo=0; akey=0xff; break;
   }
   }
   output_bit(col1,1); output_bit(col2,1); output_bit(col3,1); output_bit(col4,1);
   listo=0;
}

void limpia_tecla(void) {
   while (akey!=255) akey=255;   
}

void ingresa_tecla(void) {
    do {
        scankey(); delay_ms(300);
    } while(akey==255); 
}

//==============================================================================
void proceso_0(void) { 	pantallas(0); }

void proceso_1(void) {  pantallas(1); }

void proceso_2(void) { 
    int h=0;
    pantallas(2);
    for (h=0; h<=4;++h) {
	    output_high(rel04); delay_ms(100); 
	    output_low(rel04); delay_ms(300); 
    }
    //h=0;
}

void proceso_3(void) { 
    time = get_timer0();
    pantallas(3); 
}

void proceso_4(void) { 	
    temperatura();
    pantallas(4); 
}

void proceso_5(void) { 	
    pantallas(5); 
    output_bit(rel01,true);  output_bit(rel02,true);  output_bit(rel03,true);  output_bit(rel04,true); delay_ms(1000);
    output_bit(rel01,false); output_bit(rel02,false); output_bit(rel03,false); output_bit(rel04,false); delay_ms(1000);
}

void proceso_6(void) { 
	int k=0;
	pantallas(6);
	
	for (k=0; k<12; ++k) {
		printf(lcd_putc,"\n\r%c", Rx_Buffer[k]);
	}
	for (k=13; k<24; ++k) {
		printf(lcd_putc,"\n\r%c", Rx_Buffer[k]);
	}	
	 printf(lcd_putc,"\nfuera rutina");
	delay_ms(500);
}

void proceso_7(void) { 	pantallas(7); 
	borrar_Rx_Buffer();
}

void proceso_8(void) { 	
	envio_datos();
/*
    int i=0;
    //char c_1[] = "on_01";
    pantallas(8);
    fprintf(MODEM,"\nTemp=%f C -",temp);
    fprintf(MODEM," Hum=%f RH",hum);
    for (i==0;i<=3;++i) {
    	fprintf(MODEM,"%f ", valor_ad[i]);
    }	
    delay_ms(10);
    printf(lcd_putc,"\ft1 activo %s", t1);
    delay_ms(300); t1=0;
   */ 
}

void proceso_9(void) { 	pantallas(9); }
void proceso_10(void) { pantallas(10); }
void proceso_11(void) { pantallas(11); }
void proceso_12(void) { pantallas(12); }
void proceso_13(void) { pantallas(13); }
void proceso_21(void) { pantallas(21); }
void proceso_22(void) { pantallas(22); }

void temperatura(void) {
	int i;
	for (i=0;i<=2;++i) {
	    set_adc_channel(i);
	    valor_ad[i] = read_adc(); delay_ms(50);
	    //valor_ad=read_adc(); 
	}    
//   temp_actual=82+0.02246*valor_ad;
//   centigrados_a_fahrenheit(temp_actual);
//   temp_actual_1=161.8991+0.018745*valor_ad;         //Formula por minimos cuadrados medicion a 1080°C
//   centigrados_a_fahrenheit(temp_actual_1);
   //temp_actual_2=117.62976+.019907*valor_ad;         //Formula obtenido con valores extremos medicion 1080°C
   //centigrados_a_fahrenheit(temp_actual_2);
}
void temphum(void){
	      sht_rd(restemp, truehumid); 
            temp = restemp; //(int) 
            hum =  truehumid; //(int)
}

void Prende_On(void) 
	{
	    char c_1[] = "on_01";
	    char c_3[] = "on_02";
	    t1 = strstr(Rx_Buffer,c_1);
	    t3 =  strstr(Rx_Buffer,c_3);
	
	    if (t1) { valor = 1; fputs(t1, MODEM); t1=0;};
	    if (t3) { valor2 = 1; fputs(t3, MODEM); t3=0;};
	    borrar_Rx_Buffer();  
	    //printf(lcd_putc,"\ft1 activo %u", t1);
	    delay_ms(2000); 
	}    
 
void Apaga_Off(void) 
	{
		char c_2[] = "off_01";
		char c_4[] = "off_02";
		t2 = strstr(Rx_Buffer,c_2);
		t4 = strstr(Rx_Buffer,c_4);
		
		if (t2) { valor = 0; fputs(t2, MODEM); 	 t2=0;};
		if (t4) { valor2 = 0; fputs(t4, MODEM); t4=0;};
		borrar_Rx_Buffer();
		//printf(lcd_putc,"\ft2 activo %u", t2);
		delay_ms(2000); 
}

void envio_datos(void) {
    int i=0;
    //char c_1[] = "on_01";
    pantallas(8);
    fprintf(MODEM,"\n%5.2f, ",temp);
    fprintf(MODEM,"%5.2f, ",hum);
    for (i==0;i<=3;++i) {
    	fprintf(MODEM,"%5.2f, ", valor_ad[i]);
    }	
    delay_ms(10);
    printf(lcd_putc,"\fEnviando datos %s", t1);
    delay_ms(300); t1=0;
}	