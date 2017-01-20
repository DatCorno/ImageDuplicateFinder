#include "directoryexplorer.h"

using namespace std;
namespace fs = std::experimental::filesystem;

unordered_set<string> get_all_images(const string& root)
{
    return get_all_images(fs::path(root), unordered_set<string>());
}

unordered_set<string> get_all_images(const fs::path& top_level_dir, unordered_set<std::string>& paths)
{
    for(auto& dir_entry: fs::recursive_directory_iterator(top_level_dir))
    {
        if(fs::is_directory(dir_entry.status())
            continue;

        else if(fs::is_regular_file(dir_entry.status()))
        {
            if(is_image(dir_entry.path())
                paths.insert(dir_entry.path());
        }
    }

    return paths;
}

bool is_image(const fs::path& file_path)
{
    ifstream stream(path);
    bool is_image = false;

    if(stream)
    {
        unsigned char data_buffer[IMAGE_MAGIC_NUMBER];

        stream.read((char *)data_buffer, IMAGE_MAGIC_NUMBER);

        ImageFileType file_type = get_image_type(data_buffer, IMAGE_MAGIC_NUMBER);

        is_image = file_type != IMAGE_FILE_INVALID;
    }

    stream.close();

    return is_image;
}

ImageFileType get_image_type(const uint8_t *data, uint32_t len )
{
   if ( len < 16 ) return IMAGE_FILE_INVALID;

   // .jpg:  FF D8 FF
   // .png:  89 50 4E 47 0D 0A 1A 0A
   // .gif:  GIF87a
   //        GIF89a
   // .tiff: 49 49 2A 00
   //        4D 4D 00 2A
   // .bmp:  BM
   // .webp: RIFF ???? WEBP
   // .ico   00 00 01 00
   //        00 00 02 00 ( cursor files )

   switch ( data[0] )
   {
      case (uint8_t)'\xFF':
         return ( !strncmp( (const char*)data, "\xFF\xD8\xFF", 3 )) ?
            IMAGE_FILE_JPG : IMAGE_FILE_INVALID;

      case (uint8_t)'\x89':
         return ( !strncmp( (const char*)data,
                            "\x89\x50\x4E\x47\x0D\x0A\x1A\x0A", 8 )) ?
            IMAGE_FILE_PNG : IMAGE_FILE_INVALID;

      case 'G':
         return ( !strncmp( (const char*)data, "GIF87a", 6 ) ||
                  !strncmp( (const char*)data, "GIF89a", 6 ) ) ?
            IMAGE_FILE_GIF : IMAGE_FILE_INVALID;

      case 'I':
         return ( !strncmp( (const char*)data, "\x49\x49\x2A\x00", 4 )) ?
            IMAGE_FILE_TIFF : IMAGE_FILE_INVALID;

      case 'M':
         return ( !strncmp( (const char*)data, "\x4D\x4D\x00\x2A", 4 )) ?
             IMAGE_FILE_TIFF : IMAGE_FILE_INVALID;

      case 'B':
         return (( data[1] == 'M' )) ?
             IMAGE_FILE_BMP : IMAGE_FILE_INVALID;

      case 'R':
         if ( strncmp( (const char*)data,     "RIFF", 4 ))
            return IMAGE_FILE_INVALID;
         if ( strncmp( (const char*)(data+8), "WEBP", 4 ))
            return IMAGE_FILE_INVALID;
         return IMAGE_FILE_WEBP;

      case '\0':
         if ( !strncmp( (const char*)data, "\x00\x00\x01\x00", 4 ))
            return IMAGE_FILE_ICO;
         if ( !strncmp( (const char*)data, "\x00\x00\x02\x00", 4 ))
            return IMAGE_FILE_ICO;
         return IMAGE_FILE_INVALID;

      default:
         return IMAGE_FILE_INVALID;
   }
}
