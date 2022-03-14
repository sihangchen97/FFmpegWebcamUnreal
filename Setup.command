
export FFmpegZipUrl=http://10.4.5.27/FFmpegWebcamUnreal/dev/ffmpeg-4.4.1-Mac.zip
export FFmpegZip=ffmpeg-4.4.1-Mac.zip

cd "`dirname "$0"`"

cd ThirdParty

curl $FFmpegZipUrl > $FFmpegZip
unzip $FFmpegZip