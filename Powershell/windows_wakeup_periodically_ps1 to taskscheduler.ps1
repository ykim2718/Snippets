<#
y (copyRight) windows_wakeup_periodically_ps1 to taskscheduler.ps1

Version 0.0
-----------
. enactment, 2019.12.12, 12.14, 12.16 - 18
. use New-ScheduledTaskPrincipal, 2020.1.11

Reference
---------
[1] https://comfix.kr/248
[2] https://docs.microsoft.com/en-us/powershell/module/scheduledtasks/new-scheduledtasksettingsset?view=win10-ps
[3] https://docs.microsoft.com/en-us/powershell/module/scheduledtasks/new-scheduledtaskprincipal?view=win10-ps
[4] https://stackoverflow.com/questions/20713782/suspend-or-hibernate-from-powershell
[5] https://www.howtogeek.com/119028/how-to-make-your-pc-wake-from-sleep-automatically/ ★★★
[6] https://www.ghacks.net/2015/09/23/use-powershell-to-manage-scheduled-tasks-in-windows/
[7] https://docs.microsoft.com/en-us/powershell/module/scheduledtasks/get-scheduledtask?view=win10-ps
[8] https://youtu.be/gBtSkJePt0s
[9] https://docs.microsoft.com/en-us/powershell/module/scheduledtasks/new-scheduledtaskprincipal?view=win10-ps

Note
----
. Ensure waker timers are enabled [5]:
  For this to work, you’ll need to ensure “wake timers” are enabled in Windows. To do so, head to
  Control Panel > Hardware and Sound > Power Options. Click “Change plan settings” for the current power plan,
  click “Change advanced power settings,” expand the “Sleep” section, expand the “Allow wake timers” section,
  and ensure it’s set to “Enable.”
. Get-ScheduledTask -TaskName Google* returns all tasks that start with Google.
  Get-ScheduledTask -TaskPath \ returns all tasks that are placed in the TaskPath root. [6, 7]

Windows 10 Dose Not Wake Up From Sleep FIX [8]
------------------------------------------
#1 Control Panel:
    > All Control Panel Items > Power Options > Edit Plan Settings
    > Change advanced power settings > PCI Express Tree > Link State Power Management
    > Setting = Off
#2 Administrative Command Prompt (disabling hiberation):
    powercfg -h off

Example
-------
Get-ExecutionPolicy
Get-ExecutionPolicy -List
Get-Help Set-ExecutionPolicy
Set-ExectutionPolicy -ExecutionPolicy Unrestricted -Scope CurrentUser
Get-Host
Start-Sleep -Seconds 1.1

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


$task_name = "Y windows_wakeup every friday"
$task_path = "Y"

$Action = New-ScheduledTaskAction -Execute 'cmd.exe' ` -Argument "/c 'exit'"
$Trigger = New-ScheduledTaskTrigger -Weekly -WeeksInterval 1 -DaysOfWeek Wednesday -At 4:00:00pm # Friday -At 3:00:00pm
$Settings = New-ScheduledTaskSettingsSet -Priority 0 -WakeToRun  # [2]
#$STPrin = New-ScheduledTaskPrincipal -GroupId "BUILTIN\Administrators" -RunLevel Highest  # [9]
#$STPrin = New-ScheduledTaskPrincipal -UserId "LOCALSERVICE" -RunLevel Highest -LogonType ServiceAccount  # [9]
$STPrin = New-ScheduledTaskPrincipal -UserId "Y20170707\Y" -RunLevel Highest -LogonType ServiceAccount  # [9]
$Task = New-ScheduledTask -Action $Action -Trigger $Trigger -Settings $Settings -Principal $STPrin
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

