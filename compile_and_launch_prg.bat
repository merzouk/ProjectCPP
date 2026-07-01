if exist bin (
  echo bin directory exist 
) else (
  echo bin directory No exist
  mkdir bin
)


if exist obj (
  echo obj directory exist 
) else (
  echo obj directory No exist
  mkdir obj
)


make clean 


make binary


.\bin\manage_prg.exe .\datas\privates.dat .\datas\pros.dat