#include "kf/kf_log.h"
#include <fstream>
#include <string>
#include <vector>

namespace kf
{

   namespace Log
   {
      LogSystem &getDefault()
      {
         static LogSystem g_default_log;
         return g_default_log;
      }
   }

   LogCallBack::LogCallBack(log_callback_t callback, void *userdata, bool auto_delete):
      m_function(callback),
      m_user_data(userdata),
      m_auto_delete(auto_delete) 
   {
   }

   LogCallBack::~LogCallBack()
   {
      if(m_auto_delete)
      {
         delete m_user_data;
      }
   }
   
   void LogCallBack::call(unsigned int level, const std::string &subsys, const std::string &s)
   {
      m_function(level, subsys, s, m_user_data);
   }

   LogCallBack::log_callback_t LogCallBack::getFunction()
   {
      return m_function;
   }

   void *LogCallBack::getUserData()
   {
      return m_user_data;
   }

   bool LogCallBack::getAutoDelete()
   {
      return m_auto_delete;
   }



   LogEntry::LogEntry(unsigned int level, const std::string &subsys, const std::string &s):
      m_level(level),
      m_subsys(subsys),
      m_text(s)
   {
   }

   LogEntry::~LogEntry()
   {
   }

   unsigned int LogEntry::getLevel() const
   {
      return m_level;
   }

   const std::string &LogEntry::getSubSystem() const
   {
      return m_subsys;
   }

   const std::string &LogEntry::getText() const
   {
      return m_text;
   }

   LogSystem::LogSystem(unsigned int level): m_min_level(level)
   {
   }

   LogSystem::~LogSystem()
   {
   }

   void LogSystem::log(unsigned int level, const std::string &subsys, const std::stringstream &ss)
   {
      log(level, subsys, ss.str());
   }

   void LogSystem::log(unsigned int level, const std::string &subsys, const std::string &s)
   {
      if(level<m_min_level)
      {
         return;
      }
      if(m_callbacks.size()==0)
      {
         m_cached_entries.push_back(new LogEntry(level, subsys, s));
         return;
      }
      for(std::vector<LogCallBack *>::iterator it = m_callbacks.begin(); it != m_callbacks.end(); ++it)
      {
         (*it)->call(level, subsys, s);
      }
   }

   void LogSystem::setMinLevel(unsigned int level)
   {
      m_min_level = level;
   }

   unsigned int LogSystem::getMinLevel() const
   {
      return m_min_level;
   }

   void LogSystem::addCallBack(LogCallBack::log_callback_t func, void *userdata, bool auto_delete)
   {
      m_callbacks.push_back(new LogCallBack(func, userdata, auto_delete));
      if(m_cached_entries.size()>0)
      {
         for(unsigned int i=0;i<m_cached_entries.size();i++)
         {
            func(m_cached_entries[i]->getLevel(),m_cached_entries[i]->getSubSystem(),m_cached_entries[i]->getText(), userdata);
            delete m_cached_entries[i];
         }
         m_cached_entries.clear();
      }
   }

   void LogSystem::removeCallBack(LogCallBack::log_callback_t func, void *userdata)
   {
      for(std::vector<LogCallBack *>::iterator it = m_callbacks.begin(); it != m_callbacks.end(); ++it)
      {
         if(func == (*it)->getFunction() && userdata == (*it)->getUserData())
         {
            if((*it)->getAutoDelete())
            {
               delete (*it)->getUserData();
            }
            m_callbacks.erase(it);
            return;
         }
      }
   }

   class LogFileInfo
   {
   public:
      LogFileInfo(std::fstream *file, unsigned int min_level, unsigned int max_level):
         m_file(file), m_min_level(min_level), m_max_level(max_level)
      {
      }
      ~LogFileInfo()
      {
         delete m_file;
      }
      std::fstream *m_file;
      unsigned int m_min_level;
      unsigned int m_max_level;
   };

   void logToCout(unsigned int level, const std::string &subsys, const std::string &s, void *userdata)
   {
      if(level >= ((std::pair<unsigned int, unsigned int>*)userdata)->first && level <= ((std::pair<unsigned int, unsigned int>*)userdata)->second)
      {
		 if(subsys == "General")
			std::cout << s;
		 else
			std::cout << subsys << ": " << s;
         std::cout.flush();
      }
   }

   void logToFile(unsigned int level, const std::string &subsys, const std::string &s, void *userdata)
   {
      if(((LogFileInfo *)userdata)->m_file->is_open())
      {
		 if(subsys == "General")
			*(((LogFileInfo *)userdata)->m_file) << s;
		 else
			*(((LogFileInfo *)userdata)->m_file) << (subsys) << ": " << s;
         ((LogFileInfo *)userdata)->m_file->flush();
      }
   }

   void LogSystem::addCout(unsigned int min_level, unsigned int max_level)
   {
      addCallBack(logToCout,new std::pair<unsigned int, unsigned int>(min_level, max_level), true);
   }

   void LogSystem::addFile(const std::string &filename, unsigned int min_level, unsigned int max_level)
   {
      std::fstream *file = new std::fstream(filename.c_str(), std::ios::out);
      if(file->is_open())
      {
         addCallBack(logToFile, new LogFileInfo(file, min_level, max_level), true);
      }
   }
}
