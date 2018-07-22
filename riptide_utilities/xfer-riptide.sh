#ssh ros@riptide 'rm -rf ~/osu-uwrt/riptide_software/src'

dates_scripts/date_set-riptide.sh

rsync -tvrz --exclude=".*" --exclude=".*/" ~/osu-uwrt/riptide_software/src ros@riptide:~/osu-uwrt/riptide_software
ssh ros@riptide 'chmod 700 ~/osu-uwrt/riptide_software/src/riptide_utilities/*.sh'
