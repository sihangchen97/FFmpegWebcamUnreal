
set FFmpegZipUrl=http://10.4.5.27/FFmpegWebcamUnreal/dev/ffmpeg-4.4.1-Win64.zip
set FFmpegZip=ffmpeg-4.4.1-Win64.zip

cd ThirdParty

curl %FFmpegZipUrl% > %FFmpegZip%
unzip %FFmpegZip%