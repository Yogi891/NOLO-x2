#ifndef QGF2D_ANIM_HEADER
#define QGF2D_ANIM_HEADER
#include "kf/kf_vector2.h"
#include <SFML/Graphics.hpp>

namespace qgf
{
	class AnimSequence
	{
	public:
		AnimSequence();
		AnimSequence(int start, int end, float length, bool looping);
		virtual ~AnimSequence();
		virtual AnimSequence &looping(bool l);
		virtual bool looping();
		std::string m_name;
		int m_start;
		int m_end;
		float m_length;
		bool m_looping;
	};

	class Anim
	{
	public:
		Anim(sf::Sprite *sprite, int startX, int startY, int frameWidth, int frameHeight, int columns, int rows);
		virtual ~Anim();
		virtual Anim &addSequence(const std::string &name, int frameStart, int frameEnd, float length, bool looping);
		virtual bool isPlaying() const;
		virtual Anim &frame(int f);
		virtual int frame() const;
		virtual Anim &update(float deltaT);
		virtual Anim &play(const std::string &name, bool restart);
		virtual AnimSequence *getSequence(const std::string &name);

	protected:
		sf::Sprite *m_sprite;
		bool m_playing;
		int m_startX, m_startY;
		int m_frameWidth, m_frameHeight;
		int m_columns, m_rows;
		int m_frame;
		float m_time;
		std::map<std::string, AnimSequence> m_sequences;
		std::map<std::string, AnimSequence>::iterator m_current;
	};
}
#endif
