;****************************************************************************
;* HC12 Program:  YourProg - MiniExplanation                                *
;* Processor:     mc9s12xdp512                                              *
;* Xtal Speed:    16 MHz                                                    *
;* Author:        Ang                                                       *
;* Date:          16:00 May 19, 2010	                                      *
;*                                                                          *
;* Details: A more detailed explanation of the program is entered here      *
;*                                                                          * 
;*                                                                          *
;*                                                                          *
;*                                                                          *
;****************************************************************************

; export symbols
            XDEF Entry            ; export 'Entry' symbol
            ABSENTRY Entry        ; for absolute assembly: mark this as application entry point

; include derivative specific macros
            INCLUDE 'mc9s12xdp512.inc'
            
            
;**************************************************************
;*                  Equates Declared Here                     *
;**************************************************************
ROMStart    EQU  $4000  ; absolute address to place my code/constant data


            

;**************************************************************
;*                 Variables Declared Here                    * <------
;**************************************************************
            ORG RAMStart 			;Address $0400            
;Insert your variables here 

  org $2500

Count ds.w 1
TopCount ds.w 1
 




;**************************************************************
;*                 Constants Declared Here                    *
;**************************************************************
            
Constants	EQU $C000	
	ORG Constants 			;Address $C000

            
;Insert your constants here 




;**************************************************************
;*                 Code Section Here                          *<-----
;**************************************************************
            ORG   ROMStart		  ;Address	$4000
Entry:
            LDS   #RAMEnd+1       ; initialize the stack pointer
                                  ; enable interrupts                        
                                  

;Place your code here starting at the Main label                                
  ;; insih us                          
Main:
  jsr LED_7Seg_Insh
  bset DDRAB, #$80
  bclr PORTA,#$80
  
  
Reset:
  ldaa PORTA
  eora #$80
  staa PORTA
  ldx #16
  jsr QuickDelay
  eora #$80
  staa PORTA
  ldx #32
  jsr QuickDelay
  bra Reset
  
;Cycle:
  ;ldx #100 ;on 100
  ;jsr QuickDelay
  ;jsr CallSwitchWave
  
  ;ldx #100 ;on 200
  ;jsr QuickDelay
  ;jsr CallSwitchWave
  
  ;ldx #100 ;on 300
  ;jsr QuickDelay
  ;jsr CallSwitchWave
  
  ;ldx #33  ; 333  char
  ;jsr QuickDelay
  ;jsr Print
  
  ;ldx #67  ;on 400
  ;jsr QuickDelay
  ;jsr CallSwitchWave
  
  ;ldx #100 ;on 500
  ;jsr QuickDelay
 ; jsr CallSwitchWave
  
;  ldx #100 ;on 600
;  jsr QuickDelay
;  jsr CallSwitchWave
  
;  ldx #66  ;666 char
;  jsr QuickDelay
;  jsr Print
  
;  ldx #34  ;on 700
;  jsr QuickDelay
;  jsr CallSwitchWave
  
;  ldx #100 ;on 800
;  jsr QuickDelay
;  jsr CallSwitchWave
  
;  ldx #100 ;on 900
;  jsr QuickDelay
;  jsr CallSwitchWave
  
;  ldx #99  ;999 char off
;  jsr QuickDelay
;  jsr Print
;  jsr CallSwitchWave
  
  
  
;  bra Cycle
  

  
;CallSwitchWave:
;  ldaa PORTA
;  eora #$80
;  staa PORTA
;  rts 
  
  
;Print:
;  ldab Count
;  addb #1;
;  jsr  Print7SegByteTop
;  stab Count
;  rts
;  ldab Count
;  addb #1 
;  stab Count
  
;Cycle:
;  incb
;  stab Count
;
;  
;  ldaa #0
;  ldy #0
;  ldx #6
;  EDIV 
;  cpd #0
;  beq CallCountTop
;ContOne:
;
;  ldab Count
;  ldaa #0
;  ldy #0
;  ldx #5
;  EDIV 
;  cpd #0
;  beq CallSwitchWave
;ContTwo:
;
;  ldx  #18
;  jsr  QuickDelay
;  ldab Count
;  cmpa #30
;  beq Reset 
;  bra Cycle
;  
;CallSwitchWave:
;  ldaa PORTA
;  eora #$80
;  staa PORTA
;  bra  ContTwo
;
;CallCountTop: 
;  ldab TopCount
;  addb #1;
;  jsr  Print7SegByteTop
;  stab TopCount
;  bra ContOne
 
  
  
  
;**************************************************************
;*                 Buttons JSRs  Extened                      *
;************************************************************** 
;***************************************    top   
I_SW_Top_Down:
  jsr RedLedToggle
  rts  
  
  
I_SW_Top_Held:
  rts
  
  
I_SW_Top_Up:
  jsr RedLedToggle
  rts
;***************************************    cent  
I_SW_Cen_Down:
  jsr YelLedToggle
  rts
  
I_SW_Cen_Held:
  rts
  
I_SW_Cen_Up:
  jsr YelLedToggle
  rts
  
;***************************************    bot
  
I_SW_Bot_Down:
  jsr GreLedToggle
  rts
  
I_SW_Bot_Held:
  rts
  
I_SW_Bot_Up:
  jsr GreLedToggle
  rts
  
;***************************************    left
  
I_SW_Lef_Down:
  jsr RedLedToggle
  rts 
  
I_SW_Lef_Held:
  rts 
  
I_SW_Lef_Up:
  jsr RedLedToggle
  rts 
  
;***************************************    right
  
I_SW_Rig_Down:
  jsr GreLedToggle
  rts 

I_SW_Rig_Held:
  rts 
  
I_SW_Rig_Up:
  jsr GreLedToggle
  rts 
 
;**************************************************************
;*                 Buttons JSRs                               *
;************************************************************** 
 
 
TI_SW_Top_Action:
  jsr RedLedToggle
  rts
  
TI_SW_Cen_Action:
  jsr YelLedToggle
  rts
  
TI_SW_Bot_Action:
  jsr GreLedToggle
  rts
  
TI_SW_Lef_Action:
  jsr RedLedToggle
  rts 
  

TI_SW_Rig_Action:
  jsr GreLedToggle
  rts
  
;**************************************************************
;*                 SCI VT100 Strings Defined Here             *
;**************************************************************  
  
     
     
;**************************************************************
;*                 Look-Up Table Includes                     *
;**************************************************************

          ;INCLUDE "YourLookUp.inc" 

 
     
;**************************************************************
;*            Absolute DP128 Library Includes                 *
;************************************************************** 
      
         
         ;INCLUDE "A2D_LIB.inc"
         ;INCLUDE "DAC4822_LIB.inc"
         ;INCLUDE "Delays.inc"
         ;INCLUDE "My Delays.inc"
          
         ;INCLUDE "LCD_LIB.inc"
         ;INCLUDE "LEDS_RYG.inc"
         ;INCLUDE "LEDS_7Seg.inc"
         ;INCLUDE "SCI_LIB.inc"
                  
         ;INCLUDE "SPI_4822.inc"
         ;INCLUDE "STRING_LIB.inc"
         ;INCLUDE "HC12_Switches.inc"
                   
         ;INCLUDE "UTILITY_LIB.inc"
         ;INCLUDE "Math_Utility_Lib.inc"
         
         
;**************************************************************
;*           Absolute XDP512 Library Includes                 *
;************************************************************** 
         ; XDP512 Libs
         ;INCLUDE "IIC-24AA512_EEPROM.inc"
         ;INCLUDE "LCD_XDP512.inc"
         ;INCLUDE "LEDS_7Seg.inc"
         ;INCLUDE "LEDS_RYG_XDP512.inc"         
         ;INCLUDE "My Delays.inc"
         ;INCLUDE "Switches_XDP512.inc"
         INCLUDE "LED_RYG_AND_SWITCHES_MC9S12XDP512_AngeloSanche'sCMPE2200.inc"
         INCLUDE "Seg7_MC9S12XDP512_AngeloSanche'sCMPE2200.inc"
         
       
         

;**************************************************************
;*                 Interrupt Vectors                          *
;**************************************************************
            ORG   $FFFE
            DC.W  Entry           ; Reset Vector