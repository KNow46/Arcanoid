"# Arcanoid" 


In project properties -> build events -> post-build events

xcopy /y /d  "$(SolutionDir)external\bin\*.dll" "$(OutDir)"
mkdir  "$(OutDir)data"
xcopy /y /d  "$(SolutionDir)data\*.png" "$(OutDir)dat

Copies the selected folders