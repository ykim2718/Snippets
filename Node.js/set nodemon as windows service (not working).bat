:: y, 2018.10.28
:: https://support.microsoft.com/en-us/help/251192/how-to-create-a-windows-service-by-using-sc-exe

title %~0

:: sc delete Y_Homepage
sc create Y_Homepage binpath="C:\Users\User\AppData\Roaming\npm\nodemon.cmd  \"d:\Wolf\Homo academicus\yStudy on code - node.js\y_node_js\bin\www\""
:: sc create Y_Homepage5 binPath= "c:\y\nodejs\node.exe  \"d:\Wolf\Homo academicus\yStudy on code - node.js\y_node_js\bin\www"
pause