# WMI Event Subscription

# Authorship Information

* Issac Briones (@1d8)
* https://1d8.github.io
* https://github.com/1d8
* https://linkedin.com/in/icyber

# Technique Information

* Technique Title: WMI Event Subscriptions
* Technique Category (required): Sandbox Evasion
* Technique Description: Adversaries may leverage WMI event subscriptions to evade detection by triggering malicious actions only under specific conditions that are unlikely to occur in a sandboxed environment. For instance, a threat actor might configure an event subscription to monitor file system, network, or logon activity, ensuring that their second-stage payload is only downloaded and executed when a particular event suggests real user activity, thereby bypassing automated analysis

# Additional Resources
* https://attack.mitre.org/techniques/T1546
* https://github.com/1d8/offsec/tree/main/persistence/windows/wmi-event-subscription
