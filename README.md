# CarTracing
The National Undergraduate Electronic Design Competition second prize

                                                              Abstract
	This system is mainly composed of metal signal detection, vehicle speed and the line of road detecting and automatic control 
	in three parts. System master choose ST's STM32F103C8T6 chip, the chip for metal detection and vehicle automatic movement of
	the centralized processing and control. Metal detection system uses the subject required by TI company LDC1314 digital 
	converter chip inductor, by reading this chip internal related register metal objects degree of change in value judgment, 
	so as to inform the master control chip change vehicle movement. Vehicle system by L198N drives, and two dc motors, 
	photoelectric speed detector, the pipe has a main control chip output four PWM signals according to the results of the metal detection driver L298N drive control two dc motors to achieve the purpose of control and regulation of the vehicle movement,
	the encoder and the system master match the internal timer and external interruption, vehicle speed and moving away.

Keywords: LDC1314  STM32F103C8T6  PWM  L298N  DC-Motor

