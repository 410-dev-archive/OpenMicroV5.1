# AVER Robotics Machine API Documentation

This markdown file is a documentation of AVER Machine controlling API.
Expand the collapsible table to see the methods that are accessible.

[DP] tag means that the method / class is deprecated.
[UD] tag means that the method / class is under development.
[BF] tag means that the method / class is currently failing.

<details>
  <summary>AEFileControl (mach_aver_fctl.h)</summary>
    This class depends on:
    vex.h,
  	string,
  	fstream,
  	iostream

  This class uses namespace on:
  	vex,
  	std

  <details>
    <summary>   (bool) doesFileExists(loadFile: std::string)</summary>

		This method returns true or false based on the fact whether
    the specified file exists on the microSD storage inserted 
    in VEX V5 Brain.
  </details>

  <details>
    <summary>   (string) loadString(loadFile: std::string)</summary>

		This method returns the string that is saved in the specified 
    file that exists on the microSD storage inserted in VEX V5 Brain.
		It does not check the file existence, therefore using 
    doesFileExists(loadFile) method to check first is recommended.
  </details>

  <details>
    <summary>   (int) saveString(fileTitle: string, contents: std::string)</summary>

    	This method saves string in 'contents' variable, with the file 
      name of 'fileTitle' variable. It returns an exit code.
    	The possible returned exit codes are:
    		0: SD Card is not inserted
    		1: Successfully written a file
    		-1: Failed to write a file
  </details>
</details>


<details>
  <summary>AEScreenControl (mach_aver_scctl.h)</summary>
  This class depends on:
  	vex.h,
  	string

  This class uses namespace on:
  	vex,
  	std

  <details>
    <summary>   (void) init()</summary>

		This method runs Brain.Screen.render method 
    with parameter: true, false.
  </details>

  <details>
    <summary>   (int) setLinePrefix(lineNumber: int, text: std::string)</summary>

		This method sets the n th line (Determined by lineNumber variable)
     with the specified text in 'text' variable.
		It returns the length of the 'text' variable, 
    so that the text could be updated at the specified location.
  </details>

  <details>
    <summary>   (void) setValueOfLine(lineNumber: int, prefixLength: int, text: std::string)</summary>

    	This method sets the value of a line. This method can specify
      the starting cursor location with lineNumber (vertical), 
      and prefixLength (horizontal).
  </details>

   <details>
    <summary>   (void) clearLine(lineNumber: int)</summary>

    	This method clears the specified line.
  </details>

   <details>
    <summary>   (void) clearScreen()</summary>

    	This method clears the entire screen.
  </details>
</details>


<details>
  <summary>AEMotorControl (mach_aver_mtctl.h)</summary>
  This class depends on:
  	vex.h

  This class uses namespace on:
  	vex
  	std

  <details>
    <summary>   [UD] [BF] (int) runMotor(motorObjects: vex::motor[], timeInMillisecond: int)</summary>

    	This method runs multiple motors at once, that is included in motorObjects array.
    	The running time should be determined by the variable 'timeInMillisecond'.
    	It is recommended to run this method asynchronously, since this method
      uses vex::task::sleep method.
    	This method returns the exit code:
    		0: Task complete
    		1: Unhandled Exception (Probably invalid motor address)
  </details>
</details>