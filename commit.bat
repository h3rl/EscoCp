@echo off
if %1.==. (
	echo No parameters have been provided.
) else (
	git add -A
	git commit -a -m %1
	git push
)