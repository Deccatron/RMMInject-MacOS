#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/stat.h>
#include <libgen.h>
#include <filesystem>

// Just a check if the file even fucking exists :)
bool file_exists(const char* path) {
    struct stat buffer;
    return (stat(path, &buffer) == 0 && access(path, R_OK) == 0);
}

bool has_dylib_extension(const char* path) {
    std::string str_path(path);
    return str_path.length() >= 6 && str_path.substr(str_path.length() - 6) == ".dylib";
}

// Dylib inject func n shi
bool inject_dylib(const char* dylib_path, const char* target_app_path) {
  
    if (!dylib_path || !target_app_path) {
        std::cerr << "Error: Invalid path provided\n";
        return false;
    }
    
    // Yet another check never would have guessed it...
    if (!file_exists(dylib_path)) {
        std::cerr << "Error: Dylib file does not exist or is not readable: " << dylib_path << "\n";
        return false;
    }

    // Check if the app even fucking exists
    if (!file_exists(target_app_path) || access(target_app_path, X_OK) != 0) {
        std::cerr << "Error: Target application does not exist or is not executable: " << target_app_path << "\n";
        return false;
    }

    // Validate dylib extension
    if (!has_dylib_extension(dylib_path)) {
        std::cerr << "Error: File does not have .dylib extension: " << dylib_path << "\n";
        return false;
    }

    // Set DYLD_INSERT_LIBRARIES as environment variable
    if (setenv("DYLD_INSERT_LIBRARIES", dylib_path, 1) != 0) {
        std::cerr << "Error: Failed to set DYLD_INSERT_LIBRARIES: " << strerror(errno) << "\n";
        return false;
    }

    // Set DYLD_FORCE_FLAT_NAMESPACE for compatibility stuff
    if (setenv("DYLD_FORCE_FLAT_NAMESPACE", "1", 1) != 0) {
        std::cerr << "Error: Failed to set DYLD_FORCE_FLAT_NAMESPACE: " << strerror(errno) << "\n";
        return false;
    }

    std::cout << "Injecting dylib: " << dylib_path << " into: " << target_app_path << "\n";

    // Launch Roblox
    if (execl(target_app_path, target_app_path, (char*)nullptr) == -1) {
        std::cerr << "Error: Failed to launch target application: " << strerror(errno) << "\n";
        return false;
    }

    return true;
}

void print_usage(const char* program_name) {
    std::cerr << "Usage: " << program_name << " <dylib_path> <target_app_path>\n";
    std::cerr << "Example: " << program_name << " /path/to/mydylib.dylib /Applications/Roblox.app/Contents/MacOS/RobloxPlayer\n";
}

int main(int argc, char* argv[]) {
    // Hardcoded path to the Dumper.dylib
    const char* dylib_path = "Just put your hardoded path to your dylib here!";
    // Default target application path (you can change this if you want)
    const char* target_app_path = "/Applications/Roblox.app/Contents/MacOS/RobloxPlayer";

    std::cout << "Using paths:\n";
    std::cout << "Dylib: " << dylib_path << "\n";
    std::cout << "Target: " << target_app_path << "\n";

    // Inject the dylib
    if (!inject_dylib(dylib_path, target_app_path)) {
        std::cerr << "Failed to inject dylib\n";
        print_usage(argv[0]);
        return 1;
    }

    return 0;
}
