#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <filesystem> // For std::filesystem::current_path

#include "alloc/general_allocation.h"
#include "metadata/pe_image_reader.h"
#include "utils/mem_pool.h"
#include "metadata/module_def.h"
#include "vm/assembly.h"
#include "vm/settings.h"
#include "vm/runtime.h"

using namespace leanclr;

// Global library search directories
static std::vector<std::string> g_lib_dirs;
static RtResult<utils::Span<byte>> assembly_file_loader(const char* assembly_name)
{
    for (const auto& dir : g_lib_dirs)
    {
        std::string file_path = dir + "/" + assembly_name + ".dll";
        std::ifstream dll_file(file_path, std::ios::binary | std::ios::ate);
        if (!dll_file.is_open())
        {
            continue; // Try next directory
        }

        std::streamsize file_size = dll_file.tellg();
        dll_file.seekg(0, std::ios::beg);

        auto* dll_data = static_cast<uint8_t*>(alloc::GeneralAllocation::malloc(file_size));
        if (!dll_data)
        {
            return RtErr::OutOfMemory;
        }

        if (!dll_file.read(reinterpret_cast<char*>(dll_data), file_size))
        {
            alloc::GeneralAllocation::free(dll_data);
            continue;
        }
        dll_file.close();

        return utils::Span<byte>(dll_data, static_cast<size_t>(file_size));
    }

    return RtErr::FileNotFound;
}

static void setup_default_lib_dirs()
{
    g_lib_dirs.push_back("."); // Current directory
    std::string cur_dir = std::filesystem::current_path().string();

    std::string library_dir;
    size_t pos = cur_dir.find("samples");
    if (pos != std::string::npos)
    {
        library_dir = cur_dir.substr(0, pos) + "/libraries";
        g_lib_dirs.push_back(library_dir + "/netframework4.x"); // Example additional directory
    }
    for (const auto& dir : g_lib_dirs)
    {
        std::cout << "Library search directory: " << dir << std::endl;
    }
}

int main()
{
    setup_default_lib_dirs();

    vm::Settings::set_assembly_loader(assembly_file_loader);
    auto result = vm::Runtime::initialize();
    if (result.is_err())
    {
        std::cout << "Failed to initialize runtime, error: " << static_cast<int>(result.unwrap_err()) << std::endl;
        return -1;
    }
    auto corlib = vm::Assembly::get_corlib();
    std::cout << "Corlib assembly loaded successfully." << corlib << std::endl;
    return 0;
}
