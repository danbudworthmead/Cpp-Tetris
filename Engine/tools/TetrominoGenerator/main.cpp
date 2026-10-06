#include <filesystem>
#include <fstream>
#include <lodepng.h>
#include <iostream>
#include <print>

namespace
{
    struct Pixel
    {
        unsigned char r, g, b, a;
    };
    
    struct Tetromino
    {
        unsigned width, height;
        std::vector<Pixel> pixels;
        std::string file_name;
    };
    
    [[nodiscard]]
    std::optional<Tetromino> load_tetromino(const std::filesystem::path& file_path)
    {
        unsigned char* image = {};
        unsigned width = {};
        unsigned height = {};

        const unsigned error = lodepng_decode32_file(
            &image,
            &width,
            &height,
            file_path.string().c_str()
        );

        if (error)
        {
            std::println("ERROR {}: {}", error, lodepng_error_text(error));
            return std::nullopt;
        }
        
        const std::string parent_directory = file_path.parent_path().generic_string();
        const std::string file_name = file_path.filename().generic_string();
        std::stringstream out_file_name;
        out_file_name << parent_directory.substr(parent_directory.find_last_of("/") + 1);
        out_file_name << file_name.substr(0, file_name.find_first_of("."));
    
        Pixel* pixels = reinterpret_cast<Pixel*>(image);
        Tetromino result 
        {
            .width = width,
            .height = height,
            .pixels = std::vector<Pixel>(pixels, pixels + static_cast<size_t>(width * height)), // copy the pixels data#
            .file_name = out_file_name.str(),
        };
        
        free(image);
        
        return result;
    }
    
    void bake(const Tetromino& tetromino)
    {
        const std::string parent_folder("Tetrominos");
        std::filesystem::create_directories(parent_folder);
        std::ofstream output(std::format("{}/{}.h", parent_folder, tetromino.file_name));

        output << "#pragma once\n\n";
        output << "namespace Tetromino\n";
        output << "{\n";

        output << "    constexpr unsigned Width = "
               << tetromino.width << ";\n";

        output << "    constexpr unsigned Height = "
               << tetromino.height << ";\n\n";

        output << "    constexpr unsigned char Pixels[] =\n";
        output << "    {\n";

        for (const Pixel& pixel : tetromino.pixels)
        {
            output << "        "
                   << static_cast<unsigned>(pixel.r) << ", "
                   << static_cast<unsigned>(pixel.g) << ", "
                   << static_cast<unsigned>(pixel.b) << ", "
                   << static_cast<unsigned>(pixel.a) << ",\n";
        }

        output << "    };\n";
        output << "}\n";
    }
}

int main(const int argc, char *argv[]) {
    if (argc != 2)
    {
        std::println("ERROR: Incorrect number of arguments");
        return 1;
    }
    
    const char* file_path = argv[1];
    
    if (const std::optional<Tetromino> tetromino = load_tetromino(file_path); tetromino.has_value())
    {
        bake(tetromino.value());
    }
    
    return 0;
}
