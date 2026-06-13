<#
y (copyRight) windows_sleep.ps1

Version 0.0
-----------
2019.12.12

Reference
---------
[1] https://superuser.com/questions/1116599/what-is-the-powershell-command-equivalent-to-selecting-sleep-from-the-win7-men
[2] https://stackoverflow.com/questions/20713782/suspend-or-hibernate-from-powershell

Example
-------
C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe -ExecutionPolicy Bypass -Command d:\script.ps1
%windir%\System32\rundll32.exe powrprof.dll,SetSuspendState Standby  # [2]
#>

# load assembly System.Windows.Forms which will be used
Add-Type -AssemblyName System.Windows.Forms

# set powerstate to suspend (sleep mode)
$PowerState = [System.Windows.Forms.PowerState]::Suspend;

# do not force putting Windows to sleep
$Force = $false;

# so you can wake up your computer from sleep
$DisableWake = $false;

# do it! Set computer to sleep
[System.Windows.Forms.Application]::SetSuspendState($PowerState, $Force, $DisableWake); `
