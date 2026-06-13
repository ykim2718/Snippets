<#
y (copyRight) windows_sleep_ps1 to taskscheduler.ps1

Version 0.0
-----------
2019.12.12, 12.14, 12.16

Reference
---------
[1] https://comfix.kr/248
[2] https://www.ghacks.net/2015/09/23/use-powershell-to-manage-scheduled-tasks-in-windows/
[3] https://docs.microsoft.com/en-us/powershell/module/scheduledtasks/get-scheduledtask?view=win10-ps

Note
----
. Get-ScheduledTask -TaskName Google* returns all tasks that start with Google.
  Get-ScheduledTask -TaskPath \ returns all tasks that are placed in the TaskPath root. [2, 3]

Example
-------
C:\Windows\System32\WindowsPowerShell\v1.0\powershell.exe -ExecutionPolicy Bypass -Command d:\script.ps1
$CurrentFolder = (Get-Location).path  # Not script location
$PSScriptRoot  # script location, automatic variables [4]
#>

$taskLog = [System.Diagnostics.Eventing.Reader.EventLogConfiguration]::new(
        "Microsoft-Windows-TaskScheduler/Operational"
)
$taskLog.IsEnabled = $true
$taskLog.SaveChanges()

function remove_registered_task($taskName)
{
    $task = Get-ScheduledTask -TaskName $taskName -ErrorAction SilentlyContinue
    if ($null -ne $task)
    {
        Unregister-ScheduledTask -TaskName $taskName -Confirm:$false
        # TODO 2019.11.23 # Unregister-ScheduledTask -TaskName $task_name -Confirm $False | Out-Null
        # & schtasks /delete /tn $task_name /f | Out-Null
    }
}

function confirm_registered_task($taskName, $taskPath)
{
    $task = Get-ScheduledTask -TaskName $taskName -ErrorAction SilentlyContinue
    if ($null -ne $task)
    {
        Write-Output "Created scheduled task: '$($taskName.ToString() )'."
        Get-ScheduledTaskInfo -TaskName $taskName -TaskPath $taskPath
    }
    else
    {
        Write-Output "Created scheduled task: FAILED."
    }
}

$task_name = "Y windows_sleep every monday"
$task_path = "Y"
$script_file_name = 'windows_sleep.ps1'

$script_file_path = Join-Path -Path $PSScriptRoot -ChildPath $script_file_name
$Action = New-ScheduledTaskAction -Execute 'powershell.exe' `
    -Argument "-WindowStyle Hidden -File ""$script_file_path"""
#    -Argument '-NonInteractive -NoLogo -NoProfile -File "{$script_file_path}"'
$Trigger = New-ScheduledTaskTrigger -Weekly -WeeksInterval 1 -DaysOfWeek Monday -At 4:00:00am
$Settings = New-ScheduledTaskSettingsSet -Priority 0
$Task = New-ScheduledTask -Action $Action -Trigger $Trigger -Settings $Settings
$params = @{
    'TaskName' = $task_name;
    'TaskPath' = $task_path;
    'InputObject' = $Task;
    #    'User' = 'YourUserName';
    #    'Password' = 'YourPassword'
}
remove_registered_task $task_name
Register-ScheduledTask @params
confirm_registered_task $task_name $task_path
"^^Y .."

