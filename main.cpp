#define _CRT_SECURE_NO_WARNINGS // remove warning issues
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

std::mutex mtx;

void convert_png_to_jpg(const std::string& input_path, const std::string& output_path) {
    int width, height, channels;
    unsigned char* img = stbi_load(input_path.c_str(), &width, &height, &channels, 0);
    if (img) {
        stbi_write_jpg(output_path.c_str(), width, height, channels, img, 95);
        stbi_image_free(img);
    } else {
        std::unique_lock<std::mutex> lock(mtx);
        std::cerr << "Error: Failed to read image file: " << input_path << std::endl;
        std::cerr << "Reason: " << stbi_failure_reason() << std::endl;
    }
}

void process_image(const std::filesystem::directory_entry& entry) {
    if (entry.is_regular_file() && entry.path().extension() == ".png") {
        std::string output_path = entry.path().stem().string() + ".jpg";
        {
            std::unique_lock<std::mutex> lock(mtx);
            std::cout << "Converting: " << entry.path() << " to " << output_path << std::endl;
        }
        convert_png_to_jpg(entry.path().string(), output_path);
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: ./png2jpg <folder_path>" << std::endl;
        return 1;
    }

    std::string folder_path(argv[1]);
    std::vector<std::thread> threads;

    std::cout << "Starting the conversion process..." << std::endl;
    std::cout << "Folder path: " << folder_path << std::endl; // Line Added

    int files_processed = 0; // Line added

    for (const auto& entry : std::filesystem::directory_iterator(folder_path)) {
        if (threads.size() >= 8) {
            for (auto& t : threads) {
                t.join();
            }
            threads.clear();
        }

        threads.emplace_back(process_image, entry);
        files_processed++; // Line added
    }

    for (auto& t : threads) {
        t.join();
    }

    if (files_processed == 0) { // Line added
        std::cout << "No PNG files found in the folder." << std::endl;
    } else {
        std::cout << "Finished converting PNGs to JPGs." << std::endl;
    }

    return 0;
}
