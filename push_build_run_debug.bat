@echo off

set remotedir=/home/%user%/temp_proj

.\binary\putty\PLINK.EXE %user%@%remotehost% -pw "%password%" -batch "rm -rf %remotedir% || true; mkdir -p %remotedir%;"

.\binary\putty\PSCP.EXE -r -pw "%password%" .\src %user%@%remotehost%:%remotedir%

rem .\binary\putty\PLINK.EXE %user%@%remotehost% -pw "%password%" -batch "cd %remotedir%/src ; pwd; ls -l;"

.\binary\putty\PLINK.EXE %user%@%remotehost% -pw "%password%" -batch "cd %remotedir%/src ; gcc -Wall -Wextra -D CL_TARGET_OPENCL_VERSION=220 main/Main.c -o HelloOpenCL -lOpenCL -g;"

.\binary\putty\PLINK.EXE %user%@%remotehost% -pw "%password%" -batch "cd %remotedir%/src ; ./HelloOpenCL;"

echo 
echo Execution completed