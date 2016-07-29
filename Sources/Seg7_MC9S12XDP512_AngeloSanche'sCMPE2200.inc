;****************************************************************************
;* HC12 Program:  YourProg - MiniExplanation                                *
;* Processor:     mc9s12xdp512                                              *
;* Xtal Speed:    16 MHz                                                    *
;* Author:        Ang                                                       *
;* Date:          1/12/16	                                                  *
;*                                                                          *
;* Details: 7Seg Led display                                                *
;*                                                                          * 
;*                                                                          *
;*                                                                          *
;*                                                                          *
;***************************************************************************


; Requires:  none
; Returns:   None
; Regs Affected:
; Direction: used in preperation to use port a or for a full clear
LED_7Seg_Insh:
  psha
  pshb
  
  bclr DDRA, #$FF
  bset DDRA, #$03
  bset DDRB, #$ff
  
  movb #$03, PORTA
  
  clrb 
  orab #$70
  
  ldaa #$8
  
  
ClearDigs:
  stab PORTB
  
  movb #$02, PORTA
  movb #$03, PORTA
  
  movb #$80, PORTB
  
  movb #$00, PORTA
  movb #$01, PORTA
  
  incb
  dbne a, ClearDigs
  
  pulb
  pula
  
  rts
  
  
; Requires:  Posish at acum A and Number at acum B($00- $0F)
; Returns:   None
; Regs Affected:
; Direction: sets a posish of a 7 seg to number
;*********************************
Char7Seg:
  pshd
  
  oraa #$50
  staa PORTB
  
  bclr PORTA,#$03
  bset PORTA,#$02
  bset PORTA,#$03
  
  orab #$80
  stab PORTB
  
  bclr PORTA, #$03 
  bset PORTA, #$01
  puld 
  rts


; Requires:  Posish at acum A and Number at acum B($00- $0F)
; Returns:   None
; Regs Affected:
; Direction: with decimal on  
;******************************  
Char7SegD:
  pshd
  
  oraa #$50
  staa PORTB
  
  bclr PORTA,#$03
  bset PORTA,#$02
  bset PORTA,#$03
  
  eorb #$80
  stab PORTB
  
  bclr PORTA, #$03 
  bset PORTA, #$01
  puld 
  rts

; Requires:  Posish at port A
; Returns:   None
; Regs Affected:
; Direction: Clears a posish
;******************************
Clear7Seg:
  pshd
  oraa #$70
  staa PORTB
  
  bclr PORTA,#$03
  bset PORTA,#$02
  bset PORTA,#$03
  
  ldab #$80
  stab PORTB
  
  bclr PORTA, #$03 
  bset PORTA, #$01
  puld 
  rts
  
  
; Requires:  an number(FullByte) at acum b
; Returns:   None
; Regs Affected:
; Direction: Sets an FF number to top back half led 
;*******************  
Print7SegByteTop:
  pshd
  
  pshb
  pshb
  
  ldaa 00
  jsr Clear7Seg
  ldaa 01
  jsr Clear7Seg
  
  pulb
  ldy #4
IShiftFour:
  lsrb
  dbne y,IShiftFour
  
  ldaa #$02
  jsr Char7Seg
  
  pulb 
  andb #$0F
  
  ldaa #$03
  jsr Char7Seg 
  
  puld
  rts 
  
  
; Requires:  an number(FullByte) at acum b
; Returns:   None
; Regs Affected:
; Direction: Sets an FF number to bot back half led 
;*******************  
Print7SegByteBot:
  pshd
  
  pshb
  pshb
  
  ldaa 00
  jsr Clear7Seg
  ldaa 01
  jsr Clear7Seg
  
  pulb
  ldy #4
IShiftFour2:
  lsrb
  dbne y,IShiftFour2
  
  ldaa #$06
  jsr Char7Seg
  
  pulb 
  andb #$0F
  
  ldaa #$07
  jsr Char7Seg 
  
  puld
  rts 
  
  
; Requires:  an number(Fullword) at acum d
; Returns:   None
; Regs Affected:
; Direction: Sets an FFFF number to bot led 
;*******************  
Print7SegWordBot:
  pshx
  pshy
  pshd 
  pshd
  pshd
  pshd
  
  
  ldx #3
IRepeateShiftFourWordBot: 
  ldy #4
IShiftFourWordBot:
  lsrd
  dbne y,IShiftFourWordBot
  dbne x,IRepeateShiftFourWordBot
  
  andb #$0F
  
  ldaa #$04
  jsr Char7Seg
  
  
  puld
  
  ldx #2
IRepeateShiftFourWordBot2: 
  ldy #4
IShiftFourWordBot2:
  lsrd
  dbne y,IShiftFourWordBot2
  dbne x,IRepeateShiftFourWordBot2
  
  andb #$0F
  
  ldaa #$05
  jsr Char7Seg
  
  
  puld
  
  ldy #4
IShiftFourWordBot3:
  lsrd
  dbne y,IShiftFourWordBot3
  
  andb #$0F
  
  ldaa #$06
  jsr Char7Seg
  
  
  puld
  
  andb #$0F
  
  ldaa #$07
  jsr Char7Seg 
  
  puld
  puly
  pulx
  rts 


; Requires:  an number(Fullword) at acum d
; Returns:   None
; Regs Affected:
; Direction: Sets an FFFF number to top led 
;*******************  
Print7SegWordTop:
  pshx  ;
  pshy ;
  pshd ;
  pshd ;
  pshd ;
  pshd  ;
  
  
  ldx #3
IRepeateShiftFourWordTop: 
  ldy #4
IShiftFourWordTop:
  lsrd
  dbne y,IShiftFourWordTop
  dbne x,IRepeateShiftFourWordTop
  
  andb #$0F
  
  ldaa #$00
  jsr Char7Seg
  
  
  puld ;
  
  ldx #2
IRepeateShiftFourWordTop2: 
  ldy #4
IShiftFourWordTop2:
  lsrd
  dbne y,IShiftFourWordTop2
  dbne x,IRepeateShiftFourWordTop2
  
  andb #$0F
  
  ldaa #$01
  jsr Char7Seg
  
  
  puld  ;
  
  ldy #4
IShiftFourWordTop3:
  lsrd
  dbne y,IShiftFourWordTop3
  
  andb #$0F
  
  ldaa #$02
  jsr Char7Seg
  
  
  puld   ;
   
  andb #$0F
  
  ldaa #$03
  jsr Char7Seg 
  
  puld   ;
  puly   ;
  pulx   ;
  rts     

  
  
  
  