#include <18F4550.h>
#device  ADC=10

#use delay(clock=16Mhz)
#fuses HSPLL, NOWDT, PROTECT, USBDIV, PLL5,  NOMCLR, NOXINST, WDT128
//#fuses HSPLL, NOWDT, NOPROTECT, NOLVP, NODEBUG, PLL5, CPUDIV1, USBDIV, VREGEN    VREGEN, NOPBADEN, WRTB,  NOBROWNOUT,CPB,

#use RS232(BAUD=9600, xmit=PIN_C6, rcv=PIN_C7, PARITY=N, BITS=8, STOP=1, STREAM=MODEM, TIMEOUT=10)
//#ORG DEFAULT

#include <LCD420_gus.c>
//long puerto_a;
#byte puerto_a = 0xF80
#byte puerto_b = 0xF81
#byte puerto_c = 0xF82
#byte puerto_d = 0xF83
#byte puerto_e = 0xF84
//#byte tris_a = 0XF92
//#byte tris_b = 0XF93
//#byte tris_c = 0XF94
//#byte tris_d = 0XF95
//#byte tris_e = 0XF96

#define Trig           	 	PIN_A4
#define Echo           		PIN_A5
#define sht_data_pin    	PIN_C1 
#define sht_clk_pin     	PIN_C2 
#define col1            		PIN_D4
#define col2            		PIN_D5
#define col3            		PIN_D6
#define col4            		PIN_D7
#define rel01           		PIN_B3
#define rel02           		PIN_E0
#define rel03           		PIN_E1
#define rel04           		PIN_E2
//#define rel05           	PIN_E3


#use i2c(master, sda=sht_data_pin, scl=sht_clk_pin)

#include <SHT15.h>
#include <string.h>
#include <stdlib.h>
#include <funciones.h>
#include <24256.c>


//-----VARIABLES GLOBALES------
int 		akey=255, time, segundo, minuto, hora, f_seg, valor;
int		tm1, valor2;
float 	restemp, truehumid, temp,hum;
//long 	valor_ad[4];
float	valor_ad[4];
char 	string1[6], TC1[6], HR1[6];
char	*t1, *t2, *t3, *t4;

//#define Rx_BUFFER_SIZE	24
#define Rx_BUFFER_SIZE	60
char 	Rx_Buffer[Rx_BUFFER_SIZE + 1];
char 	Rx_Wr_Index = 0;
char	Rx_Rd_Index = 0;
char	Rx_Counter = 0;
int 		Rx_Buffer_Overflow = 0;

#define	Tx_BUFFER_SIZE	60
char 	Tx_Buffer [Tx_BUFFER_SIZE + 1];
char 	Tx_Rd_Index = 0;
char	Tx_Wr_Index = 0;
char	Tx_Counter = 0; 

/*
#byte TOSU=0XFFF
#byte TOSH=0XFFE
#byte TOSL=0XFFD
#byte STKPTR=0XFFC
#byte PCLATU=0XFFB
#byte PCLATH=0XFFA
#byte PCL=0XFF9
#byte TBLPTRU=0XFF8
#byte TBLPTRH=0XFF7
#byte TBLPTRL=0XFF6
#byte TABLAT=0XFF5
#byte PRODH=0XFF4
#byte PRODL=0XFF3
#byte INTCON=0XFF2
#byte INTCON2=0XFF1
#byte INTCON3=0XFF0
//#byte INDF0(1)=0XFEF
//#byte POSTINC0(1)=0XFEE
//#byte POSTDEC0(1)=0XFED
//#byte PREINC0(1)=0XFEC
//#byte PLUSW0(1)=0XFEB
#byte FSR0H=0XFEA
#byte FSR0L=0XFE9
#byte WREG=0XFE8
//#byte INDF1(1)=0XFE7
//#byte POSTINC1(1)=0XFE6
//#byte POSTDEC1(1)=0XFE5
//#byte PREINC1(1)=0XFE4
//#byte PLUSW1(1)=0XFE3
#byte FSR1H=0XFE2
#byte FSR1L=0XFE1
#byte BSR=0XFE0
//#byte INDF2(1)=0XFDF
//#byte POSTINC2(1)=0XFDE
//#byte POSTDEC2(1)=0XFDD
//#byte PREINC2(1)=0XFDC
//#byte PLUSW2(1)=0XFDB
#byte FSR2H=0XFDA
#byte FSR2L=0XFD9
#byte STATUS=0XFD8
#byte TMR0H=0XFD7
#byte TMR0L=0XFD6
#byte T0CON=0XFD5
#byte OSCCON=0XFD3
#byte HLVDCON=0XFD2
#byte WDTCON=0XFD1
#byte RCON=0XFD0
#byte TMR1H=0XFCF
#byte TMR1L=0XFCE
#byte T1CON=0XFCD
#byte TMR2=0XFCC
#byte PR2=0XFCB
#byte T2CON=0XFCA
#byte SSPBUF=0XFC9
#byte SSPADD=0XFC8
#byte SSPSTAT=0XFC7
#byte SSPCON1=0XFC6
#byte SSPCON2=0XFC5
#byte ADRESH=0XFC4
#byte ADRESL=0XFC3
#byte ADCON0=0XFC2
#byte ADCON1=0XFC1
#byte ADCON2=0XFC0
#byte CCPR1H=0XFBF
#byte CCPR1L=0XFBE
#byte CCP1CON=0XFBD
#byte CCPR2H=0XFBC
#byte CCPR2L=0XFBB
#byte CCP2CON=0XFBA
#byte BAUDCON=0XFB8
#byte ECCP1DEL=0XFB7
#byte ECCP1AS=0XFB6
#byte CVRCON=0XFB5
#byte CMCON=0XFB4
#byte TMR3H=0XFB3
#byte TMR3L=0XFB2
#byte T3CON=0XFB1
#byte SPBRGH=0XFB0
#byte SPBRG=0XFAF
#byte RCREG=0XFAE
#byte TXREG=0XFAD
#byte TXSTA=0XFAC
#byte RCSTA=0XFAB
#byte EEADR=0XFA9
#byte EEDATA=0XFA8
//#byte EECON2(1)=0XFA7
#byte EECON1=0XFA6
#byte IPR2=0XFA2
#byte PIR2=0XFA1
#byte PIE2=0XFA0
#byte IPR1=0XF9F
#byte PIR1=0XF9E
#byte PIE1=0XF9D
#byte OSCTUNE=0XF9B
//#byte TRISE=0XF96
//#byte TRISD=0XF95
//#byte TRISC=0XF94
//#byte TRISB=0XF93
//#byte TRISA=0XF92
#byte LATE=0XF8D
#byte LATD=0XF8C
#byte LATC=0XF8B
#byte LATB=0XF8A
#byte LATA=0XF89
//#byte PORTE=0XF84
//#byte PORTD=0XF83
//#byte PORTC=0XF82
//#byte PORTB=0XF81
//#byte PORTA=0XF80
#byte UEP15=0XF7F
#byte UEP14=0XF7E
#byte UEP13=0XF7D
#byte UEP12=0XF7C
#byte UEP11=0XF7B
#byte UEP10=0XF7A
#byte UEP9=0XF79
#byte UEP8=0XF78
#byte UEP7=0XF77
#byte UEP6=0XF76
#byte UEP5=0XF75
#byte UEP4=0XF74
#byte UEP3=0XF73
#byte UEP2=0XF72
#byte UEP1=0XF71
#byte UEP0=0XF70
#byte UCFG=0XF6F
#byte UADDR=0XF6E
#byte UCON=0XF6D
#byte USTAT=0XF6C
#byte UEIE=0XF6B
#byte UEIR=0XF6A
#byte UIE=0XF69
#byte UIR=0XF68
#byte UFRMH=0XF67
#byte UFRML=0XF66
#byte SPPCON=0XF65
#byte SPPEPS=0XF64
#byte SPPCFG=0XF63
#byte SPPDATA=0XF62

*/