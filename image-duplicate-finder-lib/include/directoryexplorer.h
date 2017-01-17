#ifndef DIRECTORYEXPLORER_H
#define DIRECTORYEXPLORER_H

#include <string>
#include <unordered_set>
#include <QDir>
#include <QFileInfo>
#include <fstream>
#include "imagetype.h"

#define IMAGE_MAGIC_NUMBER 16

std::unordered_set<std::string> get_all_images(const std::string&);
std::unordered_set<std::string> get_all_images(const QDir&, std::unordered_set<std::string>&);

bool is_image(const std::string&);

ImageFileType get_image_type(const uint8_t*, uint32_t);

#endif // DIRECTORYEXPLORER_H
