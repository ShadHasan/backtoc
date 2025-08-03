@echo off

set remotedir=/home/%user%/temp_proj

.\binary\putty\PLINK.EXE %user%@%remotehost% -pw "%password%" -batch "rm -rf %remotedir% || true; mkdir -p %remotedir%;"

.\binary\putty\PSCP.EXE -r -pw "%password%" .\src %user%@%remotehost%:%remotedir%

rem .\binary\putty\PLINK.EXE %user%@%remotehost% -pw "%password%" -batch "cd %remotedir%/src ; pwd; ls -l;"

.\binary\putty\PLINK.EXE %user%@%remotehost% -pw "%password%" -batch "cd %remotedir%/src ; gcc -I %remotedir%/src/main -Wall -Wextra -D CL_TARGET_OPENCL_VERSION=120 main/Main.c -o HelloOpenCL -L/usr/lib/aarch64-linux-gnu/ -lOpenCL;"

.\binary\putty\PLINK.EXE %user%@%remotehost% -pw "%password%" -batch "cd %remotedir%/src ; CL_LOG_ERRORS=stdout ./HelloOpenCL;"

echo 
echo Execution completed