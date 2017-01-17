#include "include/directoryexplorer.h"

using namespace std;

unordered_set<string> get_all_images(const string& root)
{
    return get_all_images(QDir(QString(root.c_str())), unordered_set<string>());
}

unordered_set<string> get_all_images(const QDir& dir, unordered_set<std::string>& paths)
{
    QFileInfoList infos = dir.entryInfoList(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

    foreach(QFileInfo info, infos)
    {
        if(info.isDir())
            return get_all_images(info.absoluteFilePath(), paths);

        else if(info.isFile())
        {
            if(is_image(info.absoluteFilePath().toStdString()))
                paths.insert(info.absoluteFilePath().toStdString());
        }
    }

    return paths;
}

bool is_image(const std::string& path)
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
