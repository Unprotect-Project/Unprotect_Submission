// This code came from a YouTube
// video of John Hammond on how to
// extract plaintext Wi-Fi passwords.
//
// https://www.youtube.com/watch?v=auGJJOfmrMM

#![warn(unused)]
#![warn(deprecated)]
#![warn(unused_variables)]

use std::{ffi::OsString, os::windows::ffi::OsStringExt};
use windows::{
    core::{GUID, HSTRING, PCWSTR, PWSTR},
    Data::Xml::Dom::{XmlDocument, XmlElement},
    Win32::{
        Foundation::{ERROR_SUCCESS, HANDLE, INVALID_HANDLE_VALUE, WIN32_ERROR},
        NetworkManagement::WiFi::{
            WlanCloseHandle, WlanEnumInterfaces, WlanFreeMemory, WlanGetProfile,
            WlanGetProfileList, WlanOpenHandle, WLAN_API_VERSION_2_0, WLAN_INTERFACE_INFO_LIST,
            WLAN_PROFILE_GET_PLAINTEXT_KEY, WLAN_PROFILE_INFO_LIST,
        },
    },
};

fn open_wlan_handle(api_version: u32) -> Result<HANDLE, windows::core::Error> {
    let mut negotiatied_version = 0;
    let mut wlan_handle = INVALID_HANDLE_VALUE;
    let result = unsafe {
        WlanOpenHandle(api_version, None, &mut negotiatied_version, &mut wlan_handle)
    };
    WIN32_ERROR(result).ok()?;
    Ok(wlan_handle)
}

fn enum_wlan_interfaces(handle: HANDLE) -> Result<*mut WLAN_INTERFACE_INFO_LIST, windows::core::Error> {
    let mut interface_ptr = std::ptr::null_mut();
    let result = unsafe {
        WlanEnumInterfaces(handle, None, &mut interface_ptr)
    };
    WIN32_ERROR(result).ok()?;
    Ok(interface_ptr)
}

fn grab_interface_profiles(
    handle: HANDLE,
    interface_guid: &GUID,
) -> Result<*const WLAN_PROFILE_INFO_LIST, windows::core::Error> {
    let mut wlan_profiles_ptr = std::ptr::null_mut();
    let result = unsafe {
        WlanGetProfileList(handle, interface_guid, None, &mut wlan_profiles_ptr)
    };
    WIN32_ERROR(result).ok()?;
    Ok(wlan_profiles_ptr)
}

fn parse_utf16_slice(string_slice : &[u16]) -> Option<OsString> {
    let null_index = string_slice.iter().position(|c| c == &0)?;
    Some(OsString::from_wide(&string_slice[..null_index]))
}

fn load_xml_data(xml: &OsString) -> Result<XmlDocument, windows::core::Error> {
    let xml_document = XmlDocument::new()?;
    xml_document.LoadXml(&HSTRING::from(xml))?;
    Ok(xml_document)
}

fn traverse_xml_tree(xml: &XmlElement, node_path: &[&str]) -> Option<String> {
    let mut subtree_list = xml.ChildNodes().ok()?;
    let last_node_name = node_path.last()?;
    'node_traverse: for node in node_path {
        let node_name = OsString::from_wide(&node.encode_utf16().collect::<Vec<u16>>());
        for subtree_value in &subtree_list {
            let element_name = match subtree_value.NodeName() {
                Ok(name) => name,
                Err(_) => continue,
            };
            if element_name.to_os_string() == node_name {
                if element_name.to_os_string().to_string_lossy().to_string() == last_node_name.to_string() {
                    return Some(subtree_value.InnerText().ok()?.to_string());
                }
                subtree_list = subtree_value.ChildNodes().ok()?;
                continue 'node_traverse;
            }
        }
    }
    None
}

fn get_profile_xml(
    handle: HANDLE,
    interface_guid: &GUID,
    profile_name: &OsString,
) -> Result<OsString, windows::core::Error> {
    let mut profile_xml_data = PWSTR::null();
    let mut profile_get_flags = WLAN_PROFILE_GET_PLAINTEXT_KEY;
    let result = unsafe {
        WlanGetProfile(
            handle,
            interface_guid,
            PCWSTR(HSTRING::from(profile_name).as_ptr()),
            None,
            &mut profile_xml_data,
            Some(&mut profile_get_flags),
            None,
        )
    };
    WIN32_ERROR(result).ok()?;

    let xml_string = match unsafe { profile_xml_data.to_hstring() } {
        Ok(data) => data,
        Err(e) => {
            unsafe { WlanFreeMemory(profile_xml_data.as_ptr().cast())};
            return Err(e);
        }
    };
    Ok(xml_string.to_os_string())
}

fn main() {
    let wlan_handle = open_wlan_handle(WLAN_API_VERSION_2_0).expect("Failed to open WLAN handle!");
    let interface_ptr = match enum_wlan_interfaces(wlan_handle) {
        Ok(interfaces) => interfaces,
        Err(e) => {
            eprintln!("Failed to get the wireless interfaces: {:?}", e);
            unsafe { WlanCloseHandle(wlan_handle, None) };
            std::process::exit(1);
        }
    };

    let interfaces_list = unsafe {
        std::slice::from_raw_parts(
            (*interface_ptr).InterfaceInfo.as_ptr(),
            (*interface_ptr).dwNumberOfItems as usize,
        )
    };

    for interface_info in interfaces_list {
        let interface_description = match parse_utf16_slice(interface_info.strInterfaceDescription.as_slice()) {
            Some(name) => name,
            None => {
                eprintln!("Could net parse our interface description.");
                continue;
            }
        };
        let wlan_profile_ptr = match grab_interface_profiles(wlan_handle, &interface_info.InterfaceGuid) {
            Ok(profiles) => profiles,
            Err(_e) => {
                eprintln!("Failed to retrive profiles");
                continue;
            }
        };
        let wlan_profile_list = unsafe {
            std::slice::from_raw_parts(
                (*wlan_profile_ptr).ProfileInfo.as_ptr(),
                (*wlan_profile_ptr).dwNumberOfItems as usize,
            )
        };

        for profile in wlan_profile_list {
            let profile_name = match parse_utf16_slice(&profile.strProfileName) {
                Some(name) => name,
                None => {
                    eprintln!("Could not parse profile name.");
                    continue;
                }
            };
            let profile_xml_data = match get_profile_xml(wlan_handle, &interface_info.InterfaceGuid, &profile_name) {
                Ok(data) => data,
                Err(_e) => {
                    eprintln!("Failed to extract XML data.");
                    continue;
                }
            };
            let xml_document = match load_xml_data(&profile_xml_data) {
                Ok(xml) => xml,
                Err(_e) => {
                    eprintln!("Failed to extract XML document.");
                    continue;
                }
            };
            let root = match xml_document.DocumentElement() {
                Ok(root) => root,
                Err(_e) => {
                    eprintln!("Failed to get document root for profile XML.");
                    continue;
                }
            };
            let auth_type = match traverse_xml_tree(
                &root,
                &["MSM", "security", "authEncryption", "authentication"]
            ) {
                Some(t) => t,
                None => {
                    eprintln!("Failed to get auth type for this profile.");
                    continue;
                }
            };
            match auth_type.as_str() {
                "open" => {
                    println!("Wi-Fi Name: {}, No password", profile_name.to_string_lossy().to_string());
                },
                "WPA2" | "WPA2PSK" => {
                    if let Some(password) = traverse_xml_tree(&root, &["MSM", "security", "sharedKey", "keyMaterial"]) {
                        println!(
                            "Wi-Fi Name: {}, Authentication: {}, Password: {}",
                            profile_name.to_string_lossy().to_string(),
                            auth_type,
                            password
                        );
                    }
                },
                _ => {
                    println!(
                        "Wi-Fi Name: {}, Authentication {}",
                        profile_name.to_string_lossy().to_string(),
                        auth_type
                    );
                }
            }
        }
    }
    unsafe { WlanFreeMemory(interface_ptr.cast()) };
    unsafe { WlanCloseHandle(wlan_handle, None) };
}
