<#
y (copyRight) python_script_to_windows_taskscheduler.ps1

Version 0.0
-----------
. 2020.9.1 - 2

Reference
---------
[1] https://comfix.kr/248
[2] https://www.ghacks.net/2015/09/23/use-powershell-to-manage-scheduled-tasks-in-windows/
[3] https://docs.microsoft.com/en-us/powershell/module/scheduledtasks/get-scheduledtask?view=win10-ps
[4] https://youtu.be/gBtSkJePt0s
[5] https://docs.microsoft.com/en-us/powershell/module/scheduledtasks/new-scheduledtaskprincipal?view=win10-ps
[6] https://dog-developers.tistory.com/183
[7] https://www.powershellgallery.com/packages/beam.serverside/0.0.6/Content/functions%5Cnew-task.ps1

Must [4]
----
PS >> Set-ExecutionPolicy RemoteSigned

Note
----
. Get-ScheduledTask -TaskName Google* returns all tasks that start with Google.
  Get-ScheduledTask -TaskPath \ returns all tasks that are placed in the TaskPath root. [2, 3]

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


#############################################################################

$my_collection_name     = "pa_fab.foundry_fab_inspection_item_reference"


if (("pa_fab.foundry_fab_inspection_wf", "pa_fab.foundry_fab_wip_status_history",
     "pa_fab.foundry_et_test").contains($my_collection_name)) {
    $my_start_times        = @("00:00am")
    $my_duration_minutes   = 1440 - 5  # 1 day - 5 min
    $my_repetition_minutes = 5
} elseif ($my_collection_name -eq "pa_fab.foundry_mi_reticle") {
    $my_start_times        = @("04:00am")
    $my_duration_minutes   = 60
    $my_repetition_minutes = 5
} elseif ($my_collection_name -eq "pa_fab.foundry_fab_inspection_item_reference") {
    $my_start_times        = @("00:00am")
    $my_duration_minutes   = 1440 - 60
    $my_repetition_minutes = 60
} elseif (("pa_fab.foundry_einecn_document", "pa_fab.foundry_einecn_applied_lot"
    ).contains($my_collection_name)) {
    $my_start_times        = @("01:00am")
    $my_duration_minutes   = 60
    $my_repetition_minutes = 10
}

#---------------------------------------------------------------------------#

$python_exe = "pythonw.exe"
$python_exe = "c:\Y\Anaconda3\envs\python374\python.exe"
$script_file_name = "PASystem_upload_ftp2.py"
$task_name = "PASystem_upload_ftp2^" + $my_collection_name
$task_path = "PASystem"

#############################################################################

$script_file_path = Join-Path -Path $PSScriptRoot -ChildPath $script_file_name
$Action = New-ScheduledTaskAction -Execute $python_exe -Argument """$script_file_path"" $my_collection_name"
# $Action = New-ScheduledTaskAction -Execute $python_exe `
#    -Argument "-WindowStyle Hidden -File ""$script_file_path"" $my_collection_name"

$triggers = @()
foreach ( $start_time in $my_start_times ) {
    $trigger_main = New-ScheduledTaskTrigger -Daily -At $start_time
    $trigger_sub = New-ScheduledTaskTrigger -Once -At $start_time `
        -RepetitionDuration (New-TimeSpan -Minutes $my_duration_minutes) `
        -RepetitionInterval (New-TimeSpan -Minutes $my_repetition_minutes)
    $trigger_main.Repetition = $trigger_sub.Repetition
    $trigger_main.Repetition.StopAtDurationEnd = $false
    $triggers += $trigger_main
}

$Settings = New-ScheduledTaskSettingsSet -Priority 0
$Task = New-ScheduledTask -Action $Action -Trigger $triggers -Settings $Settings
$params = @{
    'TaskName' = $task_name;
    'TaskPath' = $task_path;
    'InputObject' = $Task;
}
remove_registered_task $task_name
Register-ScheduledTask @params
confirm_registered_task $task_name $task_path

"^^Y .."

