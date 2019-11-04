#ifndef KF_FILE_HEADER
#define KF_FILE_HEADER
#include "vector"
#include "iostream"
#include "string"
#include "kf/kf_types.h"

namespace kf
{
	
	class KF_API Path
	{
	public:
		Path()
		{
			m_absolute = false;
		}
		~Path()
		{
		}
		Path(const std::string &s)
		{
			m_absolute = false;
			std::string::const_iterator a;
			std::string::const_iterator b;
			a=s.begin();
			for(b=s.begin();b!=s.end();b++)
			{
				if(*b=='/' || *b=='\\')
				{
					if(b==s.begin())
					{
						m_absolute = true;
					}
					if(a!=b)
					{
						m_path.push_back(std::string(a,b));
						a=b+1;
					}
					else
					{
						a++;
					}
				}
			}
			if(a!=b)
			{
				m_path.push_back(std::string(a,b));
			}
		}
		Path &operator/(const Path &p)
		{
			if(p.m_absolute)
			{
				m_path = p.m_path;
				m_absolute = p.m_absolute;
				return *this;
			}
			for(std::vector<std::string>::const_iterator it = p.m_path.begin(); it!=p.m_path.end(); it++)
			{
				m_path.push_back(*it);
			}
			return *this;
		}

		Path &operator/(const std::string &s)
		{
			return operator/(Path(s));
		}

		Path normalise() const
		{
			Path p;
			p.m_absolute = m_absolute;
			
			for(std::vector<std::string>::const_iterator it = m_path.begin(); it!=m_path.end(); it++)
			{
				if(*it=="..")
				{
					if(p.m_path.size()>0)
					{
						p.m_path.pop_back();
					}
				}
				else if(*it==".")
				{

				}
				else
				{
					p.m_path.push_back(*it);
				}
				
			}
			return p;

		}
		
		std::string str() const
		{
			std::string s;
			for(std::vector<std::string>::const_iterator it = m_path.begin(); it!=m_path.end(); it++)
			{
				if(it!=m_path.begin() || m_absolute)
				{
					s+="/";
				}
				s+=*it;
			}
			return s;
		}
		
		Path parent() const
		{
			Path p(*this);
			p.m_path.pop_back();
			return p;
			

		}

	protected:
		bool m_absolute;
		std::vector<std::string> m_path;
		friend std::ostream &operator<<(std::ostream &os, const Path &p);
		

	};

	std::ostream &operator<<(std::ostream &os, const Path &p)
	{
		os<<p.str();
		return os;
	}



}

#endif