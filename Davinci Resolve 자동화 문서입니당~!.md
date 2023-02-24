참고 페이지
https://gist.github.com/garyo/c398abc2d3d6f801a61ad86a0f5b651e

```sh
# by 김이해초 (fimicat@gmail.com)
############### 프로그램을 돌리기 전에 
# 터미널에서 'sh automatic_bu.sh' 엔터 치면 바로 실행됩니다.
# 1. 아래 환경변수 아래 파일 경로를 바꿔주세요(그 외에는 건드리지 마세요)
# 2. 다빈치 리졸브를 켜서 프록시 돌릴 파일을 전부 render que에 세팅해주세요.
# 마지막 프록시 제작은 다빈치 리졸브에 켜져 있는 프로젝트를 가져와서,
# render all만 실행시킵니다.
# 이게 완료되셨다면 이 문서를 끄고, 실행해주시면 됩니다.

####### 환경변수세팅 : 변경 후 진행해주세요 #########
# 원본 파일 경로
PATH_0="/Volumes/hard_disk_name/backupfolder"
# 1차 백업 파일 경로
PATH_1="/Volumes/hard_disk_name/backupfolder"
# 2차 백업 파일 경로
PATH_2="/Volumes/hard_disk_name/backupfolder"





###########################################################
# 이 아래로는 건드리지 마세요 Don't touch under this line
###########################################################
DR_PATH=/Library/Application\ Support/Blackmagic\ Design/DaVinci\ Resolve/Fusion/Scripts/Comp/ 
SCRIPT=renderall.py
TESTSCRIPT=test.py


# 다빈치 리졸브 커맨드 라인 세팅
export RESOLVE_SCRIPT_API="/Library/Application Support/Blackmagic Design/DaVinci Resolve/Developer/Scripting/"
export RESOLVE_SCRIPT_LIB="/Applications/DaVinci Resolve/DaVinci Resolve.app/Contents/Libraries/Fusion/fusionscript.so"
export PYTHONPATH="$PYTHONPATH:$RESOLVE_SCRIPT_API/Modules/"

# 스크립트 파일 이동
cp $SCRIPT /Library/Application Support/Blackmagic Design/DaVinci Resolve/Fusion/Scripts/Comp/

# 스크립트 파일 실행
python3 $(DR_PATH)$SCRIPT




```

```python

#!/usr/bin/env python

import DaVinciResolveScript as dvr_script
resolve = dvr_script.scriptapp("Resolve")
fusion = resolve.Fusion()
projectManager = resolve.GetProjectManager()
prj = projectManager.GetCurrentProject()
projectManager.SaveProject()
prj.StartRendering()

```