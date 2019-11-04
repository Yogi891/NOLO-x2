#include "qgf2d/anim.h"
namespace qgf
{
	AnimSequence::AnimSequence()
	{
	}

	AnimSequence::AnimSequence(int start, int end, float length, bool looping):m_start(start), m_end(end), m_length(length), m_looping(looping)
	{
	}

	AnimSequence::~AnimSequence()
	{
	}

	AnimSequence &AnimSequence::looping(bool l)
	{
		m_looping = l;
		return *this;
	}

	bool AnimSequence::looping()
	{
		return m_looping;
	}


	Anim::Anim(sf::Sprite *sprite, int startX, int startY, int frameWidth, int frameHeight, int columns, int rows): m_sprite(sprite), m_startX(startX), m_startY(startY), m_frameWidth(frameWidth), m_frameHeight(frameHeight), m_columns(columns), m_rows(rows)
	{
		frame(0);
	}

	Anim::~Anim()
	{
	}

	Anim &Anim::addSequence(const std::string &name, int frameStart, int frameEnd, float length, bool looping)
	{
		AnimSequence as(frameStart, frameEnd, length, looping);
		m_sequences[name] = as;
		return *this;
	}

	bool Anim::isPlaying() const
	{
		return m_playing;
	}

	Anim &Anim::frame(int f)
	{
		m_frame = f;
		if(m_frame >= m_rows * m_columns)
			m_frame = m_rows * m_columns - 1;
		int c = m_frame % m_columns;
		int r = m_frame / m_columns;
		m_sprite->SetSubRect(sf::IntRect(m_startX + c * m_frameWidth, m_startY + r * m_frameHeight, m_startX + c * m_frameWidth + m_frameWidth - 1, m_startY + r * m_frameHeight + m_frameHeight - 1));
		return *this;
	}

	int Anim::frame() const
	{
		return m_frame;
	}

	Anim &Anim::update(float deltaT)
	{
		if(m_playing && m_current != m_sequences.end())
		{
			m_time += deltaT;
			if(m_time < 0)
			{
				if(m_current->second.m_looping)
				{
					m_time = fmod(m_time, m_current->second.m_length) + m_current->second.m_length;
				}
				else
				{
					m_time = 0;
					m_playing = false;
				}
			}
			else if(m_time > m_current->second.m_length)
			{
				if(m_current->second.m_looping)
				{
					m_time = fmod(m_time, m_current->second.m_length);
				}
				else
				{
					m_time = m_current->second.m_length;
					m_playing = false;
				}
			}
			frame(((m_current->second.m_end - m_current->second.m_start) / m_current->second.m_length) * m_time + m_current->second.m_start);
		}
		return *this;
	}

	Anim &Anim::play(const std::string &name, bool restart)
	{
		m_current = m_sequences.find(name);
		if(restart)
		{
			m_frame = 0;
			m_time = 0;
		}
		m_playing = true;
		return *this;
	}

	AnimSequence *Anim::getSequence(const std::string &name)
	{
		std::map<std::string, AnimSequence>::iterator it = m_sequences.find(name);
		if(it!=m_sequences.begin())
		{
			return &(it->second);
		}
		return 0;
	}


}