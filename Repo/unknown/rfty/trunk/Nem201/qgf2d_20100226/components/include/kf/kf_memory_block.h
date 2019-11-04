#ifndef KF_MEMORY_BLOCK_HEADER
#define KF_MEMORY_BLOCK_HEADER

#include "kf/kf_types.h"

#include <ostream>

// to do: add search to memBlock

namespace kf
{
	class KF_API MemBlock
	{
	public:
		MemBlock();
		MemBlock(byte *start, qword length);
		~MemBlock();
		void setRange(byte *start, qword length);
		bool seek(sqword offset, bool relative = false);
		MemBlock &operator+=(sqword offset);
		MemBlock &operator-=(sqword offset);
		MemBlock &operator++();
		MemBlock &operator--();
		MemBlock operator()(int offset, bool relative = true);
		bool operator==(const MemBlock &rhs);
		MemBlock &operator=(const MemBlock &rhs);
		byte *begin() const;
		byte *end() const;
		byte *current() const;
		qword size() const;
		qword  MemBlock::getQword(bool move);
		sqword  MemBlock::getSqword(bool move);
		dword  getDword(bool move = true);
		dword  get24Bit(bool move = true);
		sdword getS24Bit(bool move = true);
		sdword getSdword(bool move = true);
		word   getWord(bool move = true);
		sword  getSword(bool move = true);
		byte   getByte(bool move = true);
		sbyte  getSbyte(bool move = true);
		float  getFloat(bool move = true);
		double getDouble(bool move = true);
		void getBlock(byte *destination, dword length, bool move = true);
		std::string getString(dword length=0, bool move = true);
		void setDword(dword value, bool move = true);
		void setSdword(sdword value, bool move = true);
		void setWord(word value, bool move = true);
		void setSword(sword value, bool move = true);
		void setByte(byte value, bool move = true);
		void setSbyte(sbyte value, bool move = true);
		void setFloat(float value, bool move = true);
		void setDouble(double value, bool move = true);
		void setBlock(byte *source, dword length, bool move = true);
		void setString(const std::string &value, bool include_terminator = true, dword length = 0, bool pad = false, bool move = true);

		/*
		MemBlock &operator<<(dword value);
		MemBlock &operator<<(sdword value);
		MemBlock &operator<<(word value);
		MemBlock &operator<<(sword value);
		MemBlock &operator<<(byte value);
		MemBlock &operator<<(sbyte value);
		MemBlock &operator<<(float value);
		MemBlock &operator<<(double value);
		MemBlock &operator<<(const std::string &value);
		*/

	protected:
		byte *m_begin;
		byte *m_end;
		byte *m_current;
	};

	KF_API std::ostream &operator<<(std::ostream &os, const MemBlock &src);
}

#endif
