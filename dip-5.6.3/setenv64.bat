@echo off
echo ===================================================
echo Setting up DIP Environment
echo ===================================================

if (%DIPBASE%)==() (
echo DIPBASE not set, defaulting to current directory
set DIPBASE=%CD%
)

set PATH=%DIPBASE%\lib64;%PATH%
echo PATH was prepended with %DIPBASE%\lib64
set DIM_DNS_PORT=2506
echo DIM DNS PORT was set to DIP standard 2506
set CLASSPATH=%DIPBASE%\lib64\dip-jni-5.6.3.nar;%DIPBASE%\lib64\dip-jni-5.6.3-.nar;%CLASSPATH%
echo CLASSPATH was prepended with %DIPBASE%\lib64\dip-jni-5.6.3.nar
echo Done.
