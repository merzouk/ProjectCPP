echo First argument: %1

if "%1"=="" (
    echo No argument provided.
    exit
) else (
    cd %1
    del *.o
    cd ..
)