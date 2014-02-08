#!/bin/bash

SPEECH=0
for file in part_*;
do echo $file && SPEECH=$((SPEECH+1)) && cat $file | say -v 'Lee' -o "aani_$SPEECH" && SPEECH=$((SPEECH+1)) && ln -s puhlu.mp3 "aani_$SPEECH.mp3"
done
