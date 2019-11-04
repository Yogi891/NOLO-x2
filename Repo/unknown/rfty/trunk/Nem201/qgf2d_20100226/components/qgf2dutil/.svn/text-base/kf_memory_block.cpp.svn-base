#include "kf/kf_memory_block.h"

namespace kf
{
	namespace
	{
		byte bytetohex(byte b)
		{
			if((b&0x0f)<10)
			{
				return '0' + (b&0x0f);
			}
			else
			{
				return 'A' + ((b&0x0f)-10);
			}
		}
	}

	MemBlock::MemBlock()
	{
		m_begin = NULL;
		m_end = NULL;
		m_current = m_begin;
	}

	MemBlock::MemBlock(byte *start, qword length)
	{
		m_begin = start;
		m_end = m_begin + length;
		m_current = m_begin;
	}

	MemBlock::~MemBlock()
	{
	}

	void MemBlock::setRange(byte *start, qword length)
	{
		m_begin = start;
		m_end = m_begin + length;
		m_current = m_begin;
	}

	bool MemBlock::seek(sqword offset, bool relative)
	{
		if(relative)
		{
			if(offset>=0) 
			{
				qword distance = m_end - m_current;
				if((qword)offset <= distance)
				{
					m_current += offset;
					return true;
				}
				else
				{
					m_current += distance;
					return false;
				}
			}
			else
			{
				offset = -offset;
				qword distance = m_current - m_begin;
				if((qword)offset <= distance)
				{
					m_current -= offset;
					return true;
				}
				else
				{
					m_current -= distance;
					return false;
				}
			}
		}
		else
		{
			if(m_end - m_begin > (qword)offset)
			{
				m_current = m_begin + (qword)offset;
				return true;
			}
			else
			{
				m_current = m_end;
				return false;
			}
		}
	}

	MemBlock &MemBlock::operator+=(sqword offset)
	{
		seek(offset, true);
		return *this;
	}

	MemBlock &MemBlock::operator-=(sqword offset)
	{
		seek(offset, true);
		return *this;
	}

	MemBlock &MemBlock::operator++()
	{
		if(m_current != m_end)
		{
			m_current++;
		}
		return *this;
	}

	MemBlock &MemBlock::operator--()
	{
		if(m_current != m_begin)
		{
			m_current--;
		}
		return *this;
	}

	bool MemBlock::operator==(const MemBlock &rhs)
	{
		return m_current == rhs.m_current;
	}

	MemBlock &MemBlock::operator=(const MemBlock &rhs)
	{
		m_current = rhs.m_current;
		m_begin = rhs.m_begin;
		m_end = rhs.m_end;
		return *this;
	}

	MemBlock MemBlock::operator()(int offset, bool relative)
	{
		MemBlock m = *this;
		m.seek(offset, relative);
		return m;
	}

	byte *MemBlock::begin() const
	{
		return m_begin;
	}

	byte *MemBlock::end() const
	{
		return m_end;
	}

	byte *MemBlock::current() const
	{
		return m_current;
	}

	qword MemBlock::size() const
	{
		return (m_end - m_begin);
	}

	qword  MemBlock::getQword(bool move)
	{
		qword nearEnd = m_end - m_current;
		byte *temp = m_current;
		if(nearEnd >= sizeof(qword))
		{
			if(move)
				operator+=(sizeof(qword));
			return *((qword *)temp);
		}
		else
		{
			qword q;
			q = getDword(true);
			q |= getDword(true)<<32;
			if(!move)
			{
				m_current = temp;
			}
			return q;
		}
	}

	sqword  MemBlock::getSqword(bool move)
	{
		qword nearEnd = m_end - m_current;
		byte *temp = m_current;
		if(nearEnd >= sizeof(sqword))
		{
			if(move)
				operator+=(sizeof(sqword));
			return *((sqword *)temp);
		}
		else
		{
			sqword q;
			q = getDword(true);
			q |= getDword(true)<<32;
			if(!move)
			{
				m_current = temp;
			}
			return q;
		}
	}


	dword  MemBlock::getDword(bool move)
	{
		qword nearEnd = m_end - m_current;
		if(nearEnd >= sizeof(dword))
		{
			byte *temp = m_current;
			if(move)
				operator+=(sizeof(dword));
			return *((dword *)temp);
		}
		else if(nearEnd >= 3)
		{
			return get24Bit(move);
		}
		else if(nearEnd >= sizeof(word))
		{
			return getWord(move);
		}
		else if(nearEnd >= sizeof(byte))
		{
			return getByte(move);
		}
		return 0;
	}

	sdword MemBlock::getSdword(bool move)
	{
		qword nearEnd = m_end - m_current;
		if(nearEnd >= sizeof(sdword))
		{
			byte *temp = m_current;
			if(move)
				operator+=(sizeof(sdword));
			return *((sdword *)temp);
		}
		else if(nearEnd >= 3)
		{
			return getS24Bit(move);
		}
		else if(nearEnd >= sizeof(sword))
		{
			return getSword(move);
		}
		else if(nearEnd >= sizeof(sbyte))
		{
			return getSbyte(move);
		}
		return 0;
	}

	dword MemBlock::get24Bit(bool move)
	{
		qword nearEnd = m_end - m_current;
		if(nearEnd >= 3)
		{
			byte *temp = m_current;
			if(move)
				operator+=(3);
			return temp[0]|(temp[1]<<8)|(temp[2]<<16);
		}
		else if(nearEnd >= sizeof(word))
		{
			return getWord(move);
		}
		else if(nearEnd >= sizeof(byte))
		{
			return getByte(move);
		}
		return 0;
	}

	sdword MemBlock::getS24Bit(bool move)
	{
		qword nearEnd = m_end - m_current;
		if(nearEnd >= 3)
		{
			byte *temp = m_current;
			if(move)
				operator+=(3);
			sdword val = temp[0]|(temp[1]<<8)|(temp[2]<<16);
			if(val & 0x800000) val |= 0xff000000;
			return val;
		}
		else if(nearEnd >= sizeof(word))
		{
			return getWord(move);
		}
		else if(nearEnd >= sizeof(byte))
		{
			return getByte(move);
		}
		return 0;
	}

	word MemBlock::getWord(bool move)
	{
		qword nearEnd = m_end - m_current;
		if(nearEnd >= sizeof(word))
		{
			byte *temp = m_current;
			if(move)
				operator+=(sizeof(word));
			return *((word *)temp);
		}
		else if(nearEnd >= sizeof(byte))
		{
			return getByte(move);
		}
		return 0;
	}

	sword  MemBlock::getSword(bool move)
	{
		qword nearEnd = m_end - m_current;
		if(nearEnd >= sizeof(sword))
		{
			byte *temp = m_current;
			if(move)
				operator+=(sizeof(sword));
			return *((sword *)temp);
		}
		else if(nearEnd >= sizeof(sbyte))
		{
			return getSbyte(move);
		}
		return 0;
	}

	byte MemBlock::getByte(bool move)
	{
		qword nearEnd = m_end - m_current;
		if(nearEnd >= sizeof(byte))
		{
			byte *temp = m_current;
			if(move)
				operator+=(sizeof(byte));
			return *((byte *)temp);
		}
		return 0;
	}

	sbyte MemBlock::getSbyte(bool move)
	{
		qword nearEnd = m_end - m_current;
		if(nearEnd >= sizeof(sbyte))
		{
			byte *temp = m_current;
			if(move)
				operator+=(sizeof(sbyte));
			return *((sbyte *)temp);
		}
		return 0;
	}

	float MemBlock::getFloat(bool move)
	{
		qword nearEnd = m_end - m_current;
		if(nearEnd >= sizeof(float))
		{
			byte *temp = m_current;
			if(move)
				operator+=(sizeof(float));
			return *((float *)temp);
		}
		return 0.0f;
	}

	double MemBlock::getDouble(bool move)
	{
		qword nearEnd = m_end - m_current;
		if(nearEnd >= sizeof(double))
		{
			byte *temp = m_current;
			if(move)
				operator+=(sizeof(double));
			return *((double *)temp);
		}
		return 0.0;
	}

	void MemBlock::getBlock(byte *destination, dword length, bool move)
	{
		byte *temp = m_current;
		operator+=(length);
		memcpy(destination,temp,(dword)(m_current-temp));
	}

	std::string MemBlock::getString(dword length, bool move)
	{
		std::string s;
		byte *temp = m_current;
		if(length>m_end-m_begin)
		{
			length = m_end-m_begin;
		}
		while(m_current<m_end)
		{
			if(*m_current == 0 || (length>0 && (dword)(m_current-temp)>=length))
			{
				s = std::string(temp, m_current);
				if(length>0)
				{
					m_current = temp + length;
				}
				else
				{
					m_current++;
				}
				return s;
			}
			m_current++;
		}
		return std::string(temp,m_end);
	}


	void MemBlock::setDword(dword value, bool move)
	{
		*((dword *)m_current) = value;
		operator+=(sizeof(dword));
	}

	void MemBlock::setSdword(sdword value, bool move)
	{
		*((sdword *)m_current) = value;
		operator+=(sizeof(sdword));
	}

	void MemBlock::setWord(word value, bool move)
	{
		*((word *)m_current) = value;
		operator+=(sizeof(word));
	}

	void MemBlock::setSword(sword value, bool move)
	{
		*((sword *)m_current) = value;
		operator+=(sizeof(sword));
	}

	void MemBlock::setByte(byte value, bool move)
	{
		*((byte *)m_current) = value;
		operator+=(sizeof(byte));
	}

	void MemBlock::setSbyte(sbyte value, bool move)
	{
		*((sbyte *)m_current) = value;
		operator+=(sizeof(sbyte));
	}

	void MemBlock::setFloat(float value, bool move)
	{
		*((float *)m_current) = value;
		operator+=(sizeof(float));
	}

	void MemBlock::setDouble(double value, bool move)
	{
		*((double *)m_current) = value;
		operator+=(sizeof(double));
	}

	void MemBlock::setBlock(byte *src, dword length, bool move)
	{
		byte *temp = m_current;
		operator+=(length);
		memcpy(temp,src,m_current-temp);
	}

	void MemBlock::setString(const std::string &value, bool include_terminator, dword length, bool pad, bool move)
	{
		byte *temp = m_current;
		dword stringlength = dword(value.size()) + (include_terminator?1:0);


		if(length > 0)
		{
			if(length < stringlength)
			{
				stringlength = length - (include_terminator?1:0);
			}
			operator+=(length);
		}
		else
		{
			operator+=(stringlength);
		}
		memcpy(temp,value.c_str(),stringlength);
		if(length > 0 && stringlength < length && pad)
		{
			temp += stringlength;
			for(dword i=0;i<length-stringlength;i++)
			{
				if(temp >= m_end)
				{
					return;
				}
				*(temp++) = 0;
			}
		}
	}


	std::ostream &operator<<(std::ostream &os, const MemBlock &src)
	{
		byte c;
		byte buf[81]={0};
		dword i,j;
		dword address;
		MemBlock mi(src);
		mi.seek(0);

		for(j = 0; j < (mi.size()+15) / 16; j++)
		{
			for(i = 0; i < 79; i++)
			{
				buf[i]=' ';
			}
			address = ((dword)mi.begin())+j*16;
			for(i=0;i<8;i++)
			{
				buf[i]=bytetohex(address>>((7-i)*4));
			}

			for(i = 0; i < 16; i++)
			{
				if(i + j * 16 >= mi.size())
				{
					break;
				}
				c = mi.getByte();
				buf[i * 3 + 9 + (i/4)] = bytetohex(c >> 4);
				buf[i * 3 + 10 + (i/4)] = bytetohex(c & 0x0f);

				if(c>=32 && c<=127)
				{
					buf[63 + i] = c;
				}
				else
				{
					buf[63 + i] = '.';
				}
			}
			os<<buf<<"\n";
		}
		return os;
	}
}
