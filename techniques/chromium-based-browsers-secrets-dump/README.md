<div align="center">
  <h1><code>Rust Chromium Based Browsers Secrets Dump</code></h1>
  <p>This Rust project is a utility to extract and decrypt sensitive data such as passwords, credit card information and cookies from various Chromium-based browsers on Windows systems. The extracted data includes information from the Login Data and Web Data databases used by browsers like Chrome, Edge, and others.</p>
</div>

---

## Overview
The utility performs the following steps:

1. **Locate Browser Data**: Identifies the paths to the local state and database files of various Chromium-based browsers.
2. **Decrypt Secret Key**: Decrypts the encryption key used by the browser, which is stored in the `Local State` file.
3. **Connect to Databases**: Establishes connections to the SQLite databases containing encrypted user data.
4. **Decrypt and Display Data**: Extracts and decrypts the sensitive data (such as passwords, credit card numbers and cookies) from the databases.

---

## List of supported browsers
The utility supports the following Chromium-based browsers:

- Avast
- Amigo
- Torch
- Kometa
- Orbitum
- Cent Browser
- 7star
- Sputnik
- Vivaldi
- Google Chrome sxs
- Google Chrome
- Epic Privacy Browser
- Microsoft Edge
- Uran
- Yandex
- Brave Browser
- Iridium

---
## Key Components
1. Path Detection
`get_paths()`: Searches for known paths where different Chromium-based browsers store their user data.

2. Key Decryption
`get_secret_key()`: Decrypts the browser's master key stored in the Local State file using the Windows Data Protection API (DPAPI).

3. Database Connection
`get_db_connection()`: Copies the relevant SQLite database and connects to it.

4. Data Querying and Decryption
`query_data()`: Executes SQL queries on the databases to retrieve and decrypt sensitive information such as login credentials and credit card details.

5. AES-GCM Decryption
`aes_gcm_256()`: Uses AES-GCM to decrypt encrypted data using the extracted master key.

---

## Usage
Prerequisites
- Rust Toolchain: Ensure you have Rust installed. You can install it from rust-lang.org.
- Windows OS: This tool utilizes the Windows Data Protection API (DPAPI), so it must be run on a Windows system.

### Build and Run
Clone the Repository:

```bash
git clone https://github.com/Fastiraz/chromium-based-browsers-secrets-dump.git
cd chromium-based-browsers-secrets-dump
```

Run the Project:

```bash
cargo add serde_json base64 hex winapi regex rusqlite aes_gcm
cargo run
```

---

## Output
The utility prints the extracted data in the console. For each detected browser profile, it will show:

- Logins
  - URL
  - Email addresses
  - Passwords
- Credit cards
  - Card number
  - Expiration date
  - Name on card
- Cookies

Example Output
```rust
Processing: C:\Users\username\AppData\Local\Google\Chrome\User Data
Executing query 'logins' for Login Data
["https://example.com/login", "user@example.com", "password123"]

Executing query 'credit_cards' for Web Data
["John Doe", "1234 1234 1234 1234", "12", "2024", "1633027200"]

Executing query 'cookies' for Network\Cookies
[".example.com", "session_id", "/", "cookie_value123", "1633027200"]

Processing: C:\Users\username\AppData\Local\Microsoft\Edge\User Data
Executing query 'logins' for Login Data
["https://example.com/login", "user@example.com", "password456"]

Executing query 'credit_cards' for Web Data
["Jane Smith", "5555555555554444", "6", "2025", "1640985600"]

Executing query 'cookies' for Network\Cookies
[".anotherexample.com", "tracking_id", "/shop", "another_cookie_value456", "1640985600"]

Processing: C:\Users\username\AppData\Local\BraveSoftware\Brave-Browser\User Data
Executing query 'logins' for Login Data
["https://brave.example.com/login", "braveuser@example.com", "bravepassword"]

Executing query 'credit_cards' for Web Data
["Alex Johnson", "378282246310005", "8", "2026", "1656806400"]

Executing query 'cookies' for Network\Cookies
[".brave.example.com", "auth_token", "/", "brave_cookie_value789", "1656806400"]
```

---

## Security Considerations
- **Use Responsibly**: This tool should be used ethically and with the consent of the data owner. Unauthorized access to data is illegal.
- **Handle Data Securely**: Be cautious with the extracted data, especially if it contains sensitive information.
