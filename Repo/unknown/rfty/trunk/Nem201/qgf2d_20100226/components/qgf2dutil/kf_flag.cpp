#include "kf/kf_flag.h"

namespace kf
{
   void FlagGroup::addFlag(unsigned int flagmask, unsigned int flagvalue, const std::string &flagname)
   {
      m_flags.push_back(Flag(flagmask,flagvalue,flagname));
   }

   std::string FlagGroup::toString(unsigned int value)
   {
      std::string text;
      bool first=true;
      for(int i=0;i<m_flags.size();i++)
      {
         if((value & m_flags[i].m_mask) == m_flags[i].m_value)
         {
            if(!first)
            {
               text += " | ";
            }
            else
            {
               first = false;
            }
            text += m_flags[i].m_text;
         }
      }
      return text;
   }
}