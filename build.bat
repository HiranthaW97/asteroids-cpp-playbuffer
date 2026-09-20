@echo off
REM ===========================================================================
REM  build.bat  -  One-click build for the Asteroids assignment (MSYS2/MinGW).
REM  Double-click this file, or run it from a terminal, to (re)build the game.
REM ---------------------------------------------------------------------------
REM  Why each flag/library is here:
REM    -std=c++17            modern C++ used by PlayBuffer and our classes
REM    -mwindows             build a GUI app (PlayBuffer provides WinMain)
REM    -DUNICODE -D_UNICODE  PlayBuffer expects a Unicode Win32 build (as in VS)
REM    -Wno-multichar        silence harmless warnings inside Play.h's WAV loader
REM    -static...            bundle the runtime so Asteroids.exe runs on its own
REM    -l...                 Windows libs PlayBuffer needs (graphics/audio/etc.)
REM ===========================================================================
setlocal
set "GPP=C:\msys64\ucrt64\bin\g++.exe"

"%GPP%" -std=c++17 -O2 -mwindows -DUNICODE -D_UNICODE -Wno-multichar ^
  -static -static-libgcc -static-libstdc++ ^
  Play.cpp MainGame.cpp Rigidbody.cpp Ship.cpp Asteroid.cpp ^
  -o Asteroids.exe ^
  -lgdiplus -ldwmapi -ldbghelp -lgdi32 -lwinmm -lole32 -lShlwapi -luuid -lxaudio2_8

if %ERRORLEVEL%==0 (
    echo.
    echo Build succeeded -^> Asteroids.exe
) else (
    echo.
    echo Build FAILED. Read the errors above.
)
endlocal
