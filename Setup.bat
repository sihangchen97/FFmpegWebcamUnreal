
set FFmpegZipUrl=http://file.intra.sensetime.com/seafhttp/files/9fd1d26e-3d1e-4850-815e-c5801d9d0004/ffmpeg-4.4.1-Win64.zip
set FFmpegZip=ffmpeg-4.4.1-Win64.zip

mkdir ThirdParty
cd ThirdParty

curl %FFmpegZipUrl% > %FFmpegZip%
unzip %FFmpegZip%