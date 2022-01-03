@echo off
setlocal enabledelayedexpansion
g++ -std=c++17 -I C:\\Users\\stran\\Desktop\\programming\\c++\\comp\\header -DMORIRIN -D_GLIBCXX_DEBUG -O2 -Wall -Wextra c:\\Users\\stran\\Desktop\\programming\\c++\\comp\\contest\\atcoder\\ahc007\\2.cpp -o C:\\Users\\stran\\Desktop\\programming\\c++\\comp\\a.exe
for /l %%a in (1,1,10) do (
	set num=000%%a
	set num=!num:~-4,4!
	a.exe < C:\\Users\\stran\\Desktop\\download_temperately\\tools\\in\\!num!.txt > txt\\test_out.txt
)
endlocal