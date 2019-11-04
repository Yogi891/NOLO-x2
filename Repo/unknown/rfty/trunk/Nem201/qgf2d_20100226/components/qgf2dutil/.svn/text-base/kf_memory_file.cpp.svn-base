#include "kf/kf_memory_file.h"

namespace kf
{

   MemFile::MemFile()
   {
      m_handle_file = INVALID_HANDLE_VALUE;
      m_handle_map = INVALID_HANDLE_VALUE;
      m_read_only = true;
      m_size = 0;
   }

   MemFile::MemFile(const std::string &name, bool read_only, bool create_new, dword size)
   {
      if(create_new)
      {
         create(name, size);
      }
      else
      {
         open(name, read_only);
      }
   }

   MemFile::~MemFile()
   {
      close();
   }

   void MemFile::close()
   {
      if(m_handle_map != INVALID_HANDLE_VALUE)
      {
         CloseHandle(m_handle_map);
         m_handle_map = INVALID_HANDLE_VALUE;
      }
      if(m_handle_file != INVALID_HANDLE_VALUE)
      {
         CloseHandle(m_handle_file);
         m_handle_file = INVALID_HANDLE_VALUE;
      }
   }

   bool MemFile::open(const std::string &name, bool read_only)
   {
      OFSTRUCT of;

      m_handle_file = INVALID_HANDLE_VALUE;
      m_handle_map = INVALID_HANDLE_VALUE;
      m_read_only = read_only;
      m_size = 0;
      m_mem_block.setRange(NULL, 0);
      m_name = name;

      m_handle_file = (HANDLE)OpenFile(m_name.c_str(), &of, (read_only ? OF_READ : OF_READWRITE));
      if(m_handle_file != INVALID_HANDLE_VALUE)
      {
         m_size=GetFileSize(m_handle_file, NULL);
         return map();
      }
      return false;
   }

   bool MemFile::map()
   {
      m_handle_map = CreateFileMapping(m_handle_file, NULL, (m_read_only ? PAGE_READONLY : PAGE_READWRITE), 0, m_size, NULL);
      if(m_handle_map != INVALID_HANDLE_VALUE)
      {
         void *vp;
         vp = MapViewOfFile(m_handle_map, (m_read_only ? FILE_MAP_READ : FILE_MAP_WRITE), 0, 0, m_size);
         if(vp)
         {
            m_mem_block.setRange((byte *)vp, m_size);
            return true;
         }
      }
      return false;
   }

   bool MemFile::create(const std::string &name, dword size)
   {
      m_handle_file = INVALID_HANDLE_VALUE;
      m_handle_map = INVALID_HANDLE_VALUE;
      m_read_only = false;
      m_size = size;
      m_mem_block.setRange(NULL, 0);
      m_name = name;

      m_handle_file = CreateFile (name.c_str(),
         GENERIC_WRITE | GENERIC_READ,
         FILE_SHARE_WRITE,
         NULL,
         CREATE_ALWAYS,
         FILE_ATTRIBUTE_NORMAL,
         NULL);
      if(m_handle_file != INVALID_HANDLE_VALUE)
      {
         return map();
      }
      return false;
   }

   bool MemFile::is_good() const
   {
      return m_handle_map != INVALID_HANDLE_VALUE;
   }

   MemBlock MemFile::get_block()
   {
      return m_mem_block;
   }

}
