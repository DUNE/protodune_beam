echo Starting DIP Browser
set PATH=%CD%\lib64;%PATH%
echo Starting DIP Browser 5.6.3
javaw -Djava.library.path=%CD%\lib64 -jar %CD%\tools\dip-browser-5.6.3.jar
