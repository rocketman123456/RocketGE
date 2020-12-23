import os

path = '/Users/developer/Program/CppCode/RocketGE/Assets/sounds/Piano.ff/'
command_1 = 'ffmpeg -i '
command_3 = ' -af loudnorm,silenceremove=start_periods=1:start_silence=0.05:start_threshold=-40dB,afade=out:st=3:d=1.5,afade=in:st=0:d=0.05 -to 4.5 '

for audio in os.listdir(path):
    if os.path.isfile(os.path.join(path, audio)) and audio != '.DS_Store':
        #filetype = os.path.splitext(audio)[1]
        audio_new = audio.replace('aiff','wav')
        full_command = command_1 + os.path.join(path, audio) + command_3 + os.path.join(path, audio_new)
        print(full_command)
        os.system(full_command)