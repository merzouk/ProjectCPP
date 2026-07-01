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

echo Clean all object link and executable program
make clean

echo Compile and create executable program
make binary

echo Launch program
.\bin\manage_prg.exe .\datas\privates.dat .\datas\pros.dat