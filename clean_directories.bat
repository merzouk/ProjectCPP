if exist bin (
  echo bin directory exist
  cd bin
  del * /S /Q
  cd ..
) else (
  echo bin directory No exist
  mkdir bin
)


if exist obj (
  echo obj directory exist
  cd obj
  del * /S /Q
  cd ..
) else (
  echo obj directory No exist
  mkdir obj
)
