;***************************************************************************
; HC12 Program:  YourProg - MiniExplanation                                
; Processor:     mc9s12xdp512                                              
; Xtal Speed:    16 MHz                                                    
; Author:        Ang                                                       
; Date:          16:00 May 19, 2010	                                      
;                                                                          
;.            Angelo's LED Lib INC        
;     Functions/Sub: 
;     -LedCleanSet: sets Registers for leds insh use also clears
;
;     -RedLedOn: set the out for red on
;     -RedLedOff: Sets the ou for red off
;     -RedLedToggle: Toggles on off
;
;     -YelLedOn: set the out for red on
;     -YelLedOff: Sets the out for red off
;     -YelLedToggle: Toggles on off
;
;     -GreLedOn: set the out for red on
;     -GreLedOff: Sets the out for red off
;     -GreLedToggle: Toggles on off
;*******************************************************************

; Requires:  None
; Returns:   None
; Regs Affected: none
; Direction: Sub that will cleanly set the registers need for the input/out puts
LedCleanSet:
  bclr PT1AD1,    #$E0        ;Clear all bits to start
  bset DDR1AD1,   #$E0      ;Set the input/outputs to first three out
  bset ATD1DIEN1, #$1F      ;Ennable the bit ports   
  rts  
  
  
; Requires:  None
; Returns:   None
; Regs Affected: none
; Direction: turns on red led %100%
RedLedOn:
  psha
  pshb
  
  ldd PT1AD1                ;Grab the reg to work on
  oraa #$80                 ;set the first bit for red on
  std PT1AD1                ;store it back tho the register
  
  pulb
  pula
  rts
  
  
  
; Requires:  None
; Returns:   None
; Regs Affected: none 
; Direction: turns off red led %100%
RedLedOff:
  psha
  pshb
  
  ldd PT1AD1                ;Grab the reg to work on
  anda #$7F                 ;set the first bit for red on
  std PT1AD1                ;store it back tho the register
  
  pulb
  pula
  rts
  
  
  
; Requires:  None
; Returns:   None
; Regs Affected: none 
; Direction: toggles red led %100%
RedLedToggle:
  psha
  pshb
  
  ldd PT1AD1                ;Grab the reg to work on
  eora #$80                 ;set the first bit for red on
  std PT1AD1                ;store it back tho the register
  
  pulb
  pula
  rts
  
  
  
  
  
; Requires:  None
; Returns:   None
; Regs Affected: none
; Direction: turns on red led %010%
YelLedOn:
  psha
  pshb
  
  ldd PT1AD1                ;Grab the reg to work on
  oraa #$40                 ;set the first bit for red on
  std PT1AD1                ;store it back tho the register
  
  pulb
  pula
  rts
  
  
  
; Requires:  None
; Returns:   None
; Regs Affected: none 
; Direction: turns off yellow led %010%
YelLedOff:
  psha
  pshb
  
  ldd PT1AD1                ;Grab the reg to work on
  anda #$BF                 ;set the first bit for red on
  std PT1AD1                ;store it back tho the register
  
  pulb
  pula
  rts
  
  
  
; Requires:  None
; Returns:   None
; Regs Affected: none 
; Direction: toggles yellow led %010%
YelLedToggle:
  psha
  pshb
  
  ldd PT1AD1                ;Grab the reg to work on
  eora #$40                 ;set the first bit for red on
  std PT1AD1                ;store it back tho the register
  
  pulb
  pula
  rts
  
  
  ; Requires:  None
; Returns:   None
; Regs Affected: none
; Direction: turns on green led %001%
GreLedOn:
  psha
  pshb
  
  ldd PT1AD1                ;Grab the reg to work on
  oraa #$20                 ;set the first bit for red on
  std PT1AD1                ;store it back tho the register
  
  pulb
  pula
  rts
  
  
  
; Requires:  None
; Returns:   None
; Regs Affected: none 
; Direction: turns off green led %001%
GreLedOff:
  psha
  pshb
  
  ldd PT1AD1                ;Grab the reg to work on
  anda #$DF                 ;set the first bit for red on
  std PT1AD1                ;store it back tho the register
  
  pulb
  pula
  rts
  
  
  
; Requires:  None
; Returns:   None
; Regs Affected: none 
; Direction: toggles green led %001%
GreLedToggle:
  psha
  pshb
  
  ldd PT1AD1                ;Grab the reg to work on
  eora #$20                 ;set the first bit for red on
  std PT1AD1                ;store it back tho the register
  
  pulb
  pula
  rts
  
  
;*********************************************************************************************
; Extended
; Requires:  None
; Returns:   None
; Regs Affected: none 
; Direction: Toggles style button Press led $10
CheckSWTop:
  pshx
  ldy   #PT1AD1
  brset 0,Y,#$10,I_TopDebounce
  bra   I_TopButton_Done
  
I_TopDebounce:
  ldx #10
  jsr QuickDelay
  ldy   #PT1AD1
  brset 0,Y,#$10,I_TopDo
  bra I_TopButton_Done
  
I_TopDo:
  jsr I_SW_Top_Down

I_TopLiftWait:
  jsr   I_SW_Top_Held
  ldy   #PT1AD1
  brset 0,Y,#$10,I_TopLiftWait
  
  jsr   I_SW_Top_Up
I_TopButton_Done:
  pulx
  rts  
  
; Requires:  X reg to be set for wait period for next action
; Returns:   None
; Regs Affected: none 
; Direction: Wait and hit again style button Press led $10

CheckSWCen:
  pshx
  ldy   #PT1AD1
  brset 0,Y,#$01,I_CenDebounce
  bra   I_CenButton_Done
  
I_CenDebounce:
  ldx #10
  jsr QuickDelay
  ldy   #PT1AD1
  brset 0,Y,#$01,I_CenDo
  bra I_CenButton_Done
  
I_CenDo:
  jsr I_SW_Cen_Down
  
I_CenLiftWait:
  jsr I_SW_Cen_Held
  ldy   #PT1AD1
  brset 0,Y,#$01,I_CenLiftWait
  
  jsr I_SW_Cen_Up
I_CenButton_Done:
  pulx
  rts  
  
; Requires:  X reg to be set for wait period for next action
; Returns:   None
; Regs Affected: none 
; Direction: Wait and hit again style button Press led $10
CheckSWBot:
  pshx
  ldy   #PT1AD1
  brset 0,Y,#$04,I_BotDebounce
  bra   I_BotButton_Done
  
I_BotDebounce:
  ldx #10
  jsr QuickDelay
  ldy   #PT1AD1
  brset 0,Y,#$04,I_BotDo
  bra I_BotButton_Done
  
I_BotDo:
  jsr I_SW_Bot_Down
  
I_BotLiftWait:
  jsr I_SW_Bot_Held
  ldy   #PT1AD1
  brset 0,Y,#$04,I_BotLiftWait
  
  jsr I_SW_Bot_Up
I_BotButton_Done:
  pulx
  rts  
  
; Requires:  X reg to be set for wait period for next action
; Returns:   None
; Regs Affected: none 
; Direction: Wait and hit again style button Press led $10
CheckSWLef:
  pshx
  ldy   #PT1AD1
  brset 0,Y,#$08,I_LefDebounce
  bra   I_LefButton_Done
  
I_LefDebounce:
  ldx #10
  jsr QuickDelay
  ldy   #PT1AD1
  brset 0,Y,#$08,I_LefDo
  bra I_LefButton_Done
  
I_LefDo:
  jsr I_SW_Lef_Down
  
I_LefLiftWait:
  jsr I_SW_Lef_Held
  ldy   #PT1AD1
  brset 0,Y,#$08,I_LefLiftWait
  
  jsr I_SW_Lef_Up
I_LefButton_Done:
  pulx
  rts  
  
  
; Requires:  X reg to be set for wait period for next action
; Returns:   None
; Regs Affected: none 
; Direction: Wait and hit again style button Press led $10
CheckSWRig:
  pshx
  ldy   #PT1AD1
  brset 0,Y,#$02,I_LRigDebounce
  bra   I_RigButton_Done
  
I_LRigDebounce:
  ldx #10
  jsr QuickDelay
  ldy   #PT1AD1
  brset 0,Y,#$02,I_RigDo
  bra I_RigButton_Done
  
I_RigDo:
  jsr I_SW_Rig_Down
  
I_RigLiftWait:
  jsr I_SW_Rig_Held
  ldy   #PT1AD1
  brset 0,Y,#$02,I_RigLiftWait
  
  jsr I_SW_Rig_Up
I_RigButton_Done:
  pulx
  rts  
;*************************************************************************************************
; marks basic-----------------------------------------  
; Requires:  None
; Returns:   None
; Regs Affected: none 
; Direction: Toggles style button Press led $10
TCheckSWTop:
  pshx
  ldy   #PT1AD1
  brset 0,Y,#$10,TI_TopDebounce
  bra   TI_TopButton_Done
  
TI_TopDebounce:
  ldx #10
  jsr QuickDelay
  ldy   #PT1AD1
  brset 0,Y,#$10,TI_TopDo
  bra TI_TopButton_Done
  
TI_TopDo:
  jsr TI_SW_Top_Action

TI_TopLiftWait:
  ldy   #PT1AD1
  brset 0,Y,#$10,TI_TopLiftWait
  
TI_TopButton_Done:
  pulx
  rts  
  
; Requires:  X reg to be set for wait period for next action
; Returns:   None
; Regs Affected: none 
; Direction: Wait and hit again style button Press led $10

TCheckSWCen:
  pshx
  ldy   #PT1AD1
  brset 0,Y,#$01,TI_CenDebounce
  bra   TI_CenButton_Done
  
TI_CenDebounce:
  ldx #10
  jsr QuickDelay
  ldy   #PT1AD1
  brset 0,Y,#$01,TI_CenDo
  bra TI_CenButton_Done
  
TI_CenDo:
  jsr TI_SW_Cen_Action
  
TI_CenLiftWait:
  ldy   #PT1AD1
  brset 0,Y,#$01,TI_CenLiftWait
  
TI_CenButton_Done:
  pulx
  rts  
  
; Requires:  X reg to be set for wait period for next action
; Returns:   None
; Regs Affected: none 
; Direction: Wait and hit again style button Press led $10
TCheckSWBot:
  pshx
  ldy   #PT1AD1
  brset 0,Y,#$04,TI_BotDebounce
  bra   TI_BotButton_Done
  
TI_BotDebounce:
  ldx #10
  jsr QuickDelay
  ldy   #PT1AD1
  brset 0,Y,#$04,TI_BotDo
  bra TI_BotButton_Done
  
TI_BotDo:
  jsr TI_SW_Bot_Action
  
TI_BotLiftWait:
  ldy   #PT1AD1
  brset 0,Y,#$04,TI_BotLiftWait
  
TI_BotButton_Done:
  pulx
  rts  
  
; Requires:  X reg to be set for wait period for next action
; Returns:   None
; Regs Affected: none 
; Direction: Wait and hit again style button Press led $10
TCheckSWLef:
  pshx
  ldy   #PT1AD1
  brset 0,Y,#$08,TI_LefDebounce
  bra   TI_LefButton_Done
  
TI_LefDebounce:
  ldx #10
  jsr QuickDelay
  ldy   #PT1AD1
  brset 0,Y,#$08,TI_LefDo
  bra TI_LefButton_Done
  
TI_LefDo:
  jsr TI_SW_Lef_Action
  
TI_LefLiftWait:
  ldy   #PT1AD1
  brset 0,Y,#$08,TI_LefLiftWait
  
TI_LefButton_Done:
  pulx
  rts  
  
  
; Requires:  X reg to be set for wait period for next action
; Returns:   None
; Regs Affected: none 
; Direction: Wait and hit again style button Press led $10
TCheckSWRig:
  pshx
  ldy   #PT1AD1
  brset 0,Y,#$02,TI_LRigDebounce
  bra   TI_RigButton_Done
  
TI_LRigDebounce:
  ldx #10
  jsr QuickDelay
  ldy   #PT1AD1
  brset 0,Y,#$02,TI_RigDo
  bra TI_RigButton_Done
  
TI_RigDo:
  jsr TI_SW_Rig_Action
  
TI_RigLiftWait:
  ldy   #PT1AD1
  brset 0,Y,#$02,TI_RigLiftWait
  
TI_RigButton_Done:
  pulx
  rts  
  
;**************************************************************************************
  

  
; De-apeachate when done not so practical
; Requires:  Time to wait in aprox it would multipy to somehting like 375us(x)
; Returns:   None
; Regs Affected: none
; Direction: Sub that will cleanly set the registers need for the input/out puts
DirtyWait:
  dbne x, DirtyWait ; if not 0 branch
  rts

; Requires:  Time to wait in aprox it would multipy to somehting like 375us(x)
; Returns:   None
; Regs Affected: trashes y
; Direction: Sub that will cleanly set the registers need for the input/out puts
QuickDelay:  
  ldy #2665
delayIn:    
  dbne y, delayIn
  dbne x, QuickDelay
  rts
  
  
; Requires:  Time to wait in aprox it would multipy to somehting like 375us(x)
; Returns:   None
; Regs Affected:
; Direction: Sub that will cleanly set the registers need for the input/out puts
SafeDelay: 
  pshy
SafeDelayLoop: 
  ldy #2665
SafedelayIn:    
  dbne y, SafedelayIn
  dbne x, SafeDelayLoop
  puly
  rts
  

  
   
