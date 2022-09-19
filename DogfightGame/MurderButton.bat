del "*.sln" /s /f /q
@RD /S /Q ".vs"
@RD /S /Q "Binaries"
@RD /S /Q "Build"
@RD /S /Q "Intermediate"
@RD /S /Q "DerivedDataCache"
@RD /S /Q "Saved"
set /p DUMMY=Hit ENTER to continue...