#ifndef QGF2D_GAMEOBJECT_HEADER
#define QGF2D_GAMEOBJECT_HEADER
#include "kf/kf_vector2.h"
#include <SFML/Graphics.hpp>
#include "Box2D.h"

namespace qgf
{
	class GameObject
	{
	public:
		enum PhysicsStyle
		{
			e_psNone=0,
			e_psNewtonian,
			e_psBox2D
		};
		kf::Vector2 m_position;
		kf::Vector2 m_velocity;
		kf::Vector2 m_force;
		float m_rotation;
		float m_life;
		bool m_dead;
		long long m_id;
		PhysicsStyle m_physicsStyle;
		bool m_overlap;
		int m_type;
		bool m_collide;
		bool m_gravity;
		sf::Sprite *m_sprite;
		b2Body *m_body;
		GameObject();
		~GameObject();
		void update(float dt);
		void render(sf::RenderWindow *rw);
		GameObject &position(const kf::Vector2 &pos);
		GameObject &velocity(const kf::Vector2 &vel);
		kf::Vector2 position();
		kf::Vector2 velocity();
		GameObject &addForce(const kf::Vector2 &force);
		static GameObject *build();
	};

	typedef void (*CollisionCallback_t)(GameObject *obj1, GameObject *obj2);

	namespace GameWorld
	{
		kf::Vector2 gravity();
		void gravity(const kf::Vector2 &grav);
		long long newID();
		void update(float dt);
		void render(sf::RenderWindow *rw);
	}

	class ObjectTemplate
	{
	public:
		ObjectTemplate();
		std::string m_imageName;
		kf::Vector2T<int> m_corner1,m_corner2;
		kf::Vector2 m_centre;
		int m_type;
		float m_life;
		bool m_gravity;
		GameObject *(*m_buildFunc)();
	};

	class ObjectFactory
	{
	public:
		ObjectFactory();
		virtual ~ObjectFactory();
		std::map<std::string, ObjectTemplate> m_objectTemplates;
		std::map<std::string, sf::Image *> m_images;
		GameObject *addObject(const std::string name);
		sf::Image *getImage(const std::string &filename);
	};
	extern CollisionCallback_t CollisionCallback;
	extern ObjectFactory g_objectFactory;
}

#endif