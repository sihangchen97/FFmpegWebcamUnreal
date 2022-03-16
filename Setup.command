
export FFmpegZipUrl=http://file.intra.sensetime.com/seafhttp/files/d8b60b02-fb16-4bcd-91a7-aa273357b03f/ffmpeg-4.4.1-Mac.zip
export FFmpegZip=ffmpeg-4.4.1-Mac.zip

cd "`dirname "$0"`"

mkdir ThirdParty
cd ThirdParty
curl $FFmpegZipUrl > $FFmpegZip
unzip $FFmpegZip