# OpenMicroV5.1

## Info

Building software: [VEXcode Pro V5](https://www.vexrobotics.com/vexcode-download?___store=vexroboticsap&___from_store=vexrobotics#ttps://www.vexrobotics.com/vexcode-download#v5pro)

Language: C++

Purpose: Easier development for VEX. Most of the low-level components are already developed, and developer may add custom code.

## Features

- MDisplay: Control the display of LCD on Vex Brain
  - (-> void) init(): Initialize Brain LCD
  - (->short) setLinePrefix(int lineNumber, std::string text): Sets text to the line, then returns the count of the text (Able to use as offset for labeling)
  - (-> void) setValueOfLine(short lineNumber, short prefixLength, std::string text): Set vtext to the line, starting from a certain point.
  - (-> void) clearLine(int lineNumber): Clear specified line
  - (-> void) clearScreen(): Clear entire display
- MFiles: Control the files stored in MicroSD Card. The MicroSD Card MUST BE FORMATTED TO FAT16 or 32, WITH LESS THAN 16GB OF PHYSICAL SIZE!
  - (-> bool) doesFileExist(std::string filePath): Checks whether the file exist or not
  - (-> std::string) loadString(std::string filePath): Reads the text data from the file
  - (-> int) saveString(std::string fileName, std::string content): Write a file with given content, and returns exit code. 1 should be returned if successful.
- MMacro: Incomplete
- MMotor: Controls the connected motors
  - (-> int) runMotors(vex::motor motorObjects[], int motorsCount, vex::directionType direction, float speed): Run all given motors at the same time
  - (-> int) runSingleMotor(vex::motor motorObject, vex::directionType direction, float speed): Run just one motor
  - (-> int) stopMotors(vex::motor motorObjects[], int motorCount): Stops multiple motors at once
  - (-> int) stopMotor(vex::motor motorObject): Stops one motor
- MRemote: 
  - (-> bool) updateAll(vex::controller Controller, bool liveControl)
- MSensor: 
- MTypeConvert: 

