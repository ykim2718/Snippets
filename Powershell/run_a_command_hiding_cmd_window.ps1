<#
y, 2020.1.16
run_a_command_hiding_cmd_window.ps1

Reference
---------
[1] https://github.com/PowerShell/PowerShell/issues/3028

Note
----
C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe -ExecutionPolicy Bypass -Command d:\script.ps1
C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe -ExecutionPolicy Bypass -File d:\my script.ps1

Example
-------
wscript "./ps-run.vbs" "./run_a_command_hiding_cmd_window.ps1"  # [1]
#>

#Start-Process -FilePath "cmd /c notepad"  # -NoNewWindow
Start-Process -FilePath "notepad"  # -NoNewWindow
