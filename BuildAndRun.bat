@echo off
title Pikachu Game
echo Start Compiling

g++ Source\*.cpp -lwinmm -o Pukachi
echo Compiling done. Press any key to start the game
Pause
Start "" "Pukachi.exe"