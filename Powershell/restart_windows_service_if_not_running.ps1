<#
y, 2020.1.26 - 27
restart_windows_service_if_not_running.ps1

Reference
---------
[1] https://github.com/PowerShell/PowerShell/issues/3028

Note
----
C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe -ExecutionPolicy Bypass -Command d:\script.ps1
C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe -ExecutionPolicy Bypass -File d:\my script.ps1

Example
-------
wscript "./ps-run.vbs" "./restart_windows_service_if_not_running.ps1"  # [1]
#>

$service_name = 'Y_MongoDb'
$service = Get-Service $service_name
if ($service.Status -ne 'Running') {
    Start-Service $service_name
    $service = Get-Service $service_name
    Write-Output "$( $service_name ) service is restarted and $( $service.Status )"
} else {
    Write-Output "$( $service_name ) service is $( $service.Status )"
}
Write-Output "^^Y"
