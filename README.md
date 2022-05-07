<h1>Valve Controller Firmware</h1>

<p>PCB: Valve Controller L0005</p>
<p>MCU: STM32H750VBT6 </p>
<p>MPU Architecture: ARM Cortex-M7</p>

<p>The liquid engine's valve controller (L0005) contains the processor responsible for managing valve actuation commands issued by the liquid engine controller (L0002). The board contains opto-isolated solid state relays for solenoid actuation and a Pulse Width Modulation interface for issuing stepper motor commands that initiate actuation of the liquid engine's main propellant valves. The board contains an STM32H7 ARM Cortex-M7 microcontroller for processing, programmed using a STLink-V2 with a 20-pin IDC cable connection. The board is powered from the 5V buck converter on L0002, which is also used to power the photogate sensors used for valve position calibration. In order to allow the controller to know the true actuation state of the solenoids even in the event of a power failure, the board contains an AC power supply monitoring circuit which produces an indication signal read by the MCU when AC power is available for solenoid actuation. </p>

<p><b>Source Directories:</b></p>
<p>
hotfire: firmware to be run during hotfire testing

terminal: firmware to allow terminal access to all PCB hardware 
</p>

<p><b>Working Directory Structure</b></p>

<p>
doc: documentation

src: source code files and build files

lib: libraries for device drivers and external functions
</p>
