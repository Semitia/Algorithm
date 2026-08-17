[CmdletBinding()]
param(
    [switch]$Clear
)

$variableName = 'LEETCODE_SESSION'

if ($Clear) {
    [Environment]::SetEnvironmentVariable($variableName, $null, 'User')
    Write-Host 'LEETCODE_SESSION has been removed from the current Windows user environment.'
    Write-Host 'Restart ChatGPT/Codex before using this project again.'
    exit 0
}

$secureSession = Read-Host 'Paste the LEETCODE_SESSION cookie value' -AsSecureString
$credential = [PSCredential]::new('leetcode', $secureSession)
$session = $credential.GetNetworkCredential().Password

if ([string]::IsNullOrWhiteSpace($session)) {
    throw 'The cookie value cannot be empty.'
}

[Environment]::SetEnvironmentVariable($variableName, $session, 'User')
$session = $null

Write-Host 'LEETCODE_SESSION has been saved to the current Windows user environment.'
Write-Host 'Restart ChatGPT/Codex so the MCP server can read it.'
