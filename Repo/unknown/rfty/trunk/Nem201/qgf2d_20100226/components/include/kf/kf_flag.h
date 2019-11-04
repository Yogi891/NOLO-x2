#ifndef KF_FLAG_HEADER
#define KF_FLAG_HEADER
#include "vector"
#include "iostream"
#include "string"
#include "kf/kf_types.h"

namespace kf
{
   class KF_API Flag
   {
   public:
      Flag():m_value(0),m_mask(0),m_text("") { }
      Flag(unsigned int flagmask, unsigned int flagvalue, const std::string &flagname):m_value(flagvalue),m_mask(flagmask),m_text(flagname) { }
      Flag(unsigned int flagmask, unsigned int flagvalue):m_value(flagvalue),m_mask(flagmask)
      {
         char buf[100];
         sprintf(buf,"%x",flagvalue);
         m_text = buf;
      }

      unsigned int m_value;
      unsigned int m_mask;
      std::string m_text;
   };

   class KF_API FlagGroup
   {
   public:
      std::vector<Flag> m_flags;
      void addFlag(unsigned int flagmask, unsigned int flagvalue, const std::string &flagname);
      std::string toString(unsigned int value);

   };

}
#endif
