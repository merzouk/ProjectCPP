echo First argument: %1

if "%1"=="" (
    echo No argument provided.

) else (
    cd %1
    del *.o
    cd ..
)