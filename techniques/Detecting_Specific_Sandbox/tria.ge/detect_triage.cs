private static bool detect_triage()
{
    
    string triage_wallpaper = System.Environment.GetEnvironmentVariable("USERPROFILE") + "\\Pictures\\My Wallpaper.jpg";

    return File.Exists(triage_wallpaper);

}