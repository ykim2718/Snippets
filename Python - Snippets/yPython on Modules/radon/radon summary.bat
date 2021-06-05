@echo on
:: y, 2017.8.16

set out=%~n0.out

radon cc abc.py -o ALPHA > "%out%"
radon cc abc.py -a -nc -o ALPHA >> "%out%"

timeout 9
