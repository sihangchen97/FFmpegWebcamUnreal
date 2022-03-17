
export FFmpegUrl=http://file.intra.sensetime.com/f/39cc29cda3/?raw=1

cd "`dirname "$0"`"

mkdir download
mkdir ThirdParty

if [ -e download/ffmpeg-4.4.1-Mac.zip ]
then echo ffmpeg-4.4.1-Mac.zip already exists
else utils/mac/wget $FFmpegUrl -O download/ffmpeg-4.4.1-Mac.zip
fi

unzip -o -d ThirdParty download/ffmpeg-4.4.1-Mac.zip