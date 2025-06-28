@echo off

set remotedir=/home/%user%/temp_proj

.\binary\putty\PLINK.EXE %user%@%remotehost% -pw "%password%" -batch "rm -rf %remotedir% || true; mkdir -p %remotedir%;"

.\binary\putty\PSCP.EXE -r -pw "%password%" .\src %user%@%remotehost%:%remotedir%

.\binary\putty\PLINK.EXE %user%@%remotehost% -pw "%password%" -batch "cd %remotedir%/src ; pwd; ls -l;"