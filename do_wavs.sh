#!/bin/bash

TARGET_DIR=$1
TARGET_VOICE="1"

if [ -d $TARGET_DIR ]; then
  echo "$TARGET_DIR already exists."
  exit 1
fi

mkdir -p $TARGET_DIR

encode () {
    sox $1 --norm=-1 -e unsigned-integer -b 8 -r 31250 -c 1 -t raw $2
}

#for i in {1..5}
for i in {1..136}
do
  TARGET_NUMBER=`printf "%d" $i`
  TARGET_FILE="${TARGET_DIR}/${TARGET_NUMBER}-${TARGET_VOICE}.wav"
  echo "Target: $TARGET_FILE"
  if [ -f "aani_${i}.aiff" ]; then
    encode aani_${i}.aiff $TARGET_FILE
  fi
  if [ -f "aani_${i}.mp3" ]; then
    encode aani_${i}.mp3 $TARGET_FILE
  fi
done
