!include "EnvVarUpdate.nsh"
; ${EnvVarUpdate} $0 "NEXUSDIR" "P" "HKLM" "C:\Program Files\Windows Resource Kits\Tools"
; ${EnvVarUpdate} $0 "PATH" "A" "HKLM" "%NEXUSDIR%\bin"
; ${EnvVarUpdate} $0 "LIB" "A" "HKLM" "%NEXUSDIR%\lib"
; ${EnvVarUpdate} $0 "INCLUDE" "A" "HKLM" "%NEXUSDIR%\include"
; ${EnvVarUpdate} $0 "PYTHONPATH" "A" "HKLM" "%NEXUSDIR%\python;%NEXUSDIR%\bin"
; ${EnvVarUpdate} $0 "CLASSPATH" "A" "HKLM" "%NEXUSDIR%\java\jnexus.jar"