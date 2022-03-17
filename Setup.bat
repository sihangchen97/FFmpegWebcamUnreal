@echo off

cd /d %~dp0

mkdir download
mkdir ThirdParty

set FFmpegUrl=http://file.intra.sensetime.com/f/96626cac14/?raw=1

if exist download/ffmpeg-4.4.1-Win64.zip (
	echo ffmpeg-4.4.1-Win64.zip already exists
) else (
	utils\win\wget -P ./download %FFmpegUrl%
)
unzip -o -d ThirdParty download/ffmpeg-4.4.1-Win64.zip
mkdir ..\..\Binaries\Win64
xcopy ThirdParty\ffmpeg-4.4.1-Win64\lib ..\..\Binaries\Win64 /s /y

pause
