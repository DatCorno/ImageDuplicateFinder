#ifndef DIRECTORYEXPLORER_H
#define DIRECTORYEXPLORER_H

#include <string>
#include <unordered_set>
#include <fstream>
#include "imagetype.h"
#include <experimental/filesystem>


#define IMAGE_MAGIC_NUMBER 16

std::unordered_set<std::string> get_all_images(const std::string&);
std::unordered_set<std::string> get_all_images(const std::experimental::filesystem::path&, std::unordered_set<std::string>&);

bool is_image(const const std::experimental::filesystem::path&&);

ImageFileType get_image_type(const uint8_t*, uint32_t);

#endif // DIRECTORYEXPLORER_H
