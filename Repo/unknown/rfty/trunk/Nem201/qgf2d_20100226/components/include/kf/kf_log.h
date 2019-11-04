#ifndef KF_LOG_HEADER
#define KF_LOG_HEADER

#include <iostream>
#include <ostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include "kf/kf_types.h"

#define kf_log_detail(KFLOGMACROTEXT) {std::stringstream tempstream; tempstream<<__FILE__<<"("<<kf::dword(__LINE__)<<") : "<<KFLOGMACROTEXT<<std::endl; kf::Log::getDefault().log(0, "General", tempstream);}
#define kf_log_detail2(KFLOGMACROLEVEL, KFLOGMACROTEXT) {std::stringstream tempstream; tempstream<<__FILE__<<"("<<kf::dword(__LINE__)<<") : "<<KFLOGMACROTEXT<<std::endl; kf::Log::getDefault().log(KFLOGMACROLEVEL, "General", tempstream);}
#define kf_log_detail3(KFLOGMACROLEVEL, KFLOGMACROSUBSYS, KFLOGMACROTEXT) {std::stringstream tempstream; tempstream<<__FILE__<<"("<<kf::dword(__LINE__)<<") : "<<KFLOGMACROTEXT<<std::endl; kf::Log::getDefault().log(KFLOGMACROLEVEL, KFLOGMACROSUBSYS, tempstream);}
#define kf_log(KFLOGMACROTEXT) {std::stringstream tempstream; tempstream<<KFLOGMACROTEXT<<std::endl; kf::Log::getDefault().log(0, "General", tempstream);}
#define kf_log2(KFLOGMACROLEVEL, KFLOGMACROTEXT) {std::stringstream tempstream; tempstream<<KFLOGMACROTEXT<<std::endl; kf::Log::getDefault().log(KFLOGMACROLEVEL, "General", tempstream);}
#define kf_log3(KFLOGMACROLEVEL, KFLOGMACROSUBSYS, KFLOGMACROTEXT) {std::stringstream tempstream; tempstream<<KFLOGMACROTEXT<<std::endl; kf::Log::getDefault().log(KFLOGMACROLEVEL, KFLOGMACROSUBSYS, tempstream);}
#define kf_log_no_lf(KFLOGMACROTEXT) {std::stringstream tempstream; tempstream<<KFLOGMACROTEXT; kf::Log::getDefault().log(0, "General", tempstream);}
#define kf_log_no_lf2(KFLOGMACROLEVEL, KFLOGMACROTEXT) {std::stringstream tempstream; tempstream<<KFLOGMACROTEXT; kf::Log::getDefault().log(KFLOGMACROLEVEL, "General", tempstream);}
#define kf_log_no_lf3(KFLOGMACROLEVEL, KFLOGMACROSUBSYS, KFLOGMACROTEXT) {std::stringstream tempstream; tempstream<<KFLOGMACROTEXT; kf::Log::getDefault().log(KFLOGMACROLEVEL, KFLOGMACROSUBSYS, tempstream);}

namespace kf
{
   class KF_API LogCallBack
   {
   public:
      typedef void (*log_callback_t)(unsigned int level, const std::string &subsys, const std::string &s, void *userdata);
      LogCallBack(log_callback_t, void *userdata=NULL, bool auto_delete=false);
      ~LogCallBack();
      void call(unsigned int level, const std::string &subsys, const std::string &s);
      log_callback_t getFunction();
      void *getUserData();
      bool getAutoDelete();
   protected:
      log_callback_t m_function;
      void *m_user_data;
      bool m_auto_delete;
   };

   class KF_API LogEntry
   {
   public:
      LogEntry(unsigned int level, const std::string &subsys, const std::string &s);
      ~LogEntry();
      unsigned int getLevel() const;
      const std::string &getSubSystem() const;
      const std::string &getText() const;
   protected:
      unsigned int m_level;
      std::string m_subsys;
      std::string m_text;
   };

   class KF_API LogSystem
   {
   public:
      LogSystem(unsigned int level = 0);
      ~LogSystem();
      void log(unsigned int level, const std::string &subsys, const std::stringstream &ss);
      void log(unsigned int level, const std::string &subsys, const std::string &s);
      void setMinLevel(unsigned int level);
      unsigned int getMinLevel() const;
      void addCallBack(LogCallBack::log_callback_t func, void *userdata=NULL, bool auto_delete=false);
      void removeCallBack(LogCallBack::log_callback_t func, void *userdata);
      void removeCallBack(LogCallBack::log_callback_t func);
      void addCout(unsigned int min_level=0, unsigned int max_level=0xffffffff);
      void addFile(const std::string &filename, unsigned int min_level=0, unsigned int max_level=0xffffffff);
   protected:
      std::stringstream m_log_stream_cache;
      std::vector<LogCallBack *> m_callbacks;
      std::vector<LogEntry *> m_cached_entries;
      unsigned int m_min_level;
   };

   namespace Log
   {
      KF_API LogSystem &getDefault();
   }
}

#endif
